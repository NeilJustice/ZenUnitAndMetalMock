#!/bin/bash
set -eu
python3 ZenUnitPy/ZenUnitPy/BuildAndInstall.py Ninja Debug ZenUnit ZenUnit.Test "GCC:" "" NoInstall
