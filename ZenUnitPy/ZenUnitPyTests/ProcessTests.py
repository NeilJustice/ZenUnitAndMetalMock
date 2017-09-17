import multiprocessing
import os
import platform
import shlex
import sys
import subprocess
import unittest
from unittest.mock import patch, call, sentinel
from ZenUnitPy import Process, UnitTester

testNames = [
'run_RunsProcess_SysExitsIfExitCodeNonZero_test',
'run_and_get_exitcode_CallsSubprocessCallCommand_WithShlexCommandIfNotWindows_ReturnsExitCode_test',
'run_and_get_stdout_RunsProcess_ReturnsStandardOutput_test',
'to_utf8_ReturnsBytesDecodedToUtf8_test',
'run_and_check_stdout_for_substring_test',
'run_exe_ArgsNotSpecified_CallsRunWithExpected_test',
'run_exe_ArgSpecified_CallsRunWithExpected_test',
'append_args_AppendsSpaceThenArgsIfArgsNotEmpty_test',
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
   Configuration = 'Configuration'
   ProjectName = 'ProjectName'
   AppendArgsReturnValue = 'AppendArgsReturnValue'
   Command = 'Command Arg1 Arg2'

   def run_RunsProcess_SysExitsIfExitCodeNonZero_test(self):
      @patch('ZenUnitPy.Process.run_and_get_exitcode', spec_set=True)
      @patch('builtins.print', spec_set=True)
      @patch('sys.exit', spec_set=True)
      def testcase(exitCode, expectPrintCommandFailedAndExit, _1, _2, _3):
         with self.subTest(f'{exitCode}, {expectPrintCommandFailedAndExit}'):
            Process.run_and_get_exitcode.return_value = exitCode
            #
            Process.run(self.Command)
            #
            Process.run_and_get_exitcode.assert_called_once_with(self.Command)
            if expectPrintCommandFailedAndExit:
               expectedSingleQuotedCommand = '\'' + self.Command + '\''
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
            CurrentWorkingDirectory = 'CurrentWorkingDirectory'
            os.getcwd.return_value = CurrentWorkingDirectory
            platform.system.return_value = platformValue
            ShlexedCommand = 'ShlexedCommand'
            shlex.split.return_value = ShlexedCommand
            ExitCode = 1
            subprocess.call.return_value = ExitCode
            #
            exitCode = Process.run_and_get_exitcode(self.Command)
            #
            expectedSingleQuotedCommand = '\'' + self.Command + '\''
            os.getcwd.assert_called_once_with()
            print.assert_called_once_with(
               'Running', expectedSingleQuotedCommand, 'from', CurrentWorkingDirectory)
            if expectShlexSplitCommand:
               shlex.split.assert_called_once_with(self.Command)
               subprocess.call.assert_called_once_with(ShlexedCommand)
            else:
               shlex.split.assert_not_called()
               subprocess.call.assert_called_once_with(self.Command)
            self.assertEqual(ExitCode, exitCode)
      testcase('Windows', False)
      testcase('windows', True)
      testcase('Linux', True)

   @patch('shlex.split', spec_set=True)
   @patch('subprocess.check_output', spec_set=True)
   @patch('ZenUnitPy.Process.to_utf8', spec_set=True)
   def run_and_get_stdout_RunsProcess_ReturnsStandardOutput_test(self, _1, _2, _3):
      ShlexReturnValue = 'ShlexReturnValue'
      shlex.split.return_value = ShlexReturnValue
      CheckOutputReturnValue = 'CheckOutputReturnValue'
      subprocess.check_output.return_value = CheckOutputReturnValue
      ToUtf8ReturnValue = 'ToUtf8ReturnValue'
      Process.to_utf8.return_value = ToUtf8ReturnValue
      #
      standardOutput = Process.run_and_get_stdout(self.Command)
      #
      shlex.split.assert_called_once_with(self.Command)
      subprocess.check_output.assert_called_once_with(ShlexReturnValue)
      Process.to_utf8.assert_called_once_with(CheckOutputReturnValue)
      self.assertEqual(ToUtf8ReturnValue, standardOutput)

   def to_utf8_ReturnsBytesDecodedToUtf8_test(self):
      self.assertEqual('', Process.to_utf8(b''))

   def run_and_check_stdout_for_substring_test(self):
      @patch('builtins.print', spec_set=True)
      @patch('ZenUnitPy.Process.run_and_get_stdout', spec_set=True)
      @patch('sys.exit', spec_set=True)
      def testcase(stdout, substring, expectExit, _1, _2, _3):
         with self.subTest(f'{stdout}, {substring}, {expectExit}'):
            Process.run_and_get_stdout.return_value = stdout
            #
            Process.run_and_check_stdout_for_substring(self.Command, substring)
            #
            self.assertEqual(2, len(print.call_args_list))
            print.assert_has_calls([
               call('Running \'' + self.Command + '\' and checking for substring \'' + substring + '\''),
               call('Substring \'' + substring + '\' ' + ('found.' if not expectExit else 'not found.'))])
            if expectExit:
               sys.exit.assert_called_once_with(1)
            else:
               sys.exit.assert_not_called()
      testcase('stdout', 'abc', True)
      testcase('stdout', 'StdOut', True)
      testcase('stdout', 'stdout', False)
      testcase('prefix stdout suffix', 'stdout', False)

   @patch('ZenUnitPy.Process.run', spec_set=True)
   @patch('ZenUnitPy.Process.append_args', spec_set=True)
   def run_exe_ArgsNotSpecified_CallsRunWithExpected_test(self, _1, _2):
      Process.append_args.return_value = self.AppendArgsReturnValue
      #
      Process.run_exe(self.ProjectName, self.Configuration)
      #
      self.assert_exe_behavior('')

   @patch('ZenUnitPy.Process.run', spec_set=True)
   @patch('ZenUnitPy.Process.append_args', spec_set=True)
   def run_exe_ArgSpecified_CallsRunWithExpected_test(self, _1, _2):
      Process.append_args.return_value = self.AppendArgsReturnValue
      #
      Process.run_exe(self.ProjectName, self.Configuration, 'args')
      #
      self.assert_exe_behavior('args')

   def assert_exe_behavior(self, expectedArgs):
      expectedExePath = '{0}\\{1}\\{0}.exe'.format(self.ProjectName, self.Configuration)
      Process.append_args.assert_called_once_with(expectedExePath, expectedArgs)
      Process.run.assert_called_once_with(self.AppendArgsReturnValue)

   def append_args_AppendsSpaceThenArgsIfArgsNotEmpty_test(self):
      def testcase(expectedReturnValue, args):
         with self.subTest(f'{expectedReturnValue}, {args}'):
            returnValue = Process.append_args('ExePath', args)
            self.assertEqual(expectedReturnValue, returnValue)
      testcase('ExePath', '')
      testcase('ExePath  ', ' ')
      testcase('ExePath arg1', 'arg1')
      testcase('ExePath arg1 arg2', 'arg1 arg2')

   def map_parallel_CallsMultiprocessingPoolMap_Returns1IfAnyExitCodesNon0_test(self):
      @patch('multiprocessing.Pool', spec_set=True)
      @patch('multiprocessing.cpu_count', spec_set=True)
      def testcase(expectedReturnValue, exitCodes, _1, _2):
         with self.subTest(f'{expectedReturnValue}, {exitCodes}'):
            multiprocessing.cpu_count.reset_mock()
            multiprocessing.Pool.reset_mock()
            CpuCount = 128
            multiprocessing.cpu_count.return_value = CpuCount
            Iterable = ['a', 'b', 'c']
            poolMock = PoolMock()
            poolMock.map_return_value = exitCodes
            multiprocessing.Pool.return_value = poolMock
            #
            allCommandsExited0 = Process.map_parallel(len, Iterable)
            #
            multiprocessing.cpu_count.assert_called_once_with()
            multiprocessing.Pool.assert_called_once_with(CpuCount)
            poolMock.assert_map_called_once_with(len, Iterable)
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
            Iterable = ['a', 'b', 'c']
            #
            allCommandsExited0 = Process.map_sequential(len, Iterable)
            #
            map.assert_called_once_with(len, Iterable)
            any.assert_called_once_with(sentinel.ExitCodesMapObject)
            self.assertEqual(expectedReturnValue, allCommandsExited0)
      testcase(False, True)
      testcase(True, False)

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(RunTests, testNames)
