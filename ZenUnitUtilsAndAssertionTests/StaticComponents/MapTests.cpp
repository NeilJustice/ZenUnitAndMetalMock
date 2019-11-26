#include "pch.h"

namespace ZenUnit
{
   template<
      template<typename...>
   class MapType, typename KeyType, typename ValueType>
   TEMPLATE_TESTS(MapTests, MapType, KeyType, ValueType)
   AFACT(InsertKeyAndValueWithoutOverwritingKey_KeyAlreadyInMap_Throws)
   AFACT(InsertKeyAndValueWithoutOverwritingKey_KeyNotAlreadyInMap_InsertsKeyAndValue_ReturnsCostPointerToInsertedValue);
   AFACT(At_KeyNotPresentInMap_Throws)
   AFACT(At_KeyPresentInMap_ReturnsConstReferenceToValue)
   AFACT(ContainsKeyWithValue_MapDoesNotContainKey_ReturnsFalseAndFalse)
   AFACT(ContainsKeyWithValue_MapContainsKeyWithMismatchingValue_ReturnsTrueAndFalse)
   AFACT(ContainsKeyWithValue_MapContainsKeyWithMatchingValue_ReturnsTrueAndTrue)
   EVIDENCE

   MapType<KeyType, ValueType> _map;

   TEST(InsertKeyAndValueWithoutOverwritingKey_KeyAlreadyInMap_Throws)
   {
      _map[KeyType()] = ValueType();
      string expectedToStringedKey = ToStringer::ToString(KeyType());
      string expectedWhat = "ZenUnit::Map::InsertKeyAndValueWithoutOverwritingKey: Key already present in map: " + expectedToStringedKey;
      THROWS_EXCEPTION(Map::InsertKeyAndValueWithoutOverwritingKey(_map, KeyType(), ValueType()), invalid_argument, expectedWhat);
   }

   TEST(InsertKeyAndValueWithoutOverwritingKey_KeyNotAlreadyInMap_InsertsKeyAndValue_ReturnsCostPointerToInsertedValue)
   {
      ValueType nonDefaultValueType(1);
      //
      const ValueType* constPointerToInsertedValue = Map::InsertKeyAndValueWithoutOverwritingKey(_map, KeyType(), nonDefaultValueType);
      //
      IS_TRUE(constPointerToInsertedValue != &nonDefaultValueType);
      ARE_EQUAL(nonDefaultValueType, *constPointerToInsertedValue);
      ARE_EQUAL(constPointerToInsertedValue, &_map[KeyType()]);
   }

   TEST(At_KeyNotPresentInMap_Throws)
   {
      string expectedToStringedKey = ToStringer::ToString(KeyType());
      string expectedWhat = "ZenUnit::Map::At(): Key not found in map: " + expectedToStringedKey;
      THROWS_EXCEPTION(Map::At(_map, KeyType()), out_of_range, expectedWhat);
   }

   TEST(At_KeyPresentInMap_ReturnsConstReferenceToValue)
   {
      ValueType nonDefaultValueInMap(1);
      _map[KeyType()] = nonDefaultValueInMap;
      //
      const ValueType& constReferenceToValueInMap = Map::At(_map, KeyType());
      //
      ARE_EQUAL(nonDefaultValueInMap, constReferenceToValueInMap);
   }

   TEST(ContainsKeyWithValue_MapDoesNotContainKey_ReturnsFalseAndFalse)
   {
      const pair<bool, bool> containsKeyValue = Map::ContainsKeyWithValue(_map, KeyType(), ValueType());
      //
      ARE_EQUAL(make_pair(false, false), containsKeyValue);
   };

   TEST(ContainsKeyWithValue_MapContainsKeyWithMismatchingValue_ReturnsTrueAndFalse)
   {
      _map[KeyType()] = ValueType(1);
      //
      const pair<bool, bool> containsKeyValue = Map::ContainsKeyWithValue(_map, KeyType(), ValueType());
      //
      ARE_EQUAL(make_pair(true, false), containsKeyValue);
   }

   TEST(ContainsKeyWithValue_MapContainsKeyWithMatchingValue_ReturnsTrueAndTrue)
   {
      _map[KeyType()] = ValueType();
      //
      const pair<bool, bool> containsKeyValue = Map::ContainsKeyWithValue(_map, KeyType(), ValueType());
      //
      ARE_EQUAL(make_pair(true, true), containsKeyValue);
   }

   RUN_TEMPLATE_TESTS(MapTests, map, int, int)
   THEN_RUN_TEMPLATE_TESTS(MapTests, map, UserType, int)
   THEN_RUN_TEMPLATE_TESTS(MapTests, map, int, UserType)
   THEN_RUN_TEMPLATE_TESTS(MapTests, map, UserType, UserType)
   THEN_RUN_TEMPLATE_TESTS(MapTests, unordered_map, int, int)
   THEN_RUN_TEMPLATE_TESTS(MapTests, unordered_map, UserType, int)
   THEN_RUN_TEMPLATE_TESTS(MapTests, unordered_map, int, UserType)
   THEN_RUN_TEMPLATE_TESTS(MapTests, unordered_map, UserType, UserType)
}
