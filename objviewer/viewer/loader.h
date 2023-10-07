#ifndef OBJVIEWER_VIEWER_LOADER_LOADER_H_
#define OBJVIEWER_VIEWER_LOADER_LOADER_H_

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>

#include <array>
#include <unordered_map>
#include <memory>

#include "objviewer/lib/mesh_maker/mesh_maker.h"

namespace objv {

enum class ProjType : bool { kParallel, kCentral };

enum class ViewType : short int { kWireframe, kSolid, kMaterial };

enum class ShadingType : bool { kSmooth, kFlat };

enum class EdgeType : bool { kSolid, kDashed };

enum class VertexType : short int { kNone, kQuad, kCircle };

class Loader final : public QOpenGLWidget, protected QOpenGLFunctions {
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
  const std::vector<NewMtl>& GetMaterialData() noexcept;
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

 private:
  struct Maps;

  using ShaderPaths = std::pair<std::string_view, std::string_view>;
  using TextureShaderPaths = std::unordered_map<bool, std::unordered_map<ShadingType, ShaderPaths>>;
  using SolidShaderPaths = std::unordered_map<ShadingType,ShaderPaths>;
  using WireframeShaderPaths = std::unordered_map<EdgeType, ShaderPaths>;

  inline static TextureShaderPaths map_texture_;
  inline static SolidShaderPaths map_solid_;
  inline static WireframeShaderPaths map_wireframe_;

  static void InitializeShaderPaths();
  ShaderPaths GetShaderPaths();

  void initializeGL() override;
  void resizeGL(int, int) override;
  void paintGL() override;

  void ProgramCreate();
  void ProgramDestroy();

  std::unique_ptr<Maps[]> maps_{};
  std::unique_ptr<Mesh> mesh_{};
  QOpenGLBuffer vbo_;
  QOpenGLBuffer ebo_;
  QOpenGLShaderProgram* program_{};
  QOpenGLVertexArrayObject vao_;
  std::array<GLint, 11> locations_{};
  QMatrix4x4 p_mat_;
  QMatrix4x4 v_mat_;
  QMatrix4x4 m_mat_rotate_;
  QMatrix4x4 m_mat_move_;
  QMatrix4x4 m_mat_scale_;
  QVector3D angles_{};
  QVector3D moves_{};
  struct {
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
  } settings_;
  QImage frame_;
};

}  // namespace objv

#endif  // OBJVIEWER_VIEWER_LOADER_LOADER_H_
