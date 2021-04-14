Set-PSDebug -Trace 1

cd ZenUnitPy
$env:PYTHONPATH = "."
python.exe ZenUnitPy/RunZenUnitPyTestsWithCoverageAndLinting.py
cd ..

Set-PSDebug -Trace 0
exit $LastExitCode
