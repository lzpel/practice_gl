#!/bin/bash

mkdir lib include include/GLFW
curl -Lo glfw-.zip https://github.com/glfw/glfw/releases/download/3.3.2/glfw-3.3.2.bin.WIN64.zip && unzip glfw-.zip
find -name "libglfw3.a" | xargs -I{} mv {} lib/
find -name "glfw3.h" | xargs -I{} mv {} include/GLFW/
rm -rf glfw-*