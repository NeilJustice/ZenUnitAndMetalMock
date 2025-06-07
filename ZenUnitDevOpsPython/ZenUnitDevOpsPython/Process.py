import concurrent.futures
import multiprocessing
import os
import platform
import shlex
import subprocess
import sys
import time
from typing import Any, List, Tuple
from ZenUnitDevOpsPython import ProcessThread

def append_args(exePath: str, args: str) -> str:
   exePathWithArgs = exePath + (' ' + args if args != '' else '')
   return exePathWithArgs

def bytes_to_utf8(byteString: bytes) -> str:
   utf8 = byteString.decode('utf-8')
   return utf8

def fail_fast_run(command: str) -> None:
   exitCode = run_and_get_exit_code(command)
   if exitCode != 0:
      singleQuotedCommand = f'\'{command}\''
      print('Command', singleQuotedCommand, 'failed with exit code', exitCode)
      sys.exit(exitCode)

def cross_platform_subprocess_call(command: str) -> int:
   systemName = platform.system()
   if systemName == 'Windows':
      exitCode = subprocess.call(command)
   else:
      shlexedCommand = shlex.split(command)
      exitCode = subprocess.call(shlexedCommand)
   return exitCode

def run(command: str) -> Tuple[str, str]:
   shlexedCommand = shlex.split(command)
   completedProcess = subprocess.run(shlexedCommand, stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=False)
   stdout = bytes_to_utf8(completedProcess.stdout)
   stderr = bytes_to_utf8(completedProcess.stderr)
   return stdout, stderr

def run_and_get_exit_code(command: str) -> int:
   singleQuotedCommand = f'\'{command}\''
   currentWorkingDirectory = os.getcwd()
   print(' Running:', singleQuotedCommand, 'from', currentWorkingDirectory)
   try:
      exitCode = cross_platform_subprocess_call(command)
   except FileNotFoundError as ex:
      exceptionMessage = str(ex)
      print(exceptionMessage)
      sys.exit(1)
   else:
      return exitCode

def run_parallel_processpoolexecutor(func: Any, iterable: Any) -> bool:
   cpuCount = multiprocessing.cpu_count()
   processPoolExecutor = concurrent.futures.ProcessPoolExecutor(cpuCount) # pylint: disable=consider-using-with
   exitCodes = processPoolExecutor.map(func, iterable)
   processPoolExecutor.shutdown(wait=True)
   allCommandsSucceeded = not any(exitCodes)
   return allCommandsSucceeded

def run_parallel_processthread(command: str, commandSuffixArgs: List[str]) -> bool: # pragma nocover
   numberOfCommands = len(commandSuffixArgs)
   processThreads = [None] * numberOfCommands
   processExitCodes = [0] * numberOfCommands
   beginTime = time.process_time()
   for commandIndex, commandSuffixArg in enumerate(commandSuffixArgs):
      processThread = ProcessThread.ProcessThread(commandIndex, command, commandSuffixArg, processExitCodes)
      processThread.start()
      processThreads[commandIndex] = processThread # type: ignore
   for processThread in processThreads: # type: ignore
      processThread.join()
   endTime = time.process_time()
   elapsedMilliseconds = int((endTime - beginTime) * 1000)
   allProcessesExitedZero = not any(processExitCodes)
   print('Done in', elapsedMilliseconds, 'ms')
   print('All processes exited 0:', allProcessesExitedZero)
   return allProcessesExitedZero
