$env:PYTHONPATH="."
python.exe -u ZenUnitDevOpsPython\BuildAndTestZenUnitAndMetalMock.py `
   --cmake-generator="Visual Studio 17 2022" `
   --cmake-build-type="Debug" `
   --cmake-definitions=""
if ($LastExitCode -ne 0) { exit $LastExitCode }

AcceliTune.exe collect-threading `
   --app-working-dir=ZenUnitLibraryTests\Debug `
   --program-name=ZenUnitLibraryTests.exe `
   --program-args="" `
   --results-folder=C:\VTuneProfilingResults\ZenUnitLibraryTests_Threading `
   --overwrite-results-folder
