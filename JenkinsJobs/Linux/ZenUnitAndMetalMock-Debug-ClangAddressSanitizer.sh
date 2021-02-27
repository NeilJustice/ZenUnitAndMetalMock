#!/bin/bash
set -ev

export PYTHONPATH=ZenUnitPy
export CXX=/usr/bin/clang++
python ZenUnitPy/ZenUnitPy/BuildZenUnitAndMetalMock.py --cmake-generator=Ninja --cmake-build-type=Debug --cmake-definitions="-DClangAddressSanitizerMode=ON"
