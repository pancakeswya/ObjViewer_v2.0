#ifndef SRC_MODEL_MESH_MAKER_H_
#define SRC_MODEL_MESH_MAKER_H_

#include "types/data_types.h"

#include <string_view>
#include <utility>

namespace objv::MeshMaker {

extern std::pair<Mesh*, Status> MakeFromFile(std::string_view path);

}  // namespace objv::MeshMaker

#endif  // SRC_MODEL_MESH_MAKER_H_
