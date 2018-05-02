#include "pch.h"

namespace ZenUnit
{
   template<
      template<typename...>
   class MapType>
   TEMPLATE_TESTS(MapEqualizerTests, MapType)
   AFACT(ARE_EQUAL_EqualStdMaps_CompilesAndDoesNotThrow)
   EVIDENCE

   TEST(ARE_EQUAL_EqualStdMaps_CompilesAndDoesNotThrow)
   {
      const MapType<int, int> expectedMap;
      const MapType<int, int> actualMap;
      ARE_EQUAL(expectedMap, actualMap);
   }

   RUN_TEMPLATE_TESTS(MapEqualizerTests, map)
   THEN_RUN_TEMPLATE_TESTS(MapEqualizerTests, unordered_map)
}
