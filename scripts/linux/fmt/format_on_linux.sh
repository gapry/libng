#!/bin/sh

export dir_list=( libcxx libng sample test benchmark )

for dir in ${dir_list[@]}; do
  find `pwd`/$dir -type f -iname "*.cpp" -o -iname "*.hpp" -o -iname "*.h"  | 
    xargs clang-format -style=file -i
done

