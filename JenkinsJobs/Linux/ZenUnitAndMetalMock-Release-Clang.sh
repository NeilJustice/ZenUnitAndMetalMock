#!/bin/bash
set -ev
PYTHONPATH=ZenUnitPy CXX=/usr/bin/clang++ python ZenUnitPy/ZenUnitPy/BuildZenUnitAndMetalMock.py --cmake-generator=Ninja --cmake-build-type=Release --cmake-definitions=""
