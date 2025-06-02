#!/bin/bash
set -e

./RelWithDebInfo/MetalMockTests/MetalMockTests
./RelWithDebInfo/MetalMockExamples/MetalMockExamples
./RelWithDebInfo/ZenUnitLibraryTests/ZenUnitLibraryTests
./RelWithDebInfo/ZenUnitUtilsAndAssertionTests/ZenUnitUtilsAndAssertionTests
./RelWithDebInfo/ZenUnitExamples/ZenUnitExamples

