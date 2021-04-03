cmake_minimum_required(VERSION 3.10)

set(lib_log "log")
project(${lib_log})

file(GLOB_RECURSE src_files "*.hpp" "*.cpp")

add_library(${lib_log} ${src_files})

target_include_directories(${lib_log} PUBLIC include)
