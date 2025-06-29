#!/bin/bash
set -ev

export PYTHONPATH=ZenUnitDevOpsPython
export CXX=/usr/bin/clang++
export UBSAN_OPTIONS=halt_on_error=true
python -u ZenUnitDevOpsPython/ZenUnitDevOpsPython/BuildAndTestZenUnitAndMetalMock.py \
   --cmake-build-type=Debug \
   --cmake-definitions="-DClangUndefinedBehaviorSanitizerMode=ON -DFastLinuxDebugBuildMode=ON"
