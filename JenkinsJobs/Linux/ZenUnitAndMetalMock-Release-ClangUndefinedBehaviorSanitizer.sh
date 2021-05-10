#!/bin/bash
set -ev

export CXX=/usr/bin/clang++
export PYTHONPATH=.
export UBSAN_OPTIONS=halt_on_error=true
python ZenUnitDevOpsPython/BuildAndTestZenUnitAndMetalMock.py --cmake-generator=Ninja --cmake-build-type=Release --cmake-definitions="-DClangUndefinedBehaviorSanitizerMode=ON"
