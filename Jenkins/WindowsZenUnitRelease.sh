#!/bin/bash
set -eu
python ZenUnitPy/ZenUnitPy/BuildAndInstall.py "Visual Studio 14 2015 Win64" Release ZenUnit ZenUnitTests "" -DCMAKE_INSTALL_PREFIX=C:/install Install
cd ZenUnitHelloWorld
python ../ZenUnitPy/ZenUnitPy/BuildAndInstall.py "Visual Studio 14 2015 Win64" Release StaticLibrary StaticLibraryTests "" -DCMAKE_INSTALL_PREFIX=. NoInstall
