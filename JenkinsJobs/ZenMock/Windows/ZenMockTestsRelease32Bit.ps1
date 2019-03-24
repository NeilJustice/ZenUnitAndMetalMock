$ErrorActionPreference = "Stop"
Copy-Item ..\ZenUnit\ZenUnit\ZenUnit.h ZenUnit.h
python.exe ..\ZenUnit\ZenUnitPy\ZenUnitPy\BuildZenUnitOrZenMock.py --ZenUnitOrZenMock=ZenMock --generator="Visual Studio 15 2017" --buildType=Release --definitions=""
