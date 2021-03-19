#!/usr/bin/env bash

declare -r proj=GNet
declare -r dir_build=build
declare -r client=${proj}_client.out

rm -rf $dir_build; 

bash -x ./$dir_scripts/fmt.sh

mkdir $dir_build; 

cmake -B $dir_build .

make -C $dir_build; 

./$build/$client
