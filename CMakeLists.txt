cmake_minimum_required(VERSION 3.16)
project(calc LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Agregamos el ejecutable principal
add_executable(calc src/main.cpp src/math_utils.cpp)
target_include_directories(calc PRIVATE include)
