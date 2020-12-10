#!/bin/bash
set -e

./Release/MetalMockTests/MetalMockTests
./Release/MetalMockExamples/MetalMockExamples
./Release/ZenUnitLibraryTests/ZenUnitLibraryTests
./Release/ZenUnitUtilsAndAssertionTests/ZenUnitUtilsAndAssertionTests
./Release/ZenUnitExamples/ZenUnitExamples

