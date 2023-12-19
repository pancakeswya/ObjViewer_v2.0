#ifndef SRC_VIEW_VIEWER_H_
#define SRC_VIEW_VIEWER_H_

#include <QMainWindow>
#include <QSettings>

#include "base/data_types.h"
#include "controller/controller.h"

namespace objv {

QT_BEGIN_NAMESPACE
namespace Ui {
class Viewer;
}
QT_END_NAMESPACE

class Viewer : public QMainWindow {
  Q_OBJECT

 public:
  explicit Viewer(Controller* controller);
  explicit Viewer(QWidget* parent = nullptr);
  ~Viewer() override;

 protected:
  static void SetTheme();
  void Initialize();
  void SaveSettings();
  void LoadSettings();
  void LoadMaterial(const std::vector<NewMtl>&);
 private slots:
  void OnDoubleSpinBoxStepScaleValueChanged(double new_step);
  void OnDoubleSpinBoxStepMoveValueChanged(double new_step);
  void OnDoubleSpinBoxMoveValueChanged(double value);
  void OnSpinBoxRotateValueChanged(int value);
  void OnPushButtonOpenFileClicked();
  void OnPushButtonBgColorClicked();
  void OnPushButtonEdgeColorClicked();
  void OnPushButtonVertexColorClicked();
  void OnPushButtonScreenClicked();
  void OnPushButtonResetClicked();
  void OnPushButtonGifClicked();

 private:
  Ui::Viewer* ui_;
  QSettings settings_;
};

}  // namespace objv

#endif  // SRC_VIEW_VIEWER_H_
