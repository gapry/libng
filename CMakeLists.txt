cmake_minimum_required(VERSION 3.10)

set(project_name "GNet")

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(dir_vcpkg "externals/vcpkg")

set(CMAKE_TOOLCHAIN_FILE "${dir_vcpkg}/scripts/buildsystems/vcpkg.cmake")

set(client   "${project_name}_client.out")
set(server   "${project_name}_server.out")
set(unittest "${project_name}_unittest.out")
set(profiler "${project_name}_profiler.out")

set(dir_inc      "include")
set(dir_libcxx   "libcxx")
set(dir_src      "src")
set(dir_client   "client")
set(dir_server   "server")
set(dir_net      "net")
set(dir_test     "test")
set(dir_profiler "benchmark")

file(GLOB_RECURSE client_files    "${dir_src}/${dir_client}/*.*")
file(GLOB_RECURSE server_files    "${dir_src}/${dir_server}/*.*" 
                                  "${dir_src}/${dir_net}/*.*")
file(GLOB_RECURSE test_files      "${dir_test}/*.*")
file(GLOB_RECURSE profiler_files  "${dir_profiler}/*.*")

project(GNet)

find_package(fmt)
find_package(Threads)
find_package(imgui)
find_package(EASTL CONFIG REQUIRED)

include_directories(${dir_inc})
include_directories(${dir_libcxx})
include_directories(${dir_src})

add_executable(${client}   ${client_files})
add_executable(${server}   ${server_files})
add_executable(${unittest} ${test_files})
add_executable(${profiler} ${profiler_files})

target_precompile_headers(${client}   PRIVATE ${dir_inc}/pch.hpp)
# target_precompile_headers(${server}   PRIVATE ${dir_inc}/pch.h)
# target_precompile_headers(${unittest} PRIVATE ${dir_inc}/pch.h)
# target_precompile_headers(${profiler} PRIVATE ${dir_inc}/pch.h)

target_link_libraries(${client} fmt::fmt Threads::Threads imgui::imgui)
target_link_libraries(${server} fmt::fmt Threads::Threads) #EASTL)
target_link_libraries(${unittest} fmt::fmt Threads::Threads imgui::imgui)
target_link_libraries(${profiler} fmt::fmt Threads::Threads)
