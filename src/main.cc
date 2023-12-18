#include <QApplication>

#include "controller/controller.h"
#include "model/model.h"
#include "view/view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  objv::Model m;
  objv::Controller c(&m);
  objv::View v(&c);
  v.show();
  return a.exec();
}
