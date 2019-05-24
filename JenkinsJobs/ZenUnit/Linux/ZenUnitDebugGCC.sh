#!/bin/bash
set -e
CXX=/usr/bin/g++ python3 ZenUnitPy/ZenUnitPy/BuildZenUnitOrZenMock.py --zenunit-or-zenmock=ZenUnit --cmake-generator=Ninja --cmake-build-type=Debug --cmake-definitions=""
