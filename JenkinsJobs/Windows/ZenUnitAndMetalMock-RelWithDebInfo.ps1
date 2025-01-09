$env:PYTHONPATH="."
python.exe -u ZenUnitDevOpsPython\BuildAndTestZenUnitAndMetalMock.py `
   --cmake-build-type="RelWithDebInfo" `
   --cmake-definitions=""
exit $LastExitCode