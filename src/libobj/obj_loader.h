#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>

#include "obj_mesh.h"

namespace Obj {

class Loader : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
 public:
  Status Open(const QString&);
  void Rotate(float, int);
  void Zoom(float);
  void Move(float, int);
  void InitProgram();
  void SetLineSize(float);
  void SetPointSize(float);
  void SetColorPoint(const QColor&);
  void SetColorLine(const QColor&);
  void SetColorBg(const QColor&);
  void SetModelViewType(int);
  void SetPointType(int);
  void SetLineType(bool);
  void SetProjectionType(int);
  unsigned int GetVertexCount() noexcept;
  unsigned int GetFacetCount() noexcept;
  QColor GetColorLine() noexcept;
  QColor GetColorPoint() noexcept;
  QColor GetColorBg() noexcept;
  QImage& GetFramebuffer();
  explicit Loader(QWidget* parent = nullptr);
  ~Loader() override;
 public slots:
  void UpdateFramebuffer();

 protected:
  void initializeGL() override;
  void resizeGL(int, int) override;
  void paintGL() override;
  void VaoCreate();
  void VaoDestroy();

 private:
  enum ProjType { PARALLEL, CENTRAL };
  bool m_line_type{};
  int m_point_type{};
  int m_proj_type;
  int m_model_view_type{};
  GLint m_projUniform;
  GLint m_viewUniform;
  GLint m_modelUniform;
  GLint m_colorUniform;
  GLfloat m_point_size;
  GLfloat m_line_size;
  Mesh m_obj{};
  QOpenGLBuffer m_vbo;
  QOpenGLBuffer m_ebo;
  QVector3D m_color_line;
  QVector3D m_color_point;
  QColor m_color_bg;
  QOpenGLShaderProgram* m_program{};
  QOpenGLVertexArrayObject m_vao;
  QMatrix4x4 m_pMat;
  QMatrix4x4 m_vMat;
  QMatrix4x4 m_mMatRotate;
  QMatrix4x4 m_mMatMove;
  QMatrix4x4 m_mMatZoom;
  QVector3D m_angles{};
  QVector3D m_moves{};
  QImage m_frame;
};

}  // namespace Obj

#endif  // OBJ_LOADER_H
