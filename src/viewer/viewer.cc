#include "viewer.h"

#include <QImageWriter>
#include <QMessageBox>
#include <QStandardPaths>
#include <QStyleFactory>

#include "../util/gif_maker.h"
#include "./ui_viewer.h"

namespace obj {

Viewer::Viewer(QWidget* parent)
    : QMainWindow(parent),
      ui_(new Ui::Viewer),
      settings_("Winfordt", "ObjViewer") {
  ui_->setupUi(this);
  SetTheme();
  Init();
  LoadSettings();
}

Viewer::~Viewer() {
  SaveSettings();
  delete ui_;
}

void Viewer::Init() {
  connect(ui_->pushbutton_open_file, SIGNAL(clicked()), this,
          SLOT(OnPushButtonOpenFileClicked()));
  connect(ui_->combo_box_projection, QOverload<int>::of(&QComboBox::currentIndexChanged), ui_->obj_widget, &Loader::SetProjectionType);
  connect(ui_->combo_box_view_type, QOverload<int>::of(&QComboBox::currentIndexChanged), ui_->obj_widget, &Loader::SetViewType);
  connect(ui_->combo_box_edge_type, QOverload<int>::of(&QComboBox::currentIndexChanged), ui_->obj_widget, &Loader::SetEdgeType);
  connect(ui_->spin_box_edge_size, QOverload<int>::of(&QSpinBox::valueChanged), ui_->obj_widget, &Loader::SetEdgeSize);
  connect(ui_->combo_box_type_vertex, QOverload<int>::of(&QComboBox::currentIndexChanged), ui_->obj_widget, &Loader::SetVertexType);
  connect(ui_->spin_box_vertex_size, QOverload<int>::of(&QSpinBox::valueChanged), ui_->obj_widget, &Loader::SetVertexSize);
  connect(ui_->pushbutton_bg_color, SIGNAL(clicked()), this, SLOT(OnPushButtonBgColorClicked()));
  connect(ui_->puhsbutton_edge_color, SIGNAL(clicked()), this, SLOT(OnPushButtonEdgeColorClicked()));
  connect(ui_->pushbutton_vertex_color, SIGNAL(clicked()), this,
          SLOT(OnPushButtonVertexColorClicked()));
  connect(ui_->pushbutton_reset, SIGNAL(clicked()), this, SLOT(OnPushButtonResetClicked()));
  connect(ui_->pushbutton_gif, SIGNAL(clicked()), this, SLOT(OnPushButtonGifClicked()));
  connect(ui_->d_spin_box_scale, QOverload<double>::of(&QDoubleSpinBox::valueChanged), ui_->obj_widget, &Loader::Scale);
  connect(ui_->d_spin_box_move_x, SIGNAL(valueChanged(double)), this,
          SLOT(OnDoubleSpinBoxMoveValueChanged(double)));
  connect(ui_->d_spin_box_move_y, SIGNAL(valueChanged(double)), this,
          SLOT(OnDoubleSpinBoxMoveValueChanged(double)));
  connect(ui_->d_spin_box_move_z, SIGNAL(valueChanged(double)), this,
          SLOT(OnDoubleSpinBoxMoveValueChanged(double)));
  connect(ui_->spin_box_rotate_x, SIGNAL(valueChanged(int)), this,
          SLOT(OnSpinBoxRotateValueChanged(int)));
  connect(ui_->spin_box_rotate_y, SIGNAL(valueChanged(int)), this,
          SLOT(OnSpinBoxRotateValueChanged(int)));
  connect(ui_->spin_box_rotate_z, SIGNAL(valueChanged(int)), this,
          SLOT(OnSpinBoxRotateValueChanged(int)));
  connect(ui_->pushbutton_screen, SIGNAL(clicked()), this,
          SLOT(OnPushButtonScreenClicked()));
  connect(ui_->slider_rotate_x, &QSlider::valueChanged, ui_->spin_box_rotate_x,
          &QSpinBox::setValue);
  connect(ui_->spin_box_rotate_x, QOverload<int>::of(&QSpinBox::valueChanged),
          ui_->slider_rotate_x, &QSlider::setValue);
  connect(ui_->slider_rotate_y, &QSlider::valueChanged, ui_->spin_box_rotate_y,
          &QSpinBox::setValue);
  connect(ui_->spin_box_rotate_y, QOverload<int>::of(&QSpinBox::valueChanged),
          ui_->slider_rotate_y, &QSlider::setValue);
  connect(ui_->slider_rotate_z, &QSlider::valueChanged, ui_->spin_box_rotate_z,
          &QSpinBox::setValue);
  connect(ui_->spin_box_rotate_z, QOverload<int>::of(&QSpinBox::valueChanged),
          ui_->slider_rotate_z, &QSlider::setValue);
}

void Viewer::SetTheme() {
  QApplication::setStyle(QStyleFactory::create("Fusion"));
  QPalette darkPalette;
  darkPalette.setColor(QPalette::Window, QColor(36, 36, 36));
  darkPalette.setColor(QPalette::WindowText, Qt::white);
  darkPalette.setColor(QPalette::Base, QColor(53, 53, 53));
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
  settings_.setValue("projection", ui_->combo_box_projection->currentIndex());
  settings_.setValue("edge type", ui_->combo_box_edge_type->currentIndex());
  settings_.setValue("edge color", ui_->obj_widget->GetEdgeColor());
  settings_.setValue("edge size", ui_->spin_box_edge_size->value());
  settings_.setValue("vertex type", ui_->combo_box_type_vertex->currentIndex());
  settings_.setValue("vertex color", ui_->obj_widget->GetVertexColor());
  settings_.setValue("vertex size", ui_->spin_box_vertex_size->value());
  settings_.setValue("background color", ui_->obj_widget->GetBgColor());
}

void Viewer::LoadSettings() {
  QString settingsFilePath = settings_.fileName();
  QFile file(settingsFilePath);
  if (file.exists()) {
    ui_->combo_box_projection->setCurrentIndex(
        settings_.value("projection").toInt());
    ui_->combo_box_edge_type->setCurrentIndex(settings_.value("edge type").toInt());
    ui_->obj_widget->SetEdgeColor(settings_.value("edge color").value<QColor>());
    ui_->spin_box_edge_size->setValue(settings_.value("edge size").toInt());
    ui_->combo_box_type_vertex->setCurrentIndex(
        settings_.value("point type").toInt());
    ui_->obj_widget->SetVertexColor(settings_.value("vertex color").value<QColor>());
    ui_->spin_box_vertex_size->setValue(settings_.value("vertex size").toInt());
    ui_->obj_widget->SetBgColor(
        settings_.value("background color").value<QColor>());
  }
}

void Viewer::OnPushButtonOpenFileClicked() {
  QString filepath = QFileDialog::getOpenFileName(
      this, tr("Open File"), QDir::homePath(), tr("OBJ files (*.obj)"));
  if (filepath.isEmpty()) {
      return;
  }
  QFileInfo fileInfo(filepath);
  auto stat = ui_->obj_widget->Open(filepath);
  if (stat != Status::noExc) {
    QMessageBox::critical(this, "Error",
                          QStringList({"No errors occurred", "Invalid file",
                                       "No obj file to open"})[short(stat)]);
  }
  ui_->label_file_name_text->setText(fileInfo.fileName());
  ui_->label_vertex_am_int->setText(QString::number(ui_->obj_widget->GetVertexCount()));
  ui_->label_facets_amount_int->setText(QString::number(ui_->obj_widget->GetFacetCount()));
  ui_->label_edge_amount_int->setText(QString::number(ui_->obj_widget->GetEdgeCount()));
}

void Viewer::OnPushButtonBgColorClicked() {
  QColor color = QColorDialog::getColor(QColor(0.0, 0.0, 0.0, 0));
  if (color.isValid()) {
    ui_->obj_widget->SetBgColor(color);
  }
}

void Viewer::OnPushButtonEdgeColorClicked() {
  QColor color = QColorDialog::getColor(QColor(0.0, 0.0, 0.0, 0));
  if (color.isValid()) {
    ui_->obj_widget->SetEdgeColor(color);
  }
}

void Viewer::OnPushButtonVertexColorClicked() {
  QColor color = QColorDialog::getColor(QColor(0.0, 0.0, 0.0, 0));
  if (color.isValid()) {
    ui_->obj_widget->SetVertexColor(color);
  }
}

void Viewer::OnDoubleSpinBoxMoveValueChanged(double value) {
  auto move_spin_box = dynamic_cast<QDoubleSpinBox*>(sender());
  ui_->obj_widget->Move(value, ui_->vertical_layout_spin_boxes_move->indexOf(move_spin_box));
}

void Viewer::OnSpinBoxRotateValueChanged(int value) {
  auto rotate_spin_box = dynamic_cast<QSpinBox*>(sender());
  ui_->obj_widget->Rotate(value, ui_->vertical_layout_rotate_spin_boxes->indexOf(rotate_spin_box));
}

void Viewer::OnPushButtonScreenClicked() {
  const QRect rect(0, 0, ui_->obj_widget->width(), ui_->obj_widget->height());
  QPixmap pixmap = ui_->obj_widget->grab(rect);
  const QString format = "png";

  QString save_path =
      QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
  if (save_path.isEmpty()) {
    save_path = QDir::currentPath();
  }
  save_path += tr("/screenshot.") + format;

  QFileDialog file_dialog(this, tr("Save As"), save_path);
  file_dialog.setAcceptMode(QFileDialog::AcceptSave);
  file_dialog.setFileMode(QFileDialog::AnyFile);
  file_dialog.setDirectory(save_path);

  QStringList mime_types;
  const QList<QByteArray> ba_mime_types = QImageWriter::supportedMimeTypes();
  for (const QByteArray& bf : ba_mime_types) {
    mime_types.append(QLatin1String(bf));
  }
  file_dialog.setMimeTypeFilters(mime_types);
  file_dialog.selectMimeTypeFilter("image/" + format);
  file_dialog.setDefaultSuffix(format);
  if (file_dialog.exec() != QDialog::Accepted) {
    return;
  }

  const QString file_name = file_dialog.selectedFiles().constFirst();
  if (!pixmap.save(file_name)) {
    QMessageBox::warning(this, tr("Save Error"),
                         tr("The image could not be saved to \"%1\".")
                             .arg(QDir::toNativeSeparators(file_name)));
  }
}

void Viewer::OnPushButtonResetClicked() {
  ui_->combo_box_projection->setCurrentIndex(0);
  ui_->combo_box_edge_type->setCurrentIndex(0);
  ui_->obj_widget->SetEdgeColor(QColor::fromRgbF(0.7f, 0.7f, 0.7f));
  ui_->spin_box_edge_size->setValue(1);
  ui_->combo_box_type_vertex->setCurrentIndex(0);
  ui_->obj_widget->SetVertexColor(QColor::fromRgbF(0.7f, 0.7f, 0.7f));
  ui_->spin_box_vertex_size->setValue(1);
  ui_->obj_widget->SetBgColor(QColor(Qt::black));
}

void Viewer::OnPushButtonGifClicked() {
  const QString format = "gif";
  QString save_path =
      QStandardPaths::writableLocation(QStandardPaths::MoviesLocation);
  if (save_path.isEmpty()) {
    save_path = QDir::currentPath();
  }
  save_path += tr("/gif_image.") + format;

  QFileDialog file_dialog(this, tr("Save As"), save_path);
  file_dialog.setAcceptMode(QFileDialog::AcceptSave);
  file_dialog.setFileMode(QFileDialog::AnyFile);
  file_dialog.setDirectory(save_path);
  file_dialog.setDefaultSuffix(format);

  if (file_dialog.exec() != QDialog::Accepted) {
    return;
  }
  QString filepath = file_dialog.selectedFiles().constFirst();
  auto gif = new GifMaker(ui_->obj_widget->GetFramebuffer(), std::move(filepath));
  connect(gif, &GifMaker::MakinGif, ui_->obj_widget,
                   &Loader::UpdateFramebuffer);
  connect(gif, &GifMaker::GifFailed, this, [this]() {
      QMessageBox::warning(this, "Invalid gif", "Gif making processing is failed");
  });
  connect(gif, &GifMaker::finished, gif, &GifMaker::quit);
  connect(gif, &GifMaker::finished, gif, &GifMaker::deleteLater);
  gif->start();
}

} // namespace obj

