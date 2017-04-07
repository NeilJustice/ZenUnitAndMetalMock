#!/bin/bash
set -eu
python ZenUnitPy/ZenUnitPy/CoveragePylintFlake8.py ZenUnitPy/ZenUnitPy.Test RunAllWithCoverage.py
python ZenUnitPy/ZenUnitPy/BuildAndInstall.py "Visual Studio 14 2015 Win64" Debug ZenUnit ZenUnit.Test "" -DCMAKE_INSTALL_PREFIX=C:/install Install
cd ZenUnitHelloWorld
python ../ZenUnitPy/ZenUnitPy/BuildAndInstall.py "Visual Studio 14 2015 Win64" Debug ZenUnitHelloWorld LibraryNameTests "" -DCMAKE_INSTALL_PREFIX=. Install
