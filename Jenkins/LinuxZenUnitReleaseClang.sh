#!/bin/bash
set -e
python3 ZenUnitPy/ZenUnitPy/BuildZenUnit.py --compiler=/usr/bin/clang++ --generator=Ninja --buildType=Release --definitions="" --installDirectory=/usr/local
python3 ZenUnitPy/ZenUnitPy/BuildZenUnitHelloWorld.py --generator=Ninja --buildType=Release --definitions=""
