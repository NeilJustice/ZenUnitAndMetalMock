import platform
from ZenUnitPy import Process, Python

def main():
   lowercasePlatformSystem = platform.system().casefold()
   pythonExecutableName = 'python' if lowercasePlatformSystem == 'linux' else 'python.exe'
   Process.fail_fast_run(f'{pythonExecutableName} -u ZenUnitPyTests/RunAllWithCoverage.py')
   Python.pylint_all()
   Python.flake8_all()

if __name__ == '__main__': # pragma nocover
   main()
