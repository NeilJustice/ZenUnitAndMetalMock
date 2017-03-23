import os
import platform
from ZenUnitPy import Process

def generate(
   folderPath, generator, buildType, cmakeDefinitions, cmakeListsFolderPath):
   os.makedirs(folderPath, exist_ok=True)
   os.chdir(folderPath)
   print('Generating CMake in folder', folderPath)
   if platform.system() == 'Linux':
      cmakeCommand = 'cmake -G"{0}" -DCMAKE_BUILD_TYPE={1} {2} {3}'.format(
         generator, buildType, cmakeDefinitions, cmakeListsFolderPath)
   else:
      cmakeCommand = 'cmake -G"{0}" {1} {2}'.format(
         generator, cmakeDefinitions, cmakeListsFolderPath)
   Process.run(cmakeCommand)
