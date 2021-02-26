#!/bin/bash
set -ev

cd ZenUnitPy
export PYTHONPATH=.
python ZenUnitPy/RunZenUnitPyTestsWithCoverageAndLinting.py
cd ..
export PYTHONPATH=ZenUnitPy
export CXX=/usr/bin/clang++
python ZenUnitPy/ZenUnitPy/BuildZenUnitAndMetalMock.py --cmake-generator=Ninja --cmake-build-type=Debug --cmake-definitions=""
