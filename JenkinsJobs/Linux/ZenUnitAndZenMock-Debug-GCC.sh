#!/bin/bash
set -e
CXX=/usr/bin/g++ python3 ZenUnitPy/ZenUnitPy/BuildZenUnitAndZenMock.py --cmake-generator=Ninja --cmake-architecture=x64 --cmake-build-type=Debug --cmake-definitions=""

