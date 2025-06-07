$env:PYTHONPATH="ZenUnitDevOpsPython"
python.exe -u ZenUnitDevOpsPython\ZenUnitDevOpsPython\BuildAndTestZenUnitAndMetalMock.py `
   --cmake-build-type="Debug" `
   --cmake-definitions=""
exit $LastExitCode
