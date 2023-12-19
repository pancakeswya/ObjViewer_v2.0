#include "model/mesh_model.h"

#include "base/mesh_maker.h"

namespace objv {

MeshModel::MeshModel() noexcept : mesh_() {}

MeshModel::~MeshModel() { delete mesh_; }

Status MeshModel::CreateMesh(std::string_view path) {
  auto [mesh, status] = MeshMaker::MakeFromFile(path);
  mesh_ = mesh;
  return status;
}

const Mesh* MeshModel::GetMesh() noexcept { return mesh_; }

void MeshModel::Reset() noexcept {
  delete mesh_;
  mesh_ = nullptr;
}

}  // namespace objv