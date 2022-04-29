cmake_minimum_required(VERSION 3.10)

set(major        "libng")
set(minor        "test")
set(project_name ${major}_${minor})

project(${project_name})

libng_add_executable(${project_name} ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(${project_name} PROPERTIES FOLDER ${minor})

# target_link_libraries(${project_name} PUBLIC EASTL fmt::fmt Threads::Threads ${major}_log) 
target_link_libraries(${project_name} PUBLIC EASTL fmt::fmt) 
