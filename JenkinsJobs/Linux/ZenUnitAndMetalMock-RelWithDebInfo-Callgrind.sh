#!/bin/bash
set -ev

export CXX=clang++
LinuxCallgrindRunner build-then-run-callgrind-four-times \
   --solution=ZenUnitAndMetalMock \
   --configuration=RelWithDebInfo \
   --program=ZenUnitLibraryTests \
   --args="" \
   --callgrind-reports-folder="/code/LinuxPerformanceTestResults/CallgrindReports"

