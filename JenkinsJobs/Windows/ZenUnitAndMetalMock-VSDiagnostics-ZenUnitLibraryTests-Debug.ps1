$env:PYTHONPATH="."
python.exe -u ZenUnitDevOpsPython\BuildAndTestZenUnitAndMetalMock.py `
   --cmake-generator="Visual Studio 17 2022" `
   --cmake-build-type="Debug" `
   --cmake-definitions=""
if ($LastExitCode -ne 0) { exit $LastExitCode }
Write-Host

VSDiagnostics.exe start 1 `
   /launch:"ZenUnitLibraryTests\Debug\ZenUnitLibraryTests.exe" `
   /launchArgs:"--test-runs=10" `
   /loadConfig:"JenkinsJobs\Windows\VSDiagnosticsCPUUsage.json"
if ($LastExitCode -ne 0) { exit $LastExitCode }
sleep 10
VSDiagnostics.exe stop 1 /output:"D:\PerformanceProfilingResults\VSDiagnostics\ZenUnitLibraryTests-Debug.diagsession"
exit $LastExitCode
