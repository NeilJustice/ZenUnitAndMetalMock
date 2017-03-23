#!/bin/bash
set -eu
export CXX=/usr/bin/clang++
python3 ZenUnitPy/ZenUnitPy/BuildAndInstall.py Ninja Debug ZenUnit ZenUnit.Test "clang version" -DAddressSanitizerMode=ON NoInstall
