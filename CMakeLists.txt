cmake_minimum_required(VERSION 2.8.6)

project(meshLib CXX)

# set the path for custom cmake scripts
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build-aux/cmake")

# include common scripts
include(GroupSourcesByFilesystem)
include(CheckIncludeFiles)

include_directories(
    ${PROJECT_SOURCE_DIR}
)

add_subdirectory(meshLib)
add_subdirectory(tools)
