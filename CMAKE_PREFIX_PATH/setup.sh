#!/bin/bash
#set -eux
cd `dirname $0`
mkdir -p bin include lib tmp
curl -LOs https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0-win32.zip
curl -LOs https://github.com/glfw/glfw/releases/download/3.3.2/glfw-3.3.2.bin.WIN64.zip
curl -LOs https://github.com/g-truc/glm/archive/0.9.9.8.zip
find -name "*.zip" | xargs -I{} unzip -q -d tmp -o {}
find tmp -name "*.lib" -or -name "*.a" | grep "64" | xargs -I{} mv -f {} lib/
find tmp -name "*.lib" -or -name "*.a" | xargs -I{} mv -n {} lib/
find tmp -name "include" -type d | xargs -I{} cp -r {} ./
cp -r **/glm-*/glm include/
rm -rf tmp

echo "CMAKE_PREFIX_PATH=`pwd -W` ;"
exit 0

DATA="bin=PATH lib=LABRARY_PATH include=CPATH"
for line  in ${DATA}
do
	line=(${line/=/ })
	mkdir -p ${line[0]}
	line[0]=`cd ${line[0]} ; ${VPWD}`
	# echo "${line[1]}=`eval echo '$'${line[1]}`:${line[0]} ;"
	echo ""
done
