cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(sticky-potatoes)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(all_tests all_tests.cpp)
target_sources(all_tests PRIVATE aad.cpp aad_tests.cpp shifted_sabr.cpp shifted_sabr_tests.cpp)
