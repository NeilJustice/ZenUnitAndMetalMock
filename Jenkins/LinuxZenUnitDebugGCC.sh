#!/bin/bash
set -eu
python3 ZenUnitPy/ZenUnitPy/BuildAndInstall.py Ninja Debug ZenUnit ZenUnitTests "GCC:" "" NoInstall
