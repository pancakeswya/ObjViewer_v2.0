#ifndef VIEWER_H
#define VIEWER_H

#include <QColorDialog>
#include <QMainWindow>
#include <QSettings>

#include "../libgif/gif_maker.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Viewer;
}
QT_END_NAMESPACE

class Viewer : public QMainWindow {
  Q_OBJECT

 public:
  explicit Viewer(QWidget *parent = nullptr);
  ~Viewer() override;

 protected:
  void Init();
  static void SetTheme();
  void SaveSettings();
  void LoadSettings();
 private slots:
  void OnPushButtonOpenObjClicked();
  void OnSwitchLineTypeCurrentIndexChanged(int);
  void OnSwitchProjectionCurrentIndexChanged(int);
  void OnLineWidthSpinBoxValueChanged(int);
  void OnSwitchTypeVertexCurrentIndexChanged(int);
  void OnVertexSizeSpinBoxValueChanged(int);
  void OnBgColorClicked();
  void OnLineColorClicked();
  void OnVertexColorClicked();
  void OnZoomSpinBoxValueChanged(double);
  void OnMoveSpinBoxXValueChanged(int);
  void OnMoveSpinBoxYValueChanged(int);
  void OnMoveSpinBoxZValueChanged(int);
  void OnRotateSpinBoxXValueChanged(int);
  void OnRotateSpinBoxYValueChanged(int);
  void OnRotateSpinBoxZValueChanged(int);
  void OnScreenButtonClicked();
  void OnResetClicked();
  void OnGifButtonClicked();
  void OnComboBoxCurrentIndexChanged(int index);

 private:
  Ui::Viewer *ui;
  QSettings settings;
};
#endif  // VIEWER_H
