#!/bin/bash
set -ev

cd ZenUnitPy
export PYTHONPATH=.
python ZenUnitPy/RunZenUnitPyTestsWithCoverageAndLinting.py
cd ..
