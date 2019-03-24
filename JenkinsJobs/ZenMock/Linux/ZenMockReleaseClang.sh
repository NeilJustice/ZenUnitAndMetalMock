#!/bin/bash
set -e
CXX=/usr/bin/clang++ python3 ../ZenUnit/ZenUnitPy/ZenUnitPy/BuildZenUnitOrZenMock.py --ZenUnitOrZenMock=ZenMock --generator=Ninja --buildType=Release --definitions=""
