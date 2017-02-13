FILE(GLOB_RECURSE SOURCE_FILES ../libs/* * Imgui/imgui.cpp Imgui/imgui_draw.cpp Imgui/imgui-SFML.cpp Imgui/imgui_demo.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
add_executable(Pancake ${SOURCE_FILES})

set(WARNINGS -Wall -Wextra -Wformat-security)

add_definitions(-D PANCAKE_DEBUG)

if(WIN32)
    set(LIB opengl32)
elseif(UNIX)
    set(LIB GL)
endif()

target_link_libraries(Pancake ${SFML_LIB_DEBUG} ${LIB} ${LIB_LUA})
