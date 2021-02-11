#!/bin/bash
set -ev
PYTHONPATH=ZenUnitPy CXX=/usr/bin/clang++ UBSAN_OPTIONS=halt_on_error=true python ZenUnitPy/ZenUnitPy/BuildZenUnitAndMetalMock.py \
   --cmake-generator=Ninja --cmake-build-type=Debug --cmake-definitions="-DClangSanitizerMode_Thread=ON"
