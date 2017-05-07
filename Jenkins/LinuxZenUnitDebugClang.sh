#!/bin/bash
set -eu
export CXX=/usr/bin/clang++
python3 ZenUnitPy/ZenUnitPy/CoveragePylintFlake8.py ZenUnitPy/ZenUnitPyTests RunAllWithCoverage.py
python3 ZenUnitPy/ZenUnitPy/BuildAndInstall.py Ninja Debug ZenUnit ZenUnitTests "clang version" "" Install
cd ZenUnitHelloWorld
python3 ../ZenUnitPy/ZenUnitPy/BuildAndInstall.py Ninja Debug StaticLibrary StaticLibraryTests "" "" NoInstall
