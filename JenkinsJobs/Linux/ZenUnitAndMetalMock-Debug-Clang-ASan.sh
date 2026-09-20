#!/bin/bash
set -ev

export CXX=clang++
LinuxCPlusPlusBuilder build-cpp-solution \
   --solution=ZenUnitAndMetalMock \
   --configuration=Debug \
   --cmake-definitions="-DClangAddressSanitizerMode=ON" \
   --install=false

./TestScripts/RunAllDebugTests.sh
