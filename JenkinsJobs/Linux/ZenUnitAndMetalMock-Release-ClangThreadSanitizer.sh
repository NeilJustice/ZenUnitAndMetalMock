#!/bin/bash
set -ev
CXX=/usr/bin/clang++ python ZenUnitPy/ZenUnitPy/BuildZenUnitAndMetalMock.py \
   --cmake-generator=Ninja --cmake-build-type=Release --cmake-definitions="-DClangSanitizerMode_Thread=ON"
