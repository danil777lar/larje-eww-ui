cmake_minimum_required(VERSION 3.31)
project(LarjeUI)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src/eww_ui)
add_subdirectory(larjeuid)
add_subdirectory(larjeuictl)
add_subdirectory(widgets)
add_subdirectory(layouts)