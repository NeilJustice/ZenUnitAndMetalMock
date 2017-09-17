import os
import sys
import unittest
from unittest.mock import patch
from unittest.mock import call
from ZenUnitPy import UnitTester, Util

testNames = [
'home_folder_join_test',
'code_folder_join_ReturnsHomeFolderCodeFolderSpecifiedFolder_test',
'print_and_exit_PrintsMessageThenCallsExitWithExitCode_test'
]

Message = 'Message'

class UtilTests(unittest.TestCase):

   @patch('os.path.expanduser', spec_set=True)
   @patch('os.path.join', spec_set=True)
   def home_folder_join_test(self, _1, _2):
      HomeFolderPath = 'ExpandUserValue'
      os.path.expanduser.return_value = HomeFolderPath
      JoinedHomeFolderPath = 'JoinedHomeFolderPath'
      os.path.join.return_value = JoinedHomeFolderPath
      FolderPath = 'FolderPath'
      FileName = 'FileName'
      #
      joinedHomeFolderPath = Util.home_folder_join(FolderPath, FileName)
      #
      os.path.expanduser.assert_called_once_with('~')
      os.path.join.assert_called_once_with(HomeFolderPath, FolderPath, FileName)
      self.assertEqual(JoinedHomeFolderPath, joinedHomeFolderPath)

   @patch('os.path.expanduser', spec_set=True)
   @patch('os.path.join', spec_set=True)
   def code_folder_join_ReturnsHomeFolderCodeFolderSpecifiedFolder_test(self, _1, _2):
      HomeFolderPath = 'ExpandUserValue'
      os.path.expanduser.return_value = HomeFolderPath
      CodeFolderPath = 'CodeFolderPath'
      JoinedCodeFolderPath = 'JoinedCodeFolderPath'
      os.path.join.side_effect = [CodeFolderPath, JoinedCodeFolderPath]
      FolderPath = 'FolderPath'
      #
      joinedCodeFolderPath = Util.code_folder_join(FolderPath)
      #
      os.path.expanduser.assert_called_once_with('~')
      self.assertEqual(2, len(os.path.join.call_args_list))
      os.path.join.assert_has_calls([
         call(HomeFolderPath, 'Code'),
         call(CodeFolderPath, FolderPath)])
      self.assertEqual(JoinedCodeFolderPath, joinedCodeFolderPath)

   @patch('builtins.print', spec_set=True)
   @patch('sys.exit', spec_set=True)
   def print_and_exit_PrintsMessageThenCallsExitWithExitCode_test(self, _1, _2):
      ExitCode = 1
      #
      Util.print_and_exit(Message, ExitCode)
      #
      print.assert_called_once_with(Message)
      sys.exit.assert_called_once_with(ExitCode)

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(UtilTests, testNames)
