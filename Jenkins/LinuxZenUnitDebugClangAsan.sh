#!/bin/bash
set -eu
export CXX=/usr/local/bin/clang++
python3 ZenUnitPy/ZenUnitPy/BuildAndInstall.py Ninja Debug ZenUnit ZenUnitTests "clang version" -DAddressSanitizerMode=ON NoInstall
