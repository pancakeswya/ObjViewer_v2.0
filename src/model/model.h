#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

#include <string_view>

#include "types/data_types.h"

namespace objv {

class Model {
 public:
  Model();
  ~Model();
  const Mesh* GetMesh() noexcept;
  Status MeshFromFile(std::string_view path);
  void Reset() noexcept;

 private:
  Mesh* mesh_;
};

}  // namespace objv

#endif  // SRC_MODEL_MODEL_H_