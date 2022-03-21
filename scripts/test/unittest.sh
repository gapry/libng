#!/usr/bin/env bash

declare -r proj=libng
declare -r dir_build=build
declare -r dir_scripts=scripts
declare -r unnittest=${proj}_unittest.out

rm -rf $dir_build; 

bash -x $dir_scripts/fmt.sh

mkdir $dir_build; 

cmake -B $dir_build .

make -C $dir_build; 

$dir_build/$unnittest
