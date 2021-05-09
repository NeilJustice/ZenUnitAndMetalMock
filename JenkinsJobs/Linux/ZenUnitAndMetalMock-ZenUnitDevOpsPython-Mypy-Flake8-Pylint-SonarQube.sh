#!/bin/bash
set -ev

cd ZenUnitDevOpsPython
export PYTHONPATH=.
python ZenUnitDevOpsPython/MypyFlake8PylintThenRunTestsWithCoverage.py
cd ..
