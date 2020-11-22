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
./MetalMockTests/MetalMockTests --test-runs=3 --random-test-ordering
./MetalMockExamples/MetalMockExamples --test-runs=3 --random-test-ordering
./ZenUnitUtilsAndAssertionTests/ZenUnitUtilsAndAssertionTests --test-runs=3 --random-test-ordering
./ZenUnitLibraryTests/ZenUnitLibraryTests --test-runs=3 --random-test-ordering
./ZenUnitExamples/ZenUnitExamples --test-runs=3 --random-test-ordering
