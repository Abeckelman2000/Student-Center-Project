cmake_minimum_required(VERSION 3.22)
project(untitled)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES main.cpp funcs.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY StudentCenter)

add_executable(untitled main.cpp student.cpp student.h course.h course.cpp funcs.h funcs.cpp)
