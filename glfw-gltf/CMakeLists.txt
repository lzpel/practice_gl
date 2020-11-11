cmake_minimum_required(VERSION 3.12)
project(glfw-gltf)

# libraries linked and included
# glfw glfwを使う他のデモとの衝突を避ける
if(NOT TARGET glfw)
	set(GLFW_BUILD_EXAMPLES OFF)
	add_subdirectory(dependency/glfw)
	include_directories(${GLFW3_INCLUDE_DIR})
endif()

# libraries only included (header only)
# tiny_gltf.h std_image.h glm/gtc/matrix_transform.hpp
include_directories(dependency/tinygltf)
include_directories(dependency/tinygltf/examples/common/glm)

# libraries compiled and include
# glad/gl.h
include_directories(dependency/src)
file(GLOB dep "dependency/src/*.cpp" "dependency/src/*.c")

# target
file(GLOB src "src/*.cpp" "src/*.c")
add_executable(${PROJECT_NAME} ${src} ${dep})
target_link_libraries(${PROJECT_NAME} glfw)