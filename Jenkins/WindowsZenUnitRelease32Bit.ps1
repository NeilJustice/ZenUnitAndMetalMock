$ErrorActionPreference = "Stop"
python ZenUnitPy\ZenUnitPy\CMakeBuildZenUnit.py --generator="Visual Studio 15 2017" --buildType=Release --definitions="" --installDirectory=C:\install
python ZenUnitPy\ZenUnitPy\CMakeBuildZenUnitHelloWorld.py --generator="Visual Studio 15 2017" --buildType=Release --definitions=""
