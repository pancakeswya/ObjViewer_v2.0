#ifndef OBJ_DATA_H_
#define OBJ_DATA_H_

#include <limits>
#include <string>
#include <vector>

namespace Obj {

enum class Status : short int {
  noExc,
  invalidFile,
  noFile
};

struct Index {
  unsigned int f;
  unsigned int n;
  unsigned int t;
};

struct NewMtl {
  std::string name;
  std::string map_kd;
  std::string map_Ns;
  std::string map_bump;
  long int illum;
  float Ns;
  float Ni;
  float d;
  float Ka[3];
  float Kd[3];
  float Ks[3];
  float Ke[3];
  NewMtl();
  ~NewMtl() = default;
};

struct UseMtl {
  unsigned int index;
  unsigned int offset;
};

struct Data {
  std::vector<NewMtl> mtl;
  std::vector<UseMtl> usemtl;

  std::vector<Index> indices;
  std::vector<unsigned int> w_indices;

  std::vector<float> n;
  std::vector<float> t;
  std::vector<float> v;

  float max[3];
  float min[3];

  unsigned int facet_count;
  unsigned int vertex_count;

  std::string dir_path;
  Data();
  ~Data() = default;
  bool FromFile(const std::string &path);
  Status GetStatus() noexcept;

 protected:
  void Flush();
  void ReadFile(const std::string &path);
  void ParseBuffer(const char *ptr, const char *end);
  const char *ParseMtl(const char *ptr);
  const char *ParseUsemtl(const char *ptr);
  const char *ParseFacet(const char *ptr);
  const char *ParseVertex(const char *ptr, std::vector<float> &vertices);
  static constexpr unsigned int bufferSize = 65536;

 private:
  Status m_stat{};
};

inline NewMtl::NewMtl()
    : illum(1), Ns(32.0f), Ni(1.0f), d(1.0f), Kd{0.7f, 0.7f, 0.7f} {}

inline Data::Data()
    : max{std::numeric_limits<float>::min(), std::numeric_limits<float>::min(),
          std::numeric_limits<float>::min()},
      min{std::numeric_limits<float>::max(), std::numeric_limits<float>::max(),
          std::numeric_limits<float>::max()} {}

inline Status Data::GetStatus() noexcept {
  return m_stat;
}

}

#endif // OBJ_DATA_H_
