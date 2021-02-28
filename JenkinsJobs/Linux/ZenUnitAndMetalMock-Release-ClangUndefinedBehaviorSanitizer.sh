#!/bin/bash
set -ev

export CXX=/usr/bin/clang++
export PYTHONPATH=ZenUnitPy
export UBSAN_OPTIONS=halt_on_error=true
python ZenUnitPy/ZenUnitPy/BuildZenUnitAndMetalMock.py --cmake-generator=Ninja --cmake-build-type=Release --cmake-definitions="-DClangUndefinedBehaviorSanitizerMode=ON"
