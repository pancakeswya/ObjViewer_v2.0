#ifndef OBJVIEWER_V2_SRC_MODEL_MESH_H_
#define OBJVIEWER_V2_SRC_MODEL_MESH_H_

#include "data.h"

namespace obj::MeshMaker {

std::pair<Mesh*, Status> FromFile(std::string_view path);

}  // namespace obj::MeshMaker

#endif  // OBJVIEWER_V2_SRC_MODEL_MESH_H_
