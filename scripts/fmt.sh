#!/usr/bin/env bash

declare -r dir_list=( include libcxx src test benchmark )

for dir in ${dir_list[@]}; do
  find `pwd`/$dir -type f -iname "*.cpp" -o -iname "*.h" | 
    xargs clang-format -style=file -i
done

