FILE(GLOB_RECURSE SOURCE_FILES ../libs/* * ../include/imgui/imgui.cpp ../include/imgui/imgui_draw.cpp ../include/imgui/imgui-SFML.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
add_executable(Pancake ${SOURCE_FILES})

add_definitions(-D PANCAKE_DEBUG)

target_link_libraries(Pancake ${SFML_LIB_DEBUG} opengl32)