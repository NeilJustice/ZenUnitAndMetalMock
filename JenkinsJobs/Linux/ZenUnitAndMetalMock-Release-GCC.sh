#!/bin/bash
set -ev
CXX=/usr/bin/g++ python ZenUnitPy/ZenUnitPy/BuildZenUnitAndMetalMock.py --cmake-generator=Ninja --cmake-build-type=Release --cmake-definitions=""
