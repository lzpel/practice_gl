cmake_minimum_required(VERSION 3.12)
project(gear)

include_directories(./ ./include)
link_directories(./lib)

file(GLOB sourcefiles "*.h" "*.cpp" "*.c")
add_executable(${PROJECT_NAME} ${sourcefiles})

target_link_libraries(${PROJECT_NAME} glfw3)