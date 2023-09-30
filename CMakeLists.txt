cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

#Compiler paths
# set(CMAKE_CXX_COMPILER /usr/local/bin/g++-11)
# set(CMAKE_C_COMPILER /usr/local/bin/gcc-11)
set(CMAKE_BUILD_TYPE Debug)

set(PROJECT_NAME RayTracer)
project(${PROJECT_NAME}  VERSION 1.0)

file(GLOB_RECURSE SRC_FILES src/*.cpp src/*.c)

add_executable(${PROJECT_NAME} main/main.cpp ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/dependencies)

add_subdirectory(dependencies)

set(logl_root "${CMAKE_SOURCE_DIR}")
configure_file(config.h.in config.h)
include_directories(${CMAKE_BINARY_DIR})