#!/bin/bash
set -ev

export CXX=/usr/bin/g++
export PYTHONPATH=ZenUnitPy
python ZenUnitPy/ZenUnitPy/BuildZenUnitAndMetalMock.py --cmake-generator=Ninja --cmake-build-type=Debug --cmake-definitions=""
