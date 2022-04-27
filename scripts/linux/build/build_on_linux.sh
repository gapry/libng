#!/bin/sh

export dir_build=`pwd`/build

rm -rf $dir_build

mkdir $dir_build

cd $dir_build

cmake -DBUILD_GAME=ON ..

make -j$(nproc)

./game/libng_game
