AcceliTune.exe build-then-collect-vsdiagnostics `
   --working-dir="." `
   --solution="ZenUnitAndMetalMock" `
   --program="ZenUnitLibraryTests" `
   --configuration=Debug `
   --args-file="JenkinsJobs\Windows\VSDiagnosticsArgs.txt" `
   --session-id=40 `
   --diagsession-output-file="D:\PerformanceProfilingResults\VSDiagnostics\ZenUnitLibraryTests-Debug-VSDiagnostics.diagsession"
