#!/bin/bash

PREFIX="x86_64"
while getopts x86_64:i686: OPT
do
  case $OPT in
    "x86_64" ) ;;
    "i686" ) PREFIX="i686" ;;
  esac
done
find -name "SDL2*.tar.gz" | xargs -I{} tar zxvf {} --transform="s,^[^/]+/${PREFIX}[^/]+/(bin|include|lib),\1,x;s,^SDL2,/dev/null/,x" --absolute-names --show-transformed-names
