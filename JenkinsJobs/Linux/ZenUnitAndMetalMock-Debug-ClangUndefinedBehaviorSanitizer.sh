#!/bin/bash
set -ev

export PYTHONPATH=ZenUnitPy
export CXX=/usr/bin/clang++
export UBSAN_OPTIONS=halt_on_error=true
python -u ZenUnitPy/ZenUnitPy/BuildAndTestZenUnitAndMetalMock.py \
   --cmake-generator=Ninja \
   --cmake-build-type=Debug \
   --cmake-definitions="-DClangUndefinedBehaviorSanitizerMode=ON"
