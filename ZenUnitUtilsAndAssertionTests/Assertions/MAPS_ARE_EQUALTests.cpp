#include "pch.h"

namespace ZenUnit
{
   template<
      template<typename...>
      class MapType>
   TEMPLATE_TESTS(MAPS_ARE_EQUALTests, MapType)
   AFACT(BothMapsAreEmpty_DoesNotThrowExceptionException)
   AFACT(ExpectedAndActualMapSizesAreDifferent_ThrowsAnomaly)
   AFACT(SizesDifferent_Throws_MessagesTestCase)
   AFACT(MapSizesAreEqual_KeysAreNotEqual_ThrowsAnomaly)
   AFACT(SizesEqual_KeysNotEqual_Throws_MessagesTestCase)
   AFACT(SizesEqual_KeysEqual_ValuesNotEqual_Throws)
   AFACT(SizesEqual_KeysEqual_ValuesNotEqual_Throws_MessagesTestCase)
   AFACT(SizesEqual_UserTypeKeysNotEqual_Throws)
   AFACT(SizesEqual_UserTypeKeysEqual_ValuesNotEqual_Throws)
   EVIDENCE

   TEST(BothMapsAreEmpty_DoesNotThrowExceptionException)
   {
      MAPS_ARE_EQUAL((MapType<int, int>()), (MapType<int, int>()));

      MapType<int, int> expectedMap;
      MapType<int, int> actualMap;
      MAPS_ARE_EQUAL(expectedMap, actualMap);

      expectedMap.insert({ 1, 1 });
      expectedMap.insert({ 2, 2 });
      actualMap.insert({ 1, 1 });
      actualMap.insert({ 2, 2 });
      MAPS_ARE_EQUAL(expectedMap, actualMap);
   }

   TEST(ExpectedAndActualMapSizesAreDifferent_ThrowsAnomaly)
   {
      MapType<int, int> expectedMap;
      expectedMap[ZenUnit::Random<int>()] = ZenUnit::Random<int>();

      MapType<int, int> actualMap;

      THROWS_EXCEPTION(MAPS_ARE_EQUAL(expectedMap, actualMap),
         ZenUnit::Anomaly, TestUtil::NewlineConcat("",
"  Failed: MAPS_ARE_EQUAL(expectedMap, actualMap)",
" Because: ARE_EQUAL(expectedMap.size(), actualMap.size()) failed",
"Expected: 1",
"  Actual: 0",
"File.cpp(1)"));
   }

   TEST(SizesDifferent_Throws_MessagesTestCase)
   {
      MapType<int, int> expectedMap;
      expectedMap[ZenUnit::Random<int>()] = ZenUnit::Random<int>();

      MapType<int, int> actualMap;

      const string messageA = ZenUnit::Random<string>();
      const string messageB = ZenUnit::Random<string>();

      THROWS_EXCEPTION(MAPS_ARE_EQUAL(expectedMap, actualMap, messageA, messageB), ZenUnit::Anomaly, TestUtil::NewlineConcat("",
"  Failed: MAPS_ARE_EQUAL(expectedMap, actualMap, messageA, messageB)",
" Because: ARE_EQUAL(expectedMap.size(), actualMap.size()) failed",
"Expected: 1",
"  Actual: 0",
" Message: \"" + messageA + "\", \"" + messageB + "\"",
"File.cpp(1)"));
   }

   TEST(MapSizesAreEqual_KeysAreNotEqual_ThrowsAnomaly)
   {
      const int key = ZenUnit::RandomBetween<int>(-10, 10);
      const int valueThatDoesNotEqualKey = key + ZenUnit::RandomBetween<int>(1, 3);

      MapType<int, int> expectedMap;
      expectedMap.insert({ key, ZenUnit::Random<int>() });

      MapType<int, int> actualMap;
      actualMap.insert({ valueThatDoesNotEqualKey, ZenUnit::Random<int>() });

      THROWS_EXCEPTION(MAPS_ARE_EQUAL(expectedMap, actualMap),
         ZenUnit::Anomaly, TestUtil::NewlineConcat("",
" Failed: MAPS_ARE_EQUAL(expectedMap, actualMap)",
"Because: Actual map does not contain expected key",
"Expected key: " + to_string(key),
"File.cpp(1)"));
   }

   TEST(SizesEqual_KeysNotEqual_Throws_MessagesTestCase)
   {
      MapType<int, int> expectedMap;
      expectedMap.insert({ 10, 0 });

      MapType<int, int> actualMap;
      actualMap.insert({ 20, 0 });

      const string messageA = ZenUnit::Random<string>();
      const string messageB = ZenUnit::Random<string>();

      THROWS_EXCEPTION(MAPS_ARE_EQUAL(expectedMap, actualMap, messageA, messageB), ZenUnit::Anomaly, TestUtil::NewlineConcat("",
" Failed: MAPS_ARE_EQUAL(expectedMap, actualMap, messageA, messageB)",
"Because: Actual map does not contain expected key",
"Expected key: 10",
"Message: \"" + messageA + "\", \"" + messageB + "\"",
"File.cpp(1)"));
   }

   TEST(SizesEqual_KeysEqual_ValuesNotEqual_Throws)
   {
      MapType<string, string> expectedMap;
      expectedMap.insert({ "key", "value" });

      MapType<string, string> actualMap;
      actualMap.insert({ "key", "not_value" });

      THROWS_EXCEPTION(MAPS_ARE_EQUAL(expectedMap, actualMap), ZenUnit::Anomaly, TestUtil::NewlineConcat("",
" Failed: MAPS_ARE_EQUAL(expectedMap, actualMap)",
"Because: Actual map contains expected key but with an unexpected value",
"  Expected key: \"key\"",
"    Actual key: \"key\"",
"Expected value: \"value\"",
"  Actual value: \"not_value\"",
"File.cpp(1)"));
   }

   TEST(SizesEqual_KeysEqual_ValuesNotEqual_Throws_MessagesTestCase)
   {
      MapType<string, string> expectedMap;
      expectedMap.insert({ "key", "value" });

      MapType<string, string> actualMap;
      actualMap.insert({ "key", "not_value" });

      const string messageA = ZenUnit::Random<string>();
      const string messageB = ZenUnit::Random<string>();

      THROWS_EXCEPTION(MAPS_ARE_EQUAL(expectedMap, actualMap, messageA, messageB), ZenUnit::Anomaly, TestUtil::NewlineConcat("",
" Failed: MAPS_ARE_EQUAL(expectedMap, actualMap, messageA, messageB)",
"Because: Actual map contains expected key but with an unexpected value",
"  Expected key: \"key\"",
"    Actual key: \"key\"",
"Expected value: \"value\"",
"  Actual value: \"not_value\"",
"Message: \"" + messageA + "\", \"" + messageB + "\"",
"File.cpp(1)"));
   }

   TEST(SizesEqual_UserTypeKeysNotEqual_Throws)
   {
      MapType<UserType, int> expectedMap;
      expectedMap.insert({ 10, 0 });

      MapType<UserType, int> actualMap;
      actualMap.insert({ 20, 0 });

      THROWS_EXCEPTION(MAPS_ARE_EQUAL(expectedMap, actualMap), ZenUnit::Anomaly, TestUtil::NewlineConcat("",
" Failed: MAPS_ARE_EQUAL(expectedMap, actualMap)",
"Because: Actual map does not contain expected key",
"Expected key: UserType@10",
"File.cpp(1)"));
   }

   TEST(SizesEqual_UserTypeKeysEqual_ValuesNotEqual_Throws)
   {
      MapType<string, UserType> expectedMap;
      expectedMap.insert({ "key", 10 });

      MapType<string, UserType> actualMap;
      actualMap.insert({ "key", 20 });

      THROWS_EXCEPTION(MAPS_ARE_EQUAL(expectedMap, actualMap), ZenUnit::Anomaly, TestUtil::NewlineConcat("",
" Failed: MAPS_ARE_EQUAL(expectedMap, actualMap)",
"Because: Actual map contains expected key but with an unexpected value",
"  Expected key: \"key\"",
"    Actual key: \"key\"",
"Expected value: UserType@10",
"  Actual value: UserType@20",
"File.cpp(1)"));
   }

   RUN_TEMPLATE_TESTS(MAPS_ARE_EQUALTests, map)
   THEN_RUN_TEMPLATE_TESTS(MAPS_ARE_EQUALTests, unordered_map)
}
