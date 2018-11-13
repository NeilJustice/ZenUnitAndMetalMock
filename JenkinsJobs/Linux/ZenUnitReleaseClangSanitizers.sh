#!/bin/bash
set -e
CXX=/usr/bin/clang++ python3 ZenUnitPy/ZenUnitPy/BuildZenUnit.py --generator=Ninja --buildType=Release --definitions=""

