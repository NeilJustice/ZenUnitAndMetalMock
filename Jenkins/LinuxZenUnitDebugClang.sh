#!/bin/bash
set -e
python3 ZenUnitPy/ZenUnitPy/RunTestsWithCoverageAndPylintFlake8.py
CXX=/usr/bin/clang++ python3 ZenUnitPy/ZenUnitPy/BuildZenUnit.py --generator=Ninja --buildType=Debug --definitions=\"\" --installDirectory=/usr/local
CXX=/usr/bin/clang++ python3 ZenUnitPy/ZenUnitPy/BuildZenUnitHelloWorld.py --generator=Ninja --buildType=Debug --definitions=\"\"
