#include "pch.h"

namespace ZenUnit
{
   TESTS(VectorTests)
   AFACT(ToArgcArgv_ReturnsArgsVector)
   AFACT(Join_EmptyIntVector_ReturnsEmptyStringRegardlessOfSeparator)
   AFACT(Join_1ElementIntVector_ReturnsFirstElementRegardlessOfSeparator)
   FACTS(Join_2ElementIntVector_ReturnsElementsJoinedBySeparator)
   EVIDENCE

   TEST(ToArgcArgv_ReturnsArgsVector)
   {
      const char* argvA[1] =
      {
         "ExePath"
      };
      ToArgcArgvTestCase(1, argvA, vector<string>{ "ExePath" });

      const char* argvB[2] =
      {
         "ExePath",
         "Argument1"
      };
      ToArgcArgvTestCase(2, argvB, vector<string>{ "ExePath", "Argument1" });

      const char* argvC[3] =
      {
         "ExePath",
         "Argument1",
         "Argument2"
      };
      ToArgcArgvTestCase(3, argvC, vector<string>{ "ExePath", "Argument1", "Argument2" });
   }
   static void ToArgcArgvTestCase(
      int argc, const char* argv[], const vector<string>& expectedStringVector)
   {
      VECTORS_EQUAL(expectedStringVector, Vector::FromArgcArgv(argc, const_cast<char**>(argv)));
   }

   TEST(Join_EmptyIntVector_ReturnsEmptyStringRegardlessOfSeparator)
   {
      const vector<int> emptyIntVector;
      ARE_EQUAL("", Vector::Join(emptyIntVector, ' '));
      ARE_EQUAL("", Vector::Join(emptyIntVector, ','));
   }

   TEST(Join_1ElementIntVector_ReturnsFirstElementRegardlessOfSeparator)
   {
      const vector<int> intVec{ 1 };
      ARE_EQUAL("1", Vector::Join(intVec, ' '));
      ARE_EQUAL("1", Vector::Join(intVec, ','));
   }

   TEST3X3(Join_2ElementIntVector_ReturnsElementsJoinedBySeparator,
      const string& expectedJoinedVector, const vector<int>& vec, char separator,
      "1 2", vector<int>{ 1, 2 }, ' ',
      "1,2", vector<int>{ 1, 2 }, ',',
      "1 2 3", vector<int>{ 1, 2, 3 }, ' ',
      "1,2,3", vector<int>{ 1, 2, 3 }, ',')
   {
      const string joinedVector = Vector::Join(vec, separator);
      ARE_EQUAL(expectedJoinedVector, joinedVector);
   }

   RUN_TESTS(VectorTests)
}


template<
   template<typename...>
class SetType, typename T>
TEMPLATE_TESTS(SetTests, SetType, T)
AFACT(Contains_ReturnsTrueIfSetContainsElement)
EVIDENCE

TEST(Contains_ReturnsTrueIfSetContainsElement)
{
   SetType<T> s;
   const T element10 = 10;
   const T element20 = 20;

   IS_FALSE(Set::Contains(s, element10));
   IS_FALSE(Set::Contains(s, element20));

   s.insert(element10);
   IS_TRUE(Set::Contains(s, element10));
   IS_FALSE(Set::Contains(s, element20));

   s.insert(element20);
   IS_TRUE(Set::Contains(s, element10));
   IS_TRUE(Set::Contains(s, element20));
}

RUN_TEMPLATE_TESTS(SetTests, set, int)
THEN_RUN_TEMPLATE_TESTS(SetTests, set, unsigned long long)
THEN_RUN_TEMPLATE_TESTS(SetTests, unordered_set, int)
THEN_RUN_TEMPLATE_TESTS(SetTests, unordered_set, unsigned long long)


#include "ZenUnitTests/Testing/UserType.h"

template<
   template<typename...>
class MapType, typename KeyType, typename ValueType>
TEMPLATE_TESTS(MapTests, MapType, KeyType, ValueType)
AFACT(InsertNoOverwrite_KeyAlreadyInMap_Throws)
AFACT(InsertNoOverwrite_KeyNotAlreadyInMap_InsertsKeyAndValue_ReturnsCostPointerToInsertedValue);
AFACT(At_KeyNotPresentInMap_Throws)
AFACT(At_KeyPresentInMap_ReturnsConstReferenceToValue)
AFACT(ContainsKeyWithValue_MapDoesNotContainKey_ReturnsFalseAndFalse)
AFACT(ContainsKeyWithValue_MapContainsKeyWithMismatchingValue_ReturnsTrueAndFalse)
AFACT(ContainsKeyWithValue_MapContainsKeyWithMatchingValue_ReturnsTrueAndTrue)
EVIDENCE

MapType<KeyType, ValueType> _map;

TEST(InsertNoOverwrite_KeyAlreadyInMap_Throws)
{
   _map[KeyType()] = ValueType();
   string expectedToStringedKey = ToStringer::ToString(KeyType());
   string expectedWhat = "ZenUnit::Map::InsertNoOverwrite: Key already present in map: " + expectedToStringedKey;
   THROWS(Map::InsertNoOverwrite(_map, KeyType(), ValueType()), invalid_argument, expectedWhat);
}

TEST(InsertNoOverwrite_KeyNotAlreadyInMap_InsertsKeyAndValue_ReturnsCostPointerToInsertedValue)
{
   ValueType nonDefaultValueType(1);
   //
   const ValueType* constPointerToInsertedValue = Map::InsertNoOverwrite(_map, KeyType(), nonDefaultValueType);
   //
   IS_TRUE(constPointerToInsertedValue != &nonDefaultValueType);
   ARE_EQUAL(nonDefaultValueType, *constPointerToInsertedValue);
   ARE_EQUAL(constPointerToInsertedValue, &_map[KeyType()]);
}

TEST(At_KeyNotPresentInMap_Throws)
{
   string expectedToStringedKey = ToStringer::ToString(KeyType());
   string expectedWhat = "ZenUnit::Map::At: Key not found in map: " + expectedToStringedKey;
   THROWS(Map::At(_map, KeyType()), out_of_range, expectedWhat);
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
   pair<bool, bool> containsKeyValue = Map::ContainsKeyWithValue(_map, KeyType(), ValueType());
   //
   ARE_EQUAL(make_pair(false, false), containsKeyValue);
};

TEST(ContainsKeyWithValue_MapContainsKeyWithMismatchingValue_ReturnsTrueAndFalse)
{
   _map[KeyType()] = ValueType(1);
   //
   pair<bool, bool> containsKeyValue = Map::ContainsKeyWithValue(_map, KeyType(), ValueType());
   //
   ARE_EQUAL(make_pair(true, false), containsKeyValue);
}

TEST(ContainsKeyWithValue_MapContainsKeyWithMatchingValue_ReturnsTrueAndTrue)
{
   _map[KeyType()] = ValueType();
   //
   pair<bool, bool> containsKeyValue = Map::ContainsKeyWithValue(_map, KeyType(), ValueType());
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
