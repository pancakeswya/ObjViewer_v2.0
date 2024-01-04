#ifndef SRC_MODEL_CAMERA_MODEL_H_
#define SRC_MODEL_CAMERA_MODEL_H_

#include <QMatrix4x4>
#include <QVector3D>
#include <vector>

namespace objv {

class CameraModel {
 public:
  void SetPerspective(int width, int height, const float (&min_vertex)[3],
                      const float (&max_vertex)[3]) noexcept;
  void SetCentralProjection() noexcept;
  void SetParallelProjection() noexcept;
  void CalculateModelViewMatrix() noexcept;

  float GetMaxDistance() noexcept;
  std::vector<float> GetCenterCoords() noexcept;
  std::vector<float> GetModelViewMatrix() noexcept;
  std::vector<float> GetModelViewProjectionMatrix() noexcept;
  std::vector<float> GetModelViewMatrixInvertedTransposed() noexcept;

  void Rotate(int angle, int axis) noexcept;
  void Zoom(double coef) noexcept;
  void Move(double dist, int axis) noexcept;

  void Reset() noexcept;

 private:
  float max_size_{};
  float aspectratio_{};
  QVector3D center_{};

  QMatrix4x4 mv_mat_{};
  QMatrix4x4 v_mat_{};
  QMatrix4x4 p_mat_{};
  QMatrix4x4 m_mat_rotate_{};
  QMatrix4x4 m_mat_move_{};
  QMatrix4x4 m_mat_zoom_{};
  QVector3D angles_{};
  QVector3D moves_{};
};

}  // namespace objv

#endif  // SRC_MODEL_CAMERA_MODEL_H_