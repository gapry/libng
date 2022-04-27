#!/bin/sh

export dir_build=`pwd`/build

rm -rf $dir_build

mkdir $dir_build

cd $dir_build

cmake -DBUILD_SAMPLE=ON ..

make -j$(nproc)

./sample/libng_sample