cmake_minimum_required(VERSION 3.16)
project(tinyEngine)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)

# Add source files
file(GLOB_RECURSE SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/src/*.c
        ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES
        ${CMAKE_SOURCE_DIR}/src/*.h
        ${CMAKE_SOURCE_DIR}/src/*.hpp)

# GLFW build configuration

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(Dependencies/glfw)

# end
# ------------------------
# GLEW build configuration

add_subdirectory(Dependencies/glew)
include_directories(Dependencies/glew/include)
add_library(glew STATIC Dependencies/glew/src/glew.c src/Mesh.cpp src/Mesh.h)
add_definitions(-DGLEW_STATIC)
# end

# Assimp build configuration

add_subdirectory(Dependencies/assimp)
include_directories(Dependencies/assimp/include)
# end

# ------------------------
# Header-only libraries

include_directories(Dependencies/glm)
include_directories(Dependencies/stb)
include_directories(Dependencies/irrKlang/include)
include_directories(Dependencies/freetype/include)
# end

link_directories(Dependencies/irrKlang/bin)
link_directories(Dependencies/freetype/lib)

add_executable(tinyEngine ${HEADER_FILES} ${SOURCE_FILES} )

target_link_libraries(tinyEngine glfw glew freetype IrrKlang assimp ${OPENGL_LIBRARY})
