#!/bin/bash
set -e
python3 ZenUnitPy/ZenUnitPy/RunTestsWithCoverageAndPylintFlake8.py
python3 ZenUnitPy/ZenUnitPy/CMakeBuildZenUnit.py --compiler"/usr/bin/clang++" --generator=Ninja --buildType=Debug --installDirectory=/usr/local
python3 ZenUnitPy/ZenUnitPy/CMakeBuildZenUnitHelloWorld.py --compiler=/usr/bin/clang++ --generator=Ninja --configuration=Debug
