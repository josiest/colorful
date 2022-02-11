# --- project setup ---
cmake_minimum_required(VERSION 3.13)
project(colorful-example)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(colorful REQUIRED)
add_executable(basic basic.cpp)
include_directories(colorful::colorful)
