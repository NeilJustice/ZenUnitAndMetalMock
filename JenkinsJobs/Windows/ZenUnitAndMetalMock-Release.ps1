param([string]$installFolder = "C:\\")
Set-PSDebug -Trace 1

$env:PYTHONPATH="ZenUnitPy"
python.exe ZenUnitPy\ZenUnitPy\BuildZenUnitAndMetalMock.py `
   --cmake-generator="Visual Studio 16 2019" `
   --cmake-architecture="x64" `
   --cmake-build-type="Release" `
   --cmake-definitions="-DFastWindowsReleaseBuildMode=ON -DCMAKE_INSTALL_PREFIX=$installFolder"
exit $LastExitCode
   
Set-PSDebug -Trace 0
