import os
from ZenUnitPy import Python

if os.getcwd().endswith('ZenUnitPyTests'):
   os.chdir('..')

Python.run_all_with_coverage(testsProjectName='ZenUnitPyTests', omitPattern='/usr/*,/home/*/.local/lib/python3.9/site-packages/*')
