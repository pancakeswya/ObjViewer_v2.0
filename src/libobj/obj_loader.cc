#include "obj_loader.h"

#include <QDir>
#include <QFileDialog>
#include <cmath>

namespace Obj {

Loader::Loader(QWidget* parent)
    : QOpenGLWidget(parent),
      proj_type_(PARALLEL),
      point_size_(1.0f),
      line_size_(1.0f),
      vbo_(QOpenGLBuffer::VertexBuffer),
      ebo_(QOpenGLBuffer::IndexBuffer),
      color_line_(0.7f, 0.7f, 0.7f),
      color_point_(0.7f, 0.7f, 0.7f),
      color_bg_(Qt::black) {}

Loader::~Loader() { ProgramDestroy(); }

void Loader::UpdateFramebuffer() {
  frame_ = grabFramebuffer()
                .scaled(640, 480, Qt::IgnoreAspectRatio)
                .transformed(QTransform().rotate(180));
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

void Loader::Rotate(float angle, int axis) {
  mMatRotate_.setToIdentity();
  angles_[axis] = angle;
  mMatRotate_.rotate(angles_.x(), 1.0f, 0.0f, 0.0f);
  mMatRotate_.rotate(angles_.y(), 0.0f, 1.0f, 0.0f);
  mMatRotate_.rotate(angles_.z(), 0.0f, 0.0f, 1.0f);
  update();
}

void Loader::Zoom(float coef) {
  mMatZoom_.setToIdentity();
  mMatZoom_.scale(coef);
  update();
}

void Loader::Move(float dist, int axis) {
  moves_[axis] = dist;
  mMatMove_.setToIdentity();
  mMatMove_.translate(moves_.x(), 0.0f, 0.0f);
  mMatMove_.translate(0.0f, moves_.y(), 0.0f);
  mMatMove_.translate(0.0f, 0.0f, moves_.z());
  update();
}

std::pair<const char*, const char*> Loader::GetShadersPaths() {
  if (model_view_type_ == 2 && mesh_.has_textures) {
    if (mesh_.has_normals) {
      return std::make_pair(":/shaders/texture.vert", ":/shaders/texture.frag");
    } else {
      return std::make_pair(":/shaders/texture_no_normals.vert",
                            ":/shaders/texture_no_normals.frag");
    }
  } else if (model_view_type_ && mesh_.has_normals) {
    return std::make_pair(":/shaders/solid.vert", ":/shaders/solid.frag");
  }
  return std::make_pair(":/shaders/wireframe.vert", ":/shaders/wireframe.frag");
}

void Loader::ProgramCreate() {
  program_ = new QOpenGLShaderProgram(this);

  auto shaders_paths = GetShadersPaths();

  program_->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                     shaders_paths.first);
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                     shaders_paths.second);

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
  if (model_view_type_ && (mesh_.has_normals || mesh_.has_textures)) {
    vbo_.allocate(mesh_.vertices.data(),
                   mesh_.vertices.size() * sizeof(float));
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
    vbo_.allocate(mesh_.verticesw.data(),
                   mesh_.verticesw.size() * sizeof(float));
    ebo_.allocate(mesh_.indicesw.data(),
                   mesh_.indicesw.size() * sizeof(unsigned int));
  }

  vao_.release();
  vbo_.release();
  ebo_.release();
}

void Loader::SetLineSize(float size) {
  line_size_ = size;
  update();
}

void Loader::SetPointSize(float size) {
  point_size_ = size;
  update();
}

unsigned int Loader::GetFacetCount() noexcept { return mesh_.facet_count; }

QColor Loader::GetColorLine() noexcept {
  return QColor::fromRgbF(color_line_.x(), color_line_.y(), color_line_.z());
}

QColor Loader::GetColorPoint() noexcept {
  return QColor::fromRgbF(color_point_.x(), color_point_.y(),
                          color_point_.z());
}

QColor Loader::GetColorBg() noexcept { return color_bg_; }

QImage& Loader::GetFramebuffer() {
  UpdateFramebuffer();
  return frame_;
}

unsigned int Loader::GetVertexCount() noexcept { return mesh_.vertex_count; }

void Loader::SetColorLine(const QColor& color_line) {
  color_line_ =
      QVector3D(color_line.redF(), color_line.greenF(), color_line.blueF());
  update();
}

void Loader::SetColorPoint(const QColor& color_point) {
  color_point_ =
      QVector3D(color_point.redF(), color_point.greenF(), color_point.blueF());
  update();
}

void Loader::SetColorBg(const QColor& color_bg) {
  color_bg_ = color_bg;
  update();
}

void Loader::SetModelViewType(int view_type) {
  model_view_type_ = view_type;
  ProgramDestroy();
  ProgramCreate();
  resizeGL(width(), height());
  update();
}

void Loader::SetProjectionType(int proj_type) {
  proj_type_ = proj_type;
  resizeGL(width(), height());
  update();
}

void Loader::SetLineType(bool type) {
  line_type_ = type;
  update();
}
void Loader::SetPointType(int type) {
  point_type_ = type;
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
  if (proj_type_ == CENTRAL) {
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
  glClearColor(color_bg_.redF(), color_bg_.greenF(), color_bg_.blueF(),
               color_bg_.alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLineWidth(line_size_);
  glPointSize(point_size_);

  program_->bind();
  vao_.bind();
  QMatrix4x4 vm = vMat_ * mMatMove_ * mMatRotate_ * mMatZoom_;
  glUniformMatrix4fv(pvmUniform_, 1, GL_FALSE, (pMat_ * vm).constData());
  glUniformMatrix4fv(vmUniform_, 1, GL_FALSE, vm.constData());
  glUniformMatrix4fv(matNormalUniform_, 1, GL_FALSE,
                     vm.inverted().transposed().constData());

  program_->setUniformValue(colorUniform_, color_line_);

  if (model_view_type_ && (mesh_.has_normals || mesh_.has_textures)) {
    size_t prev_offset = 0;
    for (auto& mtl : mesh_.usemtl) {
      program_->setUniformValue("Ks", &mesh_.mtl[mtl.index].Ka);
      program_->setUniformValue("Kd", mesh_.mtl[mtl.index].Kd[0]);
      program_->setUniformValue("Ks", &mesh_.mtl[mtl.index].Ks);
      program_->setUniformValue("Ke", &mesh_.mtl[mtl.index].Ke);
      program_->setUniformValue("specPower", mesh_.mtl[mtl.index].Ns);
      program_->setUniformValue("opacity", mesh_.mtl[mtl.index].d);
      if (model_view_type_ == 2) {
        mesh_.mtl[mtl.index].map_ka.bind(0);
        mesh_.mtl[mtl.index].map_kd.bind(1);
        mesh_.mtl[mtl.index].map_ks.bind(2);
      }
      glDrawElements(GL_TRIANGLES, mtl.offset - prev_offset, GL_UNSIGNED_INT,
                     (void*)(prev_offset * sizeof(GLuint)));

      prev_offset = mtl.offset;
      if (model_view_type_ == 2) {
        mesh_.mtl[mtl.index].map_ka.release(0);
        mesh_.mtl[mtl.index].map_kd.release(1);
        mesh_.mtl[mtl.index].map_ks.release(2);
      }
    }
  } else {
    if (line_type_) {
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(2, 0x00F0);
    }
    glDrawElements(GL_LINES, mesh_.indicesw.size(), GL_UNSIGNED_INT, nullptr);
    if (line_type_) {
      glDisable(GL_LINE_STIPPLE);
    }
    if (point_type_) {
      program_->setUniformValue(colorUniform_, color_point_);
      if (point_type_ == 2) {
        glEnable(GL_POINT_SMOOTH);
      }
      glDrawElements(GL_POINTS, mesh_.indicesw.size(), GL_UNSIGNED_INT,
                     nullptr);
      if (point_type_ == 2) {
        glDisable(GL_POINT_SMOOTH);
      }
    }
  }
  vao_.release();
  program_->release();
}

}  // namespace Obj
