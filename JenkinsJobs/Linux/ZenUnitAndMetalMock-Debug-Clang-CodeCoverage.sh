#!/bin/bash
set -ev

export PYTHONPATH=ZenUnitDevOpsPython
export CXX=/usr/bin/clang++
python -u ZenUnitDevOpsPython/ZenUnitDevOpsPython/BuildAndTestZenUnitAndMetalMock.py \
   --cmake-build-type=Debug \
   --cmake-definitions="-DClangCodeCoverageMode=ON"

LinuxCodeCoverageRunner measure-cplusplus-code-coverage --solution=ZenUnitAndMetalMock --tests-project=ZenUnitUtilsAndAssertionTests
