import glob
import platform
import sys
from ZenUnitPy import Process

def pylint_file(pythonFilePath):
   pylintCommand = "pylint --rcfile=.pylintrc --score=n --init-hook=\"sys.path.append('.')\" {0}".format(pythonFilePath)
   pylintExitCode = Process.run_and_get_exitcode(pylintCommand)
   return pylintExitCode

def pylint_all():
   pyFilePaths = glob.glob('**/*.py', recursive=True)
   allPylintsSucceeded = False
   if platform.system() == 'Windows':
      allPylintsSucceeded = Process.map_sequential(pylint_file, pyFilePaths)
   else:
      allPylintsSucceeded = Process.map_parallel(pylint_file, pyFilePaths)
   if not allPylintsSucceeded:
      sys.exit(1)

def flake8_all():
   flake8Command = 'flake8 --benchmark --config=.flake8 --show-source'
   Process.run(flake8Command)
