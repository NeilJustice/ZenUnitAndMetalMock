Set-PSDebug -Trace 1

$env:PYTHONPATH="."
python.exe ZenUnitDevOpsPython\BuildAndTestZenUnitAndMetalMock.py `
   --cmake-generator="Visual Studio 16 2019" `
   --cmake-build-type="Release" `
   --cmake-definitions="-DFastWindowsReleaseBuildMode=ON"
   
Set-PSDebug -Trace 0
exit $LastExitCode
