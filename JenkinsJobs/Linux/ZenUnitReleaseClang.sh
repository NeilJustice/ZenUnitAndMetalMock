#!/bin/bash
set -e
CXX=/usr/local/bin/clang++ python3 ZenUnitPy/ZenUnitPy/BuildZenUnitOrZenMock.py --generator=Ninja --buildType=Release --definitions=""

