#ifndef OBJVIEWER_VIEWER_VIEWER_H_
#define OBJVIEWER_VIEWER_VIEWER_H_

#include <QMainWindow>
#include <QSettings>

#include "ui_viewer.h"

namespace objv {

QT_BEGIN_NAMESPACE
namespace Ui {
class Viewer;
}
QT_END_NAMESPACE

class Viewer : public QMainWindow {
  Q_OBJECT

 public:
  explicit Viewer(QWidget* parent = nullptr);
  ~Viewer() override;

 protected:
  void Init();
  static void SetTheme();
  void SaveSettings();
  void LoadSettings();
  void LoadMaterial(const MaterialData&);
 private slots:
  void OnDoubleSpinBoxStepScaleValueChanged(double);
  void OnDoubleSpinBoxStepMoveValueChanged(double);
  void OnPushButtonOpenFileClicked();
  void OnPushButtonBgColorClicked();
  void OnPushButtonEdgeColorClicked();
  void OnPushButtonVertexColorClicked();
  void OnDoubleSpinBoxMoveValueChanged(double);
  void OnSpinBoxRotateValueChanged(int);
  void OnPushButtonScreenClicked();
  void OnPushButtonResetClicked();
  void OnPushButtonGifClicked();

 private:
  Ui::Viewer* ui_;
  QSettings settings_;
};

}  // namespace objv

#endif  // OBJVIEWER_VIEWER_VIEWER_H_
