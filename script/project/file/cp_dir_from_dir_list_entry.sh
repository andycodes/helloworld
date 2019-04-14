#!/bin/bash
filepath=$(cd "$(dirname "$0")"; pwd)
subdir=/obj

while read line
do
dirpath=${filepath}${subdir}$line
father_dir=`dirname $dirpath`
mkdir -p ${father_dir}
cp -arfR $line ${father_dir}
done < dir_list.txt