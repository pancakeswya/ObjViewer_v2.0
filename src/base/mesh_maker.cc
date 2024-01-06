#include "base/mesh_maker.h"

#include <future>
#include <map>
#include <set>

#include "base/data_parser.h"

namespace objv::MeshMaker {

namespace {

struct compare {
  bool operator()(const Index& lhs, const Index& rhs) const noexcept {
    if (lhs.fv < rhs.fv) return true;
    if (rhs.fv < lhs.fv) return false;
    if (lhs.fn < rhs.fn) return true;
    if (rhs.fn < lhs.fn) return false;
    if (lhs.ft < rhs.ft) return true;
    return rhs.ft < lhs.ft;
  }
};

using IndexMap = std::map<Index, unsigned int, compare>;

std::vector<unsigned int> SetUniqueEdges(
    const std::vector<unsigned int>& edges) {
  std::vector<unsigned int> unique_edges;
  std::set<std::pair<unsigned int, unsigned int>> edges_set;
  for (size_t i = 0; i < edges.size(); i += 2) {
    std::pair<unsigned int, unsigned int> edge;
    if (edges[i] > edges[i + 1]) {
      edge = {edges[i], edges[i + 1]};
    } else {
      edge = {edges[i + 1], edges[i]};
    }
    edges_set.insert(std::move(edge));
  }
  unique_edges.reserve(edges_set.size());
  for (auto& [start, finish] : edges_set) {
    unique_edges.emplace_back(start);
    unique_edges.emplace_back(finish);
  }
  return unique_edges;
}

void DataToMesh(Data* data, Mesh* mesh) {
  IndexMap index_map;

  mesh->has_textures = !data->vt.empty();
  mesh->has_normals = !data->vn.empty();

  mesh->facet_count = data->facet_count;
  mesh->vertex_count = data->vertex_count;

  std::move(data->max, data->max + 3, mesh->max_vertex);
  std::move(data->min, data->min + 3, mesh->min_vertex);

  auto future = std::async(std::launch::async, &SetUniqueEdges, data->edges);
  mesh->edges = future.get();

  // if mesh not made up by lines
  if (data->indices.size() != 2 * mesh->facet_count) {
    mesh->vertices.reserve(data->indices.size());
    mesh->indices.reserve(data->indices.size());

    mesh->usemtl = std::move(data->usemtl);
    mesh->mtl = std::move(data->mtl);
    // create vertex for each unique index
    unsigned int next_combined_idx = 0, combined_idx = 0;
    for (const Index& idx : data->indices) {
      if (index_map.count(idx)) {
        combined_idx = index_map.at(idx);
      } else {
        combined_idx = next_combined_idx;
        index_map.insert({idx, combined_idx});
        unsigned int i_v = idx.fv * 3, i_n = idx.fn * 3, i_t = idx.ft * 2;
        mesh->vertices.push_back(data->v[i_v]);
        mesh->vertices.push_back(data->v[i_v + 1]);
        mesh->vertices.push_back(data->v[i_v + 2]);
        if (mesh->has_textures) {
          mesh->vertices.push_back(data->vt[i_t]);
          mesh->vertices.push_back(data->vt[i_t + 1]);
        }
        if (mesh->has_normals) {
          mesh->vertices.push_back(data->vn[i_n]);
          mesh->vertices.push_back(data->vn[i_n + 1]);
          mesh->vertices.push_back(data->vn[i_n + 2]);
        }
        ++next_combined_idx;
      }
      mesh->indices.push_back(combined_idx);
    }
  }
  mesh->tex_coords = std::move(data->vt);
  mesh->uv = std::move(data->uv);
  mesh->points = std::move(data->v);
}

}  // namespace

std::pair<Mesh*, Status> MakeFromFile(std::string_view path) {
  auto mesh = new Mesh;
  auto [data, stat] = DataParser::ParseFromFile(path);
  if (stat == Status::kNoExc) {
    DataToMesh(data, mesh);
  }
  delete data;
  return {mesh, stat};
}

}  // namespace objv::MeshMaker
