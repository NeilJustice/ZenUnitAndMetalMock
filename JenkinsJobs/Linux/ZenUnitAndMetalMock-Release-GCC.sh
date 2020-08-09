#!/bin/bash
set -e
CXX=/usr/bin/g++ python ZenUnitPy/ZenUnitPy/BuildAndInstallZenUnitAndMetalMock.py --cmake-generator=Ninja --cmake-architecture=x64 --cmake-build-type=Release --cmake-definitions=""

