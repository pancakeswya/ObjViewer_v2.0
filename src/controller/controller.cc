#include "controller/controller.h"

#include "model/model.h"

namespace objv {

Controller::Controller(objv::Model *model) noexcept : model_(model) {}

std::pair<const Mesh *, Status> Controller::MeshFromFile(
    std::string_view path) {
  auto status = model_->MeshFromFile(path);
  const auto mesh = model_->GetMesh();
  return {mesh, status};
}

void Controller::Reset() noexcept { model_->Reset(); }

}  // namespace objv
