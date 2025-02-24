cmake_minimum_required(VERSION 3.30.3)

project(
    cpm
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Glob all the source files in src and commands directories
file(GLOB SOURCES "${SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/commands/*.cpp")

# Add the executable
add_executable(
    ${PROJECT_NAME}
    ${SOURCES}
)

# Include the directories
target_include_directories(
    ${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/commands
)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE
)

if (CMAKE_SYSTEM_NAME MATCHES "Darwin" OR CMAKE_SYSTEM_NAME MATCHES "Linux")
    install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/bin) # Installs CPM - MacOS / Linux - sudo required (sudo make install)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    install(TARGETS ${PROJECT_NAME} DESTINATION $ENV{ProgramFiles}) # Installs CPM - Windows (make install)
endif()