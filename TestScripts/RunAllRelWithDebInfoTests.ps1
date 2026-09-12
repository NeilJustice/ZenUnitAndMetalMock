MetalMockTests\RelWithDebInfo\MetalMockTests.exe
if ($LastExitCode -ne 0) { exit $LastExitCode }
Write-Host

MetalMockExamples\RelWithDebInfo\MetalMockExamples.exe
if ($LastExitCode -ne 0) { exit $LastExitCode }
Write-Host

ZenUnitLibraryTests\RelWithDebInfo\ZenUnitLibraryTests.exe
if ($LastExitCode -ne 0) { exit $LastExitCode }
Write-Host

ZenUnitUtilsAndAssertionTests\RelWithDebInfo\ZenUnitUtilsAndAssertionTests.exe
if ($LastExitCode -ne 0) { exit $LastExitCode }
Write-Host

ZenUnitExamples\RelWithDebInfo\ZenUnitExamples.exe
