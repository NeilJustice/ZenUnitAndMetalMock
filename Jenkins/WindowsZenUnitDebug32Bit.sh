#!/bin/bash
set -eu
python ZenUnitPy/ZenUnitPy/CoveragePylintFlake8.py ZenUnitPy/ZenUnitPyTests RunAllWithCoverage.py
python ZenUnitPy/ZenUnitPy/BuildAndInstall.py "Visual Studio 15 2017" Debug ZenUnit ZenUnitTests "" -DCMAKE_INSTALL_PREFIX=C:/install Install
cd ZenUnitHelloWorld
python ../ZenUnitPy/ZenUnitPy/BuildAndInstall.py "Visual Studio 15 2017" Debug StaticLibrary StaticLibraryTests "" -DCMAKE_INSTALL_PREFIX=. NoInstall
