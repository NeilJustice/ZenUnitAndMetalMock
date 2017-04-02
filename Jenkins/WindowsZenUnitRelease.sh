#!/bin/bash
set -eu
python ZenUnitPy/ZenUnitPy/BuildAndInstall.py "Visual Studio 14 2015 Win64" Release ZenUnit ZenUnit.Test "" -DCMAKE_INSTALL_PREFIX=C:/install Install
cd ZenUnitTestedProgram
python ../ZenUnitPy/ZenUnitPy/BuildAndInstall.py "Visual Studio 14 2015 Win64" Release ZenUnitTestedProgram LibraryNameTests "" -DCMAKE_INSTALL_PREFIX=. Install
