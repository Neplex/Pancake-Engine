cmake_minimum_required(VERSION 3.6)
# Groupe 12
project(Pancake)

set(CMAKE_CXX_STANDARD 11)

include(CmakeConfig.cmake)
include_directories(${SFML_PATH}/include)

add_subdirectory(src)