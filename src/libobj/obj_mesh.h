#ifndef OBJ_MESH_H_
#define OBJ_MESH_H_

#include <QOpenGLTexture>

#include "obj_data.h"

namespace Obj {

struct Material {
  QOpenGLTexture map_kd;
  QOpenGLTexture map_Ns;
  QOpenGLTexture map_bump;
  long int illum{};
  float Ns{};
  float Ni{};
  float d{};
  float Ka[3]{};
  float Kd[3]{};
  float Ks[3]{};
  float Ke[3]{};

  Material();
  ~Material() = default;
};

struct Mesh {
  unsigned int facet_count{};
  unsigned int vertex_count{};

  float max_vertex[3]{};
  float min_vertex[3]{};

  std::vector<unsigned int> indices;
  std::vector<unsigned int> indicesw;
  std::vector<float> vertices;
  std::vector<float> verticesw;
  std::vector<UseMtl> usemtl;
  Material *mtl{};

  Mesh() = default;
  ~Mesh();

  Status Open(const std::string &path);
  bool HasTextures()
  noexcept;
  bool HasNormals()
  noexcept;
  unsigned int GetStride() const
  noexcept;
  void Destroy();

 protected:
  // convert data to prepared mesh
  void DataToObj(Data *obj_data);

 private:
  bool m_has_textures{};
  bool m_has_normals{};
};

inline Material::Material()
    : map_kd(QOpenGLTexture::Target2D),
      map_Ns(QOpenGLTexture::Target2D),
      map_bump(QOpenGLTexture::Target2D) {}

inline Mesh::~Mesh() { delete[] mtl; }

inline bool Mesh::HasNormals() noexcept {
  return m_has_normals;
}

inline bool Mesh::HasTextures() noexcept {
  return m_has_textures;
}

inline unsigned int Mesh::GetStride() const noexcept {
  if (m_has_normals && m_has_textures) {
    return 8 * sizeof(float);
  } else if (!m_has_normals) {
    return 5 * sizeof(float);
  } else if (m_has_normals) {
    return 6 * sizeof(float);
  } else {
    return 0 * sizeof(float);
  }
}

inline Status Mesh::Open(const std::string &path) {
  auto data = new Data();
  auto stat = Status::noExc;
  if (data->FromFile(path)) {
    DataToObj(data);
  } else {
    stat = data->GetStatus();
  }
  delete data;
  return stat;
}

inline void Mesh::Destroy() {
  facet_count = vertex_count = 0;
  max_vertex[0] = min_vertex[0] = 0.0f;
  max_vertex[1] = min_vertex[1] = 0.0f;
  max_vertex[2] = min_vertex[2] = 0.0f;
  std::vector<unsigned int>().swap(indices);
  std::vector<float>().swap(vertices);
  std::vector<unsigned int>().swap(indicesw);
  std::vector<float>().swap(verticesw);
  std::vector<UseMtl>().swap(usemtl);
  delete[] mtl;
  mtl = nullptr;
}

} // namespace Obj

#endif // OBJ_MESH_H_
