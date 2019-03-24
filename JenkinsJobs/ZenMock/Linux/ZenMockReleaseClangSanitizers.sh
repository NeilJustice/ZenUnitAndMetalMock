#!/bin/bash
set -e
CXX=/usr/bin/clang++ UBSAN_OPTIONS=halt_on_error=true python3 ZenUnitPy/ZenUnitPy/BuildZenUnitOrZenMock.py --zenunit-or-zenmock=ZenMock --cmake-generator=Ninja --cmake-build-type=Release --cmake-definitions="-DSanitizersMode=ON"
