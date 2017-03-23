#include "pch.h"
#include "ZenUnit/Equalizers/MapEqualizer.h"

TESTS(MapEqualizerTests)
SPEC(ARE_EQUAL_EqualStdMaps_CompilesAndDoesNotThrow)
//SKIPSPEC(ARE_EQUAL_UnequalStdMaps_SizeDifferent_Throws, "In development")
SPEC(ARE_EQUAL_UnequalStdMaps_SizeEqual_KeysDifferent_Throws)
SPEC(ARE_EQUAL_UnequalStdMaps_SizeEqual_KeysEqual_ValuesDifferent_Throws)
SPECEND

TEST(ARE_EQUAL_EqualStdMaps_CompilesAndDoesNotThrow)
{
   map<int, int> expectedMap;
   map<int, int> actualMap;
   ARE_EQUAL(expectedMap, actualMap);
}

TEST(ARE_EQUAL_UnequalStdMaps_SizeDifferent_Throws)
{
   map<int, int> m1 = { { 1, 1 } };
   map<int, int> m2;
   THROWS(ARE_EQUAL(m1, m2), Anomaly, R"(
  Failed: ARE_EQUAL(m1, m2)
 Because: MAPS_EQUAL(expectedMap, actualMap) failed
 Because: ARE_EQUAL(expectedMap.size(), actualMap.size()) failed
Expected: 1
  Actual: 0
File.cpp(1)
File.cpp(1)
File.cpp(1))");
}

TEST(ARE_EQUAL_UnequalStdMaps_SizeEqual_KeysDifferent_Throws)
{
}

TEST(ARE_EQUAL_UnequalStdMaps_SizeEqual_KeysEqual_ValuesDifferent_Throws)
{
}

}; RUN(MapEqualizerTests)
