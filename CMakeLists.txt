cmake_minimum_required(VERSION 3.18)
project("duckdb_study")

add_executable(testbplustree test/testbplustree.cpp src/bplustree.cpp)

add_executable(testtexttable test/testtexttable.cpp src/texttable.cpp)

add_executable(main example/main.cpp src/texttable.cpp src/bplustree.cpp src/duckdbms.cpp)

set(CMAKE_CXX_FLAGS "-std=c++11 -g")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)