#!/bin/bash
set -e
CXX=/usr/bin/clang++ UBSAN_OPTIONS=halt_on_error=true python3 ZenUnitPy/ZenUnitPy/BuildZenUnit.py --generator=Ninja --buildType=Debug --definitions="-DSanitizersMode=ON" --installDirectory=NoInstall
CXX=/usr/bin/clang++ UBSAN_OPTIONS=halt_on_error=true python3 ZenUnitPy/ZenUnitPy/BuildZenUnitHelloWorld.py --generator=Ninja --buildType=Debug --definitions="-DSanitizersMode=ON"
