#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>

#include "obj_mesh.h"

namespace obj {

enum class ProjType : bool { kParallel, kCentral };

enum class ViewType : short int { kWireframe, kSolid, kMaterial};

enum class EdgeType : bool { kSolid, kDashed };

enum class VertexType : short int { kNone, kQuad, kCircle };

struct Settings {
    EdgeType edge_type{};
    VertexType vertex_type{};
    ProjType proj_type;
    ViewType model_view_type{};
    GLfloat vertex_size;
    GLfloat edge_size;
    QVector3D color_line;
    QVector3D color_point;
    QColor color_bg;
};

using ShaderPaths = std::pair<const char*, const char*>;

class Loader : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
 public:
  explicit Loader(QWidget* parent = nullptr);
  ~Loader() override;
  Status Open(const QString&);
  void SetVertexColor(const QColor&);
  void SetEdgeColor(const QColor&);
  void SetBgColor(const QColor&);
  unsigned int GetVertexCount() noexcept;
  unsigned int GetFacetCount() noexcept;
  unsigned int GetEdgeCount() noexcept;
  QColor GetVertexColor() noexcept;
  QColor GetEdgeColor() noexcept;
  QColor GetBgColor() noexcept;
  QImage& GetFramebuffer();
  void Rotate(int, int);
  void Move(double, int);
 public slots:
  void Scale(double);
  void SetEdgeSize(int);
  void SetVertexSize(int);
  void SetViewType(int);
  void SetVertexType(int);
  void SetEdgeType(int);
  void SetProjectionType(int);
  void UpdateFramebuffer();

 protected:
  void initializeGL() override;
  void resizeGL(int, int) override;
  void paintGL() override;
  ShaderPaths GetShadersPaths();
  void ProgramCreate();
  void ProgramDestroy();

 private:
  GLint pvmUniform_;
  GLint vmUniform_;
  GLint matNormalUniform_;
  GLint colorUniform_;
  Mesh mesh_{};
  QOpenGLBuffer vbo_;
  QOpenGLBuffer ebo_;
  QOpenGLShaderProgram* program_{};
  QOpenGLVertexArrayObject vao_;
  QMatrix4x4 pMat_;
  QMatrix4x4 vMat_;
  QMatrix4x4 mMatRotate_;
  QMatrix4x4 mMatMove_;
  QMatrix4x4 mMatZoom_;
  QVector3D angles_{};
  QVector3D moves_{};
  Settings sett_;
  QImage frame_;
};

}  // namespace Obj

#endif  // OBJ_LOADER_H
