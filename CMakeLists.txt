cmake_minimum_required(VERSION 3.30.3)

project(
    cpm
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp")

add_executable(
    ${PROJECT_NAME}
    ${SOURCES}
)

target_include_directories(
    ${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

find_package(CURL REQUIRED)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    CURL::libcurl
)

install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/bin) # Installs CPM - MacOS / Linux - sudo required (sudo make install)