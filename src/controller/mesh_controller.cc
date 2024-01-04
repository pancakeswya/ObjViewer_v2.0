#include "controller/mesh_controller.h"

#include "model/mesh_model.h"

namespace objv {

MeshController::MeshController(MeshModel *model) noexcept : model_(model) {}

std::pair<const Mesh *, Status> MeshController::CreateMesh(
    std::string_view path) {
  auto status = model_->CreateMesh(path);
  const auto mesh = model_->GetMesh();
  return {mesh, status};
}

void MeshController::Reset() noexcept { model_->Reset(); }

}  // namespace objv