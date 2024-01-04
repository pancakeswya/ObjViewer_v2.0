#include "controller/camera_controller.h"

#include "model/camera_model.h"
#include "model/mesh_model.h"

namespace objv {

CameraController::CameraController(CameraModel *model) noexcept
    : model_(model) {}

void CameraController::SetPerspective(int width, int height,
                                      const float (&min_vertex)[3],
                                      const float (&max_vertex)[3]) noexcept {
  model_->SetPerspective(width, height, min_vertex, max_vertex);
}

void CameraController::SetCentralProjection() noexcept {
  model_->SetCentralProjection();
}

void CameraController::SetParallelProjection() noexcept {
  model_->SetParallelProjection();
}

void CameraController::CalculateModelViewMatrix() noexcept {
  model_->CalculateModelViewMatrix();
}

float CameraController::GetMaxDistance() noexcept {
  return model_->GetMaxDistance();
}

std::vector<float> CameraController::GetCenterCoords() noexcept {
  return model_->GetCenterCoords();
}

std::vector<float> CameraController::GetModelViewMatrix() noexcept {
  return model_->GetModelViewMatrix();
}

std::vector<float> CameraController::GetModelViewProjectionMatrix() noexcept {
  return model_->GetModelViewProjectionMatrix();
}

std::vector<float>
CameraController::GetModelViewMatrixInvertedTransposed() noexcept {
  return model_->GetModelViewMatrixInvertedTransposed();
}

void CameraController::Rotate(int angle, int axis) noexcept {
  model_->Rotate(angle, axis);
}

void CameraController::Zoom(double coef) noexcept { model_->Zoom(coef); }

void CameraController::Move(double dist, int axis) noexcept {
  model_->Move(dist, axis);
}

void CameraController::Reset() noexcept { model_->Reset(); }

}  // namespace objv
