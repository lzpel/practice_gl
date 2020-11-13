#!/bin/bash
#set -eux
cd `dirname $0`
mkdir -p bin include lib tmp
find -name "*.zip" | xargs -I{} unzip -q -d tmp -o {}
find tmp -name "*.lib" -or -name "*.a" | grep "mingw" | xargs -I{} mv -f {} lib/
find tmp -name "*.lib" -or -name "*.a" | xargs -I{} mv -n {} lib/
find tmp -name "include" -type d | xargs -I{} cp -r {} ./
cp -r **/glm-*/glm include/
rm -rf tmp

echo "CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}:`${VPWD}` ;"
echo "PATH=${PATH}:`cd bin ; ${VPWD}` ;"
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
