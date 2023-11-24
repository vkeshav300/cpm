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

# Find CURL package
find_package(CURL REQUIRED)

# Add executable
add_executable(cpm
    ${SOURCES}
)

# Include directories
target_include_directories(cpm PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CURL_INCLUDE_DIRS}  # Include CURL headers
)

# Link against CURL
target_link_libraries(cpm PRIVATE ${CURL_LIBRARIES})

if (CMAKE_SYSTEM_NAME MATCHES "Darwin" OR CMAKE_SYSTEM_NAME MATCHES "Linux")
    install(TARGETS cpm DESTINATION /usr/local/bin) # Installs CPM - MacOS - sudo required (sudo make install)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    install(TARGETS cpm DESTINATION $ENV{ProgramFiles}) # Installs CPM - Windows (make install)
endif()