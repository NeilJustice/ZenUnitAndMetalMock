Set-PSDebug -Trace 1
python.exe ZenUnitPy\ZenUnitPy\BuildZenUnitAndZenMock.py --cmake-generator="Visual Studio 16 2019" --cmake-arch="Win32" --cmake-build-type="Debug" --cmake-definitions=""
Set-PSDebug -Trace 0
