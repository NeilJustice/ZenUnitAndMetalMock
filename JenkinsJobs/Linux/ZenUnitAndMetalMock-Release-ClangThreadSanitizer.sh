#!/bin/bash
set -ev

export PYTHONPATH=.
export CXX=/usr/bin/clang++
python ZenUnitDevOpsPython/BuildAndTestZenUnitAndMetalMock.py \
   --cmake-generator=Ninja \
   --cmake-build-type=Release \
   --cmake-definitions="-DClangThreadSanitizerMode=ON -DFastLinuxReleaseBuildMode=ON"
