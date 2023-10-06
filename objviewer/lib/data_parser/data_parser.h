#ifndef OBJVIEWER_LIB_DATA_PARSER_DATA_PARSER_H_
#define OBJVIEWER_LIB_DATA_PARSER_DATA_PARSER_H_

#include <limits>
#include <string>
#include <utility>
#include <vector>

#include "objviewer/types/data_types.h"

namespace objv::DataParser {

std::pair<Data*, Status> ParseFromFile(std::string_view path);

}  // namespace objv::DataParser

#endif  // OBJVIEWER_LIB_DATA_PARSER_DATA_PARSER_H_
