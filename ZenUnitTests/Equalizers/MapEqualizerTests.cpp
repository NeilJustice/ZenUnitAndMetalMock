#include "pch.h"
#include "ZenUnit/Equalizers/MapEqualizer.h"

template<
   template<typename...>
   class MapType>
TEMPLATETESTS(MapEqualizerTests, MapType)
SPEC(ARE_EQUAL_EqualStdMaps_CompilesAndDoesNotThrow)
SPECEND

TEST(ARE_EQUAL_EqualStdMaps_CompilesAndDoesNotThrow)
{
   const MapType<int, int> expectedMap;
   const MapType<int, int> actualMap;
   ARE_EQUAL(expectedMap, actualMap);
}

};
RUNTEMPLATE(MapEqualizerTests, map)
RUNTEMPLATE(MapEqualizerTests, unordered_map)
