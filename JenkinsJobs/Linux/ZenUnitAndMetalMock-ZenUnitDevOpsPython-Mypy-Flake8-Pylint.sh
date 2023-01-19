#!/bin/bash
set -ev

export PYTHONPATH=.
python ZenUnitDevOpsPython/MypyFlake8PylintThenRunTestsWithCoverage.py
