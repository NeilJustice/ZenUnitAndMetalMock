#!/bin/bash
set -e
CXX=/usr/bin/clang++ UBSAN_OPTIONS=halt_on_error=true python3 ZenUnitPy/ZenUnitPy/BuildZenUnitOrZenMock.py --ZenUnitOrZenMock=ZenMock --generator=Ninja --buildType=Release --definitions="-DSanitizersMode=ON" --installDirectory=NoInstall
