set -eu
mkdir build
cd build
cmake -GNinja .. -Werror=dev -DCMAKE_CXX_COMPILER="$COMPILER" -DCMAKE_BUILD_TYPE="$CMAKE_BUILD_TYPE"
# ZenUnitTests call upon ZenMock to confirm the correctness of ZenUnit
curl https://raw.githubusercontent.com/NeilJustice/ZenMock/master/ZenMock/ZenMock.h -o ZenMock.h
ninja -v -j 3
./ZenUnitTests/ZenUnitTests
./ZenUnitExamples/ZenUnitExamples
