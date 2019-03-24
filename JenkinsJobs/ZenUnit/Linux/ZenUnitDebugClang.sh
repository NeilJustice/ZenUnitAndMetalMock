#!/bin/bash
set -e
python3 ZenUnitPy/ZenUnitPy/RunZenUnitPyTestsWithCoverageAndLinting.py
CXX=/usr/bin/clang++ python3 ZenUnitPy/ZenUnitPy/BuildZenUnitOrZenMock.py --ZenUnitOrZenMock=ZenUnit --generator=Ninja --buildType=Debug --definitions=""
