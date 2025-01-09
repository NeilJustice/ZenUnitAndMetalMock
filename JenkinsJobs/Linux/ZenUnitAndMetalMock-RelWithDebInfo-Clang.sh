#!/bin/bash
set -ev

export CXX=/usr/bin/clang++
export PYTHONPATH=.
python -u ZenUnitDevOpsPython/BuildAndTestZenUnitAndMetalMock.py \
   --cmake-build-type=RelWithDebInfo \
   --cmake-definitions="-DFastLinuxReleaseBuildMode=ON"
