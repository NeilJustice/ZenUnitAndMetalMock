#!/bin/bash
set -eu
export CXX=/usr/local/bin/clang++
python3 ZenUnitPy/ZenUnitPy/CoveragePylintFlake8.py ZenUnitPy/ZenUnitPy.Test RunAllWithCoverage.py
UBSAN_OPTIONS=halt_on_error=true python3 ZenUnitPy/ZenUnitPy/BuildAndInstall.py Ninja Debug ZenUnit ZenUnitTests "clang version" -DSanitizerMode=ON NoInstall
