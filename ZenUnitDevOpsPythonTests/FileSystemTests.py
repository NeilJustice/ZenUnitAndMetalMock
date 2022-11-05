import os
import shutil
import unittest
from unittest.mock import patch
from ZenUnitDevOpsPython import FileSystem
from ZenUnitDevOpsPythonTests import Random, UnitTester

testNames = [
'test_delete_folder_if_exists_DeletesEmptyOrNonEmptyFolderIfItExists',
'test_copy_file_to_folder_CreateDestFolderAndCopiesFile',
]

class FolderTests(unittest.TestCase):

   def test_delete_folder_if_exists_DeletesEmptyOrNonEmptyFolderIfItExists(self):
      @patch('os.path.exists', spec_set=True)
      @patch('shutil.rmtree', spec_set=True)
      @patch('builtins.print', spec_set=True)
      def testcase(folderExists, expectrmtreeCall, printMock, _2, _3):
         with self.subTest(f'{folderExists}, {expectrmtreeCall}'):
            os.path.exists.return_value = folderExists
            folderPath = Random.string()
            #
            FileSystem.delete_folder_if_exists(folderPath)
            #
            os.path.exists.assert_called_once_with(folderPath)
            if expectrmtreeCall:
               shutil.rmtree.assert_called_once_with(folderPath)
               printMock.assert_called_once_with(f'Deleted folder {folderPath}')
            else:
               shutil.rmtree.assert_not_called()
               printMock.assert_not_called()
      testcase(False, False)
      testcase(True, True)

   @staticmethod
   @patch('os.path.join', spec_set=True)
   @patch('os.path.dirname', spec_set=True)
   @patch('os.makedirs', spec_set=True)
   @patch('shutil.copy', spec_set=True)
   def test_copy_file_to_folder_CreateDestFolderAndCopiesFile(_1, _2, _3, _4):
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
