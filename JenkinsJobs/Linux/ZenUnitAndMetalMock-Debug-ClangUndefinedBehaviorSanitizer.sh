#!/bin/bash
set -ev

export PYTHONPATH=.
export CXX=/usr/bin/clang++
export UBSAN_OPTIONS=halt_on_error=true
python -u ZenUnitDevOpsPython/BuildAndTestZenUnitAndMetalMock.py \
   --cmake-generator=Ninja \
   --cmake-build-type=Debug \
   --cmake-definitions="-DClangUndefinedBehaviorSanitizerMode=ON"
