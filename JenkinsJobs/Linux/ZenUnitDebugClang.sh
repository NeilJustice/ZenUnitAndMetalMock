#!/bin/bash
set -e

python3 ZenUnitPy/ZenUnitPy/RunZenUnitPyTestsWithCoverageAndLinting.py
CXX=/usr/bin/clang++ python3 ZenUnitPy/ZenUnitPy/BuildZenUnitAndZenMock.py --cmake-generator=Ninja --cmake-build-type=Debug --cmake-definitions=""
