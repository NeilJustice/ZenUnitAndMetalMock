import os
import platform
import sys
sys.path.append('ZenUnitPy') # Jenkins
from ZenUnitPy import Process, Python

def main():
   os.chdir('ZenUnitPy/ZenUnitPyTests')
   lowercasePlatformSystem = platform.system().casefold()
   pythonExecutableName = 'python' if lowercasePlatformSystem == 'linux' else 'python.exe'
   Process.run(f'{pythonExecutableName} -u RunAllWithCoverage.py')
   os.chdir('..')
   Python.pylint_all()
   Python.flake8_all()

if __name__ == '__main__': # pragma nocover
   main()
