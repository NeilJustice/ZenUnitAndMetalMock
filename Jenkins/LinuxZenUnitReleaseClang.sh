#!/bin/bash
set -e
CXX=/usr/bin/clang++ python3 ZenUnitPy/ZenUnitPy/BuildZenUnit.py --generator=Ninja --buildType=Release --definitions="" --installDirectory=/usr/local
CXX=/usr/bin/clang++ python3 ZenUnitPy/ZenUnitPy/BuildZenUnitHelloWorld.py --generator=Ninja --buildType=Release --definitions=""
