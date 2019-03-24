#!/bin/bash
set -e
CXX=/usr/bin/clang++ python3 ZenUnitPy/ZenUnitPy/BuildZenUnitOrZenMock.py --zenunit-or-zenmock=ZenMock --cmake-generator=Ninja --cmake-build=type=Debug --cmake-definitions=""
