#ifndef SRC_VIEWER_VIEWER_H_
#define SRC_VIEWER_VIEWER_H_

#include "types/data_types.h"

#include <QMainWindow>
#include <QSettings>

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
  void Initialize();
  static void SetTheme();
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

#endif  // SRC_VIEWER_VIEWER_H_