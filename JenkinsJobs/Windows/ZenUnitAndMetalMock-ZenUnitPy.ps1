Set-PSDebug -Trace 1

python.exe ZenUnitPy/ZenUnitPy/RunZenUnitPyTestsWithCoverageAndLinting.py
exit $LastExitCode

Set-PSDebug -Trace 0
