cmake_minimum_required(VERSION 3.10)

set(major        "gnet")
set(minor        "test")
set(project_name ${major}_${minor})

project(${project_name})

gnet_add_executable(${project_name} ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(${project_name} PROPERTIES FOLDER ${minor})

target_link_libraries(${project_name} PUBLIC ${major}_client ${major}_ui)
