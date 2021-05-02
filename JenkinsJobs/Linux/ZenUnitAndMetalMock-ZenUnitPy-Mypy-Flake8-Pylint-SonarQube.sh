#!/bin/bash
set -ev

cd ZenUnitPy
export PYTHONPATH=.
python ZenUnitPy/MypyFlake8PylintThenRunTestsWithCoverage.py
cd ..
