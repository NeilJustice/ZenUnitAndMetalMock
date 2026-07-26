#!/bin/bash
set -ev

export PYTHONPATH=ZenUnitDevOpsPython
export CXX=/usr/bin/clang++

python -u ZenUnitDevOpsPython/ZenUnitDevOpsPython/BuildAndTestZenUnitAndMetalMock.py \
   --cmake-build-type=Debug \
   --cmake-definitions="-DFastLinuxDebugBuildMode=ON"

time valgrind --tool=callgrind \
   --cache-sim=yes \
   --branch-sim=yes \
   Debug/ZenUnitLibraryTests/ZenUnitLibraryTests \
   --random-seed=0 2> /code/LinuxPerformanceTestResults/CallgrindResults/ZenUnitLibraryTests/ZenUnitLibraryTests-CallgrindResults1.txt

time valgrind --tool=callgrind \
   --cache-sim=yes \
   --branch-sim=yes \
   Debug/ZenUnitLibraryTests/ZenUnitLibraryTests \
   --random-seed=0 2> /code/LinuxPerformanceTestResults/CallgrindResults/ZenUnitLibraryTests/ZenUnitLibraryTests-CallgrindResults2.txt

time valgrind --tool=callgrind \
   --cache-sim=yes \
   --branch-sim=yes \
   Debug/ZenUnitLibraryTests/ZenUnitLibraryTests \
   --random-seed=0 2> /code/LinuxPerformanceTestResults/CallgrindResults/ZenUnitLibraryTests/ZenUnitLibraryTests-CallgrindResults3.txt

time valgrind --tool=callgrind \
   --cache-sim=yes \
   --branch-sim=yes \
   Debug/ZenUnitLibraryTests/ZenUnitLibraryTests \
   --random-seed=0 2> /code/LinuxPerformanceTestResults/CallgrindResults/ZenUnitLibraryTests/ZenUnitLibraryTests-CallgrindResults4.txt

cat /code/LinuxPerformanceTestResults/CallgrindResults/ZenUnitLibraryTests/ZenUnitLibraryTests-CallgrindResults1.txt

