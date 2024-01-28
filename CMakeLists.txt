# Minimum required version of CMake (cmake --version)
cmake_minimum_required(VERSION 3.27.6)

# Project info
project(
    cpm 
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

# Giving CMake file structure info
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Get all the source files in the SOURCE_DIR
file(GLOB SOURCES "${SOURCE_DIR}/*.cpp")

# Find packages / libraries
find_package(CURL REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(JSONCPP REQUIRED jsoncpp)
link_directories(${JSONCPP_LIBRARY_DIRS})

# Add executable
add_executable(${PROJECT_NAME}
    ${SOURCES}
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CURL_INCLUDE_DIRS}
    ${JSONCPP_INCLUDE_DIRS}
    ${JSONCPP_INCLUDE_DIRS}/json
)

# Packages / libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${CURL_LIBRARIES}
    jsoncpp
)

if (CMAKE_SYSTEM_NAME MATCHES "Darwin" OR CMAKE_SYSTEM_NAME MATCHES "Linux")
    install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/bin) # Installs CPM - MacOS - sudo required (sudo make install)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    install(TARGETS ${PROJECT_NAME} DESTINATION $ENV{ProgramFiles}) # Installs CPM - Windows (make install)
endif()