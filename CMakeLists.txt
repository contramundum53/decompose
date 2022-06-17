cmake_minimum_required(VERSION 3.21)
project(decompose)

set(CMAKE_CXX_STANDARD 20)

# if toplevel
message(${CMAKE_CURRENT_LIST_DIR})
if(PROJECT_IS_TOP_LEVEL)
    include_directories(include)
    add_executable(test_decompose test/test_decompose.cpp)
else()
    add_library(decompose INTERFACE)
    target_include_directories(decompose PUBLIC include)
endif()