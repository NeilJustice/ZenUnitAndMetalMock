$ErrorActionPreference = "Stop"
python ZenUnitPy\ZenUnitPy\CMakeBuildZenUnit.py --generator="Visual Studio 15 2017 Win64" --buildType=Release --installPrefix=C:\install
python ZenUnitPy\ZenUnitPy\CMakeBuildZenUnitHelloWorld.py --generator="Visual Studio 15 2017 Win64" --buildType=Release
