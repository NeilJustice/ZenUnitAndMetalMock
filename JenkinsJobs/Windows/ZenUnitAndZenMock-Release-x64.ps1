param([string]$installFolder = "C:\\")

Set-PSDebug -Trace 1
python.exe ZenUnitPy\ZenUnitPy\BuildAndInstallZenUnitAndZenMock.py `
   --cmake-generator="Visual Studio 16 2019" `
   --cmake-architecture="x64" `
   --cmake-build-type="Release" `
   --cmake-definitions="-DFastWindowsReleaseBuildMode=ON -DCMAKE_INSTALL_PREFIX=$installFolder"
Set-PSDebug -Trace 0
