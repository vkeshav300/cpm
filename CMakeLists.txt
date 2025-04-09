# CMake config
cmake_minimum_required(VERSION 3.30.3)

# Project config
project(
    cpm
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Compile options
add_compile_options(-Wno-deprecated-declarations)

# Find all source files
file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp")

# Packages
find_package(CURL REQUIRED)
find_package(RapidJSON REQUIRED)

# Compilation
add_executable(
    ${PROJECT_NAME}
    ${SOURCES}
)

# Include files
target_include_directories(
    ${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
    ${RAPIDJSON_INCLUDE_DIRS}
    ${CURL_INCLUDE_DIRS}
)

# Link source files
target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    ${CURL_LIBRARIES}
)

# `make install` to the following location
install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/bin) # Installs CPM - MacOS / Linux - sudo required (sudo make install)
