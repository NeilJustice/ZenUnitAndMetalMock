#!/bin/bash
set -ev
cd ZenUnitPy
PYTHONPATH=. python ZenUnitPy/RunZenUnitPyTestsWithCoverageAndLinting.py
cd ..
