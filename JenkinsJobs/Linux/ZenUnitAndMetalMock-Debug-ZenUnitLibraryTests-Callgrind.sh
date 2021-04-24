#!/bin/bash
set -e

time valgrind --tool=callgrind --cache-sim=yes --branch-sim=yes Debug/ZenUnitLibraryTests/ZenUnitLibraryTests

