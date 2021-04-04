#!/bin/sh

export dir_vcpkg=externals/vcpkg
export cmd_vcpkg=$dir_vcpkg/vcpkg

git submodule update --init --recursive

sh -x $dir_vcpkg/bootstrap-vcpkg.sh

$cmd_vcpkg install fmt --recurse
$cmd_vcpkg install imgui[sdl2-binding] --recurse
$cmd_vcpkg install imgui[opengl3-glew-binding] --recurse
$cmd_vcpkg install eastl --recurse
