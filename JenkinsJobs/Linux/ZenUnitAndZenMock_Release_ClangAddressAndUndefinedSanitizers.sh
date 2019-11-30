#!/bin/bash
set -e
CXX=/usr/bin/clang++ python3 ZenUnitPy/ZenUnitPy/BuildZenUnitAndZenMock.py --cmake-generator=Ninja --cmake-architecture=x64 --cmake-build-type=Release --cmake-definitions="ClangSanitizerMode_AddressAndUndefined"

