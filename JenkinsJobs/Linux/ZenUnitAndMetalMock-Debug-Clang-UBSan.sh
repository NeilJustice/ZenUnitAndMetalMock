#!/bin/bash
set -ev

export CXX=clang++
LinuxCPlusPlusBuilder build-cpp-solution \
   --solution-name=ZenUnitAndMetalMock \
   --configuration=Debug \
   --cmake-definitions="-DClangUndefinedBehaviorSanitizerMode=ON" \
   --install=false
