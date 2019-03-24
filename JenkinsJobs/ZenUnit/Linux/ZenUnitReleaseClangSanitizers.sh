#!/bin/bash
set -e
CXX=/usr/bin/clang++ python3 ZenUnitPy/ZenUnitPy/BuildZenUnitOrZenMock.py --zenunit-or-zenmock=ZenUnit --cmake-generator=Ninja --cmake-build-type=Release --cmake-definitions=""
