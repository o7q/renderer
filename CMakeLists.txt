cmake_minimum_required(VERSION 3.10)

project(renderer)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "src/*.c")
add_executable(renderer ${SOURCES})