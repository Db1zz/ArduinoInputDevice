cmake_minimum_required(VERSION 3.12)
project(Input)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../transmitterLib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../keyboardLib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../mouseLib)

add_library(Input STATIC input.cpp input.h)

set_target_properties(
    Input PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(Input PUBLIC Transmitter)
target_link_libraries(Input PUBLIC Keyboard)
target_link_libraries(Input PUBLIC Mouse)