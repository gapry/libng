#!/bin/sh

export dir_scripts=`pwd`/scripts
export dir_vcpkg=`pwd`/externals/vcpkg
export cmd_vcpkg=$dir_vcpkg/vcpkg

if ! [ -d "$dir_vcpkg" ]; then
  sh -x $dir_scripts/install/linux.sh
fi

sh -x $dir_scripts/fmt.sh

sh -x $dir_scripts/build.sh

sh -x $dir_scripts/tmux.sh
