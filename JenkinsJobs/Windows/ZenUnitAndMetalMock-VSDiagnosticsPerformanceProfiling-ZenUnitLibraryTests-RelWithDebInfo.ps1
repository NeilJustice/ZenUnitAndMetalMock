Set-PSDebug -Trace 1

$env:PYTHONPATH="ZenUnitPy"
python.exe ZenUnitPy\ZenUnitPy\BuildZenUnitAndMetalMock.py `
   --cmake-generator="Visual Studio 16 2019" `
   --cmake-build-type="RelWithDebInfo" `
   --cmake-definitions=""
if ($LastExitCode -ne 0) { exit $LastExitCode }
   
VSDiagnostics.exe start 1 `
   /launch:ZenUnitLibraryTests\RelWithDebInfo\ZenUnitLibraryTests.exe `
   /launchArgs:"--test-runs=30" `
   /loadConfig:JenkinsJobs\Windows\VSDiagnosticsCPUUsage10000.json
if ($LastExitCode -ne 0) { exit $LastExitCode }

sleep 20

VSDiagnostics.exe stop 1 /output:JenkinsJobs\Windows\ZenUnitLibraryTests-RelWithDebInfo.diagsession

Set-PSDebug -Trace 0
