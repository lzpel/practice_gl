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
include_directories(dependency/src)
file(GLOB dep "dependency/src/*.cpp" "dependency/src/*.c")

# build
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG -DTARGET=WIN32")
include_directories(src/)
file(GLOB src "src/*.cpp" "src/node/*.cpp")
if (CMAKE_BUILD_TYPE STREQUAL "Release")
	set(SYSTEM WIN32)
endif()
add_executable(${PROJECT_NAME} ${SYSTEM} ${src} ${dep})
target_link_libraries(${PROJECT_NAME} glfw)