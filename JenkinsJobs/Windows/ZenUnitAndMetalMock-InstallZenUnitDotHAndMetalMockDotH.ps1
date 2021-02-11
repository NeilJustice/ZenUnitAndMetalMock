Set-PSDebug -Trace 1

cmake.exe . -G"Visual Studio 16 2019" -A"x64" -DCMAKE_INSTALL_PREFIX="C:\\"
if ($LastExitCode -ne 0) { exit $LastExitCode }
cmake.exe --build . --target install

Set-PSDebug -Trace 0
exit $LastExitCode
