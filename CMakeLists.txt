# Minimum required version of CMake (cmake --version)
cmake_minimum_required(VERSION 3.27.6)

# Project info
project(
    cpm 
    VERSION 0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

# Giving CMake file structure info
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Get all the source files in the SOURCE_DIR
file(GLOB SOURCES "${SOURCE_DIR}/*.cpp")

add_executable(cpm
    ${SOURCES}
)

target_include_directories(cpm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Check if the current platform is macOS
if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    # Specify the installation directory for macOS (e.g., /usr/local/bin)
    install(TARGETS cpm DESTINATION /usr/local/bin)
endif()