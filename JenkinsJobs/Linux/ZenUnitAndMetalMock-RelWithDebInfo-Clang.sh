#!/bin/bash
set -ev

export CXX=clang++
LinuxCPlusPlusBuilder build-cpp-solution \
   --solution=ZenUnitAndMetalMock \
   --configuration=RelWithDebInfo \
   --cmake-definitions="-DFastLinuxReleaseBuildMode=ON" \
   --install=false

./TestScripts/RunAllRelWithDebInfoTests.sh
