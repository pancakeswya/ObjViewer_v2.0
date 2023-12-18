#include "model/model.h"

#include "model/mesh_maker.h"

namespace objv {

Model::Model() noexcept : mesh_() {}

Model::~Model() { delete mesh_; }

Status Model::MeshFromFile(std::string_view path) {
  auto [mesh, status] = MeshMaker::MakeFromFile(path);
  mesh_ = mesh;
  return status;
}

const Mesh* Model::GetMesh() noexcept { return mesh_; }

void Model::Reset() noexcept {
  delete mesh_;
  mesh_ = nullptr;
}

}  // namespace objv