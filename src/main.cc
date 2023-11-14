#include <QApplication>

#include "view/viewer.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  objv::Viewer w;
  w.show();
  return a.exec();
}
