#!/bin/bash
set -e
python3 ZenUnitPy/ZenUnitPy/CMakeBuildZenUnit.py --compiler=/usr/bin/clang++ --generator=Ninja --buildType=Release --definitions="" --installDirectory=/usr/local
python3 ZenUnitPy/ZenUnitPy/CMakeBuildZenUnitHelloWorld.py --generator=Ninja --buildType=Release --definitions=""
