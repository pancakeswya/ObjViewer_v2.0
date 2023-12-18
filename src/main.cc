#include <QApplication>

#include "model/model.h"
#include "view/view.h"
#include "controller/controller.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  objv::Model m;
  objv::Controller c(&m);
  objv::View v(&c);
  v.show();
  return a.exec();
}
