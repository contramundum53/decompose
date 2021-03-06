cmake_minimum_required(VERSION 3.21)
project(decompose)

set(CMAKE_CXX_STANDARD 20)

# if toplevel
message(${CMAKE_CURRENT_LIST_DIR})
if(PROJECT_IS_TOP_LEVEL)
    include_directories(include)
    add_executable(test_decompose test/test_decompose.cpp)
    
    find_package(cereal)
    if(cereal_FOUND)
        message("cereal: found")
        add_executable(test_cereal_integration test/test_cereal_integration.cpp)
        target_link_libraries(test_cereal_integration cereal::cereal)
    else()
        message("cereal: not found. Skipping test_cereal_integration.")
    endif()
else()
    add_library(decompose INTERFACE)
    target_include_directories(decompose PUBLIC include)
endif()