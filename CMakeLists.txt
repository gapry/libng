cmake_minimum_required(VERSION 3.10)

set(project_name         "libng")
set(dir_src              "${CMAKE_CURRENT_LIST_DIR}/${project_name}")
set(dir_vcpkg            "externals/vcpkg")
set(dir_cmake            "cmake")
set(CMAKE_TOOLCHAIN_FILE "${dir_vcpkg}/scripts/buildsystems/vcpkg.cmake")

project(${project_name})

include(${dir_cmake}/compiler.cmake)
include(${dir_cmake}/vcpkg.cmake)
include(${dir_cmake}/helper.cmake)

include_directories("${CMAKE_CURRENT_LIST_DIR}")
include_directories("${dir_src}")
include_directories("${dir_src}/core")

OPTION(BUILD_GAME      "Build Game"      OFF)
OPTION(BUILD_TEST      "Build Test"      OFF)
OPTION(BUILD_BENCHMARK "Build Benchmark" OFF)
OPTION(BUILD_SERVER    "Build Server"    OFF)

add_subdirectory("${dir_src}/core")
add_subdirectory("${dir_src}/renderer")
add_subdirectory("${dir_src}/compiler/shader")
add_subdirectory("${dir_src}/compiler/app")

IF(BUILD_GAME)
  add_subdirectory(game)
ENDIF(BUILD_GAME)

IF(BUILD_TEST)
  add_subdirectory(test)
ENDIF(BUILD_TEST)

IF(BUILD_BENCHMARK)
  add_subdirectory(benchmark)
ENDIF(BUILD_BENCHMARK)

IF(BUILD_SERVER)
ENDIF(BUILD_SERVER)
