import platform
import os
import shutil
import unittest
from unittest.mock import patch
from ZenUnitPy import FileSystem, UnitTester

testNames = [
'delete_folder_if_exists_DeletesEmptyOrNonEmptyFolderIfItExists_test',
'get_filepaths_ReturnsAllFilePathsInAndBelowFolderPath_test',
'copy_file_to_folder_CreateDestFolderAndCopiesFile_test'
]

class FolderTests(unittest.TestCase):

   def delete_folder_if_exists_DeletesEmptyOrNonEmptyFolderIfItExists_test(self):
      @patch('os.path.exists', spec_set=True)
      @patch('shutil.rmtree', spec_set=True)
      def testcase(folderExists, expectrmtreeCall, _1, _2):
         with self.subTest(f'{folderExists}, {expectrmtreeCall}'):
            os.path.exists.return_value = folderExists
            FolderPath = 'FolderPath'
            #
            FileSystem.delete_folder_if_exists(FolderPath)
            #
            os.path.exists.assert_called_once_with(FolderPath)
            if expectrmtreeCall:
               shutil.rmtree.assert_called_once_with(FolderPath)
            else:
               shutil.rmtree.assert_not_called()
      testcase(False, False)
      testcase(True, True)

   def get_filepaths_ReturnsAllFilePathsInAndBelowFolderPath_test(self): # pragma nocover
      @patch('os.walk', spec_set=True)
      def testcase(expectedFilePaths, oswalkReturnValue, _1):
         with self.subTest(f'{expectedFilePaths}, {oswalkReturnValue}'):
            os.walk.return_value = oswalkReturnValue
            FolderPath = 'FolderPath'
            #
            filePaths = FileSystem.get_filepaths(FolderPath)
            #
            os.walk.assert_called_once_with(FolderPath)
            self.assertEqual(expectedFilePaths, filePaths)
      testcase([], [])
      if platform.system() == 'Windows':
         testcase(['.\\a.txt'], [('.', [], ['a.txt'])])
         testcase([
            '.\\file1.bin',
            '.\\file2',
            '.\\folderB\\b2.txt',
            '.\\folderB\\b1.txt',
            '.\\folderA\\a1.txt',
            '.\\folderA\\a2.txt'
         ], [
            ('.', ['folderB', 'folderA'], ['file1.bin', 'file2']),
            ('.\\folderB', ['emptyfolder'], ['b2.txt', 'b1.txt']),
            ('.\\folderB/emptyfolder', [], []),
            ('.\\folderA', [], ['a1.txt', 'a2.txt'])
         ])
      else:
         testcase(['./a.txt'], [('.', [], ['a.txt'])])
         testcase([
            './file1.bin',
            './file2',
            './folderB/b2.txt',
            './folderB/b1.txt',
            './folderA/a1.txt',
            './folderA/a2.txt'
         ], [
            ('.', ['folderB', 'folderA'], ['file1.bin', 'file2']),
            ('./folderB', ['emptyfolder'], ['b2.txt', 'b1.txt']),
            ('./folderB/emptyfolder', [], []),
            ('./folderA', [], ['a1.txt', 'a2.txt'])
         ])

   @patch('os.path.join', spec_set=True)
   @patch('os.path.dirname', spec_set=True)
   @patch('os.makedirs', spec_set=True)
   @patch('shutil.copy', spec_set=True)
   def copy_file_to_folder_CreateDestFolderAndCopiesFile_test(self, _1, _2, _3, _4):
      DestFilePath = 'DestFilePath'
      os.path.join.return_value = DestFilePath

      DestFilePathDirName = 'DestFilePathDirName'
      os.path.dirname.return_value = DestFilePathDirName

      DestFolderPath = 'DestFolderPath'
      SourceFilePath = 'SourceFilePath'
      #
      FileSystem.copy_file_to_folder(SourceFilePath, DestFolderPath)
      #
      os.path.join.assert_called_once_with(DestFolderPath, SourceFilePath)
      os.path.dirname.assert_called_once_with(DestFilePath)
      os.makedirs.assert_called_once_with(DestFilePathDirName, exist_ok=True)
      shutil.copy.assert_called_once_with(SourceFilePath, DestFilePath)

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(FolderTests, testNames)
