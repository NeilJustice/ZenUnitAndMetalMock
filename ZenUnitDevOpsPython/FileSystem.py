import os
import shutil

def delete_folder_if_exists(folderPath: str) -> None:
   if os.path.exists(folderPath):
      shutil.rmtree(folderPath)
      print(f'Deleted folder {folderPath}')

def copy_file_to_folder(sourceFilePath: str, destFolderPath: str) -> None:
   destFilePath = os.path.join(destFolderPath, sourceFilePath)
   destFilePathDirName = os.path.dirname(destFilePath)
   os.makedirs(destFilePathDirName, exist_ok=True)
   shutil.copy(sourceFilePath, destFilePath)
