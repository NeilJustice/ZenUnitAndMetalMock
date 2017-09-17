#!/bin/bash
set -e
UBSAN_OPTIONS=halt_on_error=true python3 ZenUnitPy/ZenUnitPy/BuildZenUnit.py --generator=Ninja --buildType=Debug --additionalDefinitions="-DSanitizersMode=ON"
UBSAN_OPTIONS=halt_on_error=true python3 ZenUnitPy/ZenUnitPy/BuildZenUnitHelloWorld.py --generator=Ninja --buildType=Debug --additionalDefinitions="-DSanitizersMode=ON"
