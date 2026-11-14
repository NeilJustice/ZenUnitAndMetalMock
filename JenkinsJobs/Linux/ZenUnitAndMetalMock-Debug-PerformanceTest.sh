#!/bin/bash
set -eu

args="--test-runs=100"
export CXX=clang++
LinuxAcceliTune build-then-measure-program-run-time \
   --working-dir=. \
   --solution=ZenUnitAndMetalMock \
   --configuration=Debug \
   --program=ZenUnitLibraryTests \
   --args="$args" \
   --performance-test-results-file="/code/LinuxPerformanceTestResults/Performance/ZenUnitAndMetalMock-Performance.txt"

