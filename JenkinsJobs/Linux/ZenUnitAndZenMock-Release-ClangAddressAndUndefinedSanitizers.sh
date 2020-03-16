#!/bin/bash
set -e
CXX=/usr/bin/clang++ python ZenUnitPy/ZenUnitPy/BuildAndInstallZenUnitAndZenMock.py --cmake-generator=Ninja --cmake-architecture=x64 --cmake-build-type=Release --cmake-definitions="-DClangSanitizerMode_AddressAndUndefined=ON"

