import os
import shutil

def delete_folder_if_exists(folderPath):
   if os.path.exists(folderPath):
      shutil.rmtree(folderPath)
      print(f'Deleted folder {folderPath}')

def copy_file_to_folder(sourceFilePath, destFolderPath):
   destFilePath = os.path.join(destFolderPath, sourceFilePath)
   destFilePathDirName = os.path.dirname(destFilePath)
   os.makedirs(destFilePathDirName, exist_ok=True)
   shutil.copy(sourceFilePath, destFilePath)

def get_filepaths(folderPath):
   filePaths = []
   for dirpath, _, filenames in os.walk(folderPath):
      for filename in filenames:
         filePath = os.path.join(dirpath, filename)
         filePaths.append(filePath)
   return filePaths
