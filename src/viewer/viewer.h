#ifndef VIEWER_H
#define VIEWER_H

#include <QColorDialog>
#include <QMainWindow>
#include <QSettings>

namespace obj {

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
 private slots:
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

} // namespace obj

#endif  // VIEWER_H
