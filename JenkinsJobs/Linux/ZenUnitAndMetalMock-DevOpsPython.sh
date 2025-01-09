#!/bin/bash
set -ev

export PYTHONPATH=.
python -u ZenUnitDevOpsPython/MypyFlake8PylintThenRunTestsWithCoverage.py
