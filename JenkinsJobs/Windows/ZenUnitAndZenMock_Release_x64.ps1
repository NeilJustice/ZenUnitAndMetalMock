Set-PSDebug -Trace 1
python.exe ZenUnitPy\ZenUnitPy\BuildZenUnitAndZenMock.py --cmake-generator="Visual Studio 16 2019" --cmake-architecture="x64" --cmake-build-type="Release" --cmake-definitions=""
Set-PSDebug -Trace 0
