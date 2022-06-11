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

OPTION(IDE_VSC         "IDE VSC"         OFF)
OPTION(IDE_VS          "IDE VS"          OFF)
OPTION(BUILD_GAME      "Build Game"      OFF)
OPTION(BUILD_TEST      "Build Test"      OFF)
OPTION(BUILD_BENCHMARK "Build Benchmark" OFF)
OPTION(BUILD_SERVER    "Build Server"    OFF)

IF(IDE_VSC)
  add_compile_definitions(LIBNG_IDE_VSC=1)
ENDIF(IDE_VSC)

IF(IDE_VS)
  add_compile_definitions(LIBNG_IDE_VS=1)
ENDIF(IDE_VS)

add_subdirectory("${dir_src}/core")
add_subdirectory("${dir_src}/renderer")
add_subdirectory("${dir_src}/compiler")
add_subdirectory("${dir_src}/compiler/app")
add_subdirectory("${dir_src}/engine")
add_subdirectory("${dir_src}/device")
add_subdirectory("${dir_src}/editor")
add_subdirectory("${dir_src}/editor/app")
add_subdirectory("${dir_src}/plugin")
add_subdirectory("${dir_src}/script")

IF(BUILD_COMPILER)
  add_subdirectory(test)
  add_subdirectory("${dir_src}/core/test")
  add_subdirectory("${dir_src}/compiler/test")
ENDIF(BUILD_TEST)

IF(BUILD_GAME)
  add_subdirectory(game)
ENDIF(BUILD_GAME)
 
IF(BUILD_TEST)
  add_subdirectory(test)
  add_subdirectory("${dir_src}/core/test")
  add_subdirectory("${dir_src}/compiler/test")
  add_subdirectory("${dir_src}/renderer/test")
ENDIF(BUILD_TEST)

IF(BUILD_BENCHMARK)
  add_subdirectory(benchmark)
ENDIF(BUILD_BENCHMARK)

IF(BUILD_SERVER)
ENDIF(BUILD_SERVER)
