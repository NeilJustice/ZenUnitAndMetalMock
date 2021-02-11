#!/bin/bash
set -ev
cd ZenUnitPy
PYTHONPATH=. python ZenUnitPy/RunZenUnitPyTestsWithCoverageAndLinting.py
cd ..
PYTHONPATH=ZenUnitPy CXX=/usr/bin/clang++ python ZenUnitPy/ZenUnitPy/BuildZenUnitAndMetalMock.py --cmake-generator=Ninja --cmake-build-type=Debug --cmake-definitions=""
