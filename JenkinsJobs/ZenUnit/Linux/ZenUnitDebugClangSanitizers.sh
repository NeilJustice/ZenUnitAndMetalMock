#!/bin/bash
set -e
CXX=/usr/bin/clang++ UBSAN_OPTIONS=halt_on_error=true python3 ZenUnitPy/ZenUnitPy/BuildZenUnitOrZenMock.py --ZenUnitOrZenMock=ZenUnit --generator=Ninja --buildType=Debug --definitions="-DSanitizersMode=ON"
