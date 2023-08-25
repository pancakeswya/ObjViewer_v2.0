#include "obj_loader.h"

#include <QDir>
#include <QFileDialog>
#include <QPainter>
#include <cmath>

namespace obj {

Loader::Loader(QWidget* parent)
    : QOpenGLWidget(parent),
      vbo_(QOpenGLBuffer::VertexBuffer),
      ebo_(QOpenGLBuffer::IndexBuffer),
      sett_{.proj_type = ProjType::kParallel,
            .vertex_size = 1.0f,
            .edge_size = 1.0f,
            .color_line{0.7f, 0.7f, 0.7f},
            .color_point{0.7f, 0.7f, 0.7f},
            .color_bg{Qt::black}} {}

Loader::~Loader() { ProgramDestroy(); }

void Loader::UpdateFrame() {
  frame_ = grabFramebuffer().scaled(640, 480, Qt::IgnoreAspectRatio).mirrored();
}

Status Loader::Open(const QString& path) {
  ProgramDestroy();
  auto stat = mesh_.Open(path.toStdString());
  ProgramCreate();
  resizeGL(width(), height());
  update();
  return stat;
}

void Loader::ProgramDestroy() {
  makeCurrent();
  vao_.destroy();
  vbo_.destroy();
  ebo_.destroy();
  program_->deleteLater();
}

void Loader::Rotate(int angle, int axis) {
  mMatRotate_.setToIdentity();
  angles_[axis] = angle;
  mMatRotate_.rotate(angles_.x(), 1.0f, 0.0f, 0.0f);
  mMatRotate_.rotate(angles_.y(), 0.0f, 1.0f, 0.0f);
  mMatRotate_.rotate(angles_.z(), 0.0f, 0.0f, 1.0f);
  update();
}

void Loader::Scale(double coef) {
  mMatZoom_.setToIdentity();
  mMatZoom_.scale(coef);
  update();
}

void Loader::Move(double dist, int axis) {
  moves_[axis] = dist;
  mMatMove_.setToIdentity();
  mMatMove_.translate(moves_.x(), 0.0f, 0.0f);
  mMatMove_.translate(0.0f, moves_.y(), 0.0f);
  mMatMove_.translate(0.0f, 0.0f, moves_.z());
  update();
}

ShaderPaths Loader::GetShadersPaths() {
  if (sett_.model_view_type == ViewType::kMaterial && mesh_.has_textures) {
    if (mesh_.has_normals) {
      return std::make_pair(":/shaders/texture.vert", ":/shaders/texture.frag");
    } else {
      return std::make_pair(":/shaders/texture_no_normals.vert",
                            ":/shaders/texture_no_normals.frag");
    }
  } else if (sett_.model_view_type != ViewType::kWireframe &&
             mesh_.has_normals) {
    return std::make_pair(":/shaders/solid.vert", ":/shaders/solid.frag");
  }
  return std::make_pair(":/shaders/wireframe.vert", ":/shaders/wireframe.frag");
}

void Loader::ProgramCreate() {
  program_ = new QOpenGLShaderProgram(this);

  auto [v_path, f_path] = GetShadersPaths();

  program_->addShaderFromSourceFile(QOpenGLShader::Vertex, v_path);
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment, f_path);

  if (!program_->link()) {
    close();
  }
  program_->bind();
  pvmUniform_ = program_->uniformLocation("pvm");
  vmUniform_ = program_->uniformLocation("vm");
  matNormalUniform_ = program_->uniformLocation("matNormal");
  colorUniform_ = program_->uniformLocation("color");
  program_->setUniformValue("texture_a", 0);
  program_->setUniformValue("texture_d", 1);
  program_->setUniformValue("texture_s", 2);

  vao_.create();
  vao_.bind();

  vbo_.create();
  vbo_.bind();
  vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);

  ebo_.create();
  ebo_.bind();
  ebo_.setUsagePattern(QOpenGLBuffer::StaticDraw);

  program_->enableAttributeArray("position");
  if (sett_.model_view_type != ViewType::kWireframe &&
      (mesh_.has_normals || mesh_.has_textures)) {
    vbo_.allocate(mesh_.vertices.data(), mesh_.vertices.size() * sizeof(float));
    ebo_.allocate(mesh_.indices.data(),
                  mesh_.indices.size() * sizeof(unsigned int));

    program_->setAttributeBuffer("position", GL_FLOAT, 0, 3, mesh_.stride);
    if (mesh_.has_textures) {
      program_->enableAttributeArray("texCoords");
      program_->setAttributeBuffer("texCoords", GL_FLOAT, 3 * sizeof(float), 2,
                                   mesh_.stride);
    }
    if (mesh_.has_normals) {
      program_->enableAttributeArray("normal");
      program_->setAttributeBuffer("normal", GL_FLOAT, 5 * sizeof(float), 3,
                                   mesh_.stride);
    }
  } else {
    program_->setAttributeBuffer("position", GL_FLOAT, 0, 3);
    vbo_.allocate(mesh_.points.data(), mesh_.points.size() * sizeof(float));
    ebo_.allocate(mesh_.edges.data(),
                  mesh_.edges.size() * sizeof(unsigned int));
  }

  vao_.release();
  vbo_.release();
  ebo_.release();
}

void Loader::SetEdgeSize(int size) {
  sett_.edge_size = size;
  update();
}

void Loader::SetVertexSize(int size) {
  sett_.vertex_size = size;
  update();
}

unsigned int Loader::GetVertexCount() noexcept { return mesh_.vertex_count; }

unsigned int Loader::GetFacetCount() noexcept { return mesh_.facet_count; }

unsigned int Loader::GetEdgeCount() noexcept { return mesh_.edges.size() / 2; }

MaterialData Loader::GetMaterialData() noexcept {
  return {mesh_.mtl, mesh_.material_count};
}

QColor Loader::GetEdgeColor() noexcept {
  return QColor::fromRgbF(sett_.color_line.x(), sett_.color_line.y(),
                          sett_.color_line.z());
}

QColor Loader::GetVertexColor() noexcept {
  return QColor::fromRgbF(sett_.color_point.x(), sett_.color_point.y(),
                          sett_.color_point.z());
}

QColor Loader::GetBgColor() noexcept { return sett_.color_bg; }

const QImage& Loader::GetFrame() {
  UpdateFrame();
  return frame_;
}

void Loader::ResetTexture(const QString& path, unsigned int index_mtl,
                          unsigned int index_map) {
  mesh_.ResetTexture(path.toStdString(), index_mtl, index_map);
  update();
}

void Loader::SaveUvMap(const QString& path_save, std::string_view path_texture,
                       unsigned int index_mtl) {
  unsigned int prev_off = 0;
  for (auto& umtl : mesh_.usemtl) {
    if (umtl.index == index_mtl) {
      auto img = QImage(path_texture.data()).mirrored();
      QPainter painter(&img);
      for (; prev_off < umtl.offset_uv; prev_off += 2) {
        unsigned int ft1 = mesh_.uv[prev_off] * 2;
        unsigned int ft2 = mesh_.uv[prev_off + 1] * 2;
        qreal vx1 = mesh_.tex_coords[ft1] * img.width();
        qreal vy1 = mesh_.tex_coords[ft1 + 1] * img.height();
        qreal vx2 = mesh_.tex_coords[ft2] * img.width();
        qreal vy2 = mesh_.tex_coords[ft2 + 1] * img.height();
        QLineF line(vx1, vy1, vx2, vy2);
        painter.drawLine(line);
      }
      img.mirrored().save(path_save);
      break;
    }
    prev_off = umtl.offset_uv;
  }
}

void Loader::SetEdgeColor(const QColor& color_line) {
  sett_.color_line =
      QVector3D(color_line.redF(), color_line.greenF(), color_line.blueF());
  update();
}

void Loader::SetVertexColor(const QColor& color_point) {
  sett_.color_point =
      QVector3D(color_point.redF(), color_point.greenF(), color_point.blueF());
  update();
}

void Loader::SetBgColor(const QColor& color_bg) {
  sett_.color_bg = color_bg;
  update();
}

void Loader::SetViewType(int view_type) {
  sett_.model_view_type = ViewType(view_type);
  ProgramDestroy();
  ProgramCreate();
  resizeGL(width(), height());
  update();
}

void Loader::SetProjectionType(int proj_type) {
  sett_.proj_type = ProjType(proj_type);
  resizeGL(width(), height());
  update();
}

void Loader::SetEdgeType(int type) {
  sett_.edge_type = EdgeType(type);
  update();
}
void Loader::SetVertexType(int type) {
  sett_.vertex_type = VertexType(type);
  update();
}

void Loader::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  ProgramCreate();
}

void Loader::resizeGL(int width, int height) {
  pMat_.setToIdentity();
  vMat_.setToIdentity();
  GLfloat size_x = std::abs(mesh_.min_vertex[0] - mesh_.max_vertex[0]);
  GLfloat size_y = std::abs(mesh_.min_vertex[1] - mesh_.max_vertex[1]);
  GLfloat size_z = std::abs(mesh_.min_vertex[2] - mesh_.max_vertex[2]);
  GLfloat mid_size_x = (mesh_.min_vertex[0] + mesh_.max_vertex[0]) / 2.0f;
  GLfloat mid_size_y = (mesh_.min_vertex[1] + mesh_.max_vertex[1]) / 2.0f;
  GLfloat mid_size_z = (mesh_.min_vertex[2] + mesh_.max_vertex[2]) / 2.0f;
  GLfloat max_size = std::max(std::max(size_x, size_y), size_z);
  GLfloat aspectratio = GLfloat(width) / GLfloat(height);
  QVector3D center(mid_size_x, mid_size_y, mid_size_z);
  if (sett_.proj_type == ProjType::kCentral) {
    vMat_.lookAt(QVector3D(center.x(), center.y(), center.z() + max_size),
                 center, QVector3D(0.0f, 1.0f, 0.0f));
    pMat_.perspective(100.0, aspectratio, 0.01f * max_size, 100.0f * max_size);
  } else {
    pMat_.ortho(-max_size * aspectratio, max_size * aspectratio, -max_size,
                max_size, -100.0f * max_size, 100.0f * max_size);
  }
  program_->setUniformValue(
      "lightPos", QVector3D(center.x(), center.y(), center.z() + max_size * 3));
  program_->setUniformValue("viewPos", center);
  program_->release();
}

void Loader::paintGL() {
  glClearColor(sett_.color_bg.redF(), sett_.color_bg.greenF(),
               sett_.color_bg.blueF(), sett_.color_bg.alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLineWidth(sett_.edge_size);
  glPointSize(sett_.vertex_size);

  program_->bind();
  vao_.bind();
  QMatrix4x4 vm = vMat_ * mMatMove_ * mMatRotate_ * mMatZoom_;
  glUniformMatrix4fv(pvmUniform_, 1, GL_FALSE, (pMat_ * vm).constData());
  glUniformMatrix4fv(vmUniform_, 1, GL_FALSE, vm.constData());
  glUniformMatrix4fv(matNormalUniform_, 1, GL_FALSE,
                     vm.inverted().transposed().constData());

  program_->setUniformValue(colorUniform_, sett_.color_line);

  if (sett_.model_view_type != ViewType::kWireframe &&
      (mesh_.has_normals || mesh_.has_textures)) {
    size_t prev_offset = 0;
    for (auto& usemtl : mesh_.usemtl) {
      program_->setUniformValue("Ks", &mesh_.mtl[usemtl.index].Ka);
      program_->setUniformValue("Kd", mesh_.mtl[usemtl.index].Kd[0]);
      program_->setUniformValue("Ks", &mesh_.mtl[usemtl.index].Ks);
      program_->setUniformValue("Ke", &mesh_.mtl[usemtl.index].Ke);
      program_->setUniformValue("specPower", mesh_.mtl[usemtl.index].Ns);
      program_->setUniformValue("opacity", mesh_.mtl[usemtl.index].d);
      if (sett_.model_view_type == ViewType::kMaterial) {
        mesh_.mtl[usemtl.index].map_ka.texture.bind(0);
        mesh_.mtl[usemtl.index].map_kd.texture.bind(1);
        mesh_.mtl[usemtl.index].map_ks.texture.bind(2);
      }
      glDrawElements(GL_TRIANGLES, usemtl.offset_fv - prev_offset,
                     GL_UNSIGNED_INT, (void*)(prev_offset * sizeof(GLuint)));

      prev_offset = usemtl.offset_fv;
      if (sett_.model_view_type == ViewType::kMaterial) {
        mesh_.mtl[usemtl.index].map_ka.texture.release(0);
        mesh_.mtl[usemtl.index].map_kd.texture.release(1);
        mesh_.mtl[usemtl.index].map_ks.texture.release(2);
      }
    }
  } else {
    if (sett_.edge_type == EdgeType::kDashed) {
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(2, 0x00F0);
    }
    glDrawElements(GL_LINES, mesh_.edges.size(), GL_UNSIGNED_INT, nullptr);
    if (sett_.edge_type == EdgeType::kDashed) {
      glDisable(GL_LINE_STIPPLE);
    }
    if (sett_.vertex_type != VertexType::kNone) {
      program_->setUniformValue(colorUniform_, sett_.color_point);
      if (sett_.vertex_type == VertexType::kCircle) {
        glEnable(GL_POINT_SMOOTH);
      }
      glDrawElements(GL_POINTS, mesh_.edges.size(), GL_UNSIGNED_INT, nullptr);
      if (sett_.vertex_type == VertexType::kCircle) {
        glDisable(GL_POINT_SMOOTH);
      }
    }
  }
  vao_.release();
  program_->release();
}

}  // namespace obj
