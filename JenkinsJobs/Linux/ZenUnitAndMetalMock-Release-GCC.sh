#!/bin/bash
set -ev

export CXX=/usr/bin/g++
export PYTHONPATH=.
python ZenUnitDevOpsPython/BuildAndTestZenUnitAndMetalMock.py --cmake-generator=Ninja --cmake-build-type=Release --cmake-definitions=""
