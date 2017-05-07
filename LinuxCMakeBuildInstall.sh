#!/bin/bash
set -eu

if [ $# -ne 1 ]; then
   echo "Usage: ./LinuxCMakeBuildInstall.sh <InstallDirectory>"
   exit 1
fi

function cmake_build_install
{
   local buildType="$1"
   local cmakeInstallPrefix
   cmakeInstallPrefix=$(realpath "$2")
   cmake -H. -B"$buildType" -GNinja \
      -DCMAKE_BUILD_TYPE="$buildType" \
      -DCMAKE_INSTALL_PREFIX="$cmakeInstallPrefix"
   cmake --build "$buildType" --target ZenUnit
   cmake --build "$buildType" --target install
}

cmakeInstallPrefix="$1"
cmake_build_install Debug "$cmakeInstallPrefix"
cmake_build_install Release "$cmakeInstallPrefix"
