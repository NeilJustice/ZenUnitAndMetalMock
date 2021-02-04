import glob
import os
import platform
import sys
from ZenUnitPy import Process

PylintCommand = 'pylint --rcfile=.pylintrc --score=n --init-hook=\"sys.path.append(\'.\')\" '

def pylint_file(pythonFilePath):
   pylintCommand = PylintCommand + pythonFilePath
   pylintExitCode = Process.run_and_get_exit_code(pylintCommand)
   return pylintExitCode

def pylint_all():
   pyFilePaths = glob.glob('**/*.py', recursive=True)
   allPylintsSucceeded = False
   if platform.system() == 'Windows':
      allPylintsSucceeded = Process.run_parallel_processthread(PylintCommand, pyFilePaths)
   else:
      allPylintsSucceeded = Process.run_parallel_processpoolexecutor(pylint_file, pyFilePaths)
   if not allPylintsSucceeded:
      sys.exit(1)

def flake8_all():
   flake8Command = 'flake8 --config=.flake8 --show-source --benchmark'
   Process.fail_fast_run(flake8Command)

def run_all_with_coverage(testsProjectName, omitPattern):
   print(f'Running {testsProjectName}/RunAll.py with coverage from', os.getcwd())
   Process.fail_fast_run(f'coverage run --branch {testsProjectName}/RunAll.py')
   reportExitCode = Process.run_and_get_exit_code(f'coverage report --omit="{omitPattern}" --fail-under=100 --show-missing')
   Process.fail_fast_run(f'coverage xml --omit="{omitPattern}" -o {testsProjectName}/CoberturaCodeCoverageResults_{testsProjectName}.xml')
   Process.fail_fast_run(f'coverage html --directory={testsProjectName}/CodeCoverageHTMLReport --title="{testsProjectName} Code Coverage"')
   if reportExitCode == 0:
      print('Success. Code coverage is 100%.')
   else:
      print('Failure. Code coverage is less than 100%.')
   sys.exit(reportExitCode)
