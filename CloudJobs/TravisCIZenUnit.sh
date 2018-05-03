set -eu

curl https://raw.githubusercontent.com/NeilJustice/ZenMock/master/ZenMock/ZenMock.h -o ZenMock.h
mkdir build
cd build
echo $CMAKE_BUILD_TYPE
cmake -GNinja .. -Werror=dev -DCMAKE_CXX_COMPILER="$COMPILER" -DCMAKE_BUILD_TYPE="$CMAKE_BUILD_TYPE"
ninja -v -j 3
./ZenUnitTests/ZenUnitTests
./ZenUnitExamples/ZenUnitExamples
