#ifndef SRC_CONTROLLER_CAMERA_CONTROLLER_H_
#define SRC_CONTROLLER_CAMERA_CONTROLLER_H_

#include <string_view>
#include <utility>

#include "base/data_types.h"

namespace objv {

class CameraModel;

class CameraController {
 public:
  CameraController(CameraModel* model) noexcept;

  void Rotate(int angle, int axis) noexcept;
  void Zoom(double coef) noexcept;
  void Move(double dist, int axis) noexcept;

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

  void Reset() noexcept;

 private:
  CameraModel* model_;
};

}  // namespace objv

#endif  // SRC_CONTROLLER_CAMERA_CONTROLLER_H_