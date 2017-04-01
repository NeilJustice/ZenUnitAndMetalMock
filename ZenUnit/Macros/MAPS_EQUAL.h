#pragma once
#include "ZenUnit/Anomaly/Anomaly.h"
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/Utils/AssertTrue.h"
#include "ZenUnit/Utils/Map.h"

#define MAPS_EQUAL(expectedMap, actualMap, ...) \
   ZenUnit::MAPS_EQUAL_Defined(VRT(expectedMap), VRT(actualMap), \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename... MessageTypes>
   NOINLINE void MAPS_EQUAL_Throw(
      const char* failedPrefixSpaces,
      const char* expectedMapText,
      const char* actualMapText,
      const std::string& whyBody,
      FileLine fileLine,
      const char* messagePrefixSpaces,
      const char* messagesText,
      const MessageTypes&... messages)
   {
      const std::string failedLinePrefix = String::Concat(
         failedPrefixSpaces, "Failed: MAPS_EQUAL(", expectedMapText, ", ", actualMapText);
      throw Anomaly(failedLinePrefix, whyBody, fileLine, messagePrefixSpaces, messagesText, messages...);
   }

   NOINLINE std::string MAPS_EQUAL_MakeWhyBody_SizesNotEqual(size_t expectedMapSize, size_t actualMapSize);

   template<typename KeyType>
   NOINLINE std::string MAPS_EQUAL_MakeWhyBody_ExpectedKeyNotInActualMap(const KeyType& expectedKey)
   {
      const std::string toStringedExpectedKey = ToStringer::ToString<KeyType>(expectedKey);
      const std::string whyBody = String::Concat(
         "Because: Actual map does not contain expected key\n",
         "Expected key: ", toStringedExpectedKey);
      return whyBody;
   }

   template<typename KeyType, typename ValueType, typename MapType>
   NOINLINE std::string MAPS_EQUAL_MakeWhyBody_KeysEqualValuesNotEqual(
      const KeyType& expectedKey, const ValueType& expectedValue, const MapType& actualMap)
   {
      const std::string toStringedExpectedKey = ToStringer::ToString<KeyType>(expectedKey);
      const std::string& toStringedActualKey = toStringedExpectedKey;
      const std::string toStringedExpectedValue =
         ToStringer::ToString<typename std::decay<decltype(expectedValue)>::type>(expectedValue);
      const auto& actualValue = Map::At(actualMap, expectedKey);
      const std::string toStringedActualValue =
         ToStringer::ToString<typename std::decay<decltype(actualValue)>::type>(actualValue);
      const std::string whyBody = String::Concat(
         "Because: Actual map contains expected key but with an unexpected value\n",
         "  Expected key: ", toStringedExpectedKey, '\n',
         "    Actual key: ", toStringedActualKey, '\n',
         "Expected value: ", toStringedExpectedValue, '\n',
         "  Actual value: ", toStringedActualValue);
      return whyBody;
   }

   template<typename MapType, typename... MessageTypes>
   void MAPS_EQUAL_Defined(
      VRText<MapType> expectedMapVRT,
      VRText<MapType> actualMapVRT,
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      const char* const expectedMapText = expectedMapVRT.text;
      const char* const actualMapText = actualMapVRT.text;
      const MapType& expectedMap = expectedMapVRT.value;
      const MapType& actualMap = actualMapVRT.value;
      try
      {
         ARE_EQUAL(expectedMap.size(), actualMap.size());
      }
      catch (const Anomaly&)
      {
         MAPS_EQUAL_Throw("  ", expectedMapText, actualMapText,
            MAPS_EQUAL_MakeWhyBody_SizesNotEqual(expectedMap.size(), actualMap.size()),
            fileLine, " ", messagesText, messages...);
      }
      for (const auto& expectedKeyValuePair : expectedMapVRT.value)
      {
         const auto& expectedKey = expectedKeyValuePair.first;
         const auto& expectedValue = expectedKeyValuePair.second;
         const std::pair<bool, bool> containsKeyValue =
            Map::ContainsKeyWithValue(actualMap, expectedKey, expectedValue);
         const bool mapContainsKey = containsKeyValue.first;
         if (!mapContainsKey)
         {
            MAPS_EQUAL_Throw(" ", expectedMapText, actualMapText,
               MAPS_EQUAL_MakeWhyBody_ExpectedKeyNotInActualMap(expectedKey),
               fileLine, "", messagesText, messages...);
         }
         const bool mapContainsValue = containsKeyValue.second;
         if (!mapContainsValue)
         {
            assert_true(containsKeyValue.first);
            MAPS_EQUAL_Throw(" ", expectedMapText, actualMapText,
               MAPS_EQUAL_MakeWhyBody_KeysEqualValuesNotEqual(expectedKey, expectedValue, actualMap),
               fileLine, "", messagesText, messages...);
         }
      }
   }
}
