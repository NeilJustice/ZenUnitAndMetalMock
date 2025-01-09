#!/bin/bash
set -ev

export CXX=/usr/bin/g++
export PYTHONPATH=.
python -u ZenUnitDevOpsPython/BuildAndTestZenUnitAndMetalMock.py \
   --cmake-generator=Ninja \
   --cmake-build-type=Debug \
   --cmake-definitions="-DFastLinuxDebugBuildMode=ON"
