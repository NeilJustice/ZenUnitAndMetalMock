#!/bin/bash
set -e
cd ZenUnitPy
PYTHONPATH=. python ZenUnitPy/RunZenUnitPyTestsWithCoverageAndLinting.py
cd ..
CXX=/usr/bin/clang++ python ZenUnitPy/ZenUnitPy/BuildZenUnitAndMetalMock.py \
   --cmake-generator=Ninja \
   --cmake-architecture=x64 \
   --cmake-build-type=Debug \
   --cmake-definitions=""
