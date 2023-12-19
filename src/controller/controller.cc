#include "controller/controller.h"

#include "model/camera_model.h"
#include "model/mesh_model.h"

namespace objv {

Controller::Controller(MeshModel *model, CameraModel *camera) noexcept
    : model_(model), camera_(camera) {}

std::pair<const Mesh *, Status> Controller::CreateMesh(std::string_view path) {
  auto status = model_->CreateMesh(path);
  const auto mesh = model_->GetMesh();
  return {mesh, status};
}

void Controller::SetPerspective(int width, int height,
                                const float min_vertex[3],
                                const float max_vertex[3]) noexcept {
  return camera_->SetPerspective(width, height, min_vertex, max_vertex);
}

void Controller::SetCentralProjection() noexcept {
  return camera_->SetCentralProjection();
}

void Controller::SetParallelProjection() noexcept {
  return camera_->SetParallelProjection();
}

float Controller::GetMaxDistance() noexcept {
  return camera_->GetMaxDistance();
}

QVector3D Controller::GetCenterCoords() noexcept {
  return camera_->GetCenterCoords();
}

QMatrix4x4 Controller::GetModelMatrix() noexcept {
  return camera_->GetModelMatrix();
}

QMatrix4x4 Controller::GetViewMatrix() noexcept {
  return camera_->GetViewMatrix();
}

QMatrix4x4 Controller::GetProjectionMatrix() noexcept {
  return camera_->GetProjectionMatrix();
}

void Controller::Rotate(int angle, int axis) noexcept {
  camera_->Rotate(angle, axis);
}

void Controller::Zoom(double coef) noexcept { camera_->Zoom(coef); }

void Controller::Move(double dist, int axis) noexcept {
  camera_->Move(dist, axis);
}

void Controller::Reset() noexcept { model_->Reset(); }

}  // namespace objv
