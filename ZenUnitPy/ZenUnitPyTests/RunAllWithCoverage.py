import sys
sys.path.append('..') # Jenkins
from ZenUnitPy import Process

Process.run('coverage3 run --branch --omit="/usr/*" RunAll.py')
Process.run('coverage3 report')
Process.run('coverage3 html')
Process.run('coverage3 xml')
