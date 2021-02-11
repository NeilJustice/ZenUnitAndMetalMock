#!/bin/bash
set -ev
PYTHONPATH=ZenUnitPy CXX=/usr/bin/g++ python ZenUnitPy/ZenUnitPy/BuildZenUnitAndMetalMock.py --cmake-generator=Ninja --cmake-build-type=Debug --cmake-definitions=""
