#ifndef OBJ_MESH_H_
#define OBJ_MESH_H_

#include <QOpenGLTexture>

#include "obj_data.h"

namespace obj {

struct Map {
  std::string path;
  QOpenGLTexture texture;
  Map() : texture(QOpenGLTexture::Target2D) {}
};

struct Material {
  std::string name;
  float Ns{};
  float d{};
  float Ka[3]{};
  float Kd[3]{};
  float Ks[3]{};
  float Ke[3]{};
  Map map_ka;
  Map map_kd;
  Map map_ks;
};

struct Mesh {
  bool has_textures{};
  bool has_normals{};

  unsigned int facet_count{};
  unsigned int vertex_count{};
  unsigned int material_count{};
  unsigned int stride{};

  float max_vertex[3]{};
  float min_vertex[3]{};

  std::vector<unsigned int> indices;
  std::vector<unsigned int> edges;
  std::vector<unsigned int> uv;

  std::vector<float> tex_coords;
  std::vector<float> vertices;
  std::vector<float> points;

  std::vector<UseMtl> usemtl;
  Material* mtl{};

  Mesh() = default;
  ~Mesh();

  Status Open(std::string_view path);
  void ResetTexture(std::string_view path, unsigned int index_mtl,
                    unsigned int index_map);
  void Clear();

 protected:
  // convert data to prepared mesh
  void DataToObj(Data& obj_data);
};

inline Mesh::~Mesh() { delete[] mtl; }

inline Status Mesh::Open(std::string_view path) {
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

inline void Mesh::Clear() {
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

#endif  // OBJ_MESH_H_
