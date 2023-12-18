#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include <string_view>
#include <utility>

#include "base/data_types.h"

namespace objv {

class Model;

class Controller {
 public:
  Controller(Model* model) noexcept;
  std::pair<const Mesh*, Status> MeshFromFile(std::string_view path);
  void Reset() noexcept;

 private:
  Model* model_;
};

}  // namespace objv

#endif  // SRC_CONTROLLER_CONTROLLER_H_