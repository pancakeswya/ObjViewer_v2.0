#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include <QMatrix4x4>
#include <QVector3D>
#include <string_view>
#include <utility>

#include "base/data_types.h"

namespace objv {

class MeshModel;
class CameraModel;

class Controller {
 public:
  Controller(MeshModel* model, CameraModel* camera) noexcept;
  std::pair<const Mesh*, Status> CreateMesh(std::string_view path);

  void Rotate(int angle, int axis) noexcept;
  void Zoom(double coef) noexcept;
  void Move(double dist, int axis) noexcept;

  void SetPerspective(int width, int height, const float min_vertex[3],
                      const float max_vertex[3]) noexcept;
  void SetCentralProjection() noexcept;
  void SetParallelProjection() noexcept;

  float GetMaxDistance() noexcept;
  QVector3D GetCenterCoords() noexcept;
  QMatrix4x4 GetModelMatrix() noexcept;
  QMatrix4x4 GetViewMatrix() noexcept;
  QMatrix4x4 GetProjectionMatrix() noexcept;

  void Reset() noexcept;

 private:
  MeshModel* model_;
  CameraModel* camera_;
};

}  // namespace objv

#endif  // SRC_CONTROLLER_CONTROLLER_H_