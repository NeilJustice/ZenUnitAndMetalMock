#!/bin/bash
set -ev

export CXX=/usr/bin/clang++
export PYTHONPATH=.
python ZenUnitDevOpsPython/BuildAndTestZenUnitAndMetalMock.py \
   --cmake-generator=Ninja \
   --cmake-build-type=Release \
   --cmake-definitions="-DFastLinuxReleaseBuildMode=ON"
