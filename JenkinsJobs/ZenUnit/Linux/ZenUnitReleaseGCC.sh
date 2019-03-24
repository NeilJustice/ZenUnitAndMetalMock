#!/bin/bash
set -e
CXX=/usr/bin/g++ python3 ZenUnitPy/ZenUnitPy/Buildzenunit-or-zenmock.py --zenunit-or-zenmock=ZenUnit --generator=Ninja --buildType=Release --definitions=""
