cmake.exe -G"Visual Studio 16 2019 Win64" -DCMAKE_INSTALL_PREFIX=C:\install .
if ($LastExitCode -ne 0) { exit $LastExitCode }

cmake.exe --build . --target install
