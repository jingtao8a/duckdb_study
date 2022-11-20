cmake_minimum_required(VERSION 3.18)
project("duckdb_study")

add_executable(testbplustree test/testbplustree.cpp src/bplustree.cpp)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)