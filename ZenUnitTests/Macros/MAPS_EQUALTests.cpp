#include "pch.h"

namespace ZenUnit
{
   template<
      template<typename...>
      class MapType>
   TEMPLATETESTS(MAPS_EQUALTests, MapType)
   AFACT(BothEmpty_DoesNotThrow)
   AFACT(SizesDifferent_Throws)
   AFACT(SizesDifferent_Throws_MessagesTestCase)
   AFACT(SizesEqual_KeysNotEqual_Throws)
   AFACT(SizesEqual_KeysNotEqual_Throws_MessagesTestCase)
   AFACT(SizesEqual_KeysEqual_ValuesNotEqual_Throws)
   AFACT(SizesEqual_KeysEqual_ValuesNotEqual_Throws_MessagesTestCase)
   AFACT(SizesEqual_UserTypeKeysNotEqual_Throws)
   AFACT(SizesEqual_UserTypeKeysEqual_ValuesNotEqual_Throws)
   EVIDENCE

   const string MessageA = "A", MessageB = "B";

   TEST(BothEmpty_DoesNotThrow)
   {
      MAPS_EQUAL((MapType<int, int>()), (MapType<int, int>()));
      MapType<int, int> expectedMap;
      MapType<int, int> actualMap;
      MAPS_EQUAL(expectedMap, actualMap);
      expectedMap.insert({ 1, 1 });
      expectedMap.insert({ 2, 2 });
      actualMap.insert({ 1, 1 });
      actualMap.insert({ 2, 2 });
      MAPS_EQUAL(expectedMap, actualMap);
   }

   TEST(SizesDifferent_Throws)
   {
      MapType<int, int> expectedMap;
      expectedMap.insert({ 0, 0 });
      MapType<int, int> actualMap;
      THROWS(MAPS_EQUAL(expectedMap, actualMap), ZenUnit::Anomaly, R"(
  Failed: MAPS_EQUAL(expectedMap, actualMap)
 Because: ARE_EQUAL(expectedMap.size(), actualMap.size()) failed
Expected: 1
  Actual: 0
File.cpp(1))");
   }

   TEST(SizesDifferent_Throws_MessagesTestCase)
   {
      MapType<int, int> expectedMap;
      expectedMap.insert({ 0, 0 });
      MapType<int, int> actualMap;
      THROWS(MAPS_EQUAL(expectedMap, actualMap, MessageA, MessageB), ZenUnit::Anomaly, R"(
  Failed: MAPS_EQUAL(expectedMap, actualMap, MessageA, MessageB)
 Because: ARE_EQUAL(expectedMap.size(), actualMap.size()) failed
Expected: 1
  Actual: 0
 Message: "A", "B"
File.cpp(1))");
   }

   TEST(SizesEqual_KeysNotEqual_Throws)
   {
      MapType<int, int> expectedMap;
      expectedMap.insert({ 10, 0 });
      MapType<int, int> actualMap;
      actualMap.insert({ 20, 0 });
      THROWS(MAPS_EQUAL(expectedMap, actualMap), ZenUnit::Anomaly, R"(
 Failed: MAPS_EQUAL(expectedMap, actualMap)
Because: Actual map does not contain expected key
Expected key: 10
File.cpp(1))");
   }

   TEST(SizesEqual_KeysNotEqual_Throws_MessagesTestCase)
   {
      MapType<int, int> expectedMap;
      expectedMap.insert({ 10, 0 });
      MapType<int, int> actualMap;
      actualMap.insert({ 20, 0 });
      THROWS(MAPS_EQUAL(expectedMap, actualMap, MessageA, MessageB), ZenUnit::Anomaly, R"(
 Failed: MAPS_EQUAL(expectedMap, actualMap, MessageA, MessageB)
Because: Actual map does not contain expected key
Expected key: 10
Message: "A", "B"
File.cpp(1))");
   }

   TEST(SizesEqual_KeysEqual_ValuesNotEqual_Throws)
   {
      MapType<string, string> expectedMap;
      expectedMap.insert({ "key", "value" });
      MapType<string, string> actualMap;
      actualMap.insert({ "key", "not_value" });
      THROWS(MAPS_EQUAL(expectedMap, actualMap), ZenUnit::Anomaly, R"(
 Failed: MAPS_EQUAL(expectedMap, actualMap)
Because: Actual map contains expected key but with an unexpected value
  Expected key: "key"
    Actual key: "key"
Expected value: "value"
  Actual value: "not_value"
File.cpp(1))");
   }

   TEST(SizesEqual_KeysEqual_ValuesNotEqual_Throws_MessagesTestCase)
   {
      MapType<string, string> expectedMap;
      expectedMap.insert({ "key", "value" });
      MapType<string, string> actualMap;
      actualMap.insert({ "key", "not_value" });
      THROWS(MAPS_EQUAL(expectedMap, actualMap, MessageA, MessageB), ZenUnit::Anomaly, R"(
 Failed: MAPS_EQUAL(expectedMap, actualMap, MessageA, MessageB)
Because: Actual map contains expected key but with an unexpected value
  Expected key: "key"
    Actual key: "key"
Expected value: "value"
  Actual value: "not_value"
Message: "A", "B"
File.cpp(1))");
   }

   TEST(SizesEqual_UserTypeKeysNotEqual_Throws)
   {
      MapType<UserType, int> expectedMap;
      expectedMap.insert({ 10, 0 });
      MapType<UserType, int> actualMap;
      actualMap.insert({ 20, 0 });
      THROWS(MAPS_EQUAL(expectedMap, actualMap), ZenUnit::Anomaly, R"(
 Failed: MAPS_EQUAL(expectedMap, actualMap)
Because: Actual map does not contain expected key
Expected key: UserType@10
File.cpp(1))");
   }

   TEST(SizesEqual_UserTypeKeysEqual_ValuesNotEqual_Throws)
   {
      MapType<string, UserType> expectedMap;
      expectedMap.insert({ "key", 10 });
      MapType<string, UserType> actualMap;
      actualMap.insert({ "key", 20 });
      THROWS(MAPS_EQUAL(expectedMap, actualMap), ZenUnit::Anomaly, R"(
 Failed: MAPS_EQUAL(expectedMap, actualMap)
Because: Actual map contains expected key but with an unexpected value
  Expected key: "key"
    Actual key: "key"
Expected value: UserType@10
  Actual value: UserType@20
File.cpp(1))");
   }

   };
   RUNTEMPLATETESTS(MAPS_EQUALTests, map)
   RUNTEMPLATETESTS(MAPS_EQUALTests, unordered_map)
}
