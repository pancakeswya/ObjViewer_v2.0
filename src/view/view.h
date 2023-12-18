#ifndef SRC_VIEW_VIEW_H_
#define SRC_VIEW_VIEW_H_

#include <QMainWindow>
#include <QSettings>

#include "controller/controller.h"
#include "base/data_types.h"

namespace objv {

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

class View : public QMainWindow {
  Q_OBJECT

 public:
  explicit View(Controller* controller);
  explicit View(QWidget* parent = nullptr);
  ~View() override;

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
  Ui::View* ui_;
  QSettings settings_;
};

}  // namespace objv

#endif  // SRC_VIEW_VIEW_H_
