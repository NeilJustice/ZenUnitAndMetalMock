#!/bin/bash
set -e
CXX=/usr/bin/g++ python3 ZenUnitPy/ZenUnitPy/BuildZenUnitOrZenMock.py --ZenUnitOrZenMock=ZenMock --generator=Ninja --buildType=Release --definitions="" --installDirectory=NoInstall
