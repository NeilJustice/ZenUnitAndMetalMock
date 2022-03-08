cmake.exe . -G"Visual Studio 17 2022" -A"x64" -DCMAKE_INSTALL_PREFIX="C:\\"
if ($LastExitCode -ne 0) { exit $LastExitCode }
cmake.exe --build . --target install
exit $LastExitCode