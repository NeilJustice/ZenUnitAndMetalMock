Set-PSDebug -Trace 1

$env:PYTHONPATH="ZenUnitPy"
python.exe ZenUnitPy\ZenUnitPy\BuildAndTestZenUnitAndMetalMock.py `
   --cmake-generator="Visual Studio 16 2019" `
   --cmake-build-type="Debug" `
   --cmake-definitions=""
if ($LastExitCode -ne 0) { exit $LastExitCode }

VSDiagnostics.exe start 1 `
   /launch:ZenUnitLibraryTests\Debug\ZenUnitLibraryTests.exe `
   /launchArgs:"--test-runs=10" `
   /loadConfig:JenkinsJobs\Windows\VSDiagnosticsCPUUsage8190.json
if ($LastExitCode -ne 0) { exit $LastExitCode }

sleep 20

VSDiagnostics.exe stop 1 /output:JenkinsJobs\Windows\ZenUnitLibraryTests-Debug.diagsession

Set-PSDebug -Trace 0
