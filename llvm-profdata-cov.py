import subprocess
import shlex

subprocess.call(shlex.split("""llvm-profdata merge
   Debug/ZenUnit.Test/coverage.profraw -sparse -o coverage.profdata"""))

subprocess.call(shlex.split("""llvm-cov report
   Debug/ZenUnit.Test/ZenUnit.Test -instr-profile=coverage.profdata"""))

subprocess.call(shlex.split("""llvm-cov show
   Debug/ZenUnit.Test/ZenUnit.Test -instr-profile=coverage.profdata -project-title=ZenUnit -format=html -output-dir=covhtml -show-line-counts-or-regions -Xdemangler c++filt"""))

