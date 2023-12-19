#include <QApplication>

#include "controller/controller.h"
#include "model/camera_model.h"
#include "model/mesh_model.h"
#include "view/viewer.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  objv::MeshModel mesh_model;
  objv::CameraModel camera_model;
  objv::Controller controller(&mesh_model, &camera_model);
  objv::Viewer viewer(&controller);
  viewer.show();
  return app.exec();
}
