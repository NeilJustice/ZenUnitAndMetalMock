#!/bin/bash
set -ev

export PYTHONPATH=ZenUnitPy
export CXX=/usr/bin/clang++
python ZenUnitPy/ZenUnitPy/BuildAndTestZenUnitAndMetalMock.py --cmake-generator=Ninja --cmake-build-type=Debug --cmake-definitions=""
