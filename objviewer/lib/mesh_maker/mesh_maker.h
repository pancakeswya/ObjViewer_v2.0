#ifndef OBJVIEWER_LIB_MESH_MAKER_MESH_MAKER_H_
#define OBJVIEWER_LIB_MESH_MAKER_MESH_MAKER_H_

#include "objviewer/lib/data_parser/data_parser.h"

namespace objv::MeshMaker {

std::pair<Mesh*, Status> MakeFromFile(std::string_view path);

}  // namespace objv::MeshMaker

#endif  // OBJVIEWER_LIB_MESH_MAKER_MESH_MAKER_H_
