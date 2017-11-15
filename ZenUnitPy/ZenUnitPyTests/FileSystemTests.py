import platform
import os
import shutil
import unittest
from unittest.mock import patch
from ZenUnitPy import FileSystem, UnitTester
import Random

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
            folderPath = Random.string()
            #
            FileSystem.delete_folder_if_exists(folderPath)
            #
            os.path.exists.assert_called_once_with(folderPath)
            if expectrmtreeCall:
               shutil.rmtree.assert_called_once_with(folderPath)
            else:
               shutil.rmtree.assert_not_called()
      testcase(False, False)
      testcase(True, True)

   def get_filepaths_ReturnsAllFilePathsInAndBelowFolderPath_test(self): # pragma nocover
      @patch('os.walk', spec_set=True)
      def testcase(expectedFilePaths, oswalkReturnValue, _1):
         with self.subTest(f'{expectedFilePaths}, {oswalkReturnValue}'):
            os.walk.return_value = oswalkReturnValue
            folderPath = Random.string()
            #
            filePaths = FileSystem.get_filepaths(folderPath)
            #
            os.walk.assert_called_once_with(folderPath)
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
      destFilePath = Random.string()
      os.path.join.return_value = destFilePath

      destFilePathDirName = Random.string()
      os.path.dirname.return_value = destFilePathDirName

      destFolderPath = Random.string()
      sourceFilePath = Random.string()
      #
      FileSystem.copy_file_to_folder(sourceFilePath, destFolderPath)
      #
      os.path.join.assert_called_once_with(destFolderPath, sourceFilePath)
      os.path.dirname.assert_called_once_with(destFilePath)
      os.makedirs.assert_called_once_with(destFilePathDirName, exist_ok=True)
      shutil.copy.assert_called_once_with(sourceFilePath, destFilePath)

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(FolderTests, testNames)
