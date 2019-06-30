param([string]$installFolder = "C:\install")

Set-PSDebug -Trace 1
python.exe ZenUnitPy\ZenUnitPy\BuildZenUnitAndZenMock.py --cmake-generator="Visual Studio 16 2019" --cmake-arch="x64" --cmake-build-type="Debug" --cmake-definitions="-DCMAKE_INSTALL_PREFIX=$installFolder"
Set-PSDebug -Trace 0
