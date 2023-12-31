#ifndef SRC_BASE_DATA_TYPES_H_
#define SRC_BASE_DATA_TYPES_H_

#include <string>
#include <vector>

namespace objv {

enum class Status : short int { kNoExc, kInvalidFile, kNoFile };

struct Index {
  unsigned int fv;
  unsigned int fn;
  unsigned int ft;
};

struct NewMtl {
  std::string name;
  std::string map_ka;
  std::string map_kd;
  std::string map_ks;
  float Ns;
  float d;
  float Ka[3];
  float Kd[3];
  float Ks[3];
  float Ke[3];
};

struct UseMtl {
  unsigned int index;
  unsigned int offset_fv;
  unsigned int offset_uv;
};

struct Data {
  unsigned int facet_count{};
  unsigned int vertex_count{};

  std::string dir_path;

  float max[3];
  float min[3];

  std::vector<unsigned int> edges;
  std::vector<unsigned int> uv;

  std::vector<float> vn;
  std::vector<float> vt;
  std::vector<float> v;

  std::vector<Index> indices;
  std::vector<UseMtl> usemtl;
  std::vector<NewMtl> mtl;
};

struct Mesh {
  bool has_textures{};
  bool has_normals{};

  unsigned int facet_count{};
  unsigned int vertex_count{};

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

}  // namespace objv

#endif  // SRC_BASE_DATA_TYPES_H_
