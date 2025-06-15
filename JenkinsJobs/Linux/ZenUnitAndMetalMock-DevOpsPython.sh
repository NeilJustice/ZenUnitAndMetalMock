#!/bin/bash
set -ev

cd ZenUnitDevOpsPython
export PYTHONPATH=.
python -u ZenUnitDevOpsPython/MypyFlake8PylintThenRunTestsWithCoverage.py
cd ..
