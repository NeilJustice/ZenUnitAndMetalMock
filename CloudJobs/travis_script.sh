set -eux

clang++ --version
g++ --version
cmake --version
ninja --version
python3 --version

if [ "$CODE_COV_MODE" == "ON" ];
then
  gcov --version
  lcov --version
fi

mkdir build && cd build
cmake -GNinja .. -Werror=dev -DCMAKE_CXX_COMPILER="$COMPILER" -DCMAKE_BUILD_TYPE="$CMAKE_BUILD_TYPE" -DCodeCovMode="$CODE_COV_MODE"
ninja -v
./ZenMockTests/ZenMockTests --test-runs=3 --random
./ZenMockExamples/ZenMockExamples --test-runs=3 --random
./ZenUnitUtilsAndAssertionTests/ZenUnitUtilsAndAssertionTests --test-runs=3 --random
./ZenUnitLibraryTests/ZenUnitLibraryTests --test-runs=3 --random
./ZenUnitExamples/ZenUnitExamples --test-runs=3 --random
