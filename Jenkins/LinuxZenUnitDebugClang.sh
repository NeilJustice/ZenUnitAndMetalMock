#!/bin/bash
set -eu
python3 ZenUnitPy/ZenUnitPy/CoveragePylintFlake8.py ZenUnitPy/ZenUnitPy.Test RunAllWithCoverage.py
export CXX=/usr/bin/clang++
python3 ZenUnitPy/ZenUnitPy/BuildAndInstall.py Ninja Debug ZenUnit ZenUnit.Test "clang version" -DCMAKE_INSTALL_PREFIX=/usr/local Install
cd ZenUnitTestedProgram
python3 ../ZenUnitPy/ZenUnitPy/BuildAndInstall.py Ninja Debug ZenUnitTestedProgram LibraryNameTests "" -DCMAKE_INSTALL_PREFIX=. Install
cd ..
