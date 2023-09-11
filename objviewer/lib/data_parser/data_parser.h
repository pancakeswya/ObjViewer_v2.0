#ifndef OBJVIEWER_LIB_DATA_PARSER_DATA_PARSER_H_
#define OBJVIEWER_LIB_DATA_PARSER_DATA_PARSER_H_

#include <limits>
#include <string>
#include <utility>
#include <vector>

#include "objviewer/types/data_types.h"

namespace objv::DataParser {

struct Index {
  unsigned int fv;
  unsigned int fn;
  unsigned int ft;
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

std::pair<Data*, Status> Parse(std::string_view path);

}  // namespace objv::DataParser

#endif  // OBJVIEWER_LIB_DATA_PARSER_DATA_PARSER_H_
