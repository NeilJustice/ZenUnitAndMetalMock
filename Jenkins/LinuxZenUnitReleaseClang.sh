#!/bin/bash
set -eu
export CXX=/usr/bin/clang++
python3 ZenUnitPy/ZenUnitPy/BuildAndInstall.py Ninja Release ZenUnit ZenUnit.Test "clang version" -DCMAKE_INSTALL_PREFIX=/usr/local Install
cd ZenUnitTestedProgram
python3 ../ZenUnitPy/ZenUnitPy/BuildAndInstall.py Ninja Release ZenUnitTestedProgram LibraryNameTests "" -DCMAKE_INSTALL_PREFIX=. Install
cd ..
