cmake_minimum_required(VERSION 2.6)

project(isotoponyms)

add_executable(isotopo isotopo.cpp town.cpp town.h point2d.cpp point2d.h)

add_definitions(-DsrcPath="${CMAKE_CURRENT_SOURCE_DIR}")
