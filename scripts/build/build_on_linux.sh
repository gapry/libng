#!/bin/sh

export dir_build=`pwd`/build

rm -rf $dir_build; 

mkdir $dir_build; 

cmake -B $dir_build .

make -C $dir_build; 
