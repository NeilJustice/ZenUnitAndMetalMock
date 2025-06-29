#!/bin/bash
set -ev

export PYTHONPATH=ZenUnitDevOpsPython
export CXX=/usr/bin/clang++
python -u ZenUnitDevOpsPython/ZenUnitDevOpsPython/BuildAndTestZenUnitAndMetalMock.py \
   --cmake-build-type=Debug \
   --cmake-definitions="-DFastLinuxDebugBuildMode=ON"
heaptrack Debug/ZenUnitUtilsAndAssertionTests/ZenUnitUtilsAndAssertionTests --random-seed=0
