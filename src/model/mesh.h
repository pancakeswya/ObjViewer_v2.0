#ifndef OBJVIEWER_V2_SRC_MODEL_MESH_H_
#define OBJVIEWER_V2_SRC_MODEL_MESH_H_

#include <QOpenGLTexture>

#include "data.h"

namespace obj {

struct Map {
  std::string path;
  QOpenGLTexture texture;
  Map();
  ~Map() = default;
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
                    unsigned int map_type);
  void Clear();

 protected:
  // convert data to prepared mesh
  void DataToObj(Data& obj_data);
};

inline Map::Map() : texture(QOpenGLTexture::Target2D) {}

inline Mesh::~Mesh() { delete[] mtl; }

}  // namespace obj

#endif  // OBJVIEWER_V2_SRC_MODEL_MESH_H_
