#!/bin/bash

cd `dirname $0`
mkdir dependency dependency/src dependency/include
cd dependency

# glfw for window

curl -L https://github.com/glfw/glfw/archive/3.3.2.tar.gz | tar -zxv --transform="s,^[^/]+/,glfw/,x;" --show-transformed-names

# glm for math , to be replaced by my own libraries in the future.

curl -L https://github.com/g-truc/glm/archive/0.9.9.8.tar.gz | tar -zxv --transform="s,^[^/]+/(.*\.(h|hpp|inl))$,src/\1,x;" --show-transformed-names

# tinygltf for gltf loader

curl -L https://github.com/syoyo/tinygltf/archive/v2.5.0.tar.gz | tar -zxv --transform="s,^[^/]+/(.*\.(h|hpp|inl))$,src/\1,x;" --show-transformed-names

# glad for opengl loader

cp -r glfw/deps/glad* src/
