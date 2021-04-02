#!/usr/bin/env bash
#
# usage: bash -x ./run.sh
#

declare -r dir_scripts=`pwd`/scripts
declare -r dir_vcpkg=`pwd`/externals/vcpkg
declare -r cmd_vcpkg=$dir_vcpkg/vcpkg

if ! [ -d "$dir_vcpkg" ]; then
  bash -x $dir_scripts/install/linux.sh
fi

bash -x $dir_scripts/fmt.sh

bash -x $dir_scripts/build.sh

bash -x $dir_scripts/tmux.sh
