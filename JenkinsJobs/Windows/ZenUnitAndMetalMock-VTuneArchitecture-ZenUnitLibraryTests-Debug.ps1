if ((Get-CimInstance Win32_Processor | Select-Object Manufacturer).Manufacturer -ne "GenuineIntel")
{
   Write-Host "Not running VTune in microarchitecture mode because this computer does not have a GenuineIntel processor"
   exit 0
}

$env:PYTHONPATH="."
python.exe -u ZenUnitDevOpsPython\BuildAndTestZenUnitAndMetalMock.py `
   --cmake-generator="Visual Studio 17 2022" `
   --cmake-build-type="Debug" `
   --cmake-definitions=""
if ($LastExitCode -ne 0) { exit $LastExitCode }
Write-Host

AcceliTune.exe collect-uarch-exploration `
   --app-working-dir=ZenUnitLibraryTests\Debug `
   --program=ZenUnitLibraryTests.exe `
   --args="--test-runs=10" `
   --results-folder="C:\PerformanceProfilingResults\VTune\ZenUnitLibraryTests_Architecture" `
   --overwrite-results-folder
