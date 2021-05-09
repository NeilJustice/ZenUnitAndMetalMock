#!/bin/bash
set -ev

export PYTHONPATH=ZenUnitDevOpsPython
export CXX=/usr/bin/clang++
python ZenUnitDevOpsPython/ZenUnitDevOpsPython/BuildAndTestZenUnitAndMetalMock.py --cmake-generator=Ninja --cmake-build-type=Debug --cmake-definitions=""
heaptrack Debug/ZenUnitUtilsAndAssertionTests/ZenUnitUtilsAndAssertionTests --random-seed=0
