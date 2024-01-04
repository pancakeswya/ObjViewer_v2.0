#include <QApplication>
#include <clocale>

#include "controller/camera_controller.cc"
#include "controller/mesh_controller.h"
#include "model/camera_model.h"
#include "model/mesh_model.h"
#include "view/viewer.h"

int main(int argc, char *argv[]) {
  std::setlocale(LC_NUMERIC, "C");
  QApplication app(argc, argv);

  objv::MeshModel mesh_model;
  objv::CameraModel camera_model;

  objv::MeshController mesh_controller(&mesh_model);
  objv::CameraController camera_controller(&camera_model);

  objv::Viewer viewer(&mesh_controller, &camera_controller);

  viewer.show();
  return app.exec();
}
