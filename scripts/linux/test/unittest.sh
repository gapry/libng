#!/usr/bin/env bash

declare -r proj=libng
declare -r dir_build=build 
declare -r dir_test=${dir_build}/test
declare -r unnittest=${proj}_test

rm -rf $dir_build; 

mkdir $dir_build; 

cmake -DBUILD_TEST=ON -B $dir_build .

make -j$(nproc) -C $dir_build; 

$dir_test/$unnittest
