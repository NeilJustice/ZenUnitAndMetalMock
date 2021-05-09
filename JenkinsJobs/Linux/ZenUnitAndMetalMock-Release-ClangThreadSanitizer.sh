#!/bin/bash
set -ev

export PYTHONPATH=ZenUnitDevOpsPython
export CXX=/usr/bin/clang++
python ZenUnitDevOpsPython/ZenUnitDevOpsPython/BuildAndTestZenUnitAndMetalMock.py \
   --cmake-generator=Ninja \
   --cmake-build-type=Release \
   --cmake-definitions="-DClangThreadSanitizerMode=ON"
