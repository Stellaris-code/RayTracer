cmake_minimum_required(VERSION 2.8)

project(RayTracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
option(USE_CLANG_TIDY "Run clang-tidy on build" OFF)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -Wno-potentially-evaluated-expression -mfpmath=sse -ffast-math -fopenmp")

include_directories("include/")

add_subdirectory(src)

