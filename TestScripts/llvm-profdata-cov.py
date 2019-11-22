import subprocess
import shlex

#subprocess.call(shlex.split("""llvm-profdata merge
 # Debug/ZenUnitLibraryTests/coverage.profraw -sparse -o coverage.profdata"""))

#subprocess.call(shlex.split("""llvm-cov report
 # Debug/ZenUnitLibraryTests/ZenUnitLibraryTests -instr-profile=coverage.profdata"""))

#subprocess.call(shlex.split("""llvm-cov show
 # Debug/ZenUnitLibraryTests/ZenUnitLibraryTests -instr-profile=coverage.profdata -project-title=ZenUnit -format=html -output-dir=covhtml -show-instantiation-summary -show-line-counts-or-regions -Xdemangler c++filt"""))

subprocess.call(shlex.split("""llvm-profdata merge
  Debug/ZenMockTests/coverage.profraw -sparse -o coverage.profdata"""))

subprocess.call(shlex.split("""llvm-cov report
  Debug/ZenMockTests/ZenMockTests -instr-profile=coverage.profdata"""))

subprocess.call(shlex.split("""llvm-cov show
  Debug/ZenMockTests/ZenMockTests -instr-profile=coverage.profdata -project-title=ZenUnit -format=html -output-dir=covhtml -show-instantiation-summary -show-line-counts-or-regions -Xdemangler c++filt"""))
