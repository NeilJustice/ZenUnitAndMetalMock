import sys
sys.path.append('..') # Jenkins
from ZenUnitPy import Process

Process.run('coverage3 run --branch --omit="/usr/*" RunAll.py')
Process.run('coverage3 report --fail-under=100 --show-missing')
Process.run('coverage3 xml -o ZenUnitPy/ZenUnitPyTests/CoberturaCodeCoverageResults_ZenUnitPyTests.xml')
Process.run('coverage3 html')
