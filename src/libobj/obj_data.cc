#include "obj_data.h"

#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>

namespace Obj {

namespace {

inline bool IsSpace(char c) noexcept { return (c == ' ') || (c == '\t') || (c == '\r'); }

inline bool IsDigit(char c) noexcept { return (c >= '0') && (c <= '9'); }

inline bool IsEndOfName(char c) noexcept {
  return (c == '\t') || (c == '\r') || (c == '\n');
}

const char *SkipSpace(const char *ptr) noexcept {
  for (; IsSpace(*ptr); ++ptr);
  return ptr;
}

const char *SkipLine(const char *ptr) noexcept {
  for (; *ptr != '\n'; ++ptr);
  return ++ptr;
}

unsigned long int FileSize(std::ifstream &file) noexcept {
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

std::string GetName(const char **ptr) noexcept {
  const char *p = *ptr;
  p = SkipSpace(p);
  std::string name;
  for (; !IsEndOfName(*p);++p) {
    name += *p;
  }
  *ptr = p;
  return name;
}

inline const char *ReadMtlSingle(const char *ptr, float &mtl) noexcept {
  char *end = nullptr;
  mtl = std::strtof(ptr, &end);
  return end;
}

inline const char *ReadMtlTriple(const char *ptr, float triple[3]) noexcept {
  ptr = ReadMtlSingle(ptr, triple[0]);
  ptr = ReadMtlSingle(ptr, triple[1]);
  ptr = ReadMtlSingle(ptr, triple[2]);

  return ptr;
}

inline const char *ReadMtlInt(const char *ptr, long int &val) noexcept {
  char *end = nullptr;
  val = std::strtol(ptr, &end, 10);
  return end;
}

}  // namespace

const char *Data::ParseVertex(const char *ptr, std::vector<float> &array) {
  float vert;
  char *end = nullptr;
  char type = *ptr++;
  int vert_max = (type == 't') ? 2 : 3;
  for (int i = 0; i < vert_max; ++i) {
    vert = std::strtof(ptr, &end);
    if (end == ptr) {
      m_stat = Status::invalidFile;
      break;
    }
    if (type == ' ') {
      max[i] = std::max(vert, max[i]);
      min[i] = std::min(vert, min[i]);
    }
    array.push_back(vert);
    ptr = SkipSpace(end);
  }
  return ptr;
}

const char *Data::ParseFacet(const char *ptr) {
  char *end = nullptr;
  long int tmp_i;
  unsigned start_i = w_indices.size();
  size_t curr_i = 0;
  while (*ptr != '\n') {
    Index idx = {};
    tmp_i = std::strtol(ptr, &end, 10);
    if (tmp_i < 0) {
      idx.f = v.size() / 3 - (unsigned int) (-tmp_i);
    } else if (tmp_i > 0) {
      idx.f = (unsigned int) tmp_i - 1;
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
          idx.t = t.size() / 2 - (unsigned int) (-tmp_i);
        } else if (tmp_i > 0) {
          idx.t = (unsigned int) tmp_i - 1;
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
        idx.n = n.size() / 3 - (unsigned int) (-tmp_i);
      } else if (tmp_i > 0) {
        idx.n = (unsigned int) tmp_i - 1;
      }
      if (end == ptr) {
        m_stat = Status::invalidFile;
        break;
      }
      ptr = end;
    }
    // triangulate as fan
    // TODO: find new algorithm of triangulation and learn geometry
    if (curr_i >= 3) {
      indices.push_back(indices[indices.size() - curr_i]);
      indices.push_back(indices[indices.size() - 2]);
      curr_i += 2;
    }
    // wireframe facets
    if (w_indices.size() != start_i) {
      w_indices.push_back(idx.f);
    }
    w_indices.push_back(idx.f);
    // push parsed indices
    indices.push_back(idx);
    ptr = SkipSpace(ptr);
    ++curr_i;
  }
  w_indices.push_back(w_indices[start_i]);
  return ptr;
}

const char *Data::ParseMtl(const char *p) {
  std::string path_mtl = GetName(&p);
  std::ifstream mtl_file(dir_path + path_mtl, std::ifstream::binary);
  if (mtl_file.is_open()) {
    NewMtl new_mtl;
    bool found_d = false;

    unsigned long int bytes = FileSize(mtl_file);
    char *buf = new char[bytes + 1];
    unsigned int read = mtl_file.readsome(buf, bytes);
    buf[read] = '\0';

    const char *ptr = buf;
    const char *eof = buf + read;

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
          } else if (ptr[1] == 'i') {
            ptr = ReadMtlSingle(ptr + 2, new_mtl.Ni);
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
        case 'i':
          ptr++;
          if (ptr[0] == 'l' && ptr[1] == 'l' && ptr[2] == 'u' &&
              ptr[3] == 'm' && IsSpace(ptr[4])) {
            ptr = ReadMtlInt(ptr + 4, new_mtl.illum);
          }
          break;
        case 'm':
          ptr++;
          if (ptr[0] == 'a' && ptr[1] == 'p' && ptr[2] == '_') {
            ptr += 3;
            std::string *map_ptr = nullptr;
            if (*ptr == 'K') {
              ptr++;
              if (ptr[0] == 'd' && IsSpace(ptr[1])) {
                ++ptr;
                new_mtl.map_kd = GetName(&ptr);
                map_ptr = &new_mtl.map_kd;
              }
            } else if (*ptr == 'N') {
              ptr++;
              if (ptr[0] == 's' && IsSpace(ptr[1])) {
                ++ptr;
                new_mtl.map_Ns = GetName(&ptr);
                map_ptr = &new_mtl.map_Ns;
              }
            } else if ((ptr[0] == 'b' || ptr[0] == 'B') && ptr[1] == 'u' &&
                ptr[2] == 'm' && ptr[3] == 'p' && IsSpace(ptr[4])) {
              ptr += 4;
              new_mtl.map_bump = GetName(&ptr);
              map_ptr = &new_mtl.map_bump;
            }
            if (map_ptr && std::filesystem::path(*map_ptr).is_relative()) {
              *map_ptr = dir_path + *map_ptr;
            }
          }
          break;
        case '#':break;
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

const char *Data::ParseUsemtl(const char *ptr) {
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

void Data::ParseBuffer(const char *ptr, const char *end) {
  while (ptr != end) {
    ptr = SkipSpace(ptr);
    if (*ptr == 'v') {
      ++ptr;
      if (*ptr == ' ' || *ptr == '\t') {
        ptr = ParseVertex(ptr, v);
        ++vertex_count;
      } else if (*ptr == 'n') {
        ptr = ParseVertex(ptr, n);
      } else if (*ptr == 't') {
        ptr = ParseVertex(ptr, t);
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

void Data::ReadFile(const std::string &path) {
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
  char *buffer = new char[2 * bufferSize];
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
    bytes = (unsigned int) (end - last);
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

bool Data::FromFile(const std::string &path) {
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

  std::vector<float>().swap(n);
  std::vector<float>().swap(t);
  std::vector<float>().swap(v);

  std::string().swap(dir_path);
}

} // namspace Obj
