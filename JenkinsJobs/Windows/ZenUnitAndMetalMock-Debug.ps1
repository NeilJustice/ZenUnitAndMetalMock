param($fastWindowsDebugBuildMode = "ON")

$env:PYTHONPATH="."
python.exe -u ZenUnitDevOpsPython\BuildAndTestZenUnitAndMetalMock.py `
   --cmake-generator="Visual Studio 17 2022" `
   --cmake-build-type="Debug" `
   --cmake-definitions="-DFastWindowsDebugBuildMode=$fastWindowsDebugBuildMode"
exit $LastExitCode