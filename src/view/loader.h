#ifndef SRC_VIEWER_LOADER_LOADER_H_
#define SRC_VIEWER_LOADER_LOADER_H_

#include <QOpenGLBuffer>
#ifdef __APPLE__
#include <QOpenGLFunctions_2_1>
#else
#include <QOpenGLFunctions>
#endif
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <array>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "controller/camera_controller.h"
#include "controller/mesh_controller.h"

namespace objv {

enum class ProjType : bool { kParallel, kCentral };

enum class ViewType : short int { kWireframe, kSolid, kMaterial };

enum class ShadingType : bool { kSmooth, kFlat };

enum class EdgeType : bool { kSolid, kDashed };

enum class VertexType : short int { kNone, kQuad, kCircle };

class Loader final : public QOpenGLWidget,
#ifdef __APPLE__
                     protected QOpenGLFunctions_2_1 {
#else
                     protected QOpenGLFunctions {
#endif
  Q_OBJECT
 public:
  explicit Loader(MeshController* mesh_controller,
                  CameraController* camera_controller);
  explicit Loader(QWidget* parent = nullptr);
  ~Loader() override;
  Status Open(const QString& path);
  void SetMeshController(MeshController* controller) noexcept;
  void SetCameraController(CameraController* controller) noexcept;
  void SetVertexColor(const QColor& color_point);
  void SetEdgeColor(const QColor& color_line);
  void SetBgColor(const QColor& color_bg);
  unsigned int GetVertexCount() noexcept;
  unsigned int GetFacetCount() noexcept;
  unsigned int GetEdgeCount() noexcept;
  QColor GetVertexColor() noexcept;
  QColor GetEdgeColor() noexcept;
  QColor GetBgColor() noexcept;
  const std::vector<NewMtl>& GetMaterialData() noexcept;
  void ResetTexture(unsigned int index_mtl, unsigned int map_type,
                    const QString& path = "");
  void SaveUvMap(unsigned int index_mtl, std::string_view path_texture,
                 const QString& path_save);
  const QImage& GetFrame();
  void Rotate(int angle, int axis);
  void Move(double dist, int axis);

 public slots:
  void Scale(double coef);
  void SetEdgeSize(int size);
  void SetVertexSize(int size);
  void SetViewType(int view_type);
  void SetVertexType(int type);
  void SetEdgeType(int type);
  void SetProjectionType(int proj_type);
  void SetShadingType(int shading_type);
  void UpdateFrame();

 private:
  struct Maps;

  using ShaderPaths = std::pair<std::string, std::string>;
  using TextureShaderPaths =
      std::unordered_map<bool, std::unordered_map<ShadingType, ShaderPaths>>;
  using SolidShaderPaths = std::unordered_map<ShadingType, ShaderPaths>;
  using WireframeShaderPaths = std::unordered_map<EdgeType, ShaderPaths>;

  static inline TextureShaderPaths map_texture_;
  static inline SolidShaderPaths map_solid_;
  static inline WireframeShaderPaths map_wireframe_;

  static void InitializeShaderPaths();
  ShaderPaths GetShaderPaths();
  void SetTextures();

  void paintGL() override;
  void initializeGL() override;
  void resizeGL(int width, int height) override;

  void ProgramCreate();
  void ProgramDestroy();
  void SetupProjection(int width, int height) noexcept;

  const Mesh* mesh_{};
  MeshController* mesh_controller_{};
  CameraController* camera_controller_{};
  std::unique_ptr<Maps[]> maps_{};
  QOpenGLBuffer vbo_;
  QOpenGLBuffer ebo_;
  QOpenGLShaderProgram* program_{};
  QOpenGLVertexArrayObject vao_;
  std::array<GLint, 11> locations_{};
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

#endif  // SRC_VIEWER_LOADER_LOADER_H_
