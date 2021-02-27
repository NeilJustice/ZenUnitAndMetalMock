#!/bin/bash
set -ev

export CXX=/usr/bin/clang++
export PYTHONPATH=ZenUnitPy
python ZenUnitPy/ZenUnitPy/BuildZenUnitAndMetalMock.py --cmake-generator=Ninja --cmake-build-type=Release --cmake-definitions="-DClangThreadSanitizerMode=ON"
