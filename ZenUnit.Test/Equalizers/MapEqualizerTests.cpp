#include "pch.h"
#include "ZenUnit/Equalizers/MapEqualizer.h"

TESTS(MapEqualizerTests)
SPEC(ARE_EQUAL_EqualStdMaps_CompilesAndDoesNotThrow)
SPECEND

TEST(ARE_EQUAL_EqualStdMaps_CompilesAndDoesNotThrow)
{
   const map<int, int> expectedMap;
   const map<int, int> actualMap;
   ARE_EQUAL(expectedMap, actualMap);
}

}; RUN(MapEqualizerTests)
