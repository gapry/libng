#!/usr/bin/env bash

declare -r proj=libng
declare -r dir_build=build
declare -r dir_scripts=scripts
declare -r client=${proj}_client.out

rm -rf $dir_build; 

bash -x $dir_scripts/fmt.sh

mkdir $dir_build; 

cmake -B $dir_build .

make -C $dir_build; 

$dir_build/$client
