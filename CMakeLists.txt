cmake_minimum_required(VERSION 2.8.4)
project(open_gl)
find_package(PkgConfig REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp)
add_executable(open_gl ${SOURCE_FILES})

### OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries(open_gl ${OPENGL_LIBRARIES})

### SDL
pkg_search_module(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(open_gl ${SDL2_LIBRARIES})

### GLFW
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(open_gl ${GLFW_LIBRARIES})

### GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(open_gl ${GLEW_LIBRARIES})
