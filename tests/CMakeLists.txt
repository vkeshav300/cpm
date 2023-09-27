# Minimum required version of CMake (cmake --version)
cmake_minimum_required(VERSION 3.27.0)

# Project info
project(project_name VERSION 0.0)

# Giving CMake file structure info
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Get all the source files in the SOURCE_DIR
file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)

add_executable(project_name ${SOURCES})

target_include_directories(project_name PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)