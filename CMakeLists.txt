cmake_minimum_required(VERSION 2.8.4)

project(open_gl)
find_package(PkgConfig REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -DDEBUG")

set(SOURCE_FILES core/ShaderLoader.cpp main.cpp)
add_executable(open_gl ${SOURCE_FILES})

### OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries(open_gl ${OPENGL_LIBRARIES})

### SDL
pkg_search_module(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(open_gl ${SDL2_LIBRARIES})

### GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(open_gl ${GLEW_LIBRARIES})

### GLM
include_directories(${GLM_INCLUDE_DIRS})

### Copy GLSL
add_custom_command(TARGET open_gl POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:open_gl>/shaders)