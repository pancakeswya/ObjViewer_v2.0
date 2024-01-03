#include "view/loader.h"

#include <QDir>
#include <QFileDialog>
#include <QOpenGLTexture>
#include <QPainter>
#include <cmath>

#include "base/gif_settings.h"

namespace objv {

namespace {

enum MapType { kAmbient, kDiffuse, kSpecular };

enum LocationType {
  kMvpU,
  kMvU,
  kMatNormalU,
  kColorU,
  kVertexSizeU,
  kAmbientU,
  kDiffuseU,
  kSpecularU,
  kEmissionU,
  kShinessU,
  kOpacityU
};

void LoadTexture(QOpenGLTexture& texture, const std::string& path) {
  texture.destroy();
  QImage tex_image;
  if (!path.empty()) {
    tex_image.load(path.c_str());
  }
  if (tex_image.isNull()) {
    constexpr int w = 1, h = 1;
    // make it default color texture
    QImage image(w, h, QImage::Format_RGB32);
    image.fill(Qt::lightGray);
    tex_image = std::move(image);
  }
  texture.setData(tex_image.mirrored());
  texture.setMinificationFilter(QOpenGLTexture::Nearest);
  texture.setMagnificationFilter(QOpenGLTexture::Linear);
  texture.setWrapMode(QOpenGLTexture::Repeat);
}

}  // namespace

struct Loader::Maps {
  QOpenGLTexture ambient;
  QOpenGLTexture diffuse;
  QOpenGLTexture specular;
  Maps();
  ~Maps() = default;
};

inline Loader::Maps::Maps()
    : ambient(QOpenGLTexture::Target2D),
      diffuse(QOpenGLTexture::Target2D),
      specular(QOpenGLTexture::Target2D) {}

Loader::Loader(Controller* controller) : Loader() { controller_ = controller; }

Loader::Loader(QWidget* parent)
    : QOpenGLWidget(parent),
      vbo_(QOpenGLBuffer::VertexBuffer),
      ebo_(QOpenGLBuffer::IndexBuffer),
      settings_{.proj_type = ProjType::kParallel,
                .vertex_size = 1.0f,
                .edge_size = 1.0f,
                .color_line{static_cast<float>(QColor(Qt::lightGray).redF()),
                            static_cast<float>(QColor(Qt::lightGray).greenF()),
                            static_cast<float>(QColor(Qt::lightGray).blueF())},
                .color_point{static_cast<float>(QColor(Qt::lightGray).redF()),
                             static_cast<float>(QColor(Qt::lightGray).greenF()),
                             static_cast<float>(QColor(Qt::lightGray).blueF())},
                .color_bg{Qt::black}} {}

Loader::~Loader() { ProgramDestroy(); }

void Loader::UpdateFrame() {
  frame_ = grabFramebuffer()
               .scaled(kGifWidth, kGifHeight, Qt::IgnoreAspectRatio)
               .mirrored();
}

Status Loader::Open(const QString& path) {
  ProgramDestroy();
  controller_->Reset();
  auto [mesh, stat] = controller_->CreateMesh(path.toStdString());
  mesh_ = mesh;
  if (stat == Status::kNoExc) {
    ProgramCreate();
    SetTextures();
    SetupProjection(width(), height());
    update();
  }
  return stat;
}

void Loader::SetController(Controller* controller) noexcept {
  controller_ = controller;
}

void Loader::ProgramDestroy() {
  makeCurrent();
  vao_.destroy();
  vbo_.destroy();
  ebo_.destroy();
  program_->deleteLater();
}

void Loader::Rotate(int angle, int axis) {
  controller_->Rotate(angle, axis);
  update();
}

void Loader::Scale(double coef) {
  controller_->Zoom(coef);
  update();
}

void Loader::Move(double dist, int axis) {
  controller_->Move(dist, axis);
  update();
}

void Loader::InitializeShaderPaths() {
  const std::string shader_dir =
      ":/shaders/"
#ifdef __APPLE__
      "macos/";
#else
      "";
#endif
  map_texture_[true][ShadingType::kSmooth] = {shader_dir + "texture.vert",
                                              shader_dir + "texture.frag"};
  map_texture_[true][ShadingType::kFlat] = {shader_dir + "texture.vert",
                                            shader_dir + "texture_flat.frag"};
  map_texture_[false][ShadingType::kSmooth] = {
      shader_dir + "texture_no_normals.vert",
      shader_dir + "texture_no_normals.frag"};
  map_texture_[false][ShadingType::kFlat] = {
      shader_dir + "texture_no_normals.vert",
      shader_dir + "texture_no_normals.frag"};
  map_solid_[ShadingType::kSmooth] = {shader_dir + "solid.vert",
                                      shader_dir + "solid.frag"};
  map_solid_[ShadingType::kFlat] = {shader_dir + "solid.vert",
                                    shader_dir + "solid_flat.frag"};
  map_wireframe_[EdgeType::kSolid] = {shader_dir + "wireframe.vert",
                                      shader_dir + "wireframe.frag"};
  map_wireframe_[EdgeType::kDashed] = {shader_dir + "wireframe_dashed.vert",
                                       shader_dir + "wireframe_dashed.frag"};
}

Loader::ShaderPaths Loader::GetShaderPaths() {
  if (settings_.model_view_type == ViewType::kMaterial && mesh_->has_textures) {
    return map_texture_[mesh_->has_normals][settings_.shading_type];
  } else if (settings_.model_view_type != ViewType::kWireframe &&
             mesh_->has_normals) {
    return map_solid_[settings_.shading_type];
  }
  return map_wireframe_[settings_.edge_type];
}

void Loader::ProgramCreate() {
  program_ = new QOpenGLShaderProgram(this);

  if (!mesh_) {
    return;
  }

  auto [v_path, f_path] = GetShaderPaths();

  program_->addShaderFromSourceFile(QOpenGLShader::Vertex, v_path.data());
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment, f_path.data());

  if (!program_->link()) {
    close();
  }
  program_->bind();

  locations_[kMvpU] = program_->uniformLocation("u_mvp");
  locations_[kMvU] = program_->uniformLocation("u_mv");
  locations_[kMatNormalU] = program_->uniformLocation("u_normal_mat");
  locations_[kColorU] = program_->uniformLocation("u_color");
  locations_[kVertexSizeU] = program_->uniformLocation("u_vertex_size");
  locations_[kAmbientU] = program_->uniformLocation("u_ambient");
  locations_[kDiffuseU] = program_->uniformLocation("u_diffuse");
  locations_[kSpecularU] = program_->uniformLocation("u_specular");
  locations_[kEmissionU] = program_->uniformLocation("u_emission");
  locations_[kShinessU] = program_->uniformLocation("u_shiness");
  locations_[kOpacityU] = program_->uniformLocation("u_opacity");

  program_->setUniformValue("u_texture_a", 0);
  program_->setUniformValue("u_texture_d", 1);
  program_->setUniformValue("u_texture_s", 2);

  vao_.create();
  vao_.bind();

  vbo_.create();
  vbo_.bind();
  vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);

  ebo_.create();
  ebo_.bind();
  ebo_.setUsagePattern(QOpenGLBuffer::StaticDraw);

  program_->enableAttributeArray("a_position");
  size_t stride =
      (3 + 3 * mesh_->has_normals + 2 * mesh_->has_textures) * sizeof(float);
  if (settings_.model_view_type != ViewType::kWireframe &&
      (mesh_->has_normals || mesh_->has_textures)) {
    vbo_.allocate(mesh_->vertices.data(),
                  mesh_->vertices.size() * sizeof(float));
    ebo_.allocate(mesh_->indices.data(),
                  mesh_->indices.size() * sizeof(unsigned int));

    program_->setAttributeBuffer("a_position", GL_FLOAT, 0, 3, stride);
    if (mesh_->has_textures) {
      program_->enableAttributeArray("a_tex_coords");
      program_->setAttributeBuffer("a_tex_coords", GL_FLOAT, 3 * sizeof(float),
                                   2, stride);
    }
    if (mesh_->has_normals) {
      program_->enableAttributeArray("a_normal");
      program_->setAttributeBuffer("a_normal", GL_FLOAT, 5 * sizeof(float), 3,
                                   stride);
    }
  } else {
    program_->setAttributeBuffer("a_position", GL_FLOAT, 0, 3);
    vbo_.allocate(mesh_->points.data(), mesh_->points.size() * sizeof(float));
    ebo_.allocate(mesh_->edges.data(),
                  mesh_->edges.size() * sizeof(unsigned int));
  }

  vao_.release();
  vbo_.release();
  ebo_.release();
}

void Loader::SetEdgeSize(int size) {
  settings_.edge_size = size;
  update();
}

void Loader::SetVertexSize(int size) {
  settings_.vertex_size = size;
  update();
}

unsigned int Loader::GetVertexCount() noexcept { return mesh_->vertex_count; }

unsigned int Loader::GetFacetCount() noexcept { return mesh_->facet_count; }

unsigned int Loader::GetEdgeCount() noexcept { return mesh_->edges.size() / 2; }

const std::vector<NewMtl>& Loader::GetMaterialData() noexcept {
  return mesh_->mtl;
}

QColor Loader::GetEdgeColor() noexcept {
  return QColor::fromRgbF(settings_.color_line.x(), settings_.color_line.y(),
                          settings_.color_line.z());
}

QColor Loader::GetVertexColor() noexcept {
  return QColor::fromRgbF(settings_.color_point.x(), settings_.color_point.y(),
                          settings_.color_point.z());
}

QColor Loader::GetBgColor() noexcept { return settings_.color_bg; }

const QImage& Loader::GetFrame() {
  UpdateFrame();
  return frame_;
}

void Loader::SetTextures() {
  maps_ = std::make_unique<Maps[]>(mesh_->mtl.size());
  for (size_t i = 0; i < mesh_->mtl.size(); ++i) {
    LoadTexture(maps_[i].ambient, mesh_->mtl[i].map_ka);
    LoadTexture(maps_[i].diffuse, mesh_->mtl[i].map_kd);
    LoadTexture(maps_[i].specular, mesh_->mtl[i].map_ks);
  }
}

void Loader::ResetTexture(unsigned int index_mtl, unsigned int map_type,
                          const QString& path) {
  if (map_type == kAmbient) {
    LoadTexture(maps_[index_mtl].ambient, path.toStdString());
  } else if (map_type == kDiffuse) {
    LoadTexture(maps_[index_mtl].diffuse, path.toStdString());
  } else if (map_type == kSpecular) {
    LoadTexture(maps_[index_mtl].specular, path.toStdString());
  }
  update();
}

void Loader::SaveUvMap(unsigned int index_mtl, std::string_view path_texture,
                       const QString& path_save) {
  if (path_texture.empty()) {
    return;
  }
  unsigned int prev_off = 0;
  for (const UseMtl& umtl : mesh_->usemtl) {
    if (umtl.index == index_mtl) {
      auto img = QImage(path_texture.data()).mirrored();
      QPainter painter(&img);
      for (; prev_off < umtl.offset_uv; prev_off += 2) {
        unsigned int ft1 = mesh_->uv[prev_off] * 2;
        unsigned int ft2 = mesh_->uv[prev_off + 1] * 2;
        qreal vx1 = mesh_->tex_coords[ft1] * img.width();
        qreal vy1 = mesh_->tex_coords[ft1 + 1] * img.height();
        qreal vx2 = mesh_->tex_coords[ft2] * img.width();
        qreal vy2 = mesh_->tex_coords[ft2 + 1] * img.height();
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
  settings_.color_line =
      QVector3D(color_line.redF(), color_line.greenF(), color_line.blueF());
  update();
}

void Loader::SetVertexColor(const QColor& color_point) {
  settings_.color_point =
      QVector3D(color_point.redF(), color_point.greenF(), color_point.blueF());
  update();
}

void Loader::SetBgColor(const QColor& color_bg) {
  settings_.color_bg = color_bg;
  update();
}

void Loader::SetViewType(int view_type) {
  settings_.model_view_type = ViewType(view_type);
  ProgramDestroy();
  ProgramCreate();
  SetupProjection(width(), height());
  update();
}

void Loader::SetProjectionType(int proj_type) {
  settings_.proj_type = ProjType(proj_type);
  SetupProjection(width(), height());
  update();
}

void Loader::SetShadingType(int shading_type) {
  settings_.shading_type = ShadingType(shading_type);
  ProgramDestroy();
  ProgramCreate();
  SetupProjection(width(), height());
  update();
}

void Loader::SetEdgeType(int type) {
  settings_.edge_type = EdgeType(type);
  ProgramDestroy();
  ProgramCreate();
  SetupProjection(width(), height());
  update();
}
void Loader::SetVertexType(int type) {
  settings_.vertex_type = VertexType(type);
  update();
}

void Loader::SetupProjection(int width, int height) noexcept {
  if (!mesh_) {
    return;
  }
  controller_->SetPerspective(width, height, mesh_->min_vertex,
                              mesh_->max_vertex);
  if (settings_.proj_type == ProjType::kCentral) {
    controller_->SetCentralProjection();
  } else {
    controller_->SetParallelProjection();
  }
  auto center = controller_->GetCenterCoords();
  float max_dist = controller_->GetMaxDistance();
  program_->setUniformValue(
      "u_light_pos",
      QVector3D(center.x(), center.y(), center.z() + max_dist * 3));
  program_->setUniformValue("u_resolution", width, height);
  program_->release();
}

void Loader::initializeGL() {
  InitializeShaderPaths();
  initializeOpenGLFunctions();
  glEnable(GL_PROGRAM_POINT_SIZE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  ProgramCreate();
}

void Loader::resizeGL(int width, int height) { SetupProjection(width, height); }

void Loader::paintGL() {
  glClearColor(settings_.color_bg.redF(), settings_.color_bg.greenF(),
               settings_.color_bg.blueF(), settings_.color_bg.alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (!mesh_) {
    return;
  }
  glLineWidth(settings_.edge_size);

  program_->bind();
  vao_.bind();
  const QMatrix4x4 vm =
      controller_->GetViewMatrix() * controller_->GetModelMatrix();
  const QMatrix4x4 pm = controller_->GetProjectionMatrix();
  glUniformMatrix4fv(locations_[kMvpU], 1, GL_FALSE, (pm * vm).constData());
  glUniformMatrix4fv(locations_[kMvU], 1, GL_FALSE, vm.constData());
  glUniformMatrix4fv(locations_[kMatNormalU], 1, GL_FALSE,
                     vm.inverted().transposed().constData());

  program_->setUniformValue(locations_[kColorU], settings_.color_line);
  program_->setUniformValue(locations_[kVertexSizeU], settings_.vertex_size);

  if (settings_.model_view_type != ViewType::kWireframe &&
      (mesh_->has_normals || mesh_->has_textures)) {
    // draw surface
    size_t prev_offset = 0;
    for (const UseMtl& usemtl : mesh_->usemtl) {
      program_->setUniformValue(locations_[kAmbientU],
                                &mesh_->mtl[usemtl.index].Ka);
      program_->setUniformValue(locations_[kDiffuseU],
                                &mesh_->mtl[usemtl.index].Kd);
      program_->setUniformValue(locations_[kSpecularU],
                                &mesh_->mtl[usemtl.index].Ks);
      program_->setUniformValue(locations_[kEmissionU],
                                &mesh_->mtl[usemtl.index].Ke);
      program_->setUniformValue(locations_[kShinessU],
                                mesh_->mtl[usemtl.index].Ns);
      program_->setUniformValue(locations_[kOpacityU],
                                mesh_->mtl[usemtl.index].d);
      if (settings_.model_view_type == ViewType::kMaterial) {
        maps_[usemtl.index].ambient.bind(0);
        maps_[usemtl.index].diffuse.bind(1);
        maps_[usemtl.index].specular.bind(2);
      }
      glDrawElements(GL_TRIANGLES, usemtl.offset_fv - prev_offset,
                     GL_UNSIGNED_INT,
                     reinterpret_cast<void*>(prev_offset * sizeof(GLuint)));

      prev_offset = usemtl.offset_fv;
      if (settings_.model_view_type == ViewType::kMaterial) {
        maps_[usemtl.index].ambient.release(0);
        maps_[usemtl.index].diffuse.release(1);
        maps_[usemtl.index].specular.release(2);
      }
    }
  } else {
    // draw lines
    glDrawElements(GL_LINES, mesh_->edges.size(), GL_UNSIGNED_INT, nullptr);
    if (settings_.vertex_type != VertexType::kNone) {
      program_->setUniformValue(locations_[kColorU], settings_.color_point);
      if (settings_.vertex_type == VertexType::kCircle) {
        glEnable(GL_POINT_SMOOTH);
      }
      glDrawElements(GL_POINTS, mesh_->edges.size(), GL_UNSIGNED_INT, nullptr);
      if (settings_.vertex_type == VertexType::kCircle) {
        glDisable(GL_POINT_SMOOTH);
      }
    }
  }
  vao_.release();
  program_->release();
}

}  // namespace objv
