#include "obj_mesh.h"

#include <QImage>
#include <cstring>
#include <map>
#include <utility>

namespace Obj {

namespace {

struct compare {
  bool operator()(const Index& lhs, const Index& rhs) const noexcept {
    if (lhs.f < rhs.f) return true;
    if (rhs.f < lhs.f) return false;
    if (lhs.n < rhs.n) return true;
    if (rhs.n < lhs.n) return false;
    if (lhs.t < rhs.t) return true;
    return rhs.t < lhs.t;
  }
};

using IndexMap = std::map<Index, unsigned int, compare>;

void SetTexture(QOpenGLTexture& texture, const std::string& path) {
  if (!path.empty()) {
    QImage tex_image(path.c_str());
    if (!tex_image.isNull()) {
      texture.setData(tex_image.mirrored());
      texture.setMinificationFilter(QOpenGLTexture::Nearest);
      texture.setMagnificationFilter(QOpenGLTexture::Linear);
      texture.setWrapMode(QOpenGLTexture::Repeat);
    }
  }
}

}  // namespace

void Mesh::DataToObj(Data& data) {
  IndexMap index_map;

  m_has_textures = (data.t.size() != 0);
  m_has_normals = (data.n.size() != 0);

  facet_count = data.facet_count;
  vertex_count = data.vertex_count;

  std::move(data.max, data.max + 3, max_vertex);
  std::move(data.min, data.min + 3, min_vertex);

  // if mesh not made up by lines
  if (data.indices.size() != 2 * facet_count) {
    vertices.reserve(data.indices.size());
    indices.reserve(data.indices.size());

    usemtl = std::move(data.usemtl);

    // prepare material for renderer
    mtl = new Material[data.mtl.size()];

    for (size_t i = 0; i < data.mtl.size() || i == 0; ++i) {
      SetTexture(mtl[i].map_Ns, data.mtl[i].map_Ns);
      SetTexture(mtl[i].map_kd, data.mtl[i].map_kd);
      SetTexture(mtl[i].map_bump, data.mtl[i].map_bump);
      std::memcpy(&mtl[i].illum, &data.mtl[i].illum,
                  sizeof(long int) + 15 * sizeof(float));
    }
    // optimizing indices by connecting combined idx
    unsigned int next_combined_idx = 0, combined_idx = 0;
    for (auto &idx : data.indices) {
      if (index_map.count(idx)) {
        combined_idx = index_map.at(idx);
      } else {
        combined_idx = next_combined_idx;
        index_map.insert(std::make_pair(idx, combined_idx));
        unsigned int i_v = idx.f * 3, i_n = idx.n * 3, i_t = idx.t * 2;
        vertices.push_back(data.v[i_v]);
        vertices.push_back(data.v[i_v + 1]);
        vertices.push_back(data.v[i_v + 2]);
        if (m_has_textures) {
          vertices.push_back(data.t[i_t]);
          vertices.push_back(data.t[i_t + 1]);
        }
        if (m_has_normals) {
          vertices.push_back(data.n[i_n]);
          vertices.push_back(data.n[i_n + 1]);
          vertices.push_back(data.n[i_n + 2]);
        }
        ++next_combined_idx;
      }
      indices.push_back(combined_idx);
    }
  }

  indicesw = std::move(data.w_indices);
  verticesw = std::move(data.v);
}

}  // namespace Obj
