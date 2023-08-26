#ifndef OBJVIEWER_V2_SRC_MODEL_MESH_H_
#define OBJVIEWER_V2_SRC_MODEL_MESH_H_

#include "data.h"

namespace obj {

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
  std::vector<NewMtl> mtl;

  Status Open(std::string_view path);
  void ResetTexture(std::string_view path, unsigned int index_mtl,
                    unsigned int map_type);
  void Clear();

 protected:
  // convert data to prepared mesh
  void DataToObj(Data& obj_data);
};


}  // namespace obj

#endif  // OBJVIEWER_V2_SRC_MODEL_MESH_H_
