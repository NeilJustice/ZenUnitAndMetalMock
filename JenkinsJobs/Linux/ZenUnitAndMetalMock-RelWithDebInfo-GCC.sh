#!/bin/bash
set -ev

export CXX=/usr/bin/g++
export PYTHONPATH=ZenUnitDevOpsPython
python -u ZenUnitDevOpsPython/ZenUnitDevOpsPython/BuildAndTestZenUnitAndMetalMock.py \
   --cmake-build-type=RelWithDebInfo \
   --cmake-definitions="-DFastLinuxReleaseBuildMode=ON"
