#!/bin/bash

cd `dirname $0`
mkdir dependency dependency/src
cd dependency

# glfw for window

curl -L https://github.com/glfw/glfw/archive/3.3.2.tar.gz | tar -zxv --transform="s,^[^/]+/,glfw/,x;"

# glad for opengl loader
cp -r glfw/deps/glad* src/

