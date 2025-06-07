$env:PYTHONPATH="ZenUnitDevOpsPython"
python.exe -u ZenUnitDevOpsPython\ZenUnitDevOpsPython\BuildAndTestZenUnitAndMetalMock.py `
   --cmake-build-type="RelWithDebInfo" `
   --cmake-definitions=""
exit $LastExitCode