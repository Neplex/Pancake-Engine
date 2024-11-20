cmake_minimum_required(VERSION 3.16)

# Define the project
project(Pancake VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define the project configuration options
option(PANCAKE_DEBUG "Enable Pancake Debugging" ON)

if(PANCAKE_DEBUG)
    add_definitions(-D PANCAKE_DEBUG)
endif()

# Include header files
include_directories(${CMAKE_SOURCE_DIR}/include)

# Collect all source files
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
find_package(Lua 5.3 REQUIRED)

# Include dependencies using FetchContent when necessary
include(FetchContent)

# Fetch Box2D
FetchContent_Declare(
        box2d
        GIT_REPOSITORY https://github.com/erincatto/box2d.git
        GIT_TAG v2.4.0
)
FetchContent_MakeAvailable(box2d)

# Fetch tmxparser
FetchContent_Declare(
        tmxparser
        GIT_REPOSITORY https://github.com/sainteos/tmxparser.git
        GIT_TAG v2.1.0
)
FetchContent_MakeAvailable(tmxparser)

# Fetch ImGui
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.68
)
FetchContent_MakeAvailable(imgui)
set(IMGUI_DIR ${imgui_SOURCE_DIR})

# Fetch ImGui-SFML
# Disable internal SFML finding in imgui-sfml (add this line)
set(IMGUI_SFML_FIND_SFML OFF)
FetchContent_Declare(
        imgui_sfml
        GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
        GIT_TAG v2.1
)
FetchContent_MakeAvailable(imgui_sfml)

# Create the executable target
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Link libraries to the executable
set(LINK_LIBRARIES
        ${OPENGL_LIBRARIES}
        ${LUA_LIBRARIES}
        sfml-system
        sfml-window
        sfml-graphics
        box2d
        tmxparser
        ImGui-SFML
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LINK_LIBRARIES})

# Add include directories for dependencies
# Note: Modern CMake uses `target_include_directories` instead of global `include_directories`
target_include_directories(${PROJECT_NAME} PRIVATE
        ${LUA_INCLUDE_DIR}
        ${IMGUI_INCLUDE_DIR}
        ${box2d_SOURCE_DIR}/include
        ${imgui_sfml_SOURCE_DIR}
        ${tmxparser_SOURCE_DIR}/src
        ${tmxparser_BINARY_DIR}
)

# Enable strict warnings
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(WARNINGS -Wall -Wextra -Wpedantic -Wformat-security)
    target_compile_options(${PROJECT_NAME} PRIVATE ${WARNINGS})
endif()

# Print a summary of the configuration
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Debug Mode: ${PANCAKE_DEBUG}")
message(STATUS "Source Files: ${SOURCE_FILES}")
message(STATUS "Box2D: ${box2d_SOURCE_DIR}")
message(STATUS "ImGui: ${imgui_SOURCE_DIR}")
message(STATUS "ImGui-SFML: ${imgui_sfml_SOURCE_DIR}")
message(STATUS "TMXParser: ${tmxparser_SOURCE_DIR}")
