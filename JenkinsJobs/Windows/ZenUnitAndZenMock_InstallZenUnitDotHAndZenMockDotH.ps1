Set-PSDebug -Trace 1
cmake.exe . -G"Visual Studio 16 2019" -A"x64" -DCMAKE_INSTALL_PREFIX=C:\usr_local
cmake.exe --build . --target install
Set-PSDebug -Trace 0
