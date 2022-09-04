cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(sticky-potatoes)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(sticky-potatoes aad_tests.cpp)
target_sources(sticky-potatoes PRIVATE aad.cpp)