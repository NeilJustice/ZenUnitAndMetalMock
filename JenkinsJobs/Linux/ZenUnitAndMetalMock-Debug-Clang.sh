#!/bin/bash
set -ev

export PYTHONPATH=.
export CXX=/usr/bin/clang++
python -u ZenUnitDevOpsPython/BuildAndTestZenUnitAndMetalMock.py \
   --cmake-build-type=Debug \
   --cmake-definitions="-DFastLinuxDebugBuildMode=ON"
