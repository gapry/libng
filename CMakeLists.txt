cmake_minimum_required(VERSION 3.10)

set(project_name         "GNet")
set(dir_vcpkg            "externals/vcpkg")
set(dir_cmake            "cmake")
set(CMAKE_TOOLCHAIN_FILE "${dir_vcpkg}/scripts/buildsystems/vcpkg.cmake")

project(${project_name})

include(${dir_cmake}/compiler.cmake)
include(${dir_cmake}/vcpkg.cmake)
include(${dir_cmake}/helper.cmake)

set(sample   "${project_name}_sample.out")
set(server   "${project_name}_server.out")
set(unittest "${project_name}_unittest.out")
set(profiler "${project_name}_profiler.out")

set(dir_libcxx          "libcxx")
set(dir_src             "gnet")
set(dir_inc             "${dir_src}/include")
set(dir_client          "${dir_src}/client")
set(dir_ui              "${dir_src}/ui")
set(dir_server          "${dir_src}/server")
set(dir_net             "${dir_src}/net")
set(dir_process         "${dir_src}/process")
set(dir_mm              "${dir_src}/mm")
set(dir_scheduler       "${dir_src}/scheduler")
set(dir_synchronization "${dir_src}/synchronization")
set(dir_concurrency     "${dir_src}/concurrency")
set(dir_fs              "${dir_src}/fs")
set(dir_log             "${dir_src}/log")
set(dir_timer           "${dir_src}/timer")
set(dir_test            "test")
set(dir_profiler        "benchmark")
set(dir_sample          "sample")

include_directories(${dir_libcxx})
include_directories(${dir_inc})

file(GLOB_RECURSE sample_files   "${dir_sample}/*.*"
                                 "${dir_client}/*.*"
                                 "${dir_ui}/*.*")
file(GLOB_RECURSE server_files   "${dir_server}/*.*")
file(GLOB_RECURSE test_files     "${dir_test}/*.*")
file(GLOB_RECURSE profiler_files "${dir_profiler}/*.*")

add_subdirectory(${dir_client})
add_subdirectory(${dir_ui})
add_subdirectory(${dir_net})
add_subdirectory(${dir_timer})
add_subdirectory(${dir_log})
add_subdirectory(${dir_fs})
add_subdirectory(${dir_process})
add_subdirectory(${dir_mm})
add_subdirectory(${dir_scheduler})
add_subdirectory(${dir_synchronization})
add_subdirectory(${dir_concurrency})
add_subdirectory(${dir_sample})

add_executable(${sample}   ${sample_files}
                           ${dir_client}
                           ${dir_ui})
add_executable(${server}   ${server_files}
                           ${dir_net}
                           ${dir_timer}
                           ${dir_log}
                           ${dir_fs}
                           ${dir_process}
                           ${dir_scheduler}
                           ${dir_synchronization}
                           ${dir_concurrency}
                           ${dir_mm})
add_executable(${unittest} ${test_files})
add_executable(${profiler} ${profiler_files}
                           ${dir_timer})

target_precompile_headers(${sample}   PRIVATE ${dir_inc}/pch.hpp)
target_precompile_headers(${server}   PRIVATE ${dir_inc}/pch.hpp)
target_precompile_headers(${unittest} PRIVATE ${dir_inc}/pch.hpp)
target_precompile_headers(${profiler} PRIVATE ${dir_inc}/pch.hpp)

target_link_libraries(${sample}   fmt::fmt Threads::Threads EASTL imgui::imgui)
target_link_libraries(${server}   fmt::fmt Threads::Threads EASTL)
target_link_libraries(${unittest} fmt::fmt Threads::Threads EASTL)
target_link_libraries(${profiler} fmt::fmt Threads::Threads EASTL)
