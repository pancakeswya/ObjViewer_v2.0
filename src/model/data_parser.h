#ifndef SRC_MODEL_DATA_PARSER_H_
#define SRC_MODEL_DATA_PARSER_H_

#include <string_view>
#include <utility>

#include "base/data_types.h"

namespace objv::DataParser {

extern std::pair<Data*, Status> ParseFromFile(std::string_view path);

}  // namespace objv::DataParser

#endif  // SRC_MODEL_DATA_PARSER_H_
