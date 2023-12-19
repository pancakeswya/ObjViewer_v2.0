#include "model/camera_model.h"

#include <algorithm>
#include <cmath>

namespace objv {

void CameraModel::SetPerspective(int width, int height,
                                 const float min_vertex[3],
                                 const float max_vertex[3]) noexcept {
  p_mat_.setToIdentity();
  v_mat_.setToIdentity();
  float size_x = std::abs(min_vertex[0] - max_vertex[0]);
  float size_y = std::abs(min_vertex[1] - max_vertex[1]);
  float size_z = std::abs(min_vertex[2] - max_vertex[2]);
  float mid_size_x = (min_vertex[0] + max_vertex[0]) / 2.0f;
  float mid_size_y = (min_vertex[1] + max_vertex[1]) / 2.0f;
  float mid_size_z = (min_vertex[2] + max_vertex[2]) / 2.0f;
  max_size_ = std::max(std::max(size_x, size_y), size_z);
  aspectratio_ = float(width) / float(height);
  center_ = QVector3D(mid_size_x, mid_size_y, mid_size_z);
}

void CameraModel::SetCentralProjection() noexcept {
  v_mat_.lookAt(QVector3D(center_.x(), center_.y(), center_.z() + max_size_),
                center_, QVector3D(0.0f, 1.0f, 0.0f));
  p_mat_.perspective(100.0f, aspectratio_, 0.01f * max_size_,
                     100.0f * max_size_);
}

void CameraModel::SetParallelProjection() noexcept {
  p_mat_.ortho(-max_size_ * aspectratio_, max_size_ * aspectratio_, -max_size_,
               max_size_, -100.0f * max_size_, 100.0f * max_size_);
}

float CameraModel::GetMaxDistance() noexcept { return max_size_; }

QVector3D CameraModel::GetCenterCoords() noexcept { return center_; }

QMatrix4x4 CameraModel::GetModelMatrix() noexcept {
  return m_mat_move_ * m_mat_rotate_ * m_mat_zoom_;
}

QMatrix4x4 CameraModel::GetViewMatrix() noexcept { return v_mat_; }

QMatrix4x4 CameraModel::GetProjectionMatrix() noexcept { return p_mat_; }

void CameraModel::Rotate(int angle, int axis) noexcept {
  angles_[axis] = angle;
  m_mat_rotate_.setToIdentity();
  m_mat_rotate_.rotate(angles_.x(), 1.0f, 0.0f, 0.0f);
  m_mat_rotate_.rotate(angles_.y(), 0.0f, 1.0f, 0.0f);
  m_mat_rotate_.rotate(angles_.z(), 0.0f, 0.0f, 1.0f);
}

void CameraModel::Zoom(double coef) noexcept {
  m_mat_zoom_.setToIdentity();
  m_mat_zoom_.scale(coef);
}

void CameraModel::Move(double dist, int axis) noexcept {
  moves_[axis] = dist;
  m_mat_move_.setToIdentity();
  m_mat_move_.translate(moves_.x(), 0.0f, 0.0f);
  m_mat_move_.translate(0.0f, moves_.y(), 0.0f);
  m_mat_move_.translate(0.0f, 0.0f, moves_.z());
}

void CameraModel::Reset() noexcept {
  max_size_ = 0;
  aspectratio_ = 0;
  center_ = {};

  p_mat_ = {};
  v_mat_ = {};
  m_mat_rotate_ = {};
  m_mat_move_ = {};
  m_mat_zoom_ = {};
  angles_ = {};
  moves_ = {};
}

}  // namespace objv