cmake_minimum_required(VERSION 3.10)

set(lib_imgui "imgui")
project(${lib_imgui})

file(GLOB_RECURSE src_files "*.hpp" "*.cpp")

add_library(${lib_imgui} ${src_files})

target_include_directories(${lib_imgui} PUBLIC include)
