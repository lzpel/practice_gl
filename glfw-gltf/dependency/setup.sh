#!/bin/bash

# glfw for window

curl -L https://github.com/glfw/glfw/archive/3.3.2.tar.gz | tar -zxv --transform="s,^[^/]+/,glfw/,x;"

# tinygltf for gltf loader

curl -L https://github.com/syoyo/tinygltf/archive/v2.5.0.tar.gz | tar -zxv --transform="s,^[^/]+/,tinygltf/,x;"

# glad for opengl loader
mkdir src/
cp -r glfw/deps/glad* src/

