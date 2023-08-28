#ifndef OBJVIEWER_V2_SRC_LOADER_LOADER_H
#define OBJVIEWER_V2_SRC_LOADER_LOADER_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>

#include "../model/mesh.h"

namespace obj {

enum class ProjType : bool { kParallel, kCentral };

enum class ViewType : short int { kWireframe, kSolid, kMaterial };

enum class ShadingType : bool { kSmooth, kFlat };

enum class EdgeType : bool { kSolid, kDashed };

enum class VertexType : short int { kNone, kQuad, kCircle };

struct Settings {
  EdgeType edge_type{};
  VertexType vertex_type{};
  ProjType proj_type;
  ViewType model_view_type{};
  ShadingType shading_type{};
  GLfloat vertex_size;
  GLfloat edge_size;
  QVector3D color_line;
  QVector3D color_point;
  QColor color_bg;
};

using ShaderPaths = std::pair<const char*, const char*>;

using MaterialData = std::vector<NewMtl>;

struct Maps {
  QOpenGLTexture ambient;
  QOpenGLTexture diffuse;
  QOpenGLTexture specular;
  Maps();
  ~Maps() = default;
};

inline Maps::Maps()
    : ambient(QOpenGLTexture::Target2D),
      diffuse(QOpenGLTexture::Target2D),
      specular(QOpenGLTexture::Target2D) {}

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
  const MaterialData& GetMaterialData() noexcept;
  void SetTextures();
  void ResetTexture(unsigned int, unsigned int, const QString& = "");
  void SaveUvMap(unsigned int, std::string_view, const QString&);
  const QImage& GetFrame();
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
  void SetShadingType(int);
  void UpdateFrame();

 protected:
  void initializeGL() override;
  void resizeGL(int, int) override;
  void paintGL() override;
  ShaderPaths GetShadersPaths();
  void ProgramCreate();
  void ProgramDestroy();

 private:
  GLint locations_[11];
  Maps* maps_{};
  Mesh* mesh_{};
  QOpenGLBuffer vbo_;
  QOpenGLBuffer ebo_;
  QOpenGLShaderProgram* program_{};
  QOpenGLVertexArrayObject vao_;
  QMatrix4x4 p_mat_;
  QMatrix4x4 v_mat_;
  QMatrix4x4 m_mat_rotate_;
  QMatrix4x4 m_mat_move_;
  QMatrix4x4 m_mat_scale_;
  QVector3D angles_{};
  QVector3D moves_{};
  Settings sett_;
  QImage frame_;
};

}  // namespace obj

#endif  // OBJVIEWER_V2_SRC_LOADER_LOADER_H
