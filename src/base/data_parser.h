#ifndef SRC_BASE_DATA_PARSER_DATA_PARSER_H_
#define SRC_BASE_DATA_PARSER_DATA_PARSER_H_

#include "types/data_types.h"

#include <string_view>
#include <utility>

namespace objv::DataParser {

extern std::pair<Data*, Status> ParseFromFile(std::string_view path);

}  // namespace objv::DataParser

#endif  // SRC_BASE_DATA_PARSER_DATA_PARSER_H_
