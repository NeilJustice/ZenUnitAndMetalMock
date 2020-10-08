import multiprocessing
import os
import platform
import shlex
import subprocess
import sys

def run(command):
   exitCode = run_and_get_exitcode(command)
   if exitCode != 0:
      singleQuotedCommand = '\'' + command + '\''
      print('Command', singleQuotedCommand, 'failed with exit code', exitCode)
      sys.exit(exitCode)

def run_and_get_exitcode(command):
   singleQuotedCommand = '\'' + command + '\''
   currentWorkingDirectory = os.getcwd()
   print('Running', singleQuotedCommand, 'from', currentWorkingDirectory)
   systemName = platform.system()
   if systemName == 'Windows':
      exitCode = subprocess.call(command)
   else:
      shlexedCommand = shlex.split(command)
      exitCode = subprocess.call(shlexedCommand)
   return exitCode

def map_sequential(func, iterable):
   exitCodes = map(func, iterable)
   allCommandsSucceeded = not any(exitCodes)
   return allCommandsSucceeded

def map_parallel(func, iterable):
   pool = multiprocessing.Pool(multiprocessing.cpu_count())
   exitCodes = pool.map(func, iterable)
   pool.close()
   allCommandsSucceeded = not any(exitCodes)
   return allCommandsSucceeded
