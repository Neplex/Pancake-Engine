cmake_minimum_required(VERSION 3.6)
# Groupe 12
project(Pancake)

set(CMAKE_CXX_STANDARD 11)

include(CmakeConfig.cmake)

include_directories(./libs/)
include_directories(${SFML_PATH}/include)
#include_directories(${BOOST_PATH})

add_subdirectory(src)
