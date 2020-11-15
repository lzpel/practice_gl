cmake_minimum_required(VERSION 3.12)
project(glfw-engine)

# libraries with CMake
# glfw glfwを使う他のデモとの衝突を避ける
if(NOT TARGET glfw)
	set(GLFW_BUILD_EXAMPLES FALSE)
	add_subdirectory(dependency/glfw)
	include_directories(${GLFW3_INCLUDE_DIR})
endif()

# libraries without CMake
include_directories(dependency/src src/ src/node)
file(GLOB dep "dependency/src/*.cpp" "dependency/src/*.c")

# target
file(GLOB src "src/*.cpp" "src/node/*.cpp")
add_executable(${PROJECT_NAME} ${src} ${dep})
target_link_libraries(${PROJECT_NAME} glfw)