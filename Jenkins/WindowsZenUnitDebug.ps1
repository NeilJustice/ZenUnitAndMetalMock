$ErrorActionPreference = "Stop"
python ZenUnitPy\ZenUnitPy\RunTestsWithCoverageAndPylintFlake8.py
python ZenUnitPy\ZenUnitPy\BuildZenUnit.py --generator="Visual Studio 15 2017 Win64" --buildType=Debug --installPrefix=C:\install
python ZenUnitPy\ZenUnitPy\BuildZenUnitHelloWorld.py --generator="Visual Studio 15 2017 Win64" --buildType=Debug
