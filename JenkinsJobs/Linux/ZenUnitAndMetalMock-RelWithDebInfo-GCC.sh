#!/bin/bash
set -ev

export CXX=/usr/bin/g++
export PYTHONPATH=.
python -u ZenUnitDevOpsPython/BuildAndTestZenUnitAndMetalMock.py \
   --cmake-build-type=RelWithDebInfo \
   --cmake-definitions="-DFastLinuxReleaseBuildMode=ON"
