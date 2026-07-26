$env:PYTHONPATH="ZenUnitDevOpsPython"
python.exe -u "ZenUnitDevOpsPython\ZenUnitDevOpsPython\BuildAndTestZenUnitAndMetalMock.py" `
   --cmake-build-type="Debug" `
   --cmake-definitions=""
if ($LastExitCode -ne 0) { exit $LastExitCode }
Write-Host

AcceliTune.exe measure-program-run-time `
   --app-working-dir="ZenUnitLibraryTests\Debug" `
   --program="ZenUnitLibraryTests.exe" `
   --args="--test-runs=100" `
   --performance-test-results-file="C:\Code\WindowsPerformanceTestResults\Performance\ZenUnitAndMetalMock-Performance.txt"
