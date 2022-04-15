cmake_minimum_required(VERSION 3.10)

set(major        "libng")
set(minor        "sample")
set(project_name ${major}_${minor})

project(${project_name})

find_package(GLEW REQUIRED)

libng_add_executable(${project_name} ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(${project_name} PROPERTIES FOLDER ${minor})

# target_link_libraries(${project_name} PUBLIC ${major}_client ${major}_ui)
target_link_libraries(${project_name} PUBLIC GLEW::GLEW)
