cmake_minimum_required(VERSION 3.6)
project(ZBP_matrix)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB LIB_SOURCES src/*.cpp)
file(GLOB LIB_HEADERS src/*.h)
add_library(Matrix ${LIB_SOURCES} ${LIB_HEADERS})

add_executable(scratch scratch/main.cpp)
target_link_libraries(scratch Matrix)

add_executable(unittest
        test/catch.hpp
        test/framework.cpp
        test/creating.cpp
        test/operations.cpp
        test/views.cpp
        test/iterator.cpp
        test/put.cpp
        test/det.cpp
        test/concat.cpp
)
target_link_libraries(unittest Matrix)

