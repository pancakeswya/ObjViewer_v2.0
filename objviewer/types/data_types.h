#ifndef OBJVIEWER_TYPES_DATA_TYPES_H_
#define OBJVIEWER_TYPES_DATA_TYPES_H_

#include <string>
#include <vector>

namespace objv {

enum class Status : short int { kNoExc, kInvalidFile, kNoFile };

struct NewMtl {
  std::string name;
  std::string map_ka;
  std::string map_kd;
  std::string map_ks;
  float Ns;
  float d;
  float Ka[3]{};
  float Kd[3];
  float Ks[3]{};
  float Ke[3]{};
  NewMtl();
  ~NewMtl() = default;
};

struct UseMtl {
  unsigned int index;
  unsigned int offset_fv;
  unsigned int offset_uv;
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
  std::vector<NewMtl> mtl;
};

inline NewMtl::NewMtl() : Ns(32.0f), d(1.0f), Kd{0.7f, 0.7f, 0.7f} {}

}  // namespace objv

#endif  // OBJVIEWER_TYPES_DATA_TYPES_H_