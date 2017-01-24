FILE(GLOB_RECURSE SOURCE_FILES ../libs/* *)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
add_executable(Pancake ${SOURCE_FILES})

target_link_libraries(Pancake ${SFML_LIB_DEBUG})