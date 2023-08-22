#ifndef OBJ_DATA_H_
#define OBJ_DATA_H_

#include <limits>
#include <string>
#include <vector>

namespace obj {

enum class Status : short int { noExc, invalidFile, noFile };

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
  float Ka[3]{};
  float Kd[3];
  float Ks[3]{};
  float Ke[3]{};
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
  std::vector<unsigned int> edges;

  std::vector<float> vn;
  std::vector<float> vt;
  std::vector<float> v;

  float max[3];
  float min[3];

  unsigned int facet_count{};
  unsigned int vertex_count{};

  std::string dir_path;
  Data();
  ~Data() = default;
  bool FromFile(const std::string& path);
  Status GetStatus() noexcept;

 protected:
  void Flush();
  void ReadFile(const std::string& path);
  void ParseBuffer(const char* ptr, const char* end);
  const char* ParseMtl(const char* ptr);
  const char* ParseUsemtl(const char* ptr);
  const char* ParseFacet(const char* ptr);
  const char* ParseVertex(const char* ptr, std::vector<float>& vertices);
  void ProcessPolygon(const std::vector<Index>& raw_ind, unsigned int npolys);
  static constexpr unsigned int bufferSize = 65536;

 private:
  Status m_stat{};
};

inline NewMtl::NewMtl()
    : Ns(32.0f), d(1.0f), Kd{0.7f, 0.7f, 0.7f} {}

inline Data::Data()
    : max{std::numeric_limits<float>::min(), std::numeric_limits<float>::min(),
          std::numeric_limits<float>::min()},
      min{std::numeric_limits<float>::max(), std::numeric_limits<float>::max(),
          std::numeric_limits<float>::max()} {}

inline Status Data::GetStatus() noexcept { return m_stat; }

}  // namespace Obj

#endif  // OBJ_DATA_H_
