#!/bin/bash
set -e
CXX=/usr/bin/clang++ python3 ../ZenUnit/ZenUnitPy/ZenUnitPy/BuildZenUnitOrZenMock.py --zenunit-or-zenmock=ZenMock --cmake-generator=Ninja --cmake-build-type=Release --cmake-definitions=""
