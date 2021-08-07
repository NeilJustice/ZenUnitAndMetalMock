import os
from ZenUnitDevOpsPython import Python

if os.getcwd().endswith('ZenUnitDevOpsPythonTests'):
   os.chdir('..')

Python.run_all_with_coverage(testsProjectName='ZenUnitDevOpsPythonTests', omitPattern='/usr/*,/home/*/.local/lib/python3.9/site-packages/*')
