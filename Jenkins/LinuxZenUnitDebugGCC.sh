#!/bin/bash
set -e
CXX=/usr/bin/g++ python3 ZenUnitPy/ZenUnitPy/BuildZenUnit.py --generator=Ninja --buildType=Debug --definitions="" --installDirectory=NoInstall
CXX=/usr/bin/g++ python3 ZenUnitPy/ZenUnitPy/BuildZenUnitHelloWorld.py --generator=Ninja --buildType=Debug --definitions=""
