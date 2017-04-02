#!/bin/bash
set -eu
python ZenUnitPy/ZenUnitPy/CoveragePylintFlake8.py ZenUnitPy/ZenUnitPy.Test RunAllWithCoverage.py
python ZenUnitPy/ZenUnitPy/BuildAndInstall.py "Visual Studio 14 2015 Win64" Debug ZenUnit ZenUnit.Test "" -DCMAKE_INSTALL_PREFIX=C:/install Install
cd ZenUnitTestedProgram
python ../ZenUnitPy/ZenUnitPy/BuildAndInstall.py "Visual Studio 14 2015 Win64" Debug ZenUnitTestedProgram LibraryNameTests "" -DCMAKE_INSTALL_PREFIX=. Install
