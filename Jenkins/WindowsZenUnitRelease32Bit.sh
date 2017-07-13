#!/bin/bash
set -eu
python ZenUnitPy/ZenUnitPy/BuildAndInstall.py "Visual Studio 15 2017" Release ZenUnit ZenUnitTests "" -DCMAKE_INSTALL_PREFIX=C:/install Install
cd ZenUnitHelloWorld
python ../ZenUnitPy/ZenUnitPy/BuildAndInstall.py "Visual Studio 15 2017" Release StaticLibrary StaticLibraryTests "" -DCMAKE_INSTALL_PREFIX=. NoInstall
