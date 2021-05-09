Set-PSDebug -Trace 1

cd ZenUnitDevOpsPython
$env:PYTHONPATH = "."
python.exe ZenUnitDevOpsPython/MypyFlake8PylintThenRunTestsWithCoverage.py
cd ..

Set-PSDebug -Trace 0
exit $LastExitCode
