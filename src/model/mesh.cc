#include "mesh.h"

#include <QImage>
#include <cstring>
#include <future>
#include <iostream>
#include <map>
#include <set>
#include <thread>

namespace obj {

namespace {

enum MapType { kAmbient, kDiffuse, kSpecular };

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

using Edge = std::pair<unsigned int, unsigned int>;

void SetTexture(Map& map, std::string path) {
  map.texture.destroy();
  QImage tex_image;
  if (!path.empty()) {
    tex_image.load(path.data());
  }
  if (tex_image.isNull()) {
    // make it default color texture
    QImage image(1, 1, QImage::Format_RGB32);
    image.fill(QColor::fromRgbF(0.7f, 0.7f, 0.7f));
    tex_image = std::move(image);
  }
  map.texture.setData(tex_image.mirrored());
  map.texture.setMinificationFilter(QOpenGLTexture::Nearest);
  map.texture.setMagnificationFilter(QOpenGLTexture::Linear);
  map.texture.setWrapMode(QOpenGLTexture::Repeat);
  map.path = std::move(path);
}

std::vector<unsigned int> GetUniqueEdges(
    const std::vector<unsigned int>& edges) {
  std::vector<unsigned int> unique_edges;
  std::set<Edge> edges_set;
  for (size_t i = 0; i < edges.size(); i += 2) {
    Edge edge;
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

}  // namespace

void Mesh::ResetTexture(std::string_view path, unsigned int index_mtl,
                        unsigned int map_type) {
  if (map_type == MapType::kAmbient) {
    SetTexture(mtl[index_mtl].map_ka, path.data());
  } else if (map_type == MapType::kDiffuse) {
    SetTexture(mtl[index_mtl].map_kd, path.data());
  } else if (map_type == MapType::kSpecular) {
    SetTexture(mtl[index_mtl].map_ks, path.data());
  }
}

Status Mesh::Open(std::string_view path) {
  Clear();
  auto data = new Data();
  auto stat = Status::noExc;
  if (data->FromFile(path)) {
    DataToObj(*data);
  } else {
    stat = data->GetStatus();
  }
  delete data;
  return stat;
}

void Mesh::DataToObj(Data& data) {
  IndexMap index_map;

  has_textures = !data.vt.empty();
  has_normals = !data.vn.empty();

  facet_count = data.facet_count;
  vertex_count = data.vertex_count;
  material_count = data.mtl.size();

  std::move(data.max, data.max + 3, max_vertex);
  std::move(data.min, data.min + 3, min_vertex);
  auto future = std::async(std::launch::async, &GetUniqueEdges, data.edges);
  edges = future.get();

  // if mesh not made up by lines
  if (data.indices.size() != 2 * facet_count) {
    vertices.reserve(data.indices.size());
    indices.reserve(data.indices.size());

    usemtl = std::move(data.usemtl);

    // prepare material for renderer
    mtl = new Material[data.mtl.size()];

    for (size_t i = 0; i < data.mtl.size() || i == 0; ++i) {
      mtl[i].name = std::move(data.mtl[i].name);
      SetTexture(mtl[i].map_ka, std::move(data.mtl[i].map_ka));
      SetTexture(mtl[i].map_kd, std::move(data.mtl[i].map_kd));
      SetTexture(mtl[i].map_ks, std::move(data.mtl[i].map_ks));
      std::memcpy(&mtl[i].Ns, &data.mtl[i].Ns, 14 * sizeof(float));
    }
    // create vertex for each unique index
    unsigned int next_combined_idx = 0, combined_idx = 0;
    for (auto& idx : data.indices) {
      if (index_map.count(idx)) {
        combined_idx = index_map.at(idx);
      } else {
        combined_idx = next_combined_idx;
        index_map.insert(std::make_pair(idx, combined_idx));
        unsigned int i_v = idx.fv * 3, i_n = idx.fn * 3, i_t = idx.ft * 2;
        vertices.push_back(data.v[i_v]);
        vertices.push_back(data.v[i_v + 1]);
        vertices.push_back(data.v[i_v + 2]);
        if (has_textures) {
          vertices.push_back(data.vt[i_t]);
          vertices.push_back(data.vt[i_t + 1]);
        }
        if (has_normals) {
          vertices.push_back(data.vn[i_n]);
          vertices.push_back(data.vn[i_n + 1]);
          vertices.push_back(data.vn[i_n + 2]);
        }
        ++next_combined_idx;
      }
      indices.push_back(combined_idx);
    }
  }
  if (has_normals && has_textures) {
    stride = 8 * sizeof(float);
  } else if (!has_normals) {
    stride = 5 * sizeof(float);
  } else if (has_normals) {
    stride = 6 * sizeof(float);
  }
  tex_coords = std::move(data.vt);
  uv = std::move(data.uv);
  points = std::move(data.v);
}

void Mesh::Clear() {
  facet_count = vertex_count = 0;
  max_vertex[0] = min_vertex[0] = 0.0f;
  max_vertex[1] = min_vertex[1] = 0.0f;
  max_vertex[2] = min_vertex[2] = 0.0f;
  std::vector<unsigned int>().swap(indices);
  std::vector<unsigned int>().swap(edges);
  std::vector<unsigned int>().swap(uv);
  std::vector<float>().swap(tex_coords);
  std::vector<float>().swap(vertices);
  std::vector<float>().swap(points);
  std::vector<UseMtl>().swap(usemtl);
  delete[] mtl;
  mtl = nullptr;
}

}  // namespace obj
