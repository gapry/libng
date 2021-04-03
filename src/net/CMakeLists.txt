cmake_minimum_required(VERSION 3.10)

set(lib_net "net")
project(${lib_net})

file(GLOB_RECURSE src_files "*.hpp" "*.cpp")

add_library(${lib_net} ${src_files})

target_include_directories(${lib_net} PUBLIC include)
