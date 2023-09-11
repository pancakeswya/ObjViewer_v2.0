#include "viewer.h"

#include <QColorDialog>
#include <QFileDialog>
#include <QImageWriter>
#include <QMessageBox>
#include <QStandardPaths>
#include <QStyleFactory>

#include "objviewer/util/gif_maker.h"

namespace objv {

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
  ui_->scroll_area_maps->hide();
  connect(ui_->pushbutton_open_file, SIGNAL(clicked()), this,
          SLOT(OnPushButtonOpenFileClicked()));
  connect(ui_->combo_box_projection,
          QOverload<int>::of(&QComboBox::currentIndexChanged), ui_->obj_loader,
          &Loader::SetProjectionType);
  connect(ui_->combo_box_view_type,
          QOverload<int>::of(&QComboBox::currentIndexChanged), ui_->obj_loader,
          &Loader::SetViewType);
  connect(ui_->combo_box_edge_type,
          QOverload<int>::of(&QComboBox::currentIndexChanged), ui_->obj_loader,
          &Loader::SetEdgeType);
  connect(ui_->spin_box_edge_size, QOverload<int>::of(&QSpinBox::valueChanged),
          ui_->obj_loader, &Loader::SetEdgeSize);
  connect(ui_->combo_box_type_vertex,
          QOverload<int>::of(&QComboBox::currentIndexChanged), ui_->obj_loader,
          &Loader::SetVertexType);
  connect(ui_->spin_box_vertex_size,
          QOverload<int>::of(&QSpinBox::valueChanged), ui_->obj_loader,
          &Loader::SetVertexSize);
  connect(ui_->pushbutton_bg_color, SIGNAL(clicked()), this,
          SLOT(OnPushButtonBgColorClicked()));
  connect(ui_->puhsbutton_edge_color, SIGNAL(clicked()), this,
          SLOT(OnPushButtonEdgeColorClicked()));
  connect(ui_->pushbutton_vertex_color, SIGNAL(clicked()), this,
          SLOT(OnPushButtonVertexColorClicked()));
  connect(ui_->pushbutton_reset, SIGNAL(clicked()), this,
          SLOT(OnPushButtonResetClicked()));
  connect(ui_->pushbutton_gif, SIGNAL(clicked()), this,
          SLOT(OnPushButtonGifClicked()));
  connect(ui_->d_spin_box_scale,
          QOverload<double>::of(&QDoubleSpinBox::valueChanged), ui_->obj_loader,
          &Loader::Scale);
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
  connect(ui_->d_spin_box_step_scale, SIGNAL(valueChanged(double)), this,
          SLOT(OnDoubleSpinBoxStepScaleValueChanged(double)));
  connect(ui_->d_spin_box_step_move_x, SIGNAL(valueChanged(double)), this,
          SLOT(OnDoubleSpinBoxStepMoveValueChanged(double)));
  connect(ui_->d_spin_box_step_move_y, SIGNAL(valueChanged(double)), this,
          SLOT(OnDoubleSpinBoxStepMoveValueChanged(double)));
  connect(ui_->d_spin_box_step_move_z, SIGNAL(valueChanged(double)), this,
          SLOT(OnDoubleSpinBoxStepMoveValueChanged(double)));
  connect(ui_->combo_box_shading,
          QOverload<int>::of(&QComboBox::currentIndexChanged), ui_->obj_loader,
          &Loader::SetShadingType);
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
  settings_.setValue("edge color", ui_->obj_loader->GetEdgeColor());
  settings_.setValue("edge size", ui_->spin_box_edge_size->value());
  settings_.setValue("vertex type", ui_->combo_box_type_vertex->currentIndex());
  settings_.setValue("vertex color", ui_->obj_loader->GetVertexColor());
  settings_.setValue("vertex size", ui_->spin_box_vertex_size->value());
  settings_.setValue("background color", ui_->obj_loader->GetBgColor());
}

void Viewer::LoadSettings() {
  QString settingsFilePath = settings_.fileName();
  QFile file(settingsFilePath);
  if (file.exists()) {
    ui_->combo_box_projection->setCurrentIndex(
        settings_.value("projection").toInt());
    ui_->combo_box_edge_type->setCurrentIndex(
        settings_.value("edge type").toInt());
    ui_->obj_loader->SetEdgeColor(
        settings_.value("edge color").value<QColor>());
    ui_->spin_box_edge_size->setValue(settings_.value("edge size").toInt());
    ui_->combo_box_type_vertex->setCurrentIndex(
        settings_.value("point type").toInt());
    ui_->obj_loader->SetVertexColor(
        settings_.value("vertex color").value<QColor>());
    ui_->spin_box_vertex_size->setValue(settings_.value("vertex size").toInt());
    ui_->obj_loader->SetBgColor(
        settings_.value("background color").value<QColor>());
  }
}

namespace {

void ClearLayout(QLayout* layout) {
  while (QLayoutItem* item = layout->takeAt(0)) {
    if (QWidget* widget = item->widget()) {
      widget->deleteLater();
    }
    if (QLayout* childLayout = item->layout()) {
      ClearLayout(childLayout);
    }
    delete item;
  }
}

}  // namespace

void Viewer::LoadMaterial(const MaterialData& mtl) {
  auto& layout = ui_->grid_layout_material;
  ClearLayout(layout);
  ui_->scroll_area_maps->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  ui_->scroll_area_maps->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  // set new widgets
  QStringList mtl_ftr = {
      "Ambient: ", "Diffuse: ", "Specular: ", "Emmission: ", "Opacity: ",
      "Shiness: ", "Map_Ka: ",  "Map_Kd: ",   "Map_Ks: "};
  for (unsigned int i = 0; i < mtl.size(); ++i) {
    std::array mtl_val = {mtl[i].Ka, mtl[i].Kd, mtl[i].Ks,
                          mtl[i].Ke, &mtl[i].d, &mtl[i].Ns};
    auto layout_mtl = new QGridLayout();
    layout->addLayout(layout_mtl, i, 0);

    QString material_name =
        !mtl[i].name.empty() ? mtl[i].name.data() : "<No material>";
    material_name = "Material name:\n" + material_name;
    auto label_name = new QLabel(material_name);
    label_name->setAlignment(Qt::AlignCenter);
    {
      QFont font("Segoe UI", 10);
      font.setBold(true);
      label_name->setFont(font);
    }
    label_name->setMargin(label_name->margin() + 2);
    layout_mtl->addWidget(label_name, 0, 0, 1, 2);
    for (unsigned int j = 0; j < 6; ++j) {
      QString test_k = mtl_ftr[j] + QString::number(mtl_val[j][0]);
      if (j < 4) {
        test_k += " " + QString::number(mtl_val[j][1]) + " " +
                  QString::number(mtl_val[j][2]);
      }
      auto label_k = new QLabel(test_k);
      label_k->setAlignment(Qt::AlignCenter);
      layout_mtl->addWidget(label_k, j + 1, 0, 1, 2);
    }
    auto label_maps = new QLabel("Maps/Textures: ");
    label_maps->setAlignment(Qt::AlignCenter);
    label_maps->setMargin(label_maps->margin() + 4);
    layout_mtl->addWidget(label_maps, 7, 0, 1, 2);
    std::array map_path = {mtl[i].map_ka, mtl[i].map_kd, mtl[i].map_ks};
    for (unsigned int j = 8, k = 0; j < 17; ++j) {
      QString has_texture = (map_path[k].empty()) ? "No texture" : "Textured";

      auto label_map = new QLabel(mtl_ftr[k++]);
      auto label_map_val = new QLabel(has_texture);
      auto button_uv = new QPushButton("Save UV");
      auto button_load = new QPushButton("Load texture");
      auto button_unload = new QPushButton("Unload texture");
      label_map->setAlignment(Qt::AlignCenter);
      label_map_val->setAlignment(Qt::AlignCenter);

      layout_mtl->addWidget(label_map, j, 0, Qt::AlignCenter);
      layout_mtl->addWidget(label_map_val, j, 1, Qt::AlignCenter);
      layout_mtl->addWidget(button_uv, ++j, 0);
      layout_mtl->addWidget(button_load, j, 1);
      layout_mtl->addWidget(button_unload, ++j, 0, 1, 2);
      connect(button_load, &QPushButton::clicked, this,
              [this, i, k, label_map_val]() {
                QString filepath = QFileDialog::getOpenFileName(
                    this, tr("Load texture"), QDir::homePath(),
                    tr("PNG files (*.png)"));
                if (filepath.isEmpty()) {
                  return;
                }
                ui_->obj_loader->ResetTexture(i, k - 1, filepath);
                if (label_map_val->text()[0] == 'N') {
                  label_map_val->setText("Textured");
                }
              });
      connect(button_unload, &QPushButton::clicked, this,
              [this, i, k, label_map_val]() {
                ui_->obj_loader->ResetTexture(i, k - 1);
                label_map_val->setText("No texture");
              });
      connect(button_uv, &QPushButton::clicked, this,
              [this, i, texpath = map_path[k - 1]]() {
                QString filepath = QFileDialog::getSaveFileName(
                    this, tr("Save UV-map"), QDir::homePath(),
                    tr("PNG files (*.png)"));
                if (filepath.isEmpty()) {
                  return;
                }
                ui_->obj_loader->SaveUvMap(i, texpath, filepath);
              });
    }
  }
}

void Viewer::OnPushButtonOpenFileClicked() {
  QString filepath = QFileDialog::getOpenFileName(
      this, tr("Open File"), QDir::homePath(), tr("OBJ files (*.obj)"));
  if (filepath.isEmpty()) {
    return;
  }
  QFileInfo fileInfo(filepath);
  auto stat = ui_->obj_loader->Open(filepath);
  if (stat != Status::kNoExc) {
    QMessageBox::critical(this, "Error",
                          QStringList({"Invalid file",
                                       "No obj file to open"})[int(stat) - 1]);
  }
  ui_->label_file_name_text->setText(fileInfo.fileName());
  ui_->label_vertex_am_int->setText(
      QString::number(ui_->obj_loader->GetVertexCount()));
  ui_->label_facets_amount_int->setText(
      QString::number(ui_->obj_loader->GetFacetCount()));
  ui_->label_edge_amount_int->setText(
      QString::number(ui_->obj_loader->GetEdgeCount()));
  ui_->scroll_area_maps->show();
  LoadMaterial(ui_->obj_loader->GetMaterialData());
}

void Viewer::OnPushButtonBgColorClicked() {
  QColor color = QColorDialog::getColor(QColor(0.0, 0.0, 0.0, 0));
  if (color.isValid()) {
    ui_->obj_loader->SetBgColor(color);
  }
}

void Viewer::OnPushButtonEdgeColorClicked() {
  QColor color = QColorDialog::getColor(QColor(0.0, 0.0, 0.0, 0));
  if (color.isValid()) {
    ui_->obj_loader->SetEdgeColor(color);
  }
}

void Viewer::OnPushButtonVertexColorClicked() {
  QColor color = QColorDialog::getColor(QColor(0.0, 0.0, 0.0, 0));
  if (color.isValid()) {
    ui_->obj_loader->SetVertexColor(color);
  }
}

void Viewer::OnDoubleSpinBoxStepScaleValueChanged(double new_step) {
  ui_->d_spin_box_scale->setSingleStep(new_step);
}

void Viewer::OnDoubleSpinBoxStepMoveValueChanged(double new_step) {
  auto spin_box_step_move = dynamic_cast<QDoubleSpinBox*>(sender());
  int index_step_move =
      ui_->vertical_layout_d_spin_boxes_step_move->indexOf(spin_box_step_move);
  auto spin_box_move = dynamic_cast<QDoubleSpinBox*>(
      ui_->vertical_layout_spin_boxes_move->itemAt(index_step_move)->widget());
  spin_box_move->setSingleStep(new_step);
}

void Viewer::OnDoubleSpinBoxMoveValueChanged(double value) {
  auto move_spin_box = dynamic_cast<QDoubleSpinBox*>(sender());
  ui_->obj_loader->Move(
      value, ui_->vertical_layout_spin_boxes_move->indexOf(move_spin_box));
}

void Viewer::OnSpinBoxRotateValueChanged(int value) {
  auto rotate_spin_box = dynamic_cast<QSpinBox*>(sender());
  ui_->obj_loader->Rotate(
      value, ui_->vertical_layout_rotate_spin_boxes->indexOf(rotate_spin_box));
}

void Viewer::OnPushButtonScreenClicked() {
  const QRect rect(0, 0, ui_->obj_loader->width(), ui_->obj_loader->height());
  QPixmap pixmap = ui_->obj_loader->grab(rect);
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
  ui_->obj_loader->SetEdgeColor(QColor::fromRgbF(0.7f, 0.7f, 0.7f));
  ui_->spin_box_edge_size->setValue(1);
  ui_->combo_box_type_vertex->setCurrentIndex(0);
  ui_->obj_loader->SetVertexColor(QColor::fromRgbF(0.7f, 0.7f, 0.7f));
  ui_->spin_box_vertex_size->setValue(1);
  ui_->obj_loader->SetBgColor(QColor(Qt::black));
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
  auto gif = new GifMaker(ui_->obj_loader->GetFrame(), std::move(filepath));
  connect(gif, &GifMaker::MakinGif, ui_->obj_loader, &Loader::UpdateFrame);
  connect(gif, &GifMaker::GifFailed, this, [this]() {
    QMessageBox::warning(this, "Invalid gif",
                         "Gif making processing is failed");
  });
  connect(gif, &GifMaker::finished, gif, &GifMaker::quit);
  connect(gif, &GifMaker::finished, gif, &GifMaker::deleteLater);
  gif->start();
}

}  // namespace objv
