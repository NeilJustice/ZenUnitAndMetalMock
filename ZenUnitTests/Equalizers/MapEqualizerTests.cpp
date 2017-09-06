#include "pch.h"
#include "ZenUnit/Equalizers/MapEqualizer.h"

template<
   template<typename...>
   class MapType>
TEMPLATETESTS(MapEqualizerTests, MapType)
AFACT(ARE_EQUAL_EqualStdMaps_CompilesAndDoesNotThrow)
EVIDENCE

TEST(ARE_EQUAL_EqualStdMaps_CompilesAndDoesNotThrow)
{
   const MapType<int, int> expectedMap;
   const MapType<int, int> actualMap;
   ARE_EQUAL(expectedMap, actualMap);
}

};
RUNTEMPLATETESTS(MapEqualizerTests, map)
RUNTEMPLATETESTS(MapEqualizerTests, unordered_map)
