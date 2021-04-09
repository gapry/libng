cmake_minimum_required(VERSION 3.10)

set(project_name "GNet_concurrency")

project(${project_name})

file(GLOB_RECURSE src_files "*.hpp" "*.cpp")

add_library(${project_name} ${src_files})

target_include_directories(${project_name} PUBLIC include)

target_link_libraries(${project_name} PUBLIC EASTL fmt::fmt)
