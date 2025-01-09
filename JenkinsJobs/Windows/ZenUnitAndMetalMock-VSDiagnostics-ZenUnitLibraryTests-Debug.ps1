$env:PYTHONPATH="."
python.exe -u ZenUnitDevOpsPython\BuildAndTestZenUnitAndMetalMock.py `
   --cmake-build-type="Debug" `
   --cmake-definitions=""
if ($LastExitCode -ne 0) { exit $LastExitCode }
Write-Host

AcceliTune.exe collect-vsdiagnostics `
   --launch-exe="ZenUnitLibraryTests\Debug\ZenUnitLibraryTests.exe" `
   --launch-dir="." `
   --launch-args-file="JenkinsJobs\Windows\VSDiagnosticsArgs.txt" `
   --session-id=1 `
   --diagsession-output-file="D:\PerformanceProfilingResults\VSDiagnostics\ZenUnitLibraryTests-Debug-VSDiagnostics.diagsession"
