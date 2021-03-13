Set-PSDebug -Trace 1

cppcheck.exe `
   --enable=all `
   -DTEST `
   -DTESTS `
   -I . `
   -j 64 `
   .

Set-PSDebug -Trace 0
