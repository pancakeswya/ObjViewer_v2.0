#include "obj_loader.h"

#include <QDir>
#include <QFileDialog>
#include <cmath>
#include <QDebug>

namespace Obj {

Loader::Loader(QWidget* parent)
    : QOpenGLWidget(parent),
      m_proj_type(PARALLEL),
      m_point_size(1.0f),
      m_line_size(1.0f),
      m_vbo(QOpenGLBuffer::VertexBuffer),
      m_ebo(QOpenGLBuffer::IndexBuffer),
      m_color_line(0.7f, 0.7f, 0.7f),
      m_color_point(0.7f, 0.7f, 0.7f),
      m_color_bg(Qt::black) {}

Loader::~Loader() {
  VaoDestroy();
  m_program->removeAllShaders();
  m_program->deleteLater();
}

void Loader::UpdateFramebuffer() {
  m_frame = grabFramebuffer()
                .scaled(640, 480, Qt::IgnoreAspectRatio)
                .transformed(QTransform().rotate(180));
}

Status Loader::Open(const QString& path) {
  VaoDestroy();
  m_obj.Destroy();
  auto stat = m_obj.Open(path.toStdString());
  VaoCreate();
  resizeGL(width(), height());
  update();
  return stat;
}

void Loader::VaoDestroy() {
  makeCurrent();
  m_vao.destroy();
  m_vbo.destroy();
  m_ebo.destroy();
}

void Loader::Rotate(float angle, int axis) {
  m_mMatRotate.setToIdentity();
  m_angles[axis] = angle;
  m_mMatRotate.rotate(m_angles.x(), 1.0f, 0.0f, 0.0f);
  m_mMatRotate.rotate(m_angles.y(), 0.0f, 1.0f, 0.0f);
  m_mMatRotate.rotate(m_angles.z(), 0.0f, 0.0f, 1.0f);
  update();
}

void Loader::Zoom(float coef) {
  m_mMatZoom.setToIdentity();
  m_mMatZoom.scale(coef);
  update();
}

void Loader::Move(float dist, int axis) {
  m_moves[axis] = dist;
  m_mMatMove.setToIdentity();
  m_mMatMove.translate(m_moves.x(), 0.0f, 0.0f);
  m_mMatMove.translate(0.0f, m_moves.y(), 0.0f);
  m_mMatMove.translate(0.0f, 0.0f, m_moves.z());
  update();
}

void Loader::InitProgram() {
  m_program = new QOpenGLShaderProgram(this);

  m_program->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                     ":/shaders/vertex.vert");
  m_program->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                     ":/shaders/fragment.frag");

  if (!m_program->link()) {
    close();
  }
  m_program->bind();

  m_projUniform = m_program->uniformLocation("projection");
  m_viewUniform = m_program->uniformLocation("view");
  m_modelUniform = m_program->uniformLocation("model");
  m_colorUniform = m_program->uniformLocation("color");

  m_program->release();
}

void Loader::VaoCreate() {
  bool use_normals = false, use_textures = false;

  m_program->bind();

  m_vao.create();
  m_vao.bind();

  m_vbo.create();
  m_vbo.bind();
  m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);

  m_ebo.create();
  m_ebo.bind();
  m_ebo.setUsagePattern(QOpenGLBuffer::StaticDraw);

  m_program->enableAttributeArray("position");
  if (m_model_view_type && (m_obj.HasNormals() || m_obj.HasTextures())) {
    unsigned int stride = m_obj.GetStride();

    m_vbo.allocate(m_obj.vertices.data(),
                   m_obj.vertices.size() * sizeof(float));
    m_ebo.allocate(m_obj.indices.data(),
                   m_obj.indices.size() * sizeof(unsigned int));

    m_program->setAttributeBuffer("position", GL_FLOAT, 0, 3, stride);
    if (m_obj.HasTextures()) {
      use_textures = (m_model_view_type == 2);
      m_program->enableAttributeArray("texCoords");
      m_program->setAttributeBuffer("texCoords", GL_FLOAT, 3 * sizeof(float), 2,
                                    stride);
    }
    if (m_obj.HasNormals()) {
      use_normals = true;
      m_program->enableAttributeArray("normal");
      m_program->setAttributeBuffer("normal", GL_FLOAT, 5 * sizeof(float), 3,
                                    stride);
    }
  } else {
    m_program->setAttributeBuffer("position", GL_FLOAT, 0, 3);
    m_vbo.allocate(m_obj.verticesw.data(),
                   m_obj.verticesw.size() * sizeof(float));
    m_ebo.allocate(m_obj.indicesw.data(),
                   m_obj.indicesw.size() * sizeof(unsigned int));
  }

  m_program->setUniformValue("use_texture", use_textures);
  m_program->setUniformValue("use_normals", use_normals);
  m_program->setUniformValue(
      "viewPos", QVector3D(-m_vMat.constData()[12], -m_vMat.constData()[13],
                           -m_vMat.constData()[14]));

  m_vao.release();
  m_vbo.release();
  m_ebo.release();
  m_program->release();
}

void Loader::SetLineSize(float size) {
  m_line_size = size;
  update();
}

void Loader::SetPointSize(float size) {
  m_point_size = size;
  update();
}

unsigned int Loader::GetFacetCount() noexcept { return m_obj.facet_count; }

QColor Loader::GetColorLine() noexcept {
  return QColor::fromRgbF(m_color_line.x(), m_color_line.y(), m_color_line.z());
}

QColor Loader::GetColorPoint() noexcept {
  return QColor::fromRgbF(m_color_point.x(), m_color_point.y(),
                          m_color_point.z());
}

QColor Loader::GetColorBg() noexcept { return m_color_bg; }

QImage& Loader::GetFramebuffer() {
  UpdateFramebuffer();
  return m_frame;
}

unsigned int Loader::GetVertexCount() noexcept { return m_obj.vertex_count; }

void Loader::SetColorLine(const QColor& color_line) {
  m_color_line =
      QVector3D(color_line.redF(), color_line.greenF(), color_line.blueF());
  update();
}

void Loader::SetColorPoint(const QColor& color_point) {
  m_color_point =
      QVector3D(color_point.redF(), color_point.greenF(), color_point.blueF());
  update();
}

void Loader::SetColorBg(const QColor& color_bg) {
  m_color_bg = color_bg;
  update();
}

void Loader::SetModelViewType(int view_type) {
  m_model_view_type = view_type;
  VaoDestroy();
  VaoCreate();
  update();
}

void Loader::SetProjectionType(int proj_type) {
  m_proj_type = proj_type;
  resizeGL(width(), height());
  update();
}

void Loader::SetLineType(bool type) {
  m_line_type = type;
  update();
}
void Loader::SetPointType(int type) {
  m_point_type = type;
  update();
}

void Loader::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  InitProgram();
  VaoCreate();
}

void Loader::resizeGL(int width, int height) {
  m_pMat.setToIdentity();
  m_vMat.setToIdentity();
  GLfloat size_x = std::abs(m_obj.min_vertex[0] - m_obj.max_vertex[0]);
  GLfloat size_y = std::abs(m_obj.min_vertex[1] - m_obj.max_vertex[1]);
  GLfloat size_z = std::abs(m_obj.min_vertex[2] - m_obj.max_vertex[2]);
  GLfloat mid_size_x = (m_obj.min_vertex[0] + m_obj.max_vertex[0]) / 2.0f;
  GLfloat mid_size_y = (m_obj.min_vertex[1] + m_obj.max_vertex[1]) / 2.0f;
  GLfloat mid_size_z = (m_obj.min_vertex[2] + m_obj.max_vertex[2]) / 2.0f;
  GLfloat max_size = std::max(std::max(size_x, size_y), size_z);
  GLfloat aspectratio = GLfloat(width) / GLfloat(height);
  if (m_proj_type == CENTRAL) {
    QVector3D center(mid_size_x, mid_size_y, mid_size_z);
    m_vMat.lookAt(QVector3D(center.x(), center.y(), center.z() + max_size),
                  center, QVector3D(0.0f, 1.0f, 0.0f));
    m_pMat.perspective(100.0, aspectratio, 0.01f * max_size, 100.0f * max_size);
  } else {
    m_pMat.ortho(-max_size * aspectratio, max_size * aspectratio, -max_size,
                 max_size, -100.0f * max_size, 100.0f * max_size);
  }
}

void Loader::paintGL() {
  glClearColor(m_color_bg.redF(), m_color_bg.greenF(), m_color_bg.blueF(),
               m_color_bg.alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLineWidth(m_line_size);
  glPointSize(m_point_size);

  m_program->bind();
  m_vao.bind();

  glUniformMatrix4fv(m_projUniform, 1, GL_FALSE, m_pMat.constData());
  glUniformMatrix4fv(m_viewUniform, 1, GL_FALSE, m_vMat.constData());
  glUniformMatrix4fv(m_modelUniform, 1, GL_FALSE,
                     (m_mMatMove * m_mMatRotate * m_mMatZoom).constData());

  m_program->setUniformValue(m_colorUniform, m_color_line);

  if (m_model_view_type && (m_obj.HasNormals() || m_obj.HasTextures())) {
    size_t prev_offset = 0;
    bool is_textured = (m_model_view_type == 2);
    for (auto& mtl : m_obj.usemtl) {
      if (m_model_view_type == 2) {
        bool mtl_has_texture = m_obj.mtl[mtl.index].map_kd.isCreated();
        if (is_textured != mtl_has_texture) {
          m_program->setUniformValue("use_texture", mtl_has_texture);
          is_textured = mtl_has_texture;
        }
      }
      m_program->setUniformValue("Ks", &m_obj.mtl[mtl.index].Ka);
      m_program->setUniformValue("Kd", m_obj.mtl[mtl.index].Kd[0]);
      m_program->setUniformValue("Ks", &m_obj.mtl[mtl.index].Ks);
      m_program->setUniformValue("Ke", &m_obj.mtl[mtl.index].Ke);
      m_program->setUniformValue("specPower", m_obj.mtl[mtl.index].Ns);
      m_program->setUniformValue("opacity", m_obj.mtl[mtl.index].d);
      if (is_textured) {
        m_obj.mtl[mtl.index].map_kd.bind();
      }
      glDrawElements(GL_TRIANGLES, mtl.offset - prev_offset, GL_UNSIGNED_INT,
                     (void*)(prev_offset * sizeof(GLuint)));

      prev_offset = mtl.offset;
      if (is_textured) {
        m_obj.mtl[mtl.index].map_kd.release();
      }
    }
  } else {
    if (m_line_type) {
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(2, 0x00F0);
    }
    glDrawElements(GL_LINES, m_obj.indicesw.size(), GL_UNSIGNED_INT, nullptr);
    if (m_line_type) {
      glDisable(GL_LINE_STIPPLE);
    }
    if (m_point_type) {
      m_program->setUniformValue(m_colorUniform, m_color_point);
      if (m_point_type == 2) {
        glEnable(GL_POINT_SMOOTH);
      }
      glDrawElements(GL_POINTS, m_obj.indicesw.size(), GL_UNSIGNED_INT,
                     nullptr);
      if (m_point_type == 2) {
        glDisable(GL_POINT_SMOOTH);
      }
    }
  }
  m_vao.release();
  m_program->release();
}

}  // namespace Obj
