if ((Get-CimInstance Win32_Processor | Select-Object Manufacturer).Manufacturer -ne "Intel")
{
   Write-Host "Not running VTune in memory access mode because this computer does not have an Intel processor"
   exit 0
}

$env:PYTHONPATH="."
python.exe -u ZenUnitDevOpsPython\BuildAndTestZenUnitAndMetalMock.py `
   --cmake-generator="Visual Studio 17 2022" `
   --cmake-build-type="Debug" `
   --cmake-definitions=""
if ($LastExitCode -ne 0) { exit $LastExitCode }
Write-Host

AcceliTune.exe collect-memory-access `
   --app-working-dir=ZenUnitLibraryTests\Debug `
   --program=ZenUnitLibraryTests.exe `
   --args="--test-runs=10" `
   --results-folder="C:\PerformanceProfilingResults\VTune\ZenUnitLibraryTests_Memory " `
   --overwrite-results-folder
