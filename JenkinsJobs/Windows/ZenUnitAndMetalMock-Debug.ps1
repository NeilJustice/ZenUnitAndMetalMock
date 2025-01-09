$env:PYTHONPATH="."
python.exe -u ZenUnitDevOpsPython\BuildAndTestZenUnitAndMetalMock.py `
   --cmake-build-type="Debug" `
   --cmake-definitions=""
exit $LastExitCode
