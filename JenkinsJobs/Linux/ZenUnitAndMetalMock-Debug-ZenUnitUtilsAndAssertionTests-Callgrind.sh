#!/bin/bash
set -ev

export PYTHONPATH=.
export CXX=/usr/bin/clang++
python -u ZenUnitDevOpsPython/BuildAndTestZenUnitAndMetalMock.py \
   --cmake-generator=Ninja \
   --cmake-build-type=Debug \
   --cmake-definitions="-DFastLinuxDebugBuildMode=ON"
time valgrind --tool=callgrind \
   --cache-sim=yes \
   --branch-sim=yes \
   Debug/ZenUnitUtilsAndAssertionTests/ZenUnitUtilsAndAssertionTests \
   --random-seed=0 2> callgrind_results.txt
cat callgrind_results.txt
