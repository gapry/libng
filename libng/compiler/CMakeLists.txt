cmake_minimum_required(VERSION 3.10)

set(major        "libng")
set(minor        "compiler")        # compiler driver
set(project_name ${major}_${minor})

project(${project_name})

libng_add_library(${project_name} ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(${project_name} PROPERTIES FOLDER ${major}/${minor})

target_link_libraries(${project_name} PUBLIC EASTL fmt::fmt ${major}_core ${major}_renderer)

message("-- [${project_name}] - done")