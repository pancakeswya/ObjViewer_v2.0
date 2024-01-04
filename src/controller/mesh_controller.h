#ifndef SRC_CONTROLLER_MESH_CONTROLLER_H_
#define SRC_CONTROLLER_MESH_CONTROLLER_H_

#include "base/data_types.h"

namespace objv {

class MeshModel;

class MeshController {
 public:
  MeshController(MeshModel *model) noexcept;
  std::pair<const Mesh *, Status> CreateMesh(std::string_view path);

  void Reset() noexcept;

 private:
  MeshModel *model_;
};

}  // namespace objv

#endif  // SRC_CONTROLLER_MESH_CONTROLLER_H_