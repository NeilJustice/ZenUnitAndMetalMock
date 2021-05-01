#!/bin/bash
set -ev

export CXX=/usr/bin/g++
export PYTHONPATH=ZenUnitPy
python ZenUnitPy/ZenUnitPy/BuildAndTestZenUnitAndMetalMock.py --cmake-generator=Ninja --cmake-build-type=Release --cmake-definitions=""
