/********************************************************************************
** Form generated from reading UI file 'viewer.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWER_H
#define UI_VIEWER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "obj_viewer/viewer/loader.h"

namespace objv {

class Ui_Viewer
{
public:
    QWidget *central_widget;
    QHBoxLayout *horizontalLayout;
    Loader *obj_loader;
    QTabWidget *tab_widget;
    QWidget *tab_general;
    QGridLayout *gridLayout_2;
    QGridLayout *tab_general_grid_layout;
    QSpacerItem *horizontal_spacer_general_left;
    QFrame *frame_edge;
    QGridLayout *gridLayout_12;
    QLabel *label_edge;
    QLabel *label_edge_type;
    QSpinBox *spin_box_edge_size;
    QLabel *label_edge_size;
    QComboBox *combo_box_edge_type;
    QSpacerItem *horizontal_spacer_general_right;
    QPushButton *pushbutton_reset;
    QFrame *frame_color;
    QGridLayout *gridLayout_14;
    QPushButton *pushbutton_vertex_color;
    QPushButton *puhsbutton_edge_color;
    QPushButton *pushbutton_bg_color;
    QLabel *label_color;
    QPushButton *pushbutton_gif;
    QFrame *frame_projection;
    QGridLayout *gridLayout_15;
    QLabel *label_projection;
    QComboBox *combo_box_projection;
    QSpacerItem *vertical_spacer_general_down;
    QPushButton *pushbutton_open_file;
    QFrame *frame_view_type;
    QGridLayout *gridLayout_11;
    QLabel *label_view_type;
    QComboBox *combo_box_view_type;
    QPushButton *pushbutton_screen;
    QFrame *frame_vertex;
    QGridLayout *gridLayout_13;
    QLabel *label_vertex_type;
    QLabel *label_vertex_size;
    QComboBox *combo_box_type_vertex;
    QLabel *label_vertex;
    QSpinBox *spin_box_vertex_size;
    QFrame *frame;
    QGridLayout *gridLayout_3;
    QLabel *label_shading;
    QComboBox *combo_box_shading;
    QFrame *frame_info;
    QGridLayout *gridLayout_8;
    QLabel *label_edge_amount_int;
    QLabel *label_edge_amount;
    QLabel *label_facets_amount_int;
    QLabel *label_file_name_text;
    QLabel *label_file_name;
    QLabel *label_vertex_am;
    QLabel *label_facets_am;
    QLabel *label_vertex_am_int;
    QWidget *tab_transformation;
    QGridLayout *gridLayout_7;
    QSpacerItem *vertical_spacer_transformation_down;
    QGridLayout *grid_layout_transformation;
    QFrame *frame_move;
    QGridLayout *gridLayout_17;
    QVBoxLayout *vertical_layout_spin_boxes_move;
    QDoubleSpinBox *d_spin_box_move_x;
    QDoubleSpinBox *d_spin_box_move_y;
    QDoubleSpinBox *d_spin_box_move_z;
    QLabel *label_move_z;
    QLabel *label_value_move;
    QLabel *label_move_y;
    QLabel *label_move;
    QLabel *label_step_move;
    QLabel *label_move_x;
    QVBoxLayout *vertical_layout_d_spin_boxes_step_move;
    QDoubleSpinBox *d_spin_box_step_move_x;
    QDoubleSpinBox *d_spin_box_step_move_y;
    QDoubleSpinBox *d_spin_box_step_move_z;
    QFrame *frame_rotate;
    QGridLayout *gridLayout_16;
    QLabel *label_rotate;
    QVBoxLayout *vertical_layout_rotate_spin_boxes;
    QSpinBox *spin_box_rotate_x;
    QSpinBox *spin_box_rotate_y;
    QSpinBox *spin_box_rotate_z;
    QVBoxLayout *vertical_layout_rotate_sliders;
    QSlider *slider_rotate_x;
    QSlider *slider_rotate_y;
    QSlider *slider_rotate_z;
    QVBoxLayout *vertical_layout_rotate_labels;
    QLabel *label_rotate_x;
    QLabel *label_rotate_y;
    QLabel *label_rotate_z;
    QLabel *label_value_rotate;
    QLabel *label_range_rotate;
    QFrame *frame_scale;
    QGridLayout *gridLayout_18;
    QLabel *label_scale;
    QDoubleSpinBox *d_spin_box_step_scale;
    QDoubleSpinBox *d_spin_box_scale;
    QLabel *label_step_scale;
    QLabel *label_value_scale;
    QWidget *tab_material;
    QGridLayout *gridLayout;
    QSpacerItem *vertical_spacer_material_botom;
    QScrollArea *scroll_area_maps;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_4;
    QGridLayout *grid_layout_material;
    QLabel *label_properties;

    void setupUi(QMainWindow *obj__Viewer)
    {
        if (obj__Viewer->objectName().isEmpty())
            obj__Viewer->setObjectName(QString::fromUtf8("obj__Viewer"));
        obj__Viewer->resize(1299, 725);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/ObjViewer_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        obj__Viewer->setWindowIcon(icon);
        central_widget = new QWidget(obj__Viewer);
        central_widget->setObjectName(QString::fromUtf8("central_widget"));
        central_widget->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout = new QHBoxLayout(central_widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        obj_loader = new Loader(central_widget);
        obj_loader->setObjectName(QString::fromUtf8("obj_loader"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(obj_loader->sizePolicy().hasHeightForWidth());
        obj_loader->setSizePolicy(sizePolicy);
        obj_loader->setMinimumSize(QSize(774, 0));

        horizontalLayout->addWidget(obj_loader);

        tab_widget = new QTabWidget(central_widget);
        tab_widget->setObjectName(QString::fromUtf8("tab_widget"));
        tab_widget->setStyleSheet(QString::fromUtf8(""));
        tab_widget->setTabPosition(QTabWidget::West);
        tab_general = new QWidget();
        tab_general->setObjectName(QString::fromUtf8("tab_general"));
        gridLayout_2 = new QGridLayout(tab_general);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        tab_general_grid_layout = new QGridLayout();
        tab_general_grid_layout->setObjectName(QString::fromUtf8("tab_general_grid_layout"));
        horizontal_spacer_general_left = new QSpacerItem(4, 4, QSizePolicy::Fixed, QSizePolicy::Minimum);

        tab_general_grid_layout->addItem(horizontal_spacer_general_left, 0, 0, 12, 1);

        frame_edge = new QFrame(tab_general);
        frame_edge->setObjectName(QString::fromUtf8("frame_edge"));
        frame_edge->setAutoFillBackground(true);
        frame_edge->setFrameShape(QFrame::NoFrame);
        frame_edge->setFrameShadow(QFrame::Raised);
        gridLayout_12 = new QGridLayout(frame_edge);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        gridLayout_12->setContentsMargins(7, 7, 7, 7);
        label_edge = new QLabel(frame_edge);
        label_edge->setObjectName(QString::fromUtf8("label_edge"));
        QFont font;
        font.setPointSize(10);
        label_edge->setFont(font);
        label_edge->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_edge, 0, 0, 1, 3);

        label_edge_type = new QLabel(frame_edge);
        label_edge_type->setObjectName(QString::fromUtf8("label_edge_type"));
        label_edge_type->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_edge_type, 1, 0, 1, 1);

        spin_box_edge_size = new QSpinBox(frame_edge);
        spin_box_edge_size->setObjectName(QString::fromUtf8("spin_box_edge_size"));
        sizePolicy.setHeightForWidth(spin_box_edge_size->sizePolicy().hasHeightForWidth());
        spin_box_edge_size->setSizePolicy(sizePolicy);
        spin_box_edge_size->setStyleSheet(QString::fromUtf8("QSpinBox {\n"
"  border: 2px solid rgb(76,76,76);\n"
"  border-radius: 5px;\n"
"  background-color: rgb(96, 96, 96);\n"
"  color: rgb(255,255,255);\n"
"}\n"
"\n"
"QSpinBox::down-button  {\n"
"  subcontrol-origin: margin;\n"
"  subcontrol-position: center left;\n"
"  image: url(:/images/left_arrow.png);\n"
"  background-color: rgb(76,76,76);\n"
"  left: 2px;\n"
"  height: 22px;\n"
"  width: 12px;\n"
"}\n"
"\n"
"QSpinBox::up-button  {\n"
"  subcontrol-origin: margin;\n"
"  subcontrol-position: center right;\n"
"  image: url(:/images/right_arrow.png);\n"
"  background-color: rgb(76,76,76);\n"
"  right: 2px;\n"
"  height: 22px;\n"
"  width:12px;\n"
"}"));
        spin_box_edge_size->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(spin_box_edge_size, 2, 1, 1, 2);

        label_edge_size = new QLabel(frame_edge);
        label_edge_size->setObjectName(QString::fromUtf8("label_edge_size"));
        label_edge_size->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_edge_size, 2, 0, 1, 1);

        combo_box_edge_type = new QComboBox(frame_edge);
        combo_box_edge_type->addItem(QString());
        combo_box_edge_type->addItem(QString());
        combo_box_edge_type->setObjectName(QString::fromUtf8("combo_box_edge_type"));

        gridLayout_12->addWidget(combo_box_edge_type, 1, 1, 1, 2);


        tab_general_grid_layout->addWidget(frame_edge, 6, 1, 2, 2);

        horizontal_spacer_general_right = new QSpacerItem(6, 6, QSizePolicy::Fixed, QSizePolicy::Minimum);

        tab_general_grid_layout->addItem(horizontal_spacer_general_right, 0, 5, 12, 1);

        pushbutton_reset = new QPushButton(tab_general);
        pushbutton_reset->setObjectName(QString::fromUtf8("pushbutton_reset"));
        pushbutton_reset->setStyleSheet(QString::fromUtf8("background-color: rgb(20, 99, 224);\n"
"border-radius: 15%;\n"
"padding: 3px;\n"
""));

        tab_general_grid_layout->addWidget(pushbutton_reset, 9, 1, 1, 4);

        frame_color = new QFrame(tab_general);
        frame_color->setObjectName(QString::fromUtf8("frame_color"));
        frame_color->setAutoFillBackground(true);
        frame_color->setStyleSheet(QString::fromUtf8(""));
        frame_color->setFrameShape(QFrame::NoFrame);
        frame_color->setFrameShadow(QFrame::Raised);
        gridLayout_14 = new QGridLayout(frame_color);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        gridLayout_14->setContentsMargins(7, 7, 7, 7);
        pushbutton_vertex_color = new QPushButton(frame_color);
        pushbutton_vertex_color->setObjectName(QString::fromUtf8("pushbutton_vertex_color"));
        pushbutton_vertex_color->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_14->addWidget(pushbutton_vertex_color, 2, 0, 1, 1);

        puhsbutton_edge_color = new QPushButton(frame_color);
        puhsbutton_edge_color->setObjectName(QString::fromUtf8("puhsbutton_edge_color"));

        gridLayout_14->addWidget(puhsbutton_edge_color, 2, 1, 1, 1);

        pushbutton_bg_color = new QPushButton(frame_color);
        pushbutton_bg_color->setObjectName(QString::fromUtf8("pushbutton_bg_color"));

        gridLayout_14->addWidget(pushbutton_bg_color, 1, 0, 1, 2);

        label_color = new QLabel(frame_color);
        label_color->setObjectName(QString::fromUtf8("label_color"));
        label_color->setFont(font);
        label_color->setAlignment(Qt::AlignCenter);

        gridLayout_14->addWidget(label_color, 0, 0, 1, 2);


        tab_general_grid_layout->addWidget(frame_color, 8, 1, 1, 4);

        pushbutton_gif = new QPushButton(tab_general);
        pushbutton_gif->setObjectName(QString::fromUtf8("pushbutton_gif"));
        pushbutton_gif->setMaximumSize(QSize(16777215, 16777215));
        pushbutton_gif->setFont(font);

        tab_general_grid_layout->addWidget(pushbutton_gif, 1, 3, 1, 2);

        frame_projection = new QFrame(tab_general);
        frame_projection->setObjectName(QString::fromUtf8("frame_projection"));
        frame_projection->setAutoFillBackground(true);
        frame_projection->setFrameShape(QFrame::NoFrame);
        frame_projection->setFrameShadow(QFrame::Raised);
        gridLayout_15 = new QGridLayout(frame_projection);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        gridLayout_15->setContentsMargins(7, 7, 7, 7);
        label_projection = new QLabel(frame_projection);
        label_projection->setObjectName(QString::fromUtf8("label_projection"));
        QFont font1;
        font1.setPointSize(9);
        label_projection->setFont(font1);
        label_projection->setAlignment(Qt::AlignCenter);

        gridLayout_15->addWidget(label_projection, 0, 0, 1, 1);

        combo_box_projection = new QComboBox(frame_projection);
        combo_box_projection->addItem(QString());
        combo_box_projection->addItem(QString());
        combo_box_projection->setObjectName(QString::fromUtf8("combo_box_projection"));
        combo_box_projection->setStyleSheet(QString::fromUtf8(""));

        gridLayout_15->addWidget(combo_box_projection, 0, 1, 1, 1);


        tab_general_grid_layout->addWidget(frame_projection, 3, 1, 1, 4);

        vertical_spacer_general_down = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        tab_general_grid_layout->addItem(vertical_spacer_general_down, 11, 1, 1, 4);

        pushbutton_open_file = new QPushButton(tab_general);
        pushbutton_open_file->setObjectName(QString::fromUtf8("pushbutton_open_file"));

        tab_general_grid_layout->addWidget(pushbutton_open_file, 0, 1, 1, 4);

        frame_view_type = new QFrame(tab_general);
        frame_view_type->setObjectName(QString::fromUtf8("frame_view_type"));
        frame_view_type->setAutoFillBackground(true);
        frame_view_type->setFrameShape(QFrame::NoFrame);
        frame_view_type->setFrameShadow(QFrame::Raised);
        gridLayout_11 = new QGridLayout(frame_view_type);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        gridLayout_11->setContentsMargins(7, 7, 7, 7);
        label_view_type = new QLabel(frame_view_type);
        label_view_type->setObjectName(QString::fromUtf8("label_view_type"));
        label_view_type->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(label_view_type, 0, 0, 1, 1);

        combo_box_view_type = new QComboBox(frame_view_type);
        combo_box_view_type->addItem(QString());
        combo_box_view_type->addItem(QString());
        combo_box_view_type->addItem(QString());
        combo_box_view_type->setObjectName(QString::fromUtf8("combo_box_view_type"));

        gridLayout_11->addWidget(combo_box_view_type, 0, 1, 1, 1);


        tab_general_grid_layout->addWidget(frame_view_type, 4, 1, 1, 4);

        pushbutton_screen = new QPushButton(tab_general);
        pushbutton_screen->setObjectName(QString::fromUtf8("pushbutton_screen"));
        pushbutton_screen->setMaximumSize(QSize(16777215, 16777215));
        pushbutton_screen->setFont(font);

        tab_general_grid_layout->addWidget(pushbutton_screen, 1, 1, 1, 2);

        frame_vertex = new QFrame(tab_general);
        frame_vertex->setObjectName(QString::fromUtf8("frame_vertex"));
        frame_vertex->setAutoFillBackground(true);
        frame_vertex->setFrameShape(QFrame::NoFrame);
        frame_vertex->setFrameShadow(QFrame::Raised);
        frame_vertex->setLineWidth(1);
        gridLayout_13 = new QGridLayout(frame_vertex);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        gridLayout_13->setContentsMargins(7, 7, 7, 7);
        label_vertex_type = new QLabel(frame_vertex);
        label_vertex_type->setObjectName(QString::fromUtf8("label_vertex_type"));
        label_vertex_type->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(label_vertex_type, 1, 0, 1, 1);

        label_vertex_size = new QLabel(frame_vertex);
        label_vertex_size->setObjectName(QString::fromUtf8("label_vertex_size"));
        label_vertex_size->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(label_vertex_size, 2, 0, 1, 1);

        combo_box_type_vertex = new QComboBox(frame_vertex);
        combo_box_type_vertex->addItem(QString());
        combo_box_type_vertex->addItem(QString());
        combo_box_type_vertex->addItem(QString());
        combo_box_type_vertex->setObjectName(QString::fromUtf8("combo_box_type_vertex"));

        gridLayout_13->addWidget(combo_box_type_vertex, 1, 1, 1, 2);

        label_vertex = new QLabel(frame_vertex);
        label_vertex->setObjectName(QString::fromUtf8("label_vertex"));
        label_vertex->setFont(font);
        label_vertex->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(label_vertex, 0, 0, 1, 3);

        spin_box_vertex_size = new QSpinBox(frame_vertex);
        spin_box_vertex_size->setObjectName(QString::fromUtf8("spin_box_vertex_size"));
        sizePolicy.setHeightForWidth(spin_box_vertex_size->sizePolicy().hasHeightForWidth());
        spin_box_vertex_size->setSizePolicy(sizePolicy);
        spin_box_vertex_size->setStyleSheet(QString::fromUtf8("QSpinBox {\n"
"  border: 2px solid rgb(76,76,76);\n"
"  border-radius: 5px;\n"
"  background-color: rgb(96, 96, 96);\n"
"  color: rgb(255,255,255);\n"
"}\n"
"\n"
"QSpinBox::down-button  {\n"
"  subcontrol-origin: margin;\n"
"  subcontrol-position: center left;\n"
"  image: url(:/images/left_arrow.png);\n"
"  background-color: rgb(76,76,76);\n"
"  left: 2px;\n"
"  height: 22px;\n"
"  width: 12px;\n"
"}\n"
"\n"
"QSpinBox::up-button  {\n"
"  subcontrol-origin: margin;\n"
"  subcontrol-position: center right;\n"
"  image: url(:/images/right_arrow.png);\n"
"  background-color: rgb(76,76,76);\n"
"  right: 2px;\n"
"  height: 22px;\n"
"  width:12px;\n"
"}"));
        spin_box_vertex_size->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(spin_box_vertex_size, 2, 1, 1, 2);


        tab_general_grid_layout->addWidget(frame_vertex, 6, 3, 2, 2);

        frame = new QFrame(tab_general);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setAutoFillBackground(true);
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_shading = new QLabel(frame);
        label_shading->setObjectName(QString::fromUtf8("label_shading"));
        label_shading->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_shading, 0, 0, 1, 1);

        combo_box_shading = new QComboBox(frame);
        combo_box_shading->addItem(QString());
        combo_box_shading->addItem(QString());
        combo_box_shading->setObjectName(QString::fromUtf8("combo_box_shading"));

        gridLayout_3->addWidget(combo_box_shading, 0, 1, 1, 1);


        tab_general_grid_layout->addWidget(frame, 5, 1, 1, 4);

        frame_info = new QFrame(tab_general);
        frame_info->setObjectName(QString::fromUtf8("frame_info"));
        frame_info->setAutoFillBackground(true);
        frame_info->setStyleSheet(QString::fromUtf8(""));
        frame_info->setFrameShape(QFrame::NoFrame);
        frame_info->setFrameShadow(QFrame::Raised);
        gridLayout_8 = new QGridLayout(frame_info);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout_8->setContentsMargins(7, 7, 7, 7);
        label_edge_amount_int = new QLabel(frame_info);
        label_edge_amount_int->setObjectName(QString::fromUtf8("label_edge_amount_int"));

        gridLayout_8->addWidget(label_edge_amount_int, 3, 1, 1, 1);

        label_edge_amount = new QLabel(frame_info);
        label_edge_amount->setObjectName(QString::fromUtf8("label_edge_amount"));
        label_edge_amount->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_edge_amount, 3, 0, 1, 1);

        label_facets_amount_int = new QLabel(frame_info);
        label_facets_amount_int->setObjectName(QString::fromUtf8("label_facets_amount_int"));

        gridLayout_8->addWidget(label_facets_amount_int, 2, 1, 1, 1);

        label_file_name_text = new QLabel(frame_info);
        label_file_name_text->setObjectName(QString::fromUtf8("label_file_name_text"));

        gridLayout_8->addWidget(label_file_name_text, 0, 1, 1, 1);

        label_file_name = new QLabel(frame_info);
        label_file_name->setObjectName(QString::fromUtf8("label_file_name"));
        label_file_name->setMinimumSize(QSize(0, 0));
        label_file_name->setMaximumSize(QSize(16777215, 16777215));
        label_file_name->setFont(font1);
        label_file_name->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_file_name, 0, 0, 1, 1);

        label_vertex_am = new QLabel(frame_info);
        label_vertex_am->setObjectName(QString::fromUtf8("label_vertex_am"));
        label_vertex_am->setMinimumSize(QSize(0, 0));
        label_vertex_am->setMaximumSize(QSize(16777215, 16));
        label_vertex_am->setFont(font1);
        label_vertex_am->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_vertex_am, 1, 0, 1, 1);

        label_facets_am = new QLabel(frame_info);
        label_facets_am->setObjectName(QString::fromUtf8("label_facets_am"));
        label_facets_am->setMinimumSize(QSize(0, 0));
        label_facets_am->setMaximumSize(QSize(16777215, 16));
        label_facets_am->setFont(font1);
        label_facets_am->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_facets_am, 2, 0, 1, 1);

        label_vertex_am_int = new QLabel(frame_info);
        label_vertex_am_int->setObjectName(QString::fromUtf8("label_vertex_am_int"));

        gridLayout_8->addWidget(label_vertex_am_int, 1, 1, 1, 1);


        tab_general_grid_layout->addWidget(frame_info, 2, 1, 1, 4);


        gridLayout_2->addLayout(tab_general_grid_layout, 0, 0, 1, 1);

        tab_widget->addTab(tab_general, QString());
        tab_transformation = new QWidget();
        tab_transformation->setObjectName(QString::fromUtf8("tab_transformation"));
        gridLayout_7 = new QGridLayout(tab_transformation);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        vertical_spacer_transformation_down = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_7->addItem(vertical_spacer_transformation_down, 4, 1, 1, 1);

        grid_layout_transformation = new QGridLayout();
        grid_layout_transformation->setObjectName(QString::fromUtf8("grid_layout_transformation"));
        frame_move = new QFrame(tab_transformation);
        frame_move->setObjectName(QString::fromUtf8("frame_move"));
        frame_move->setAutoFillBackground(true);
        frame_move->setFrameShape(QFrame::NoFrame);
        frame_move->setFrameShadow(QFrame::Raised);
        gridLayout_17 = new QGridLayout(frame_move);
        gridLayout_17->setObjectName(QString::fromUtf8("gridLayout_17"));
        vertical_layout_spin_boxes_move = new QVBoxLayout();
        vertical_layout_spin_boxes_move->setObjectName(QString::fromUtf8("vertical_layout_spin_boxes_move"));
        d_spin_box_move_x = new QDoubleSpinBox(frame_move);
        d_spin_box_move_x->setObjectName(QString::fromUtf8("d_spin_box_move_x"));
        d_spin_box_move_x->setMinimumSize(QSize(80, 0));
        d_spin_box_move_x->setStyleSheet(QString::fromUtf8("QDoubleSpinBox {\n"
"  border: 2px solid rgb(76,76,76);\n"
"  border-radius: 5px;\n"
"  background-color: rgb(96, 96, 96);\n"
"  color: rgb(255,255,255);\n"
"}\n"
"\n"
"QDoubleSpinBox::down-button  {\n"
"  subcontrol-origin: margin;\n"
"  subcontrol-position: center left;\n"
"  image: url(:/images/left_arrow.png);\n"
"  background-color: rgb(76,76,76);\n"
"  left: 2px;\n"
"  height: 22px;\n"
"  width: 12px;\n"
"}\n"
"\n"
"QDoubleSpinBox::up-button  {\n"
"  subcontrol-origin: margin;\n"
"  subcontrol-position: center right;\n"
"  image: url(:/images/right_arrow.png);\n"
"  background-color: rgb(76,76,76);\n"
"  right: 2px;\n"
"  height: 22px;\n"
"  width:12px;\n"
"}"));
        d_spin_box_move_x->setAlignment(Qt::AlignCenter);
        d_spin_box_move_x->setDecimals(1);
        d_spin_box_move_x->setMinimum(-1000.000000000000000);
        d_spin_box_move_x->setMaximum(1000000.000000000000000);
        d_spin_box_move_x->setSingleStep(0.100000000000000);

        vertical_layout_spin_boxes_move->addWidget(d_spin_box_move_x);

        d_spin_box_move_y = new QDoubleSpinBox(frame_move);
        d_spin_box_move_y->setObjectName(QString::fromUtf8("d_spin_box_move_y"));
        d_spin_box_move_y->setStyleSheet(QString::fromUtf8("QDoubleSpinBox {\n"
"  border: 2px solid rgb(76,76,76);\n"
"  border-radius: 5px;\n"
"  background-color: rgb(96, 96, 96);\n"
"  color: rgb(255,255,255);\n"
"}\n"
"\n"
"QDoubleSpinBox::down-button  {\n"
"  subcontrol-origin: margin;\n"
"  subcontrol-position: center left;\n"
"  image: url(:/images/left_arrow.png);\n"
"  background-color: rgb(76,76,76);\n"
"  left: 2px;\n"
"  height: 22px;\n"
"  width: 12px;\n"
"}\n"
"\n"
"QDoubleSpinBox::up-button  {\n"
"  subcontrol-origin: margin;\n"
"  subcontrol-position: center right;\n"
"  image: url(:/images/right_arrow.png);\n"
"  background-color: rgb(76,76,76);\n"
"  right: 2px;\n"
"  height: 22px;\n"
"  width:12px;\n"
"}"));
        d_spin_box_move_y->setAlignment(Qt::AlignCenter);
        d_spin_box_move_y->setDecimals(1);
        d_spin_box_move_y->setMinimum(-1000.000000000000000);
        d_spin_box_move_y->setMaximum(1000000.000000000000000);
        d_spin_box_move_y->setSingleStep(0.100000000000000);

        vertical_layout_spin_boxes_move->addWidget(d_spin_box_move_y);

        d_spin_box_move_z = new QDoubleSpinBox(frame_move);
        d_spin_box_move_z->setObjectName(QString::fromUtf8("d_spin_box_move_z"));
        d_spin_box_move_z->setStyleSheet(QString::fromUtf8("QDoubleSpinBox {\n"
"  border: 2px solid rgb(76,76,76);\n"
"  border-radius: 5px;\n"
"  background-color: rgb(96, 96, 96);\n"
"  color: rgb(255,255,255);\n"
"}\n"
"\n"
"QDoubleSpinBox::down-button  {\n"
"  subcontrol-origin: margin;\n"
"  subcontrol-position: center left;\n"
"  image: url(:/images/left_arrow.png);\n"
"  background-color: rgb(76,76,76);\n"
"  left: 2px;\n"
"  height: 22px;\n"
"  width: 12px;\n"
"}\n"
"\n"
"QDoubleSpinBox::up-button  {\n"
"  subcontrol-origin: margin;\n"
"  subcontrol-position: center right;\n"
"  image: url(:/images/right_arrow.png);\n"
"  background-color: rgb(76,76,76);\n"
"  right: 2px;\n"
"  height: 22px;\n"
"  width:12px;\n"
"}"));
        d_spin_box_move_z->setAlignment(Qt::AlignCenter);
        d_spin_box_move_z->setDecimals(1);
        d_spin_box_move_z->setMinimum(-1000.000000000000000);
        d_spin_box_move_z->setMaximum(1000000.000000000000000);
        d_spin_box_move_z->setSingleStep(0.100000000000000);

        vertical_layout_spin_boxes_move->addWidget(d_spin_box_move_z);


        gridLayout_17->addLayout(vertical_layout_spin_boxes_move, 2, 3, 3, 1);

        label_move_z = new QLabel(frame_move);
        label_move_z->setObjectName(QString::fromUtf8("label_move_z"));
        label_move_z->setMaximumSize(QSize(16777215, 21));
        QFont font2;
        font2.setPointSize(12);
        label_move_z->setFont(font2);
        label_move_z->setAlignment(Qt::AlignCenter);

        gridLayout_17->addWidget(label_move_z, 4, 1, 1, 1);

        label_value_move = new QLabel(frame_move);
        label_value_move->setObjectName(QString::fromUtf8("label_value_move"));
        label_value_move->setAlignment(Qt::AlignCenter);

        gridLayout_17->addWidget(label_value_move, 5, 3, 1, 1);

        label_move_y = new QLabel(frame_move);
        label_move_y->setObjectName(QString::fromUtf8("label_move_y"));
        label_move_y->setMaximumSize(QSize(16777215, 21));
        label_move_y->setFont(font2);
        label_move_y->setAlignment(Qt::AlignCenter);

        gridLayout_17->addWidget(label_move_y, 3, 1, 1, 1);

        label_move = new QLabel(frame_move);
        label_move->setObjectName(QString::fromUtf8("label_move"));
        label_move->setFont(font);
        label_move->setAlignment(Qt::AlignCenter);

        gridLayout_17->addWidget(label_move, 0, 2, 1, 2);

        label_step_move = new QLabel(frame_move);
        label_step_move->setObjectName(QString::fromUtf8("label_step_move"));
        label_step_move->setAlignment(Qt::AlignCenter);

        gridLayout_17->addWidget(label_step_move, 5, 2, 1, 1);

        label_move_x = new QLabel(frame_move);
        label_move_x->setObjectName(QString::fromUtf8("label_move_x"));
        label_move_x->setMaximumSize(QSize(16777215, 21));
        label_move_x->setFont(font2);
        label_move_x->setAlignment(Qt::AlignCenter);

        gridLayout_17->addWidget(label_move_x, 2, 1, 1, 1);

        vertical_layout_d_spin_boxes_step_move = new QVBoxLayout();
        vertical_layout_d_spin_boxes_step_move->setObjectName(QString::fromUtf8("vertical_layout_d_spin_boxes_step_move"));
        d_spin_box_step_move_x = new QDoubleSpinBox(frame_move);
        d_spin_box_step_move_x->setObjectName(QString::fromUtf8("d_spin_box_step_move_x"));
        d_spin_box_step_move_x->setMinimumSize(QSize(80, 0));
        d_spin_box_step_move_x->setStyleSheet(QString::fromUtf8("QDoubleSpinBox {\n"
"  border: 2px solid rgb(76,76,76);\n"
"  border-radius: 5px;\n"
"  background-color: rgb(96, 96, 96);\n"
"  color: rgb(255,255,255);\n"
"}\n"
"\n"
"QDoubleSpinBox::down-button  {\n"
"  subcontrol-origin: margin;\n"
"  subcontrol-position: center left;\n"
"  image: url(:/images/left_arrow.png);\n"
"  background-color: rgb(76,76,76);\n"
"  left: 2px;\n"
"  height: 22px;\n"
"  width: 12px;\n"
"}\n"
"\n"
"QDoubleSpinBox::up-button  {\n"
"  subcontrol-origin: margin;\n"
"  subcontrol-position: center right;\n"
"  image: url(:/images/right_arrow.png);\n"
"  background-color: rgb(76,76,76);\n"
"  right: 2px;\n"
"  height: 22px;\n"
"  width:12px;\n"
"}"));
        d_spin_box_step_move_x->setAlignment(Qt::AlignCenter);
        d_spin_box_step_move_x->setDecimals(1);
        d_spin_box_step_move_x->setMaximum(1000000.000000000000000);
        d_spin_box_step_move_x->setSingleStep(0.100000000000000);
        d_spin_box_step_move_x->setValue(0.100000000000000);

        vertical_layout_d_spin_boxes_step_move->addWidget(d_spin_box_step_move_x);

        d_spin_box_step_move_y = new QDoubleSpinBox(frame_move);
        d_spin_box_step_move_y->setObjectName(QString::fromUtf8("d_spin_box_step_move_y"));
        d_spin_box_step_move_y->setStyleSheet(QString::fromUtf8("QDoubleSpinBox {\n"
"  border: 2px solid rgb(76,76,76);\n"
"  border-radius: 5px;\n"
"  background-color: rgb(96, 96, 96);\n"
"  color: rgb(255,255,255);\n"
"}\n"
"\n"
"QDoubleSpinBox::down-button  {\n"
"  subcontrol-origin: margin;\n"
"  subcontrol-position: center left;\n"
"  image: url(:/images/left_arrow.png);\n"
"  background-color: rgb(76,76,76);\n"
"  left: 2px;\n"
"  height: 22px;\n"
"  width: 12px;\n"
"}\n"
"\n"
"QDoubleSpinBox::up-button  {\n"
"  subcontrol-origin: margin;\n"
"  subcontrol-position: center right;\n"
"  image: url(:/images/right_arrow.png);\n"
"  background-color: rgb(76,76,76);\n"
"  right: 2px;\n"
"  height: 22px;\n"
"  width:12px;\n"
"}"));
        d_spin_box_step_move_y->setAlignment(Qt::AlignCenter);
        d_spin_box_step_move_y->setDecimals(1);
        d_spin_box_step_move_y->setMaximum(1000000.000000000000000);
        d_spin_box_step_move_y->setSingleStep(0.100000000000000);
        d_spin_box_step_move_y->setValue(0.100000000000000);

        vertical_layout_d_spin_boxes_step_move->addWidget(d_spin_box_step_move_y);

        d_spin_box_step_move_z = new QDoubleSpinBox(frame_move);
        d_spin_box_step_move_z->setObjectName(QString::fromUtf8("d_spin_box_step_move_z"));
        d_spin_box_step_move_z->setStyleSheet(QString::fromUtf8("QDoubleSpinBox {\n"
"  border: 2px solid rgb(76,76,76);\n"
"  border-radius: 5px;\n"
"  background-color: rgb(96, 96, 96);\n"
"  color: rgb(255,255,255);\n"
"}\n"
"\n"
"QDoubleSpinBox::down-button  {\n"
"  subcontrol-origin: margin;\n"
"  subcontrol-position: center left;\n"
"  image: url(:/images/left_arrow.png);\n"
"  background-color: rgb(76,76,76);\n"
"  left: 2px;\n"
"  height: 22px;\n"
"  width: 12px;\n"
"}\n"
"\n"
"QDoubleSpinBox::up-button  {\n"
"  subcontrol-origin: margin;\n"
"  subcontrol-position: center right;\n"
"  image: url(:/images/right_arrow.png);\n"
"  background-color: rgb(76,76,76);\n"
"  right: 2px;\n"
"  height: 22px;\n"
"  width:12px;\n"
"}"));
        d_spin_box_step_move_z->setAlignment(Qt::AlignCenter);
        d_spin_box_step_move_z->setDecimals(1);
        d_spin_box_step_move_z->setMaximum(1000000.000000000000000);
        d_spin_box_step_move_z->setSingleStep(0.100000000000000);
        d_spin_box_step_move_z->setValue(0.100000000000000);

        vertical_layout_d_spin_boxes_step_move->addWidget(d_spin_box_step_move_z);


        gridLayout_17->addLayout(vertical_layout_d_spin_boxes_step_move, 2, 2, 3, 1);


        grid_layout_transformation->addWidget(frame_move, 1, 0, 1, 2);

        frame_rotate = new QFrame(tab_transformation);
        frame_rotate->setObjectName(QString::fromUtf8("frame_rotate"));
        frame_rotate->setAutoFillBackground(true);
        frame_rotate->setStyleSheet(QString::fromUtf8(""));
        frame_rotate->setFrameShape(QFrame::NoFrame);
        frame_rotate->setFrameShadow(QFrame::Raised);
        gridLayout_16 = new QGridLayout(frame_rotate);
        gridLayout_16->setObjectName(QString::fromUtf8("gridLayout_16"));
        label_rotate = new QLabel(frame_rotate);
        label_rotate->setObjectName(QString::fromUtf8("label_rotate"));
        label_rotate->setFont(font);
        label_rotate->setAlignment(Qt::AlignCenter);

        gridLayout_16->addWidget(label_rotate, 1, 0, 1, 3);

        vertical_layout_rotate_spin_boxes = new QVBoxLayout();
        vertical_layout_rotate_spin_boxes->setObjectName(QString::fromUtf8("vertical_layout_rotate_spin_boxes"));
        spin_box_rotate_x = new QSpinBox(frame_rotate);
        spin_box_rotate_x->setObjectName(QString::fromUtf8("spin_box_rotate_x"));
        sizePolicy.setHeightForWidth(spin_box_rotate_x->sizePolicy().hasHeightForWidth());
        spin_box_rotate_x->setSizePolicy(sizePolicy);
        spin_box_rotate_x->setMinimumSize(QSize(0, 0));
        spin_box_rotate_x->setStyleSheet(QString::fromUtf8("QSpinBox {\n"
"  border: 2px solid rgb(76,76,76);\n"
"  border-radius: 5px;\n"
"  background-color: rgb(96, 96, 96);\n"
"  color: rgb(255,255,255);\n"
"}\n"
"\n"
"QSpinBox::down-button  {\n"
"  subcontrol-origin: margin;\n"
"  subcontrol-position: center left;\n"
"  image: url(:/images/left_arrow.png);\n"
"  background-color: rgb(76,76,76);\n"
"  left: 2px;\n"
"  height: 22px;\n"
"  width: 12px;\n"
"}\n"
"\n"
"QSpinBox::up-button  {\n"
"  subcontrol-origin: margin;\n"
"  subcontrol-position: center right;\n"
"  image: url(:/images/right_arrow.png);\n"
"  background-color: rgb(76,76,76);\n"
"  right: 2px;\n"
"  height: 22px;\n"
"  width:12px;\n"
"}"));
        spin_box_rotate_x->setAlignment(Qt::AlignCenter);
        spin_box_rotate_x->setMinimum(-360);
        spin_box_rotate_x->setMaximum(360);
        spin_box_rotate_x->setStepType(QAbstractSpinBox::DefaultStepType);

        vertical_layout_rotate_spin_boxes->addWidget(spin_box_rotate_x);

        spin_box_rotate_y = new QSpinBox(frame_rotate);
        spin_box_rotate_y->setObjectName(QString::fromUtf8("spin_box_rotate_y"));
        sizePolicy.setHeightForWidth(spin_box_rotate_y->sizePolicy().hasHeightForWidth());
        spin_box_rotate_y->setSizePolicy(sizePolicy);
        spin_box_rotate_y->setMinimumSize(QSize(0, 0));
        spin_box_rotate_y->setStyleSheet(QString::fromUtf8("QSpinBox {\n"
"  border: 2px solid rgb(76,76,76);\n"
"  border-radius: 5px;\n"
"  background-color: rgb(96, 96, 96);\n"
"  color: rgb(255,255,255);\n"
"}\n"
"\n"
"QSpinBox::down-button  {\n"
"  subcontrol-origin: margin;\n"
"  subcontrol-position: center left;\n"
"  image: url(:/images/left_arrow.png);\n"
"  background-color: rgb(76,76,76);\n"
"  left: 2px;\n"
"  height: 22px;\n"
"  width: 12px;\n"
"}\n"
"\n"
"QSpinBox::up-button  {\n"
"  subcontrol-origin: margin;\n"
"  subcontrol-position: center right;\n"
"  image: url(:/images/right_arrow.png);\n"
"  background-color: rgb(76,76,76);\n"
"  right: 2px;\n"
"  height: 22px;\n"
"  width:12px;\n"
"}"));
        spin_box_rotate_y->setAlignment(Qt::AlignCenter);
        spin_box_rotate_y->setMinimum(-360);
        spin_box_rotate_y->setMaximum(360);

        vertical_layout_rotate_spin_boxes->addWidget(spin_box_rotate_y);

        spin_box_rotate_z = new QSpinBox(frame_rotate);
        spin_box_rotate_z->setObjectName(QString::fromUtf8("spin_box_rotate_z"));
        sizePolicy.setHeightForWidth(spin_box_rotate_z->sizePolicy().hasHeightForWidth());
        spin_box_rotate_z->setSizePolicy(sizePolicy);
        spin_box_rotate_z->setMinimumSize(QSize(60, 0));
        spin_box_rotate_z->setMaximumSize(QSize(16777215, 16777215));
        spin_box_rotate_z->setAutoFillBackground(false);
        spin_box_rotate_z->setStyleSheet(QString::fromUtf8("QSpinBox {\n"
"  border: 2px solid rgb(76,76,76);\n"
"  border-radius: 5px;\n"
"  background-color: rgb(96, 96, 96);\n"
"  color: rgb(255,255,255);\n"
"}\n"
"\n"
"QSpinBox::down-button  {\n"
"  subcontrol-origin: margin;\n"
"  subcontrol-position: center left;\n"
"  image: url(:/images/left_arrow.png);\n"
"  background-color: rgb(76,76,76);\n"
"  left: 2px;\n"
"  height: 22px;\n"
"  width: 12px;\n"
"}\n"
"\n"
"QSpinBox::up-button  {\n"
"  subcontrol-origin: margin;\n"
"  subcontrol-position: center right;\n"
"  image: url(:/images/right_arrow.png);\n"
"  background-color: rgb(76,76,76);\n"
"  right: 2px;\n"
"  height: 22px;\n"
"  width:12px;\n"
"}"));
        spin_box_rotate_z->setAlignment(Qt::AlignCenter);
        spin_box_rotate_z->setMinimum(-360);
        spin_box_rotate_z->setMaximum(360);

        vertical_layout_rotate_spin_boxes->addWidget(spin_box_rotate_z);


        gridLayout_16->addLayout(vertical_layout_rotate_spin_boxes, 2, 2, 1, 1);

        vertical_layout_rotate_sliders = new QVBoxLayout();
        vertical_layout_rotate_sliders->setObjectName(QString::fromUtf8("vertical_layout_rotate_sliders"));
        slider_rotate_x = new QSlider(frame_rotate);
        slider_rotate_x->setObjectName(QString::fromUtf8("slider_rotate_x"));
        slider_rotate_x->setMinimum(-360);
        slider_rotate_x->setMaximum(360);
        slider_rotate_x->setOrientation(Qt::Horizontal);

        vertical_layout_rotate_sliders->addWidget(slider_rotate_x);

        slider_rotate_y = new QSlider(frame_rotate);
        slider_rotate_y->setObjectName(QString::fromUtf8("slider_rotate_y"));
        slider_rotate_y->setMinimum(-360);
        slider_rotate_y->setMaximum(360);
        slider_rotate_y->setOrientation(Qt::Horizontal);

        vertical_layout_rotate_sliders->addWidget(slider_rotate_y);

        slider_rotate_z = new QSlider(frame_rotate);
        slider_rotate_z->setObjectName(QString::fromUtf8("slider_rotate_z"));
        slider_rotate_z->setMinimum(-360);
        slider_rotate_z->setMaximum(360);
        slider_rotate_z->setOrientation(Qt::Horizontal);

        vertical_layout_rotate_sliders->addWidget(slider_rotate_z);


        gridLayout_16->addLayout(vertical_layout_rotate_sliders, 2, 1, 1, 1);

        vertical_layout_rotate_labels = new QVBoxLayout();
        vertical_layout_rotate_labels->setObjectName(QString::fromUtf8("vertical_layout_rotate_labels"));
        label_rotate_x = new QLabel(frame_rotate);
        label_rotate_x->setObjectName(QString::fromUtf8("label_rotate_x"));
        label_rotate_x->setMaximumSize(QSize(16777215, 21));
        label_rotate_x->setFont(font);
        label_rotate_x->setAlignment(Qt::AlignCenter);

        vertical_layout_rotate_labels->addWidget(label_rotate_x);

        label_rotate_y = new QLabel(frame_rotate);
        label_rotate_y->setObjectName(QString::fromUtf8("label_rotate_y"));
        label_rotate_y->setMaximumSize(QSize(16777215, 21));
        label_rotate_y->setFont(font);
        label_rotate_y->setAlignment(Qt::AlignCenter);

        vertical_layout_rotate_labels->addWidget(label_rotate_y);

        label_rotate_z = new QLabel(frame_rotate);
        label_rotate_z->setObjectName(QString::fromUtf8("label_rotate_z"));
        label_rotate_z->setMaximumSize(QSize(16777215, 21));
        label_rotate_z->setFont(font);
        label_rotate_z->setAlignment(Qt::AlignCenter);

        vertical_layout_rotate_labels->addWidget(label_rotate_z);


        gridLayout_16->addLayout(vertical_layout_rotate_labels, 2, 0, 1, 1);

        label_value_rotate = new QLabel(frame_rotate);
        label_value_rotate->setObjectName(QString::fromUtf8("label_value_rotate"));
        label_value_rotate->setAlignment(Qt::AlignCenter);

        gridLayout_16->addWidget(label_value_rotate, 3, 2, 1, 1);

        label_range_rotate = new QLabel(frame_rotate);
        label_range_rotate->setObjectName(QString::fromUtf8("label_range_rotate"));
        label_range_rotate->setAlignment(Qt::AlignCenter);

        gridLayout_16->addWidget(label_range_rotate, 3, 1, 1, 1);


        grid_layout_transformation->addWidget(frame_rotate, 2, 0, 2, 2);

        frame_scale = new QFrame(tab_transformation);
        frame_scale->setObjectName(QString::fromUtf8("frame_scale"));
        frame_scale->setAutoFillBackground(true);
        frame_scale->setFrameShape(QFrame::NoFrame);
        frame_scale->setFrameShadow(QFrame::Raised);
        gridLayout_18 = new QGridLayout(frame_scale);
        gridLayout_18->setObjectName(QString::fromUtf8("gridLayout_18"));
        label_scale = new QLabel(frame_scale);
        label_scale->setObjectName(QString::fromUtf8("label_scale"));
        label_scale->setFont(font);
        label_scale->setAlignment(Qt::AlignCenter);

        gridLayout_18->addWidget(label_scale, 0, 0, 1, 1);

        d_spin_box_step_scale = new QDoubleSpinBox(frame_scale);
        d_spin_box_step_scale->setObjectName(QString::fromUtf8("d_spin_box_step_scale"));
        d_spin_box_step_scale->setMinimumSize(QSize(80, 0));
        d_spin_box_step_scale->setStyleSheet(QString::fromUtf8("QDoubleSpinBox {\n"
"  border: 2px solid rgb(76,76,76);\n"
"  border-radius: 5px;\n"
"  background-color: rgb(96, 96, 96);\n"
"  color: rgb(255,255,255);\n"
"}\n"
"\n"
"QDoubleSpinBox::down-button  {\n"
"  subcontrol-origin: margin;\n"
"  subcontrol-position: center left;\n"
"  image: url(:/images/left_arrow.png);\n"
"  background-color: rgb(76,76,76);\n"
"  left: 2px;\n"
"  height: 22px;\n"
"  width: 12px;\n"
"}\n"
"\n"
"QDoubleSpinBox::up-button  {\n"
"  subcontrol-origin: margin;\n"
"  subcontrol-position: center right;\n"
"  image: url(:/images/right_arrow.png);\n"
"  background-color: rgb(76,76,76);\n"
"  right: 2px;\n"
"  height: 22px;\n"
"  width:12px;\n"
"}"));
        d_spin_box_step_scale->setAlignment(Qt::AlignCenter);
        d_spin_box_step_scale->setDecimals(1);
        d_spin_box_step_scale->setMaximum(1000000.000000000000000);
        d_spin_box_step_scale->setSingleStep(0.100000000000000);
        d_spin_box_step_scale->setValue(0.100000000000000);

        gridLayout_18->addWidget(d_spin_box_step_scale, 0, 1, 1, 1);

        d_spin_box_scale = new QDoubleSpinBox(frame_scale);
        d_spin_box_scale->setObjectName(QString::fromUtf8("d_spin_box_scale"));
        d_spin_box_scale->setMinimumSize(QSize(80, 0));
        d_spin_box_scale->setStyleSheet(QString::fromUtf8("QDoubleSpinBox {\n"
"  border: 2px solid rgb(76,76,76);\n"
"  border-radius: 5px;\n"
"  background-color: rgb(96, 96, 96);\n"
"  color: rgb(255,255,255);\n"
"}\n"
"\n"
"QDoubleSpinBox::down-button  {\n"
"  subcontrol-origin: margin;\n"
"  subcontrol-position: center left;\n"
"  image: url(:/images/left_arrow.png);\n"
"  background-color: rgb(76,76,76);\n"
"  left: 2px;\n"
"  height: 22px;\n"
"  width: 12px;\n"
"}\n"
"\n"
"QDoubleSpinBox::up-button  {\n"
"  subcontrol-origin: margin;\n"
"  subcontrol-position: center right;\n"
"  image: url(:/images/right_arrow.png);\n"
"  background-color: rgb(76,76,76);\n"
"  right: 2px;\n"
"  height: 22px;\n"
"  width:12px;\n"
"}"));
        d_spin_box_scale->setAlignment(Qt::AlignCenter);
        d_spin_box_scale->setDecimals(1);
        d_spin_box_scale->setMaximum(1000000.000000000000000);
        d_spin_box_scale->setSingleStep(0.100000000000000);
        d_spin_box_scale->setValue(1.000000000000000);

        gridLayout_18->addWidget(d_spin_box_scale, 0, 2, 1, 1);

        label_step_scale = new QLabel(frame_scale);
        label_step_scale->setObjectName(QString::fromUtf8("label_step_scale"));
        label_step_scale->setAlignment(Qt::AlignCenter);

        gridLayout_18->addWidget(label_step_scale, 1, 1, 1, 1);

        label_value_scale = new QLabel(frame_scale);
        label_value_scale->setObjectName(QString::fromUtf8("label_value_scale"));
        label_value_scale->setAlignment(Qt::AlignCenter);

        gridLayout_18->addWidget(label_value_scale, 1, 2, 1, 1);


        grid_layout_transformation->addWidget(frame_scale, 0, 0, 1, 2);


        gridLayout_7->addLayout(grid_layout_transformation, 0, 1, 1, 1);

        tab_widget->addTab(tab_transformation, QString());
        tab_material = new QWidget();
        tab_material->setObjectName(QString::fromUtf8("tab_material"));
        gridLayout = new QGridLayout(tab_material);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        vertical_spacer_material_botom = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(vertical_spacer_material_botom, 2, 0, 1, 2);

        scroll_area_maps = new QScrollArea(tab_material);
        scroll_area_maps->setObjectName(QString::fromUtf8("scroll_area_maps"));
        scroll_area_maps->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 261, 319));
        gridLayout_4 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        grid_layout_material = new QGridLayout();
        grid_layout_material->setObjectName(QString::fromUtf8("grid_layout_material"));

        gridLayout_4->addLayout(grid_layout_material, 0, 0, 1, 1);

        scroll_area_maps->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scroll_area_maps, 1, 0, 1, 2);

        label_properties = new QLabel(tab_material);
        label_properties->setObjectName(QString::fromUtf8("label_properties"));
        label_properties->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_properties, 0, 0, 1, 2);

        tab_widget->addTab(tab_material, QString());

        horizontalLayout->addWidget(tab_widget);

        horizontalLayout->setStretch(0, 10);
        obj__Viewer->setCentralWidget(central_widget);

        retranslateUi(obj__Viewer);

        tab_widget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(obj__Viewer);
    } // setupUi

    void retranslateUi(QMainWindow *obj__Viewer)
    {
        obj__Viewer->setWindowTitle(QCoreApplication::translate("objv::Viewer", "ObjViewer", nullptr));
        label_edge->setText(QCoreApplication::translate("objv::Viewer", "Edge", nullptr));
        label_edge_type->setText(QCoreApplication::translate("objv::Viewer", "Type", nullptr));
        label_edge_size->setText(QCoreApplication::translate("objv::Viewer", "Size", nullptr));
        combo_box_edge_type->setItemText(0, QCoreApplication::translate("objv::Viewer", "Solid", nullptr));
        combo_box_edge_type->setItemText(1, QCoreApplication::translate("objv::Viewer", "Dashed", nullptr));

        pushbutton_reset->setText(QCoreApplication::translate("objv::Viewer", "Reset", nullptr));
        pushbutton_vertex_color->setText(QCoreApplication::translate("objv::Viewer", "Vertex", nullptr));
        puhsbutton_edge_color->setText(QCoreApplication::translate("objv::Viewer", "Edge", nullptr));
        pushbutton_bg_color->setText(QCoreApplication::translate("objv::Viewer", "Background", nullptr));
        label_color->setText(QCoreApplication::translate("objv::Viewer", "Color", nullptr));
        pushbutton_gif->setText(QCoreApplication::translate("objv::Viewer", "Make GIF", nullptr));
        label_projection->setText(QCoreApplication::translate("objv::Viewer", "Projection", nullptr));
        combo_box_projection->setItemText(0, QCoreApplication::translate("objv::Viewer", "Parallel", nullptr));
        combo_box_projection->setItemText(1, QCoreApplication::translate("objv::Viewer", "Central", nullptr));

        pushbutton_open_file->setText(QCoreApplication::translate("objv::Viewer", "Open file (.obj)", nullptr));
        label_view_type->setText(QCoreApplication::translate("objv::Viewer", "View Type", nullptr));
        combo_box_view_type->setItemText(0, QCoreApplication::translate("objv::Viewer", "Wireframe", nullptr));
        combo_box_view_type->setItemText(1, QCoreApplication::translate("objv::Viewer", "Solid", nullptr));
        combo_box_view_type->setItemText(2, QCoreApplication::translate("objv::Viewer", "Material", nullptr));

        pushbutton_screen->setText(QCoreApplication::translate("objv::Viewer", "Make screen", nullptr));
        label_vertex_type->setText(QCoreApplication::translate("objv::Viewer", "Type", nullptr));
        label_vertex_size->setText(QCoreApplication::translate("objv::Viewer", "Size", nullptr));
        combo_box_type_vertex->setItemText(0, QCoreApplication::translate("objv::Viewer", "None", nullptr));
        combo_box_type_vertex->setItemText(1, QCoreApplication::translate("objv::Viewer", "Quad", nullptr));
        combo_box_type_vertex->setItemText(2, QCoreApplication::translate("objv::Viewer", "Circle", nullptr));

        label_vertex->setText(QCoreApplication::translate("objv::Viewer", "Vertex", nullptr));
        label_shading->setText(QCoreApplication::translate("objv::Viewer", "Shading", nullptr));
        combo_box_shading->setItemText(0, QCoreApplication::translate("objv::Viewer", "Smooth", nullptr));
        combo_box_shading->setItemText(1, QCoreApplication::translate("objv::Viewer", "Flat", nullptr));

        label_edge_amount_int->setText(QString());
        label_edge_amount->setText(QCoreApplication::translate("objv::Viewer", "Edge amount:", nullptr));
        label_facets_amount_int->setText(QString());
        label_file_name_text->setText(QString());
        label_file_name->setText(QCoreApplication::translate("objv::Viewer", "File name:", nullptr));
        label_vertex_am->setText(QCoreApplication::translate("objv::Viewer", "Vertex amount:", nullptr));
        label_facets_am->setText(QCoreApplication::translate("objv::Viewer", "Facet amount", nullptr));
        label_vertex_am_int->setText(QString());
        tab_widget->setTabText(tab_widget->indexOf(tab_general), QCoreApplication::translate("objv::Viewer", "General", nullptr));
        label_move_z->setText(QCoreApplication::translate("objv::Viewer", "Z", nullptr));
        label_value_move->setText(QCoreApplication::translate("objv::Viewer", "Value", nullptr));
        label_move_y->setText(QCoreApplication::translate("objv::Viewer", "Y", nullptr));
        label_move->setText(QCoreApplication::translate("objv::Viewer", "Move", nullptr));
        label_step_move->setText(QCoreApplication::translate("objv::Viewer", "Step", nullptr));
        label_move_x->setText(QCoreApplication::translate("objv::Viewer", "X", nullptr));
        label_rotate->setText(QCoreApplication::translate("objv::Viewer", "Rotate", nullptr));
        label_rotate_x->setText(QCoreApplication::translate("objv::Viewer", "X", nullptr));
        label_rotate_y->setText(QCoreApplication::translate("objv::Viewer", "Y", nullptr));
        label_rotate_z->setText(QCoreApplication::translate("objv::Viewer", "Z", nullptr));
        label_value_rotate->setText(QCoreApplication::translate("objv::Viewer", "Value", nullptr));
        label_range_rotate->setText(QCoreApplication::translate("objv::Viewer", "Range", nullptr));
        label_scale->setText(QCoreApplication::translate("objv::Viewer", "Scale", nullptr));
        label_step_scale->setText(QCoreApplication::translate("objv::Viewer", "Step", nullptr));
        label_value_scale->setText(QCoreApplication::translate("objv::Viewer", "Value", nullptr));
        tab_widget->setTabText(tab_widget->indexOf(tab_transformation), QCoreApplication::translate("objv::Viewer", "Transformation", nullptr));
        label_properties->setText(QCoreApplication::translate("objv::Viewer", "Properties", nullptr));
        tab_widget->setTabText(tab_widget->indexOf(tab_material), QCoreApplication::translate("objv::Viewer", "Material", nullptr));
    } // retranslateUi

};

} // namespace objv

namespace objv {
namespace Ui {
    class Viewer: public Ui_Viewer {};
} // namespace Ui
} // namespace objv

#endif // UI_VIEWER_H
