#!/bin/bash

PREFIX="x86_64"
echo $1while getopts ":i686:x86_64" optKey; do
	case "$optKey" in
		i686) PREFIX="i686"
		x86_64) ;;
  esac
done
find -name "SDL2*.tar.gz" | xargs -I{} tar zxvf {} --transform="s,^[^/]+/x86_64[^/]+/(bin|include|lib),\1,x;s,^SDL2,/dev/null/,x" --absolute-names --show-transformed-names