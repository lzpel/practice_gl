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

# target
set(MIN_COMPILE "-O2 -Os -DNDEBUG -s")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${MIN_COMPILE}")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${MIN_COMPILE}")
if (CMAKE_BUILD_TYPE STREQUAL Release)
	set(SYSTEM WIN32)
endif()

# build

include_directories(src/)
file(GLOB src "src/*.cpp" "src/node/*.cpp")
add_executable(${PROJECT_NAME} ${SYSTEM} ${src} ${dep})
target_link_libraries(${PROJECT_NAME} glfw)