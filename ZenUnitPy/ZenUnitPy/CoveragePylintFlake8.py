import os
import sys
sys.path.append('ZenUnitPy') # Jenkins
from ZenUnitPy import Process, Python, Util

def main(args):
   if len(args) != 3:
      Util.print_and_exit('Usage: python3 CoveragePylintFlake8.py <TestProjectFolderName> <RunAllWithCoveragePyFileName>', 1)
   else:
      testProjectFolderName = args[1]
      runAllWithCoveragePyFileName = args[2]
      os.chdir(testProjectFolderName)
      runTestsWithCoverageCommand = 'python3 ' + runAllWithCoveragePyFileName
      Process.run(runTestsWithCoverageCommand)
      os.chdir('..')
      #Python.PylintAll() # Uncomment when pylint supports Python 3.6
      Python.flake8_all()

if __name__ == '__main__': # pragma nocover
   main(sys.argv)
