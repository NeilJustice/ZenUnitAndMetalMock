cmake.exe -G"Visual Studio 15 2017 Win64" -DCMAKE_INSTALL_PREFIX=C:\install .
if ($LastExitCode -ne 0) { exit $LastExitCode }
cmake.exe --build . --target install
