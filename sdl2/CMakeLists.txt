cmake_minimum_required(VERSION 3.12)
project(mygame)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")

include_directories(./include)
link_directories(./lib)

file(GLOB sourcefiles "*.h" "*.cpp")
add_executable(${PROJECT_NAME} ${sourcefiles})

find_package(OpenGL)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} SDL2_image SDL2 SDL2main)