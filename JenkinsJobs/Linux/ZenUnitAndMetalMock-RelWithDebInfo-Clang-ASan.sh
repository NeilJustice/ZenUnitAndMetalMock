#!/bin/bash
set -ev

export CXX=clang++
LinuxCPlusPlusBuilder build-cpp-solution \
   --solution-name=ZenUnitAndMetalMock \
   --configuration=RelWithDebInfo \
   --cmake-definitions="-DClangAddressSanitizerMode=ON -DFastLinuxReleaseBuildMode=ON" \
   --install=false
