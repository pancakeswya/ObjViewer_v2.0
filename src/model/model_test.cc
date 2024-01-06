#include <gtest/gtest.h>

#include <iostream>

#include "base/data_types.h"
#include "model/camera_model.h"
#include "model/mesh_model.h"

#define EXPECT_FLOAT_VECTOR_EQ(a, b)      \
  for (size_t i = 0; i < a.size(); i++) { \
    EXPECT_FLOAT_EQ(a[i], b[i]);          \
  }

TEST(CameraModelTests, RotateTest) {
  objv::CameraModel model;
  model.Rotate(45, 0);
  model.CalculateModelViewMatrix();
  auto vm = model.GetModelViewMatrix();
  std::vector<float> cmp = {
      1, 0,           0,          0, 0, 0.70710677, 0.70710677, 0,
      0, -0.70710677, 0.70710677, 0, 0, 0,          0,          1};
  EXPECT_FLOAT_VECTOR_EQ(vm, cmp);
}

TEST(CameraModelTests, MoveTest) {
  objv::CameraModel model;
  model.Move(5, 2);
  model.CalculateModelViewMatrix();
  auto mvp = model.GetModelViewProjectionMatrix();
  std::vector<float> cmp = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 5, 1};
  EXPECT_FLOAT_VECTOR_EQ(mvp, cmp);
}

TEST(CameraModelTests, ScaleTest) {
  objv::CameraModel model;
  model.Zoom(0.2);
  model.CalculateModelViewMatrix();
  auto vm = model.GetModelViewMatrixInvertedTransposed();
  std::vector<float> cmp = {5, 0, 0, -0, 0, 5, 0, -0, 0, 0, 5, -0, 0, 0, 0, 1};
  EXPECT_FLOAT_VECTOR_EQ(vm, cmp);
}

TEST(CameraModelTests, PerspectiveCentralTest) {
  objv::CameraModel model;
  float min[] = {1.1, 2.2, 3.3};
  float max[] = {4.4, 5.5, 6.6};
  model.SetPerspective(800, 600, min, max);
  model.SetCentralProjection();
  model.CalculateModelViewMatrix();
  auto vm = model.GetModelViewProjectionMatrix();
  auto center = model.GetCenterCoords();
  float max_distance = model.GetMaxDistance();
  std::vector<float> cmp = {
      0.62932473, 0, 0,       0,  0,         0.83909965, 0,         0,
      0,          0, -1.0002, -1, -1.730643, -3.2305336, 8.1856422, 8.25};
  std::vector<float> center_cmp = {2.75, 3.85, 4.95};
  EXPECT_FLOAT_EQ(max_distance, 3.3f);
  EXPECT_FLOAT_VECTOR_EQ(center, center_cmp);
  EXPECT_FLOAT_VECTOR_EQ(vm, cmp);
}

TEST(CameraModelTests, PerspectiveParallelTest) {
  objv::CameraModel model;
  float min[] = {1.1, 2.2, 3.3};
  float max[] = {4.4, 5.5, 6.6};
  model.SetPerspective(800, 600, min, max);
  model.SetParallelProjection();
  model.CalculateModelViewMatrix();
  auto vm = model.GetModelViewProjectionMatrix();
  auto center = model.GetCenterCoords();
  float max_distance = model.GetMaxDistance();
  std::vector<float> cmp = {0.2272727,     0, 0, 0, 0, 0.3030303, 0, 0, 0, 0,
                            -0.0030303027, 0, 0, 0, 0, 1};
  std::vector<float> center_cmp = {2.75, 3.85, 4.95};
  EXPECT_FLOAT_EQ(max_distance, 3.3f);
  EXPECT_FLOAT_VECTOR_EQ(center, center_cmp);
  EXPECT_FLOAT_VECTOR_EQ(vm, cmp);
}

TEST(MeshModelTests, ObjSimple) {
  objv::MeshModel model;
  auto stat = model.CreateMesh("../../../obj/Arisu.obj");
  [[maybe_unused]] auto mesh = model.GetMesh();
  EXPECT_EQ(stat, objv::Status::kNoExc);
  model.Reset();
}

TEST(MeshModelTests, ObjTextured) {
  objv::MeshModel model;
  auto stat = model.CreateMesh("../../../obj/tommy/tommy.obj");
  [[maybe_unused]] auto mesh = model.GetMesh();
  EXPECT_EQ(stat, objv::Status::kNoExc);
  model.Reset();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
