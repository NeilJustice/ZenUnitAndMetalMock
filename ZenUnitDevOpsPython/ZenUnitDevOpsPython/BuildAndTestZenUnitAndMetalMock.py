"""Usage: BuildAndTestZenUnitAndMetalMock.py --cmake-generator=<CMakeGenerator> --cmake-build-type=<CMakeBuildType> --cmake-definitions=<QuotedSpaceSeparatedCMakeDefinitions>"""
import os
import platform
import sys
from typing import Any
import docopt # type: ignore
from ZenUnitDevOpsPython import CMake, Process

def main() -> int:
   runningSysArgvMessage = f'Running {sys.argv}\n'
   print(runningSysArgvMessage)
   docoptDictionary: docopt.Dict = docopt.docopt(__doc__)
   cmakeGenerator: Any = docoptDictionary['--cmake-generator']
   cmakeBuildType: Any = docoptDictionary['--cmake-build-type']
   cmakeDefinitions: Any = docoptDictionary['--cmake-definitions']
   platformSystem: Any = platform.system().casefold()
   if platformSystem == 'linux':
      linux_cmake_build(cmakeGenerator, cmakeBuildType, cmakeDefinitions)
      Process.fail_fast_run('MetalMockExamples/MetalMockExamples --test-runs=2 --random --max-test-milliseconds=200')
      Process.fail_fast_run('MetalMockTests/MetalMockTests --test-runs=2 --random --max-test-milliseconds=200')
      Process.fail_fast_run('ZenUnitCompileSpeedTests/ZenUnitCompileSpeedTests --test-runs=2 --random --max-test-milliseconds=200')
      Process.fail_fast_run('ZenUnitExamples/ZenUnitExamples --test-runs=2 --random --max-test-milliseconds=200')
      Process.fail_fast_run('ZenUnitLibraryTests/ZenUnitLibraryTests --test-runs=2 --random --max-test-milliseconds=200')
      Process.fail_fast_run('ZenUnitUtilsAndAssertionTests/ZenUnitUtilsAndAssertionTests --test-runs=2 --random --max-test-milliseconds=200')
      os.chdir('..')
   else:
      windows_cmake_build(cmakeGenerator, cmakeBuildType, cmakeDefinitions) # Runs all tests once randomly as post-build events
      # Run all tests randomly a second time
      Process.fail_fast_run(f'MetalMockExamples/{cmakeBuildType}/MetalMockExamples.exe --random --max-test-milliseconds=200')
      Process.fail_fast_run(f'MetalMockTests/{cmakeBuildType}/MetalMockTests.exe --random --max-test-milliseconds=200')
      Process.fail_fast_run(f'ZenUnitCompileSpeedTests/{cmakeBuildType}/ZenUnitCompileSpeedTests.exe --random --max-test-milliseconds=200')
      Process.fail_fast_run(f'ZenUnitExamples/{cmakeBuildType}/ZenUnitExamples.exe --random --max-test-milliseconds=200')
      Process.fail_fast_run(f'ZenUnitLibraryTests/{cmakeBuildType}/ZenUnitLibraryTests.exe --random --max-test-milliseconds=200')
      Process.fail_fast_run(f'ZenUnitUtilsAndAssertionTests/{cmakeBuildType}/ZenUnitUtilsAndAssertionTests.exe --random --max-test-milliseconds=200')
   return 0

def linux_cmake_build(cmakeGenerator: str, cmakeBuildType: str, cmakeDefinitions: str) -> None:
   CMake.generate(cmakeBuildType, cmakeGenerator, cmakeBuildType, cmakeDefinitions, '..')
   Process.fail_fast_run('ninja -v')

def windows_cmake_build(cmakeGenerator: str, cmakeBuildType: str, cmakeDefinitions: str) -> None:
   CMake.generate('.', cmakeGenerator, cmakeBuildType, cmakeDefinitions, '.')
   cmakeBuildCommand = f'cmake.exe --build . --config {cmakeBuildType}'
   Process.fail_fast_run(cmakeBuildCommand)

if __name__ == "__main__": # pragma nocover
   sys.exit(main())

# Example command line arguments:
# --cmake-generator="Visual Studio 16 2019" --cmake-build-type=Debug --cmake-definitions=""
# Working directory:
# D:\Code\ZenUnitAndMetalMock
