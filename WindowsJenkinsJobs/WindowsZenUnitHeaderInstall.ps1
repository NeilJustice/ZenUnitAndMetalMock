$ErrorActionPreference = "Stop"
cmake -G"Visual Studio 15 2017 Win64" -DCMAKE_INSTALL_PREFIX=C:\install
cmake --build . --target install
