#!/bin/bash
set -ev

export CXX=/usr/bin/g++
export PYTHONPATH=ZenUnitDevOpsPython
python ZenUnitDevOpsPython/ZenUnitDevOpsPython/BuildAndTestZenUnitAndMetalMock.py --cmake-generator=Ninja --cmake-build-type=Debug --cmake-definitions=""
