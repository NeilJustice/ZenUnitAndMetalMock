#!/bin/bash
set -e
CXX=/usr/bin/g++ python3 ZenUnitPy/ZenUnitPy/BuildZenUnitOrZenMock.py --zenunit-or-zenmock=ZenMock --cmake-generator=Ninja --cmake-build-type=Release --cmake-definitions=""
