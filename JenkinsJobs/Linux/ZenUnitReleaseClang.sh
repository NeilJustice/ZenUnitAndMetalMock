#!/bin/bash
set -e

CXX=/usr/bin/clang++ python3 ZenUnitPy/ZenUnitPy/BuildZenUnitAndZenMock.py --cmake-generator=Ninja --cmake-build-type=Release --cmake-definitions=""
