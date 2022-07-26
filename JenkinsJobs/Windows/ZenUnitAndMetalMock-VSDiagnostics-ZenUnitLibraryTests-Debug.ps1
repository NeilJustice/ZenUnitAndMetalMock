$env:PYTHONPATH="."
python.exe -u ZenUnitDevOpsPython\BuildAndTestZenUnitAndMetalMock.py `
   --cmake-generator="Visual Studio 17 2022" `
   --cmake-build-type="Debug" `
   --cmake-definitions=""
if ($LastExitCode -ne 0) { exit $LastExitCode }

VSDiagnostics.exe start 5 `
   /launch:ZenUnitLibraryTests\Debug\ZenUnitLibraryTests.exe `
   /launchArgs:"--test-runs=10" `
   /loadConfig:JenkinsJobs\Windows\VSDiagnosticsCPUUsage.json
if ($LastExitCode -ne 0) { exit $LastExitCode }
sleep 30
VSDiagnostics.exe stop 5 /output:JenkinsJobs\Windows\ZenUnitLibraryTests-Debug.diagsession
exit $LastExitCode
