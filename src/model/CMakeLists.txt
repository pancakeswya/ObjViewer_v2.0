cmake_minimum_required(VERSION 3.5)

project(ModelTests VERSION 2.0)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_COMPILE_OPTIONS -Wall -Werror -Wextra -O1)

find_package(GTest REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

find_program(GCOV gcov)
find_program(LCOV lcov)

include_directories("../")

add_custom_target(test
        COMMAND ${CMAKE_MAKE_PROGRAM}
        COMMAND ./${PROJECT_NAME}
        )
add_custom_target(check-valgrind
        COMMAND ${CMAKE_MAKE_PROGRAM}
        COMMAND valgrind --tool=memcheck --trace-children=yes --track-origins=yes --leak-check=full ./${PROJECT_NAME}
        )

if (GCOV AND LCOV)
    set(CMAKE_CXX_FLAGS "--coverage")
    add_custom_target(gcov_report
            COMMAND ${CMAKE_MAKE_PROGRAM}
            COMMAND ./${PROJECT_NAME}
            COMMAND lcov -c -d CMakeFiles/${PROJECT_NAME}.dir -o coverage.info
            COMMAND lcov -r coverage.info '/usr*' -o coverage.info
            COMMAND genhtml coverage.info -o report
            COMMAND open report/index.html
            )
    add_dependencies(gcov_report ${PROJECT_NAME})
else()
    message(WARNING "Cannot find utils for coverage(lcov|gcov)")
endif()


set(PROJECT_SOURCES
    model_test.cc
    camera_model.cc
    camera_model.h
    mesh_model.cc
    mesh_model.h
    ../base/data_parser.cc
    ../base/data_parser.h
    ../base/mesh_maker.cc
    ../base/mesh_maker.h
)

add_executable(ModelTests ${PROJECT_SOURCES})

target_link_libraries(ModelTests Qt${QT_VERSION_MAJOR}::Widgets GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME} PRIVATE ${PROJECT_COMPILE_OPTIONS})
