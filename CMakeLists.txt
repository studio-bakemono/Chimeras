cmake_minimum_required(VERSION 3.1)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS " -static")

project(Chimeras)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

file(GLOB SOURCES "*.cpp")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(Chimeras ${SOURCES} )
target_link_libraries(Chimeras sfml-graphics sfml-audio -static-libgcc -static-libstdc++)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

file(GLOB SFML_DLL "SFML/bin/*.dll")
file(COPY ${SFML_DLL} DESTINATION ${CMAKE_BINARY_DIR})
