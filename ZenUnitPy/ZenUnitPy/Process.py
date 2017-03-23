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

def run_and_get_stdout(command):
   shlexedCommand = shlex.split(command)
   standardOutputBytes = subprocess.check_output(shlexedCommand)
   standardOutputUtf8 = to_utf8(standardOutputBytes)
   return standardOutputUtf8

def to_utf8(byteString):
   utf8 = byteString.decode('utf-8')
   return utf8

def run_and_check_stdout_for_substring(command, substring):
   print('Running \'' + command + '\' and checking for substring \'' + substring + '\'')
   stdOut = run_and_get_stdout(command)
   stdOutContainsSubstring = substring in stdOut
   print('Substring \'' + substring + '\' ' + ('found.' if stdOutContainsSubstring else 'not found.'))
   if not stdOutContainsSubstring:
      sys.exit(1)

def run_exe(projectName, configuration, args=''):
   exePath = '{0}\\{1}\\{0}.exe'.format(projectName, configuration)
   exePathWithArgs = append_args(exePath, args)
   run(exePathWithArgs)

def append_args(exePath, args):
   exePathWithArgs = exePath + (' ' + args if args != '' else '')
   return exePathWithArgs

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
