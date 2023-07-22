#include "viewer.h"

#include <QImageWriter>
#include <QMessageBox>
#include <QStandardPaths>
#include <QStyleFactory>

#include "./ui_viewer.h"

Viewer::Viewer(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::Viewer),
      settings("School21", "3DViewer_v1.0") {
  ui->setupUi(this);
  setWindowTitle("3DViewer_v1.0");
  setWindowIcon(QIcon(":/images/3DViewer_icon.png"));
  SetTheme();
  Init();
  LoadSettings();
}

Viewer::~Viewer() {
  SaveSettings();
  delete ui;
}

void Viewer::Init() {
  connect(ui->pushButton_openObj, SIGNAL(clicked()), this,
          SLOT(OnPushButtonOpenObjClicked()));
  connect(ui->switch_line_type, SIGNAL(currentIndexChanged(int)), this,
          SLOT(OnSwitchLineTypeCurrentIndexChanged(int)));
  connect(ui->switch_projection, SIGNAL(currentIndexChanged(int)), this,
          SLOT(OnSwitchProjectionCurrentIndexChanged(int)));
  connect(ui->LineWidth_SpinBox, SIGNAL(valueChanged(int)), this,
          SLOT(OnLineWidthSpinBoxValueChanged(int)));
  connect(ui->switch_type_vertex, SIGNAL(currentIndexChanged(int)), this,
          SLOT(OnSwitchTypeVertexCurrentIndexChanged(int)));
  connect(ui->vertexSize_SpinBox, SIGNAL(valueChanged(int)), this,
          SLOT(OnVertexSizeSpinBoxValueChanged(int)));
  connect(ui->bg_color, SIGNAL(clicked()), this, SLOT(OnBgColorClicked()));
  connect(ui->line_color, SIGNAL(clicked()), this, SLOT(OnLineColorClicked()));
  connect(ui->vertex_color, SIGNAL(clicked()), this,
          SLOT(OnVertexColorClicked()));
  connect(ui->zoom_SpinBox, SIGNAL(valueChanged(double)), this,
          SLOT(OnZoomSpinBoxValueChanged(double)));
  connect(ui->moveSpinBox_X, SIGNAL(valueChanged(int)), this,
          SLOT(OnMoveSpinBoxXValueChanged(int)));
  connect(ui->moveSpinBox_Y, SIGNAL(valueChanged(int)), this,
          SLOT(OnMoveSpinBoxYValueChanged(int)));
  connect(ui->moveSpinBox_Z, SIGNAL(valueChanged(int)), this,
          SLOT(OnMoveSpinBoxZValueChanged(int)));
  connect(ui->rotate_spinBox_X, SIGNAL(valueChanged(int)), this,
          SLOT(OnRotateSpinBoxXValueChanged(int)));
  connect(ui->rotate_spinBox_Y, SIGNAL(valueChanged(int)), this,
          SLOT(OnRotateSpinBoxYValueChanged(int)));
  connect(ui->rotate_spinBox_Z, SIGNAL(valueChanged(int)), this,
          SLOT(OnRotateSpinBoxZValueChanged(int)));
  connect(ui->screen_button, SIGNAL(clicked()), this,
          SLOT(OnScreenButtonClicked()));
  connect(ui->reset, SIGNAL(clicked()), this, SLOT(OnResetClicked()));
  connect(ui->gif_button, SIGNAL(clicked()), this, SLOT(OnGifButtonClicked()));
  connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this,
          SLOT(OnComboBoxCurrentIndexChanged(int)));
  ui->zoom_SpinBox->setValue(1);
  connect(ui->rotate_x, &QSlider::valueChanged, ui->rotate_spinBox_X,
          &QSpinBox::setValue);
  connect(ui->rotate_spinBox_X, QOverload<int>::of(&QSpinBox::valueChanged),
          ui->rotate_x, &QSlider::setValue);
  ui->rotate_x->setRange(-360, 360);
  ui->moveSpinBox_X->setRange(-1000, 1000);
  ui->moveSpinBox_X->setValue(0);

  connect(ui->rotate_y, &QSlider::valueChanged, ui->rotate_spinBox_Y,
          &QSpinBox::setValue);
  connect(ui->rotate_spinBox_Y, QOverload<int>::of(&QSpinBox::valueChanged),
          ui->rotate_y, &QSlider::setValue);
  ui->rotate_y->setRange(-360, 360);
  ui->moveSpinBox_Y->setRange(-1000, 1000);
  ui->moveSpinBox_Y->setValue(0);

  connect(ui->rotate_z, &QSlider::valueChanged, ui->rotate_spinBox_Z,
          &QSpinBox::setValue);
  connect(ui->rotate_spinBox_Z, QOverload<int>::of(&QSpinBox::valueChanged),
          ui->rotate_z, &QSlider::setValue);
  ui->rotate_z->setRange(-360, 360);
  ui->moveSpinBox_Z->setRange(-1000, 1000);
  ui->moveSpinBox_Z->setValue(0);

  connect(ui->LineWidth_Slider, &QSlider::valueChanged, ui->LineWidth_SpinBox,
          &QSpinBox::setValue);
  connect(ui->LineWidth_SpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
          ui->LineWidth_Slider, &QSlider::setValue);
  ui->LineWidth_Slider->setRange(1, 10);
  ui->LineWidth_SpinBox->setRange(1, 10);

  connect(ui->vertexSize_Slider, &QSlider::valueChanged, ui->vertexSize_SpinBox,
          &QSpinBox::setValue);
  connect(ui->vertexSize_SpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
          ui->vertexSize_Slider, &QSlider::setValue);
  ui->vertexSize_Slider->setRange(1, 10);
  ui->vertexSize_SpinBox->setRange(1, 10);

  ui->rotate_spinBox_X->setRange(-360, 360);
  ui->rotate_spinBox_X->setValue(0);

  ui->rotate_spinBox_Y->setRange(-360, 360);
  ui->rotate_spinBox_Y->setValue(0);

  ui->rotate_spinBox_Z->setRange(-360, 360);
  ui->rotate_spinBox_Z->setValue(0);
}

void Viewer::SetTheme() {
  QApplication::setStyle(QStyleFactory::create("Fusion"));
  QPalette darkPalette;
  darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
  darkPalette.setColor(QPalette::WindowText, Qt::white);
  darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
  darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
  darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
  darkPalette.setColor(QPalette::ToolTipText, Qt::white);
  darkPalette.setColor(QPalette::Text, Qt::white);
  darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
  darkPalette.setColor(QPalette::ButtonText, Qt::white);
  darkPalette.setColor(QPalette::BrightText, Qt::red);
  darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
  darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
  darkPalette.setColor(QPalette::HighlightedText, Qt::black);
  QApplication::setPalette(darkPalette);
}

void Viewer::SaveSettings() {
  settings.setValue("projection", ui->switch_projection->currentIndex());
  settings.setValue("line type", ui->switch_line_type->currentIndex());
  settings.setValue("line color", ui->objWidget->GetColorLine());
  settings.setValue("line width", ui->LineWidth_SpinBox->value());
  settings.setValue("point type", ui->switch_type_vertex->currentIndex());
  settings.setValue("point color", ui->objWidget->GetColorPoint());
  settings.setValue("point width", ui->vertexSize_SpinBox->value());
  settings.setValue("background color", ui->objWidget->GetColorBg());
}

void Viewer::LoadSettings() {
  QString settingsFilePath = settings.fileName();
  QFile file(settingsFilePath);
  if (file.exists()) {
    ui->switch_projection->setCurrentIndex(
        settings.value("projection").toInt());
    ui->switch_line_type->setCurrentIndex(settings.value("line type").toInt());
    ui->objWidget->SetColorLine(settings.value("line color").value<QColor>());
    ui->LineWidth_SpinBox->setValue(settings.value("line width").toInt());
    ui->switch_type_vertex->setCurrentIndex(
        settings.value("point type").toInt());
    ui->objWidget->SetColorPoint(settings.value("point color").value<QColor>());
    ui->vertexSize_SpinBox->setValue(settings.value("point width").toInt());
    ui->objWidget->SetColorBg(
        settings.value("background color").value<QColor>());
  }
}

void Viewer::OnPushButtonOpenObjClicked() {
  QString filepath = QFileDialog::getOpenFileName(
      this, tr("Open File"), QDir::homePath(), tr("OBJ files (*.obj)"));
  if (!filepath.isEmpty()) {
    QFileInfo fileInfo(filepath);
    auto stat = ui->objWidget->Open(filepath);
    if (stat != Obj::Status::noExc) {
      QMessageBox::critical(this, "Error",
                            QStringList({"No errors occurred", "Invalid file",
                                         "No obj file to open"})[short(stat)]);
    }
    ui->label_file_name->setText("Название файла: " + fileInfo.fileName());
    ui->label_vertex_am->setText(
        "Количество вершин: " +
        QString::number(ui->objWidget->GetVertexCount()));
    ui->label_facets_am->setText(
        "Количество ребер: " + QString::number(ui->objWidget->GetFacetCount()));
  }
}

void Viewer::OnBgColorClicked() {
  QColor color = QColorDialog::getColor(QColor(0.0, 0.0, 0.0, 0));
  if (color.isValid()) {
    ui->objWidget->SetColorBg(color);
  }
}

void Viewer::OnSwitchLineTypeCurrentIndexChanged(int index) {
  ui->objWidget->SetLineType(index);
}

void Viewer::OnSwitchProjectionCurrentIndexChanged(int index) {
  ui->objWidget->SetProjectionType(index);
}

void Viewer::OnLineWidthSpinBoxValueChanged(int arg1) {
  ui->objWidget->SetLineSize(static_cast<float>(arg1));
}

void Viewer::OnSwitchTypeVertexCurrentIndexChanged(int index) {
  ui->objWidget->SetPointType(index);
}

void Viewer::OnVertexSizeSpinBoxValueChanged(int arg1) {
  ui->objWidget->SetPointSize(static_cast<float>(arg1));
}

void Viewer::OnLineColorClicked() {
  QColor color = QColorDialog::getColor(QColor(0.0, 0.0, 0.0, 0));
  if (color.isValid()) {
    ui->objWidget->SetColorLine(color);
  }
}

void Viewer::OnVertexColorClicked() {
  QColor color = QColorDialog::getColor(QColor(0.0, 0.0, 0.0, 0));
  if (color.isValid()) {
    ui->objWidget->SetColorPoint(color);
  }
}

void Viewer::OnZoomSpinBoxValueChanged(double value) {
  ui->objWidget->Zoom(static_cast<float>(value));
}

void Viewer::OnMoveSpinBoxXValueChanged(int value) {
  ui->objWidget->Move(static_cast<float>(value), 0);
}

void Viewer::OnMoveSpinBoxYValueChanged(int value) {
  ui->objWidget->Move(static_cast<float>(value), 1);
}

void Viewer::OnMoveSpinBoxZValueChanged(int value) {
  ui->objWidget->Move(static_cast<float>(value), 2);
}

void Viewer::OnRotateSpinBoxXValueChanged(int value) {
  ui->objWidget->Rotate(static_cast<float>(value), 0);
}

void Viewer::OnRotateSpinBoxYValueChanged(int value) {
  ui->objWidget->Rotate(static_cast<float>(value), 1);
}

void Viewer::OnRotateSpinBoxZValueChanged(int value) {
  ui->objWidget->Rotate(static_cast<float>(value), 2);
}

void Viewer::OnScreenButtonClicked() {
  const QRect rect(0, 0, ui->objWidget->width(), ui->objWidget->height());
  QPixmap pixmap = ui->objWidget->grab(rect);

  const QString format = "png";
  QString savePath =
      QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
  if (savePath.isEmpty()) {
    savePath = QDir::currentPath();
  }
  savePath += tr("/screenshot.") + format;
  QFileDialog fileDialog(this, tr("Save As"), savePath);
  fileDialog.setAcceptMode(QFileDialog::AcceptSave);
  fileDialog.setFileMode(QFileDialog::AnyFile);
  fileDialog.setDirectory(savePath);

  QStringList mimeTypes;
  const QList<QByteArray> baMimeTypes = QImageWriter::supportedMimeTypes();
  for (const QByteArray& bf : baMimeTypes) {
    mimeTypes.append(QLatin1String(bf));
  }
  fileDialog.setMimeTypeFilters(mimeTypes);
  fileDialog.selectMimeTypeFilter("image/" + format);
  fileDialog.setDefaultSuffix(format);
  if (fileDialog.exec() != QDialog::Accepted) {
    return;
  }
  const QString fileName = fileDialog.selectedFiles().first();
  if (!pixmap.save(fileName)) {
    QMessageBox::warning(this, tr("Save Error"),
                         tr("The image could not be saved to \"%1\".")
                             .arg(QDir::toNativeSeparators(fileName)));
  }
}

void Viewer::OnResetClicked() {
  ui->switch_projection->setCurrentIndex(0);
  ui->switch_line_type->setCurrentIndex(0);
  ui->objWidget->SetColorLine(QColor::fromRgbF(0.7f, 0.7f, 0.7f));
  ui->LineWidth_SpinBox->setValue(0);
  ui->switch_type_vertex->setCurrentIndex(0);
  ui->objWidget->SetColorPoint(QColor::fromRgbF(0.7f, 0.7f, 0.7f));
  ui->vertexSize_SpinBox->setValue(0);
  ui->objWidget->SetColorBg(QColor(Qt::black));
}

void Viewer::OnGifButtonClicked() {
  auto gif = new GifMaker(ui->objWidget->GetFramebuffer());
  QObject::connect(gif, &GifMaker::MakinGif, ui->objWidget,
                   &Obj::Loader::UpdateFramebuffer);
  QObject::connect(gif, &GifMaker::GifDone, gif, &GifMaker::quit);
  QObject::connect(gif, &GifMaker::GifDone, gif, &GifMaker::deleteLater);
  gif->start();
}

void Viewer::OnComboBoxCurrentIndexChanged(int index) {
  ui->objWidget->SetModelViewType(index);
}
