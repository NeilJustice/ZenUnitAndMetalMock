#!/bin/bash
set -e
python3 ZenUnitPy/ZenUnitPy/RunZenUnitPyTestsWithCoverageAndLinting.py
CXX=/usr/bin/clang++ python3 ZenUnitPy/ZenUnitPy/Buildzenunit-or-zenmock.py --zenunit-or-zenmock=ZenUnit --cmake-generator=Ninja --cmake-build-type=Debug --cmake-definitions=""
