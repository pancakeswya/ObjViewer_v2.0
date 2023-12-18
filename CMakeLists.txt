cmake_minimum_required(VERSION 3.5)

project(ObjViewer_v2 VERSION 2.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -O3")

set(OpenGL_GL_PREFERENCE GLVND)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)

set(QT_OPENGL_WIDGETS_MODULE "OpenGLWidgets")

if(QT_VERSION_MAJOR EQUAL 5)
    find_package(Qt5OpenGLWidgets QUIET)
    if(NOT Qt5OpenGLWidgets_FOUND)
        set(QT_OPENGL_WIDGETS_MODULE "OpenGL")
    endif()
endif()

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets ${QT_OPENGL_WIDGETS_MODULE} REQUIRED)

include_directories("src")

add_library(Gif STATIC
    src/third_party/gif.h
    src/third_party/gif.c)

add_library(Model STATIC
    src/model/data_parser.h
    src/model/data_parser.cc
    src/model/mesh_maker.h
    src/model/mesh_maker.cc
    src/model/model.cc
    src/model/model.h)

add_library(Controller STATIC
    src/controller/controller.cc
    src/controller/controller.h)

target_link_libraries(Controller Model)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_library(ObjLoader STATIC
    src/view/loader.cc
    src/view/loader.h)

target_link_libraries(ObjLoader Qt${QT_VERSION_MAJOR}::${QT_OPENGL_WIDGETS_MODULE} Controller)

set (QRC_FILES resources/resources.qrc)

set(PROJECT_SOURCES
    src/main.cc
    src/concurrency/gif_maker.cc
    src/concurrency/gif_maker.h
    src/view/view.cc
    src/view/view.h
    src/view/view.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ObjViewer_v2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES} ${QRC_FILES})
else()
    add_executable(ObjViewer_v2
        ${PROJECT_SOURCES} ${QRC_FILES})
endif()

target_link_libraries(ObjViewer_v2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ObjLoader Gif)

set_target_properties(ObjViewer_v2 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ObjViewer_v2)
endif()
