#include "obj_data.h"

#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <map>
#include <iostream>

#include "earcut.h"

namespace Obj {

namespace {

inline bool IsSpace(char c) noexcept {
  return (c == ' ') || (c == '\t') || (c == '\r');
}

inline bool IsDigit(char c) noexcept { return (c >= '0') && (c <= '9'); }

inline bool IsEndOfName(char c) noexcept {
  return (c == '\t') || (c == '\r') || (c == '\n');
}

const char* SkipSpace(const char* ptr) noexcept {
  for (; IsSpace(*ptr); ++ptr)
    ;
  return ptr;
}

const char* SkipLine(const char* ptr) noexcept {
  for (; *ptr != '\n'; ++ptr)
    ;
  return ++ptr;
}

unsigned long int FileSize(std::ifstream& file) noexcept {
  long int p, n;
  p = file.tellg();
  file.seekg(0, std::ifstream::end);
  n = file.tellg();
  file.seekg(p, std::ifstream::beg);
  if (n > 0) {
    return static_cast<unsigned int>(n);
  } else {
    return 0;
  }
}

std::string GetName(const char** ptr) noexcept {
  const char* p = *ptr;
  p = SkipSpace(p);
  std::string name;
  for (; !IsEndOfName(*p); ++p) {
    name += *p;
  }
  *ptr = p;
  return name;
}

inline const char* ReadMtlSingle(const char* ptr, float& mtl) noexcept {
  char* end = nullptr;
  mtl = std::strtof(ptr, &end);
  return end;
}

inline const char* ReadMtlTriple(const char* ptr, float triple[3]) noexcept {
  ptr = ReadMtlSingle(ptr, triple[0]);
  ptr = ReadMtlSingle(ptr, triple[1]);
  ptr = ReadMtlSingle(ptr, triple[2]);

  return ptr;
}

struct Point3D {
  float x, y, z;
};

inline float GetLength(const Point3D& e) {
  return std::sqrt(e.x * e.x + e.y * e.y + e.z * e.z);
}

inline Point3D Cross(const Point3D& v1, const Point3D& v2) {
  return {v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
          v1.x * v2.y - v1.y * v2.x};
}

inline Point3D Normalize(const Point3D& e) {
  float inv_length = 1.0f / GetLength(e);
  return {e.x * inv_length, e.y * inv_length, e.z * inv_length};
}

inline float Dot(const Point3D& v1, const Point3D& v2) {
  return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

inline Point3D WorldToLocal(const Point3D& a, const Point3D& u,
                            const Point3D& v, const Point3D& w) {
  return {Dot(a, u), Dot(a, v), Dot(a, w)};
}

}  // namespace

void Data::ProcessPolygon(const std::vector<Index>& raw_ind,
                          unsigned int npolys) {
  // quad to 2 triangles
  if (npolys == 4) {
    size_t vi0 = size_t(raw_ind[0].fv);
    size_t vi1 = size_t(raw_ind[1].fv);
    size_t vi2 = size_t(raw_ind[2].fv);
    size_t vi3 = size_t(raw_ind[3].fv);

    if (((3 * vi0 + 2) >= v.size()) || ((3 * vi1 + 2) >= v.size()) ||
        ((3 * vi2 + 2) >= v.size()) || ((3 * vi3 + 2) >= v.size())) {
      m_stat = Status::invalidFile;
      return;
    }
    float v0x = v[vi0 * 3 + 0];
    float v0y = v[vi0 * 3 + 1];
    float v0z = v[vi0 * 3 + 2];
    float v1x = v[vi1 * 3 + 0];
    float v1y = v[vi1 * 3 + 1];
    float v1z = v[vi1 * 3 + 2];
    float v2x = v[vi2 * 3 + 0];
    float v2y = v[vi2 * 3 + 1];
    float v2z = v[vi2 * 3 + 2];
    float v3x = v[vi3 * 3 + 0];
    float v3y = v[vi3 * 3 + 1];
    float v3z = v[vi3 * 3 + 2];

    float e02x = v2x - v0x;
    float e02y = v2y - v0y;
    float e02z = v2z - v0z;
    float e13x = v3x - v1x;
    float e13y = v3y - v1y;
    float e13z = v3z - v1z;

    float sqr02 = e02x * e02x + e02y * e02y + e02z * e02z;
    float sqr13 = e13x * e13x + e13y * e13y + e13z * e13z;
    // find nearest edge
    if (sqr02 < sqr13) {
      indices.push_back(raw_ind[0]);
      indices.push_back(raw_ind[1]);
      indices.push_back(raw_ind[2]);
      indices.push_back(raw_ind[0]);
      indices.push_back(raw_ind[2]);
      indices.push_back(raw_ind[3]);
    } else {
      indices.push_back(raw_ind[0]);
      indices.push_back(raw_ind[1]);
      indices.push_back(raw_ind[3]);
      indices.push_back(raw_ind[1]);
      indices.push_back(raw_ind[2]);
      indices.push_back(raw_ind[3]);
    }
    // triangulate polygon with earcut method
  } else if (npolys > 4) {
    Index i0, i0_2;
    // Find the normal axis of the polygon using Newell's method
    Point3D n1{};
    for (size_t k = 0; k < npolys; ++k) {
      i0 = raw_ind[k % npolys];
      size_t vi0 = size_t(i0.fv);

      size_t j = (k + 1) % npolys;
      i0_2 = raw_ind[j];
      size_t vi0_2 = size_t(i0_2.fv);

      float v0x = v[vi0 * 3 + 0];
      float v0y = v[vi0 * 3 + 1];
      float v0z = v[vi0 * 3 + 2];

      float v0x_2 = v[vi0_2 * 3 + 0];
      float v0y_2 = v[vi0_2 * 3 + 1];
      float v0z_2 = v[vi0_2 * 3 + 2];

      const Point3D point1 = {v0x, v0y, v0z};
      const Point3D point2 = {v0x_2, v0y_2, v0z_2};

      Point3D a = {point1.x - point2.x, point1.y - point2.y,
                   point1.z - point2.z};
      Point3D b = {point1.x + point2.x, point1.y + point2.y,
                   point1.z + point2.z};

      n1.x += (a.y * b.z);
      n1.y += (a.z * b.x);
      n1.z += (a.x * b.y);
    }
    float length_n = GetLength(n1);
    // Check if zero length normal
    if (length_n <= 0) {
      m_stat = Status::invalidFile;
      return;
    }
    // Negative is to flip the normal to the correct direction
    float inv_length = -1.0f / length_n;
    n1.x *= inv_length;
    n1.y *= inv_length;
    n1.z *= inv_length;

    Point3D axis_w, axis_v, axis_u;
    axis_w = n1;
    Point3D a;
    if (std::abs(axis_w.x) > 0.9999999f) {
      a = {0.0f, 1.0f, 0.0f};
    } else {
      a = {1.0f, 0.0f, 0.0f};
    }
    axis_v = Normalize(Cross(axis_w, a));
    axis_u = Cross(axis_w, axis_v);
    using Point2D = std::pair<float, float>;

    // first polyline define the main polygon
    std::vector<std::vector<Point2D>> polygon;

    std::vector<Point2D> polyline;

    // Find best normal and project v0x and v0y to those coordinates, instead of
    // picking a plane aligned with an axis (which can flip polygons).

    // Fill polygon data(facevarying vertices).
    for (size_t k = 0; k < npolys; k++) {
      i0 = raw_ind[k];
      size_t vi0 = size_t(i0.fv);
      if (3 * vi0 + 2 >= v.size()) {
        m_stat = Status::invalidFile;
        return;
      }

      float v0x = v[vi0 * 3 + 0];
      float v0y = v[vi0 * 3 + 1];
      float v0z = v[vi0 * 3 + 2];

      Point3D polypoint = {v0x, v0y, v0z};
      Point3D loc = WorldToLocal(polypoint, axis_u, axis_v, axis_w);

      polyline.emplace_back(std::make_pair(loc.x, loc.y));
    }
    polygon.push_back(polyline);
    std::vector<unsigned int> order = mapbox::earcut(polygon);
    if (order.size() % 3 != 0) {
      m_stat = Status::invalidFile;
      return;
    }
    for (auto& i : order) {
      indices.push_back(raw_ind[i]);
    }
  } else {
    // polygon is a triangle just move it in
    std::move(raw_ind.begin(), raw_ind.end(), std::back_inserter(indices));
  }
}

const char* Data::ParseVertex(const char* ptr, std::vector<float>& array) {
  float vert;
  char* end = nullptr;
  char type = *ptr++;
  // texture has 2d coords everything else 3
  int vert_max = (type == 't') ? 2 : 3;
  for (int i = 0; i < vert_max; ++i) {
    vert = std::strtof(ptr, &end);
    if (end == ptr) {
      m_stat = Status::invalidFile;
      break;
    }
    // if it is a position get max
    // min value by axis
    if (type == ' ') {
      max[i] = std::max(vert, max[i]);
      min[i] = std::min(vert, min[i]);
    }
    array.push_back(vert);
    ptr = SkipSpace(end);
  }
  return ptr;
}

const char* Data::ParseFacet(const char* ptr) {
  char* end = nullptr;
  long int tmp_i;
  unsigned int start_i = w_indices.size();
  std::vector<Index> raw_ind;
  size_t npolys = 0;
  while (*ptr != '\n') {
    Index idx = {};
    tmp_i = std::strtol(ptr, &end, 10);
    if (tmp_i < 0) {
      idx.fv = v.size() / 3 - static_cast<unsigned int>(-tmp_i);
    } else if (tmp_i > 0) {
      idx.fv = static_cast<unsigned int>(tmp_i) - 1;
    }
    if (end == ptr) {
      m_stat = Status::invalidFile;
      break;
    }
    ptr = end;
    if (*ptr == '/') {
      ++ptr;
      if (IsDigit(*ptr)) {
        tmp_i = std::strtol(ptr, &end, 10);
        if (tmp_i < 0) {
          idx.ft = vt.size() / 2 - static_cast<unsigned int>(-tmp_i);
        } else if (tmp_i > 0) {
          idx.ft = static_cast<unsigned int>(tmp_i) - 1;
        }
        if (end == ptr) {
          m_stat = Status::invalidFile;
          break;
        }
        ptr = end;
      }
    }
    if (*ptr == '/') {
      tmp_i = std::strtol(++ptr, &end, 10);
      if (tmp_i < 0) {
        idx.fn = vn.size() / 3 - static_cast<unsigned int>(-tmp_i);
      } else if (tmp_i > 0) {
        idx.fn = static_cast<unsigned int>(tmp_i) - 1;
      }
      if (end == ptr) {
        m_stat = Status::invalidFile;
        break;
      }
      ptr = end;
    }
    // wireframe facets
    if (w_indices.size() != start_i) {
      w_indices.push_back(idx.fv);
    }
    w_indices.push_back(idx.fv);
    // push parsed indices
    raw_ind.push_back(idx);
    ptr = SkipSpace(ptr);
    ++npolys;
  }
  w_indices.push_back(w_indices[start_i]);
  ProcessPolygon(raw_ind, npolys);
  return ptr;
}

const char* Data::ParseMtl(const char* p) {
  std::string path_mtl = GetName(&p);
  std::ifstream mtl_file(dir_path + path_mtl, std::ifstream::binary);
  if (mtl_file.is_open()) {
    NewMtl new_mtl;
    bool found_d = false;

    unsigned long int bytes = FileSize(mtl_file);
    char* buf = new char[bytes + 1];
    unsigned int read = mtl_file.readsome(buf, bytes);
    buf[read] = '\0';

    const char* ptr = buf;
    const char* eof = buf + read;

    while (ptr < eof) {
      ptr = SkipSpace(ptr);
      switch (*ptr) {
        case 'n':
          ptr++;
          if (ptr[0] == 'e' && ptr[1] == 'w' && ptr[2] == 'm' &&
              ptr[3] == 't' && ptr[4] == 'l' && IsSpace(ptr[5])) {
            if (!new_mtl.name.empty()) {
              mtl.push_back(std::move(new_mtl));
              new_mtl = {};
            }
            ptr += 5;
            new_mtl.name = GetName(&ptr);
          }
          break;
        case 'K':
          if (ptr[1] == 'a') {
            ptr = ReadMtlTriple(ptr + 2, new_mtl.Ka);
          } else if (ptr[1] == 'd') {
            ptr = ReadMtlTriple(ptr + 2, new_mtl.Kd);
          } else if (ptr[1] == 's') {
            ptr = ReadMtlTriple(ptr + 2, new_mtl.Ks);
          } else if (ptr[1] == 'e') {
            ptr = ReadMtlTriple(ptr + 2, new_mtl.Ke);
          }
          break;
        case 'N':
          if (ptr[1] == 's') {
            ptr = ReadMtlSingle(ptr + 2, new_mtl.Ns);
          }
          break;
        case 'T':
          if (ptr[1] == 'r') {
            float Tr;
            ptr = ReadMtlSingle(ptr + 2, Tr);
            if (!found_d) {
              new_mtl.d = 1.0f - Tr;
            }
          }
          break;
        case 'd':
          if (IsSpace(ptr[1])) {
            ptr = ReadMtlSingle(ptr + 1, new_mtl.d);
            found_d = true;
          }
          break;
        case 'm':
          ptr++;
          if (ptr[0] == 'a' && ptr[1] == 'p' && ptr[2] == '_') {
            ptr += 3;
            std::string* map_ptr = nullptr;
            if (*ptr == 'K') {
              ptr++;
              if (ptr[0] == 'a' && IsSpace(ptr[1])) {
                ++ptr;
                new_mtl.map_ka = GetName(&ptr);
                map_ptr = &new_mtl.map_ka;
              } else if (ptr[0] == 'd' && IsSpace(ptr[1])) {
                ++ptr;
                new_mtl.map_kd = GetName(&ptr);
                map_ptr = &new_mtl.map_kd;
              } else if (ptr[0] == 's' && IsSpace(ptr[1])) {
                ++ptr;
                new_mtl.map_ks = GetName(&ptr);
                map_ptr = &new_mtl.map_ks;
              }
            }
            if (map_ptr && std::filesystem::path(*map_ptr).is_relative()) {
              *map_ptr = dir_path + *map_ptr;
            }
          }
          break;
        case '#':
          break;
      }
      ptr = SkipLine(ptr);
    }
    if (!new_mtl.name.empty()) {
      mtl.push_back(new_mtl);
    }
    delete[] buf;
    mtl_file.close();
  }
  return p;
}

const char* Data::ParseUsemtl(const char* ptr) {
  std::string use_mtl_name = GetName(&ptr);
  for (unsigned int i = 0; i < mtl.size(); ++i) {
    if (mtl[i].name == use_mtl_name) {
      usemtl.push_back({i, 0});
      if (!indices.empty()) {
        usemtl[usemtl.size() - 2].offset = indices.size();
      }
      break;
    }
  }
  return ptr;
}

void Data::ParseBuffer(const char* ptr, const char* end) {
  while (ptr != end) {
    ptr = SkipSpace(ptr);
    if (*ptr == 'v') {
      ++ptr;
      if (*ptr == ' ' || *ptr == '\t') {
        ptr = ParseVertex(ptr, v);
        ++vertex_count;
      } else if (*ptr == 'n') {
        ptr = ParseVertex(ptr, vn);
      } else if (*ptr == 't') {
        ptr = ParseVertex(ptr, vt);
      }
    } else if (*ptr == 'f') {
      ++ptr;
      if (*ptr == ' ' || *ptr == '\t') {
        ptr = ParseFacet(ptr);
        ++facet_count;
      }
    } else if (*ptr == 'm') {
      ++ptr;
      if (ptr[0] == 't' && ptr[1] == 'l' && ptr[2] == 'l' && ptr[3] == 'i' &&
          ptr[4] == 'b' && IsSpace(ptr[5])) {
        ptr = ParseMtl(ptr + 6);
      }
    } else if (*ptr == 'u') {
      ++ptr;
      if (ptr[0] == 's' && ptr[1] == 'e' && ptr[2] == 'm' && ptr[3] == 't' &&
          ptr[4] == 'l' && IsSpace(ptr[5])) {
        ptr = ParseUsemtl(ptr + 6);
      }
    }
    ptr = SkipLine(ptr);
  }
}

void Data::ReadFile(const std::string& path) {
  std::ifstream file(path, std::ifstream::binary);
  if (!file.is_open()) {
    m_stat = Status::noFile;
    return;
  }
  unsigned int read, bytes;
  char *start, *end, *last;
  {
    std::filesystem::path p(path);
    p.remove_filename();
    dir_path = p.generic_string();
  }
  char* buffer = new char[2 * bufferSize];
  start = buffer;
  for (;;) {
    read = file.readsome(start, bufferSize);
    if (!read && start == buffer) {
      break;
    }
    if (read < bufferSize) {
      if (!read || start[read - 1] != '\n') {
        start[read++] = '\n';
      }
    }
    end = start + read;
    if (end == buffer) {
      break;
    }
    last = end;
    while (last > buffer) {
      last--;
      if (*last == '\n') {
        break;
      }
    }
    if (*last != '\n') {
      break;
    }
    ++last;
    ParseBuffer(buffer, last);
    bytes = static_cast<unsigned int>(end - last);
    std::memmove(buffer, last, bytes);
    start = buffer + bytes;
  }
  if (mtl.empty()) {
    mtl.emplace_back(NewMtl{});
  }
  if (usemtl.empty()) {
    usemtl.emplace_back(UseMtl{});
  }
  usemtl.back().offset = indices.size();
  delete[] buffer;
  file.close();
}

bool Data::FromFile(const std::string& path) {
  ReadFile(path);
  if (m_stat != Status::noExc) {
    Flush();
    return false;
  }
  return true;
}

inline void Data::Flush() {
  std::vector<NewMtl>().swap(mtl);
  std::vector<UseMtl>().swap(usemtl);
  std::vector<Index>().swap(indices);
  std::vector<unsigned int>().swap(w_indices);

  std::vector<float>().swap(vn);
  std::vector<float>().swap(vt);
  std::vector<float>().swap(v);

  std::string().swap(dir_path);
}

}  // namespace Obj
