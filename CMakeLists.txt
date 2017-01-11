cmake_minimum_required(VERSION 3.6)
project(Projet)

set(CMAKE_CXX_STANDARD 11)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(OperatingSystem "Windows")
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/lib/Windows-SFML-2.4.1/cmake/Modules/) # You will probably have to change this
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # Linux specific code
    set(OperatingSystem "Linux")
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/lib/Linux-SFML-2.4.1/share/SFML/cmake/Modules/)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(CMAKE_BUILD_TYPE Release) #If you have problems check if you have SFML debug libraries or release libraries
find_package(SFML REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR} ${PROJECT_SOURCE_DIR})
set(SOURCE_FILES main.cpp   )
set(HEADER_FILES            )
add_executable(Projet ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(Projet ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})