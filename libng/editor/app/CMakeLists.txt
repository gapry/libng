cmake_minimum_required(VERSION 3.10)

set(major        "libng")
set(minor        "editor_app")
set(project_name ${major}_${minor})

project(${project_name})

find_package(fmt REQUIRED)

libng_add_executable(${project_name} ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(${project_name} PROPERTIES FOLDER ${major}/${minor})

target_link_libraries(${project_name} PUBLIC fmt::fmt ${major}_editor ${major}_core)

message("-- [${project_name}] - done")