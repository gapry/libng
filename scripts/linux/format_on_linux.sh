#!/bin/sh

export dir_list=( benchmark game libng test third_party )

for dir in ${dir_list[@]}; do
  find `pwd`/$dir -type f -iname "*.cpp" -o -iname "*.hpp" -o -iname "*.h"  | 
    xargs clang-format -style=file -i
done

