#!/bin/bash
set -ev

export CXX=/usr/bin/clang++
export PYTHONPATH=.
export UBSAN_OPTIONS=halt_on_error=true
python -u ZenUnitDevOpsPython/BuildAndTestZenUnitAndMetalMock.py \
   --cmake-generator=Ninja \
   --cmake-build-type=RelWithDebInfo \
   --cmake-definitions="-DClangUndefinedBehaviorSanitizerMode=ON -DFastLinuxReleaseBuildMode=ON"
