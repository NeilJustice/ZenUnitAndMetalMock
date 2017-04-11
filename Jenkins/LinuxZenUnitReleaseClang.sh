#!/bin/bash
set -eu
export CXX=/usr/bin/clang++
python3 ZenUnitPy/ZenUnitPy/BuildAndInstall.py Ninja Release ZenUnit ZenUnitTests "clang version" -DCMAKE_INSTALL_PREFIX=/usr/local Install
cd ZenUnitHelloWorld
python3 ../ZenUnitPy/ZenUnitPy/BuildAndInstall.py Ninja Release ZenUnitHelloWorld LibraryNameTests "" "" NoInstall
cd ..
