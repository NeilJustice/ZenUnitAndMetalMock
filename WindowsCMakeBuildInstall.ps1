if ($Args.Count -ne 1)
{
   Write-Host "Usage: .\WindowsCMakeBuildInstall.ps1 <InstallDirectory>"
   Exit 1
}

cmake . -G"Visual Studio 15 2017 Win64" -DCMAKE_INSTALL_PREFIX="$($Args[0])"
cmake --build . --target ZenUnit --config Debug
cmake --build . --target ZenUnit --config Release
cmake --build . --target install --config Debug
cmake --build . --target install --config Release
