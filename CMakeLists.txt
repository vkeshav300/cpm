# Minimum required version of CMake (cmake --version)
cmake_minimum_required(VERSION 3.27.0)

# Project info
project(
    CPM 
    VERSION 0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

# Giving CMake file structure info
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Get all the source files in the SOURCE_DIR
file(GLOB SOURCES "${SOURCE_DIR}/*.cpp")

add_executable(cpm
    ${SOURCES}
)

target_include_directories(cpm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)