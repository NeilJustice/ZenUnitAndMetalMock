#include "pch.h"
#include "ZenUnit/Equalizers/MapEqualizer.h"

template<
   template<typename...>
   class MapType>
TEMPLATETESTS(MapEqualizerTests, MapType)
FACT(ARE_EQUAL_EqualStdMaps_CompilesAndDoesNotThrow)
BEGINPROOF

TEST(ARE_EQUAL_EqualStdMaps_CompilesAndDoesNotThrow)
{
   const MapType<int, int> expectedMap;
   const MapType<int, int> actualMap;
   ARE_EQUAL(expectedMap, actualMap);
}

};
RUNTEMPLATE(MapEqualizerTests, map)
RUNTEMPLATE(MapEqualizerTests, unordered_map)
