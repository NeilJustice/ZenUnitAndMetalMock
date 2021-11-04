$numberOfLogicalProcessors = (Get-CimInstance -ClassName Win32_ComputerSystem).NumberOfLogicalProcessors
cppcheck.exe `
   --cppcheck-build-dir=Cppcheck `
   --enable=all `
   --suppressions-list=CppcheckSuppressions.txt `
   -DCOMMA `
   -DAFACT `
   -DFACTS `
   -DTEST `
   -DTESTS `
   -DTEST1X1 `
   -DTEST2X2 `
   -DTEST3X3 `
   -DTEST4X4 `
   -DTEST5X5 `
   -DTEST6X6 `
   -DTEST7X7 `
   -DTEST8X8 `
   -DTEST9X9 `
   -DTEST10X10 `
   -DRUN_TESTS `
   -DRUN_TEMPLATE_TESTS `
   -DMETALMOCK_NONVOID0_FREE `
   -DMETALMOCK_NONVOID0_STATIC `
   -DMETALMOCK_NONVOID1_FREE `
   -DMETALMOCK_NONVOID1_STATIC `
   -DMETALMOCK_NONVOID2_STATIC `
   -DMETALMOCK_NONVOID3_CONST `
   -DMETALMOCK_NONVOID5_FREE `
   -DMETALMOCK_VOID0_FREE `
   -DMETALMOCK_VOID1_FREE `
   -DMETALMOCK_VOID2_FREE `
   -DMETALMOCK_VOID3_FREE `
   -DMETALMOCK_VOID4_FREE `
   -DMETALMOCK_VOID5_FREE `
   -DMETALMOCK_VOID6_FREE `
   -DMETALMOCK_VOID7_FREE `
   -D_WIN32 `
   -I . `
   -j $numberOfLogicalProcessors `
   --output-file=cppcheck_results.txt `
   --error-exitcode=1 `
   .
if ($LastExitCode -eq 1)
{
   Write-Host "Cppcheck failed with exit code 1"
   exit 1
}
