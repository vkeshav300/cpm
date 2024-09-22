cmake_minimum_required(VERSION 3.30.3)

project(
    cpm
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB SOURCES "${SOURCE_DIR}/*.cpp")

add_executable(${PROJECT_NAME}
    ${SOURCES}
)

target_include_directories(
    ${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


target_link_libraries(
    ${PROJECT_NAME} PRIVATE
)

if (CMAKE_SYSTEM_NAME MATCHES "Darwin" OR CMAKE_SYSTEM_NAME MATCHES "Linux")
    install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/bin) # Installs CPM - MacOS - sudo required (sudo make install)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    install(TARGETS ${PROJECT_NAME} DESTINATION $ENV{ProgramFiles}) # Installs CPM - Windows (make install)
endif()