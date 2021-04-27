from ZenUnitPy import Process, Python

def main() -> None:
   print('[MypyFlake8PylintThenRunTestsWithCoverage.py] Running Mypy, Flake8, Pylint, then running tests with coverage...')
   Python.run_mypy()
   Python.run_flake8()
   Python.run_pylint_on_all_files_in_parallel()
   Process.fail_fast_run('python -u ZenUnitPyTests/RunAllWithCoverage.py')
   print('[MypyFlake8PylintThenRunTestsWithCoverage.py] Successfully ran mypy, flake8, pylint, and unit tests with code coverage.')
   print('[MypyFlake8PylintThenRunTestsWithCoverage.py] ExitCode: 0')

if __name__ == '__main__': # pragma nocover
   main()
