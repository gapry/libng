#!/bin/sh

export dir_build=`pwd`/build

cmake -B $dir_build $1 .

make -C $dir_build; 
