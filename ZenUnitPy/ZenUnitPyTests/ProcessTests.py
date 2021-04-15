import concurrent.futures
import multiprocessing
import os
import platform
import shlex
import sys
import subprocess
import unittest
from unittest.mock import patch, call
from ZenUnitPy import Process, UnitTester, Random

testNames = [
'fail_fast_run_CallsProcessAndGetExitCode_SysExitsWithExitCodeIfRunReturnsNonZero_test',
'run_and_get_exit_code_RunsProcess_ReturnsExitCode_test',
'run_and_get_exit_code_RunsProcess_ProcessRaisesAnException_PrintsException_Exits1_test',
'cross_platform_subprocess_call_CallsSubprocessCallOnWindows_CallsShlexSubprocessCallOnNotWindows_test',
'run_exe_CallsRunWithExpected_test',
'append_args_AppendsSpaceThenArgsIfArgsNotEmpty_testCases',
'run_parallel_multiprocessing_CallsMultiprocessingPoolMap_Returns1IfAnyExitCodesNon0_test',
'run_parallel_processpoolexecutor_CallsProcessPoolExecutorMap_Returns1IfAnyExitCodesNon0_test',
'run_and_get_stdout_test',
'bytes_to_utf8_ReturnsBytesDecodedToUtf8_test',
'run_and_check_stdout_for_substring_test'
]

class ProcessTests(unittest.TestCase):
   def setUp(self):
      self.configuration = Random.string()
      self.projectName = Random.string()
      self.command = Random.string()
      self.shlexedCommand = Random.string()
      self.currentWorkingDirectory = Random.string()
      self.ExpectedPylintcommand = 'pylint --rcfile=.pylintrc --init-hook=\"sys.path.append(\'.\')\" '

   def fail_fast_run_CallsProcessAndGetExitCode_SysExitsWithExitCodeIfRunReturnsNonZero_test(self):
      @patch('ZenUnitPy.Process.run_and_get_exit_code', spec_set=True)
      @patch('builtins.print', spec_set=True)
      @patch('sys.exit', spec_set=True)
      def testcase(exitCode, expectPrintCommandFailedAndExit, _1, printMock, _3):
         with self.subTest(f'{exitCode, expectPrintCommandFailedAndExit}'):
            Process.run_and_get_exit_code.return_value = exitCode
            #
            Process.fail_fast_run(self.command)
            #
            Process.run_and_get_exit_code.assert_called_once_with(self.command)
            if expectPrintCommandFailedAndExit:
               expectedSingleQuotedCommand = f'\'{self.command}\''
               printMock.assert_called_once_with('Command', expectedSingleQuotedCommand, 'failed with exit code', exitCode)
               sys.exit.assert_called_once_with(exitCode)
            else:
               sys.exit.assert_not_called()
      testcase(-1, True)
      testcase(0, False)
      testcase(1, True)

   @patch('os.getcwd', spec_set=True)
   @patch('builtins.print', spec_set=True)
   @patch('ZenUnitPy.Process.cross_platform_subprocess_call', spec_set=True)
   def run_and_get_exit_code_RunsProcess_ReturnsExitCode_test(self, _1, printMock, _3):
      os.getcwd.return_value = self.currentWorkingDirectory
      subprocessReturnValue = Random.integer()
      Process.cross_platform_subprocess_call.return_value = subprocessReturnValue
      #
      exitCode = Process.run_and_get_exit_code(self.command)
      #
      os.getcwd.assert_called_once_with()
      printMock.assert_called_once_with('Running', f'\'{self.command}\'', 'from', self.currentWorkingDirectory)
      Process.cross_platform_subprocess_call.assert_called_once_with(self.command)
      self.assertEqual(subprocessReturnValue, exitCode)

   @patch('os.getcwd', spec_set=True)
   @patch('builtins.print', spec_set=True)
   @patch('ZenUnitPy.Process.cross_platform_subprocess_call', spec_set=True)
   @patch('sys.exit', spec_set=True)
   def run_and_get_exit_code_RunsProcess_ProcessRaisesAnException_PrintsException_Exits1_test(self, _1, _2, printMock, _4):
      os.getcwd.return_value = self.currentWorkingDirectory
      exceptionMessage = Random.string()
      Process.cross_platform_subprocess_call.side_effect = FileNotFoundError(exceptionMessage)
      #
      Process.run_and_get_exit_code(self.command)
      #
      os.getcwd.assert_called_once_with()
      Process.cross_platform_subprocess_call.assert_called_once_with(self.command)
      self.assertEqual(2, len(printMock.call_args_list))
      printMock.assert_has_calls([
         call('Running', f'\'{self.command}\'', 'from', self.currentWorkingDirectory),
         call(exceptionMessage)])
      sys.exit.assert_called_once_with(1)

   def cross_platform_subprocess_call_CallsSubprocessCallOnWindows_CallsShlexSubprocessCallOnNotWindows_test(self):
      @patch('platform.system', spec_set=True)
      @patch('shlex.split', spec_set=True)
      @patch('subprocess.call', spec_set=True)
      def testcase(platformSystem, expectShlex, _1, _2, _3):
         with self.subTest(f'{platformSystem, expectShlex}'):
            platform.system.return_value = platformSystem
            if expectShlex:
               shlex.split.return_value = self.shlexedCommand
            subprocessCallReturnValue = 1
            subprocess.call.return_value = subprocessCallReturnValue
            #
            exitCode = Process.cross_platform_subprocess_call(self.command)
            #
            platform.system.assert_called_once_with()
            if expectShlex:
               subprocess.call.assert_called_once_with(self.shlexedCommand)
            else:
               subprocess.call.assert_called_once_with(self.command)
            self.assertEqual(subprocessCallReturnValue, exitCode)
      testcase('Windows', False)
      testcase('windows', False)
      testcase('Linux', True)
      testcase('OSX', True)

   @patch('ZenUnitPy.Process.fail_fast_run', spec_set=True)
   @patch('ZenUnitPy.Process.append_args', spec_set=True)
   def run_exe_CallsRunWithExpected_test(self, _1, _2):
      appendArgsReturnValue = Random.string()
      Process.append_args.return_value = appendArgsReturnValue
      args = Random.string()
      #
      Process.run_exe(self.projectName, self.configuration, args)
      #
      Process.append_args.assert_called_once_with(f'{self.projectName}\\{self.configuration}\\{self.projectName}.exe', args)
      Process.fail_fast_run.assert_called_once_with(appendArgsReturnValue)

   def append_args_AppendsSpaceThenArgsIfArgsNotEmpty_testCases(self):
      def testcase(expectedReturnValue, args):
         with self.subTest(f'{expectedReturnValue, args}'):
            returnValue = Process.append_args('ExePath', args)
            self.assertEqual(expectedReturnValue, returnValue)
      testcase('ExePath', '')
      testcase('ExePath  ', ' ')
      testcase('ExePath arg1', 'arg1')
      testcase('ExePath arg1 arg2', 'arg1 arg2')

   def run_parallel_multiprocessing_CallsMultiprocessingPoolMap_Returns1IfAnyExitCodesNon0_test(self):
      class MultiprocessingPoolMock:
         def __init__(self):
            self.map_return_value = 0
            self.mapArgs = []
            self.numberOfCloseCalls = 0

         def map(self, func, iterable):
            self.mapArgs.append((func, iterable))
            return self.map_return_value

         def close(self):
            self.numberOfCloseCalls = self.numberOfCloseCalls + 1

         def assert_map_called_once_with(self, expectedFunc, expectedIterable):
            assert self.mapArgs == [(expectedFunc, expectedIterable)]

         def assert_close_called_once(self):
            assert self.numberOfCloseCalls == 1

      @patch('multiprocessing.cpu_count', spec_set=True)
      @patch('multiprocessing.Pool', spec_set=True)
      def testcase(expectedReturnValue, exitCodes, _1, _2):
         with self.subTest(f'{expectedReturnValue, exitCodes}'):
            cpuCount = Random.integer()
            multiprocessing.cpu_count.return_value = cpuCount
            Iterable = ['a', 'b', 'c']
            poolMock = MultiprocessingPoolMock()
            poolMock.map_return_value = exitCodes
            multiprocessing.Pool.return_value = poolMock
            #
            allcommandsExited0 = Process.run_parallel_multiprocessing(len, Iterable)
            #
            multiprocessing.cpu_count.assert_called_once_with()
            multiprocessing.Pool.assert_called_once_with(cpuCount)
            poolMock.assert_map_called_once_with(len, Iterable)
            poolMock.assert_close_called_once()
            self.assertEqual(expectedReturnValue, allcommandsExited0)
      testcase(False, [-1])
      testcase(True, [0])
      testcase(True, [0, 0])
      testcase(False, [1])
      testcase(False, [2])
      testcase(False, [1, 0])
      testcase(False, [0, 1])
      testcase(False, [0, 1, 0])

   def run_parallel_processpoolexecutor_CallsProcessPoolExecutorMap_Returns1IfAnyExitCodesNon0_test(self):
      class ProcessPoolExecutorMock:
         def __init__(self):
            self.map_numberOfCalls = 0
            self.map_funcArg = None
            self.map_iterableArg = None
            self.map_returnValue = None
            self.shutdown_numberOfCalls = 0
            self.shutdown_waitArg = None

         def map(self, func, iterable):
            self.map_numberOfCalls = self.map_numberOfCalls + 1
            self.map_funcArg = func
            self.map_iterableArg = iterable
            return self.map_returnValue

         def shutdown(self, wait):
            self.shutdown_numberOfCalls = self.shutdown_numberOfCalls + 1
            self.shutdown_waitArg = wait

         def assert_map_called_once_with(self, expectedFunc, expectedIterable):
            assert self.map_numberOfCalls == 1
            assert expectedFunc, self.map_funcArg
            assert expectedIterable, self.map_iterableArg

         def assert_shutdown_called_once_with(self, expectedWait):
            assert 1, self.numberOfShutdownCalls
            assert expectedWait, self.shutdown_waitArg

      @patch('concurrent.futures.ProcessPoolExecutor', spec_set=True)
      @patch('multiprocessing.cpu_count', spec_set=True)
      def testcase(expectedReturnValue, exitCodes, _1, _2):
         with self.subTest(f'{expectedReturnValue, exitCodes}'):
            cpuCount = Random.integer()
            multiprocessing.cpu_count.return_value = cpuCount
            Iterable = ['a', 'b', 'c']
            processPoolExecutorMock = ProcessPoolExecutorMock()
            processPoolExecutorMock.map_returnValue = exitCodes
            concurrent.futures.ProcessPoolExecutor.return_value = processPoolExecutorMock
            #
            allCommandsExited0 = Process.run_parallel_processpoolexecutor(len, Iterable)
            #
            multiprocessing.cpu_count.assert_called_once_with()
            concurrent.futures.ProcessPoolExecutor.assert_called_once_with(cpuCount)
            processPoolExecutorMock.assert_map_called_once_with(len, Iterable)
            processPoolExecutorMock.assert_shutdown_called_once_with(True)
            self.assertEqual(expectedReturnValue, allCommandsExited0)
      testcase(False, [-1])
      testcase(True, [0])
      testcase(True, [0, 0])
      testcase(False, [1])
      testcase(False, [2])
      testcase(False, [1, 0])
      testcase(False, [0, 1])
      testcase(False, [0, 1, 0])

   @patch('shlex.split', spec_set=True)
   @patch('subprocess.check_output', spec_set=True)
   @patch('ZenUnitPy.Process.bytes_to_utf8', spec_set=True)
   def run_and_get_stdout_test(self, _1, _2, _3):
      shlexReturnValue = Random.string()
      shlex.split.return_value = shlexReturnValue
      checkOutputReturnValue = Random.string()
      subprocess.check_output.return_value = checkOutputReturnValue
      toUtf8ReturnValue = Random.string()
      Process.bytes_to_utf8.return_value = toUtf8ReturnValue
      #
      standardOutput = Process.run_and_get_stdout(self.command)
      #
      shlex.split.assert_called_once_with(self.command)
      subprocess.check_output.assert_called_once_with(shlexReturnValue)
      Process.bytes_to_utf8.assert_called_once_with(checkOutputReturnValue)
      self.assertEqual(toUtf8ReturnValue, standardOutput)

   def bytes_to_utf8_ReturnsBytesDecodedToUtf8_test(self):
      self.assertEqual('', Process.bytes_to_utf8(b''))
      self.assertEqual('\r\n', Process.bytes_to_utf8(b'\r\n'))

   def run_and_check_stdout_for_substring_test(self):
      @patch('builtins.print', spec_set=True)
      @patch('ZenUnitPy.Process.run_and_get_stdout', spec_set=True)
      @patch('sys.exit', spec_set=True)
      def testcase(stdout, substring, expectExit, _1, _2, printMock):
         with self.subTest(f'{stdout, substring, expectExit}'):
            Process.run_and_get_stdout.return_value = stdout
            #
            Process.run_and_check_stdout_for_substring(self.command, substring)
            #
            self.assertEqual(2, len(printMock.call_args_list))
            printMock.assert_has_calls([
               call(f'Running \'{self.command}\' and checking for substring \'{substring}\''),
               call(f'Substring \'{substring}\' ' + ('found.' if not expectExit else 'not found.'))])
            if expectExit:
               sys.exit.assert_called_once_with(1)
            else:
               sys.exit.assert_not_called()
      testcase('stdout', 'abc', True)
      testcase('stdout', 'StdOut', True)
      testcase('stdout', 'stdout', False)
      testcase('prefix stdout suffix', 'stdout', False)

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(ProcessTests, testNames)
