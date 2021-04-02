#!/usr/bin/env bash

declare -r dir_vcpkg=externals/vcpkg
declare -r cmd_vcpkg=$dir_vcpkg/vcpkg

git clone https://github.com/microsoft/vcpkg.git $dir_vcpkg

bash -x $dir_vcpkg/bootstrap-vcpkg.sh

$cmd_vcpkg install fmt --recurse
$cmd_vcpkg install imgui[sdl2-binding] --recurse
$cmd_vcpkg install imgui[opengl3-glew-binding] --recurse
$cmd_vcpkg install eastl --recurse

