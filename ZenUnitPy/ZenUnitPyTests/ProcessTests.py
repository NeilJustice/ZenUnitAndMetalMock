import multiprocessing
import os
import platform
import shlex
import sys
import subprocess
import unittest
from unittest.mock import patch, call, sentinel
import Random
from ZenUnitPy import Process, UnitTester

testNames = [
'run_RunsProcess_SysExitsIfExitCodeNonZero_test',
'run_and_get_exitcode_CallsSubprocessCallCommand_WithShlexCommandIfNotWindows_ReturnsExitCode_test',
'map_parallel_CallsMultiprocessingPoolMap_Returns1IfAnyExitCodesNon0_test',
'map_sequential_CallsMap_ReturnsTrueIfAllExitCodes0_test'
]

class PoolMock:
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


class RunTests(unittest.TestCase):
   def setUp(self):
      self.configuration = Random.string()
      self.projectName = Random.string()
      self.appendArgsReturnValue = Random.string()
      self.command = Random.string()

   def run_RunsProcess_SysExitsIfExitCodeNonZero_test(self):
      @patch('ZenUnitPy.Process.run_and_get_exitcode', spec_set=True)
      @patch('builtins.print', spec_set=True)
      @patch('sys.exit', spec_set=True)
      def testcase(exitCode, expectPrintCommandFailedAndExit, _1, _2, _3):
         with self.subTest(f'{exitCode}, {expectPrintCommandFailedAndExit}'):
            Process.run_and_get_exitcode.return_value = exitCode
            #
            Process.run(self.command)
            #
            Process.run_and_get_exitcode.assert_called_once_with(self.command)
            if expectPrintCommandFailedAndExit:
               expectedSingleQuotedCommand = '\'' + self.command + '\''
               print.assert_called_once_with(
                  'Command', expectedSingleQuotedCommand, 'failed with exit code', exitCode)
               sys.exit.assert_called_once_with(exitCode)
            else:
               sys.exit.assert_not_called()
      testcase(-1, True)
      testcase(0, False)
      testcase(1, True)

   def run_and_get_exitcode_CallsSubprocessCallCommand_WithShlexCommandIfNotWindows_ReturnsExitCode_test(self):
      @patch('os.getcwd', spec_set=True)
      @patch('builtins.print', spec_set=True)
      @patch('platform.system', spec_set=True)
      @patch('shlex.split', spec_set=True)
      @patch('subprocess.call', spec_set=True)
      def testcase(platformValue, expectShlexSplitCommand, _1, _2, _3, _4, _5):
         with self.subTest(f'{platformValue}, {expectShlexSplitCommand}'):
            currentWorkingDirectory = Random.string()
            os.getcwd.return_value = currentWorkingDirectory
            platform.system.return_value = platformValue
            shlexedCommand = Random.string()
            shlex.split.return_value = shlexedCommand
            subprocessCallReturnValue = Random.integer()
            subprocess.call.return_value = subprocessCallReturnValue
            #
            exitCode = Process.run_and_get_exitcode(self.command)
            #
            expectedSingleQuotedCommand = '\'' + self.command + '\''
            os.getcwd.assert_called_once_with()
            print.assert_called_once_with(
               'Running', expectedSingleQuotedCommand, 'from', currentWorkingDirectory)
            if expectShlexSplitCommand:
               shlex.split.assert_called_once_with(self.command)
               subprocess.call.assert_called_once_with(shlexedCommand)
            else:
               shlex.split.assert_not_called()
               subprocess.call.assert_called_once_with(self.command)
            self.assertEqual(subprocessCallReturnValue, exitCode)
      testcase('Windows', False)
      testcase('windows', True)
      testcase('Linux', True)

   def map_parallel_CallsMultiprocessingPoolMap_Returns1IfAnyExitCodesNon0_test(self):
      @patch('multiprocessing.Pool', spec_set=True)
      @patch('multiprocessing.cpu_count', spec_set=True)
      def testcase(expectedReturnValue, exitCodes, _1, _2):
         with self.subTest(f'{expectedReturnValue}, {exitCodes}'):
            multiprocessing.cpu_count.reset_mock()
            multiprocessing.Pool.reset_mock()
            cpuCount = Random.integer()
            multiprocessing.cpu_count.return_value = cpuCount
            iterable = [Random.string(), Random.string(), Random.string()]
            poolMock = PoolMock()
            poolMock.map_return_value = exitCodes
            multiprocessing.Pool.return_value = poolMock
            #
            allCommandsExited0 = Process.map_parallel(len, iterable)
            #
            multiprocessing.cpu_count.assert_called_once_with()
            multiprocessing.Pool.assert_called_once_with(cpuCount)
            poolMock.assert_map_called_once_with(len, iterable)
            poolMock.assert_close_called_once()
            self.assertEqual(expectedReturnValue, allCommandsExited0)
      testcase(False, [-1])
      testcase(True, [0])
      testcase(True, [0, 0])
      testcase(True, [0, 0, 0])
      testcase(False, [1])
      testcase(False, [1, 0])
      testcase(False, [0, 1])
      testcase(False, [0, 0, 5])

   def map_sequential_CallsMap_ReturnsTrueIfAllExitCodes0_test(self):
      @patch('builtins.map', spec_set=True)
      @patch('builtins.any', spec_set=True)
      def testcase(expectedReturnValue, anyReturnValue, _1, _2):
         with self.subTest(f'{expectedReturnValue}, {anyReturnValue}'):
            map.return_value = sentinel.ExitCodesMapObject
            any.return_value = anyReturnValue
            iterable = [Random.string(), Random.string(), Random.string()]
            #
            allCommandsExited0 = Process.map_sequential(len, iterable)
            #
            map.assert_called_once_with(len, iterable)
            any.assert_called_once_with(sentinel.ExitCodesMapObject)
            self.assertEqual(expectedReturnValue, allCommandsExited0)
      testcase(False, True)
      testcase(True, False)

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(RunTests, testNames)
