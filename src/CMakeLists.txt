FILE(GLOB_RECURSE SOURCE_FILES *)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
add_executable(Pancake ${SOURCE_FILES} ../include/Component.hpp ../include/GameObject.hpp ../include/Transform.hpp ../include/Scene.hpp ../include/SceneManager.hpp ../include/Time.hpp Scene.cpp GameObject.cpp Transform.cpp ../include/SpriteRenderer.hpp SpriteRenderer.cpp ../include/Command.hpp ../include/InputHandler.hpp InputHandler.cpp ../include/Window.hpp Window.cpp)

target_link_libraries(Pancake ${SFML_LIB_DEBUG})