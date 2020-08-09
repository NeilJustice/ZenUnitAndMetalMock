#!/bin/bash
set -e
CXX=/usr/bin/clang++ UBSAN_OPTIONS=halt_on_error=true python ZenUnitPy/ZenUnitPy/BuildAndInstallZenUnitAndMetalMock.py --cmake-generator=Ninja --cmake-architecture=x64 --cmake-build-type=Debug --cmake-definitions="-DClangSanitizerMode_AddressAndUndefined=ON"

