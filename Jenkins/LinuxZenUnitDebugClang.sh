#!/bin/bash
set -e
python3 ZenUnitPy/ZenUnitPy/RunTestsWithCoverageAndPylintFlake8.py
python3 ZenUnitPy/ZenUnitPy/BuildZenUnit.py --compiler"/usr/bin/clang++" --generator=Ninja --buildType=Debug --definitions="" --installDirectory=/usr/local
python3 ZenUnitPy/ZenUnitPy/BuildZenUnitHelloWorld.py --compiler=/usr/bin/clang++ --generator=Ninja --buildType=Debug --definitions=""
