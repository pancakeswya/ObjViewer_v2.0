#ifndef SRC_MODEL_MESH_MODEL_H_
#define SRC_MODEL_MESH_MODEL_H_

#include <string_view>

#include "base/data_types.h"

namespace objv {

class MeshModel {
 public:
  MeshModel() noexcept;
  ~MeshModel();
  const Mesh* GetMesh() noexcept;
  Status CreateMesh(std::string_view path);
  void Reset() noexcept;

 private:
  Mesh* mesh_;
};

}  // namespace objv

#endif  // SRC_MODEL_MESH_MODEL_H_