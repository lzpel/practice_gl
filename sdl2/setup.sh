#!/bin/bash

cd `dirname $0`
mkdir dependency dependency/src
cd dependency

# glfw for window

curl -L https://www.libsdl.org/release/SDL2-2.0.12.tar.gz | tar -zxv --transform="s,^[^/]+/,sdl2/,x;"
