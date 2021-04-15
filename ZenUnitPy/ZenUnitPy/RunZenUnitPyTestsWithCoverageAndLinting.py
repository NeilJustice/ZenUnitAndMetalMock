from ZenUnitPy import Process, Python

def main() -> None:
   Process.fail_fast_run('python -u ZenUnitPyTests/RunAllWithCoverage.py')
   Python.pylint_all()
   Python.flake8_all()

if __name__ == '__main__': # pragma nocover
   main()
