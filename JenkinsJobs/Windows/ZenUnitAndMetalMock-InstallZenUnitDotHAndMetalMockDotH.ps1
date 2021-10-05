cmake.exe . -G"Visual Studio 16 2019" -A"x64" -DCMAKE_INSTALL_PREFIX="C:\\"
if ($LastExitCode -ne 0) { exit $LastExitCode }
cmake.exe --build . --target install
exit $LastExitCode
