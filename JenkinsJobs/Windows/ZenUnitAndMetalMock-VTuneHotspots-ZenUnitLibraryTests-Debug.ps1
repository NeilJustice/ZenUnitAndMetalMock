$env:PYTHONPATH="."
python.exe -u ZenUnitDevOpsPython\BuildAndTestZenUnitAndMetalMock.py `
   --cmake-build-type="Debug" `
   --cmake-definitions=""
if ($LastExitCode -ne 0) { exit $LastExitCode }
Write-Host

AcceliTune.exe collect-hotspots `
   --app-working-dir=ZenUnitLibraryTests\Debug `
   --program=ZenUnitLibraryTests.exe `
   --args="--test-runs=100" `
   --results-folder="D:\PerformanceProfilingResults\VTune\ZenUnitLibraryTests_Hotspots" `
   --overwrite-results-folder
