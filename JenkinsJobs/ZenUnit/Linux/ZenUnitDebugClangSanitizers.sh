#!/bin/bash
set -e
CXX=/usr/bin/clang++ UBSAN_OPTIONS=halt_on_error=true python3 ZenUnitPy/ZenUnitPy/BuildZenUnitOrZenMock.py --zenunit-or-zenmock=ZenUnit --cmake-generator=Ninja --cmake-build-type=Debug --cmake-definitions="-DSanitizersMode=ON"
