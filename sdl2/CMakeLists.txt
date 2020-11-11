cmake_minimum_required(VERSION 3.12)
project(sdl2-triangle)

# libraries linked and included
# glfw glfwを使う他のデモとの衝突を避ける
if(NOT TARGET SDL2)
	add_subdirectory(dependency/sdl2)
	include_directories(${SDL2_SOURCE_DIR}/include)
endif()

# libraries compiled and include
# glad/gl.h
include_directories(dependency/src)
file(GLOB dep "dependency/src/*.cpp" "dependency/src/*.c")

# target
file(GLOB src "src/*.cpp" "src/*.c")
add_executable(${PROJECT_NAME} ${src} ${dep})
target_link_libraries(${PROJECT_NAME} SDL2-static opengl32)