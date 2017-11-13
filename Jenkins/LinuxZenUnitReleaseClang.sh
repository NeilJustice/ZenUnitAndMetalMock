#!/bin/bash
set -e
CXX=/usr/local/bin/clang++ python3 ZenUnitPy/ZenUnitPy/BuildZenUnit.py --generator=Ninja --buildType=Release --definitions="" --installDirectory=NoInstall
CXX=/usr/local/bin/clang++ python3 ZenUnitPy/ZenUnitPy/BuildZenUnitHelloWorld.py --generator=Ninja --buildType=Release --definitions=""
