#!/bin/bash
set -eu
python3 ZenUnitPy/ZenUnitPy/CoveragePylintFlake8.py ZenUnitPy/ZenUnitPy.Test RunAllWithCoverage.py
export CXX=/usr/bin/clang++
python3 ZenUnitPy/ZenUnitPy/BuildAndInstall.py Ninja Debug ZenUnit ZenUnitTests "clang version" "-DClangTidyMode=ON -DCMAKE_INSTALL_PREFIX=/usr/local" Install
cd ZenUnitHelloWorld
python3 ../ZenUnitPy/ZenUnitPy/BuildAndInstall.py Ninja Debug StaticLibrary StaticLibraryTests "" "" NoInstall
