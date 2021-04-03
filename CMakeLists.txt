cmake_minimum_required(VERSION 3.10)

set(dir_vcpkg "externals/vcpkg")
set(CMAKE_TOOLCHAIN_FILE "${dir_vcpkg}/scripts/buildsystems/vcpkg.cmake")

set(project_name "GNet")
project(${project_name})

find_package(Threads)
find_package(fmt     CONFIG REQUIRED)
find_package(imgui   CONFIG REQUIRED)
find_package(EABase  CONFIG REQUIRED)
find_package(EASTL   CONFIG REQUIRED) 

if(LINUX)
set(CMAKE_C_COMPILER   "clang")
set(CMAKE_CXX_COMPILER "clang++")
endif(LINUX)

if(MSVC)
set(CMAKE_C_COMPILER   "cl")
set(CMAKE_CXX_COMPILER "cl")
endif(MSVC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(client       "${project_name}_client.out")
set(server       "${project_name}_server.out")
set(unittest     "${project_name}_unittest.out")
set(profiler     "${project_name}_profiler.out")

set(dir_inc      "include")
set(dir_libcxx   "libcxx")
set(dir_src      "src")
set(dir_client   "${dir_src}/client")
set(dir_server   "${dir_src}/server")
set(dir_net      "${dir_src}/net")
set(dir_log      "${dir_src}/log")
set(dir_test     "test")
set(dir_profiler "benchmark")

include_directories(${dir_libcxx})
include_directories(${dir_inc})
include_directories(${dir_src})

file(GLOB_RECURSE client_files   "${dir_client}/*.*")
file(GLOB_RECURSE server_files   "${dir_server}/*.*")
file(GLOB_RECURSE test_files     "${dir_test}/*.*")
file(GLOB_RECURSE profiler_files "${dir_profiler}/*.*")

add_subdirectory(${dir_net})
add_subdirectory(${dir_log})

add_executable(${client}   ${client_files})
add_executable(${server}   ${server_files}
                           ${dir_net}
                           ${dir_log})
add_executable(${unittest} ${test_files})
add_executable(${profiler} ${profiler_files})

target_precompile_headers(${client}   PRIVATE ${dir_inc}/pch.hpp)
target_precompile_headers(${server}   PRIVATE ${dir_inc}/pch.hpp)
target_precompile_headers(${unittest} PRIVATE ${dir_inc}/pch.hpp)
target_precompile_headers(${profiler} PRIVATE ${dir_inc}/pch.hpp)

target_link_libraries(${client}   fmt::fmt Threads::Threads EASTL imgui::imgui)
target_link_libraries(${server}   fmt::fmt Threads::Threads EASTL)
target_link_libraries(${unittest} fmt::fmt Threads::Threads EASTL)
target_link_libraries(${profiler} fmt::fmt Threads::Threads EASTL)
