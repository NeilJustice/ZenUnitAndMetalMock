$ErrorActionPreference = "Stop"
python ZenUnitPy\ZenUnitPy\RunTestsWithCoverageAndLinting.py
python ZenUnitPy\ZenUnitPy\BuildZenUnitOrZenMock.py --ZenUnitOrZenMock=ZenUnit --generator="Visual Studio 15 2017 Win64" --buildType=Debug --definitions=""
