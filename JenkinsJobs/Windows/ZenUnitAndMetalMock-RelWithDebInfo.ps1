$env:PYTHONPATH="."
python.exe ZenUnitDevOpsPython\BuildAndTestZenUnitAndMetalMock.py `
   --cmake-generator="Visual Studio 16 2019" `
   --cmake-build-type="RelWithDebInfo" `
   --cmake-definitions=""
exit $LastExitCode
