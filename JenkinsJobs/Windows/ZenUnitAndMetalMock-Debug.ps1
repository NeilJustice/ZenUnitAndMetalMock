Set-PSDebug -Trace 1

$env:PYTHONPATH="ZenUnitPy"
python.exe ZenUnitPy\ZenUnitPy\BuildZenUnitAndMetalMock.py `
	--cmake-generator="Visual Studio 16 2019" `
	--cmake-build-type="Debug" `
	--cmake-definitions=""

Set-PSDebug -Trace 0
exit $LastExitCode
