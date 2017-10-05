$ErrorActionPreference = "Stop"
python ZenUnitPy\ZenUnitPy\BuildZenUnit.py --generator="Visual Studio 15 2017" --buildType=Release --definitions="" --installDirectory=C:\install
python ZenUnitPy\ZenUnitPy\BuildZenUnitHelloWorld.py --generator="Visual Studio 15 2017" --buildType=Release --definitions=""
