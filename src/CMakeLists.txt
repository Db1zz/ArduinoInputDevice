cmake_minimum_required(VERSION 3.12)
project(InputDevice)

add_executable(main main.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../keyboardLib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../mouseLib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../transmitterLib)

set_target_properties(
    main PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(main PUBLIC Keyboard)
target_link_libraries(main PUBLIC Mouse)
target_link_libraries(main PUBLIC Transmitter)