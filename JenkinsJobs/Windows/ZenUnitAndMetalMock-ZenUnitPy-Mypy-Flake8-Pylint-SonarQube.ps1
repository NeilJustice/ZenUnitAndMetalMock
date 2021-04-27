Set-PSDebug -Trace 1

cd ZenUnitPy
$env:PYTHONPATH = "."
python.exe ZenUnitPy/MypyFlake8PylintThenRunTestsWithCoverage.py
cd ..

Set-PSDebug -Trace 0
exit $LastExitCode
