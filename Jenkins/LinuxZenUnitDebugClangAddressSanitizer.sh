#!/bin/bash
set -eu
export CXX=/usr/bin/clang++
python3 ZenUnitPy/ZenUnitPy/BuildAndInstall.py Ninja Debug ZenUnit ZenUnitTests "clang version" -DAddressSanitizerMode=ON NoInstall
