#!/bin/bash
set -ev

export CXX=clang++
LinuxCPlusPlusBuilder build-cpp-solution \
   --solution=ZenUnitAndMetalMock \
   --configuration=RelWithDebInfo \
   --cmake-definitions="-DClangAddressSanitizerMode=ON -DFastLinuxReleaseBuildMode=ON" \
   --install=false

./TestScripts/RunAllRelWithDebInfoTests.sh
