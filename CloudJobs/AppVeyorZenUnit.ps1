$ErrorActionPreference = "Stop"
Invoke-WebRequest https://raw.githubusercontent.com/NeilJustice/ZenMock/master/ZenMock/ZenMock.h -OutFile ZenMock.h
MSBuild.exe ZenUnit.sln /p:Configuration=Debug /p:Platform=x64 /m
MSBuild.exe ZenUnit.sln /p:Configuration=Release /p:Platform=x64 /m
