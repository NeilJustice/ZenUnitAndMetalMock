import os
import sys
sys.path.append('ZenUnitPy') # Jenkins
from ZenUnitPy import Process, Python

Usage = 'Usage: python3 RunTestsWithCoverageAndPylintFlake8.py'

def main(args):
   os.chdir('ZenUnitPyTests')
   Process.run('python3 RunAllWithCoverage.py')
   os.chdir('..')
   Python.pylint_all()
   Python.flake8_all()

if __name__ == '__main__': # pragma nocover
   main(sys.argv)
