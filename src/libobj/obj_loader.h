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
  std::pair<const char*, const char*> GetShadersPaths();
  void ProgramCreate();
  void ProgramDestroy();

 private:
  enum ProjType { PARALLEL, CENTRAL };
  bool line_type_{};
  int point_type_{};
  int proj_type_;
  int model_view_type_{};
  GLint pvmUniform_;
  GLint vmUniform_;
  GLint matNormalUniform_;
  GLint colorUniform_;
  GLfloat point_size_;
  GLfloat line_size_;
  Mesh mesh_{};
  QOpenGLBuffer vbo_;
  QOpenGLBuffer ebo_;
  QVector3D color_line_;
  QVector3D color_point_;
  QColor color_bg_;
  QOpenGLShaderProgram* program_{};
  QOpenGLVertexArrayObject vao_;
  QMatrix4x4 pMat_;
  QMatrix4x4 vMat_;
  QMatrix4x4 mMatRotate_;
  QMatrix4x4 mMatMove_;
  QMatrix4x4 mMatZoom_;
  QVector3D angles_{};
  QVector3D moves_{};
  QImage frame_;
};

}  // namespace Obj

#endif  // OBJ_LOADER_H
