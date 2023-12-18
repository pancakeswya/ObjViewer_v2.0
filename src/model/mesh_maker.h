#ifndef SRC_MODEL_MESH_MAKER_H_
#define SRC_MODEL_MESH_MAKER_H_

#include <string_view>
#include <utility>

#include "types/data_types.h"

namespace objv::MeshMaker {

extern std::pair<Mesh*, Status> MakeFromFile(std::string_view path);

}  // namespace objv::MeshMaker

#endif  // SRC_MODEL_MESH_MAKER_H_
