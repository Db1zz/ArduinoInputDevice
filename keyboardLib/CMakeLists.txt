cmake_minimum_required(VERSION 3.12)
project(InputDevice)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../transmitterLib)

add_library(Keyboard STATIC Keyboard.cpp Keyboard.h)
set_target_properties(
                    Keyboard PROPERTIES
                    CXX_STANDARD 20
                    CXX_STANDARD_REQUIRED ON
)
target_link_libraries(Keyboard PUBLIC Transmitter)