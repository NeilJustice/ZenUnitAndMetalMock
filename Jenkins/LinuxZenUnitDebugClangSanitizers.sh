#!/bin/bash
set -eu
export CXX=/usr/local/bin/clang++
UBSAN_OPTIONS=halt_on_error=true python3 ZenUnitPy/ZenUnitPy/BuildAndInstall.py Ninja Debug ZenUnit ZenUnitTests "clang version" -DSanitizersMode=ON NoInstall
