#!/bin/bash
set -e
python ZenUnitPy/ZenUnitPy/RunZenUnitPyTestsWithCoverageAndLinting.py
CXX=/usr/bin/clang++ python ZenUnitPy/ZenUnitPy/BuildAndInstallZenUnitAndZenMock.py --cmake-generator=Ninja --cmake-architecture=x64 --cmake-build-type=Debug --cmake-definitions=""

