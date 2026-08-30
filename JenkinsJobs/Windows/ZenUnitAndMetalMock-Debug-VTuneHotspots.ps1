AcceliTune.exe build-then-collect-hotspots `
   --working-dir="." `
   --solution="ZenUnitAndMetalMock" `
   --program="ZenUnitLibraryTests" `
   --configuration=Debug `
   --args="--test-runs=100" `
   --results-folder="D:\PerformanceProfilingResults\VTune\ZenUnitLibraryTests_Hotspots" `
   --overwrite-results-folder
