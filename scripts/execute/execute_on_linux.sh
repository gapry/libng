#!/bin/sh

export dir_scripts=`pwd`/scripts
export dir_vcpkg=`pwd`/externals/vcpkg
export cmd_vcpkg=$dir_vcpkg/vcpkg

sh -x $dir_scripts/install/vcpkg_on_linux.sh

sh -x $dir_scripts/fmt/format_on_linux.sh

sh -x $dir_scripts/build/build_on_linux.sh

sh -x $dir_scripts/execute/tmux_on_linux.sh
