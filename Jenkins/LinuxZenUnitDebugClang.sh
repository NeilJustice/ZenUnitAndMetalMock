#!/bin/bash
set -e
python3 ZenUnitPy/ZenUnitPy/RunTestsWithCoverageAndLinting.py
CXX=/usr/local/bin/clang++ python3 ZenUnitPy/ZenUnitPy/BuildZenUnit.py --generator=Ninja --buildType=Debug --definitions="" --installDirectory=NoInstall
