param($fastWindowsDebugBuildMode = "ON")

$env:PYTHONPATH="."
python.exe ZenUnitDevOpsPython\BuildAndTestZenUnitAndMetalMock.py `
   --cmake-generator="Visual Studio 16 2019" `
   --cmake-build-type="Debug" `
   --cmake-definitions="-DFastWindowsDebugBuildMode=$fastWindowsDebugBuildMode"

exit $LastExitCode
