cmake_minimum_required(VERSION 3.12)
project(Input)

add_executable(main main.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../transmitterLib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../mouseLib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../keyboardLib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../inputLib)

set_target_properties(
    main PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(main PUBLIC Input)
