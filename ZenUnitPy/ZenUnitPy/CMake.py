import os
import platform
from ZenUnitPy import Process

def generate(folderPath, generator, buildType, cmakeDefinitions, cmakeListsFolderPath):
   os.makedirs(folderPath, exist_ok=True)
   os.chdir(folderPath)
   print('Generating CMake in folder', folderPath)
   if platform.system() == 'Linux':
      cmakeCommand = f'cmake -G"{generator}" -DCMAKE_BUILD_TYPE={buildType} {cmakeDefinitions} {cmakeListsFolderPath}'
   else:
      cmakeCommand = f'cmake -G"{generator}" -Ax64 {cmakeDefinitions} {cmakeListsFolderPath}'
   Process.run(cmakeCommand)
