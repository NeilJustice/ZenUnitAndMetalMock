Set-PSDebug -Trace 1

$env:PYTHONPATH="."
python.exe ZenUnitDevOpsPython/MypyFlake8PylintThenRunTestsWithCoverage.py

Set-PSDebug -Trace 0
exit $LastExitCode
