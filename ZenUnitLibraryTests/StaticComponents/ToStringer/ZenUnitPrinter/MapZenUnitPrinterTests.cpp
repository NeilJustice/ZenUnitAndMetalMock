#include "pch.h"
#include "ZenUnitTestUtils/CustomPolicyClasses.h"

namespace ZenUnit
{
   template<typename TKey, typename TValue>
   TEMPLATE_TESTS(MapZenUnitPrinterTests, TKey, TValue)
   AFACT(Print_EmptyOrderedMap_WritesExpectedString)
   AFACT(Print_NonEmptyOrderedMap_WritesExpectedString)
   AFACT(Print_EmptyUnorderedMap_WritesExpectedString)
   AFACT(Print_NonEmptyUnorderedMap_WritesExpectedString)
   EVIDENCE

   string _expectedOrderedMapTypeName;
   string _expectedUnorderedMapTypeName;

   STARTUP
   {
      map<TKey, TValue> orderedMap;
#if defined __linux__
      _expectedOrderedMapTypeName = *Type::GetName<decltype(orderedMap)>();
#elif defined _WIN32
      _expectedOrderedMapTypeName = *Type::GetName<decltype(orderedMap)>();
#endif

      unordered_map<TKey, TValue> unorderedMap;
#if defined __linux__
      _expectedUnorderedMapTypeName = *Type::GetName<decltype(unorderedMap)>();
#elif defined _WIN32
      _expectedUnorderedMapTypeName = *Type::GetName<decltype(unorderedMap)>();
#endif
   }

   TEST(Print_EmptyOrderedMap_WritesExpectedString)
   {
      ostringstream oss;
      map<TKey, TValue> emptyOrderedMap;
      //
      ZenUnit::Printer<map<TKey, TValue>>::Print(oss, emptyOrderedMap);
      //
      const string orderedMapAsString = oss.str();
      const string expectedOrderedMapAsString = _expectedOrderedMapTypeName + R"( (size 0):
{
})";
      ARE_EQUAL(expectedOrderedMapAsString, orderedMapAsString);
   }

   TEST(Print_NonEmptyOrderedMap_WritesExpectedString)
   {
      ostringstream oss;
      map<TKey, TValue> nonEmptyOrderedMap =
      {
         { TKey{1}, TValue{1} },
         { TKey{2}, TValue{2} }
      };
      //
      ZenUnit::Printer<map<TKey, TValue>>::Print(oss, nonEmptyOrderedMap);
      //
      const string orderedMapAsString = oss.str();
      const string expectedOrderedMapAsString = _expectedOrderedMapTypeName + R"( (size 2):
{
   (1, 1),
   (2, 2)
})";
      ARE_EQUAL(expectedOrderedMapAsString, orderedMapAsString);
   }

   TEST(Print_EmptyUnorderedMap_WritesExpectedString)
   {
      ostringstream oss;
      unordered_map<TKey, TValue> emptyUnorderedMap;
      //
      ZenUnit::Printer<unordered_map<TKey, TValue>>::Print(oss, emptyUnorderedMap);
      //
      const string unorderedMapAsString = oss.str();
      const string expectedUnorderedMapAsString = _expectedUnorderedMapTypeName + R"( (size 0):
{
})";
      ARE_EQUAL(expectedUnorderedMapAsString, unorderedMapAsString);
   }

   TEST(Print_NonEmptyUnorderedMap_WritesExpectedString)
   {
      ostringstream oss;
      unordered_map<TKey, TValue> nonEmptyUnorderedMap =
      {
         { TKey{1}, TValue{1} },
         { TKey{2}, TValue{2} }
      };
      //
      ZenUnit::Printer<unordered_map<TKey, TValue>>::Print(oss, nonEmptyUnorderedMap);
      //
      const string unorderedMapAsString = oss.str();
      const string expectedUnorderedMapAsString = _expectedUnorderedMapTypeName + R"( (size 2):
{
   (1, 1),
   (2, 2)
})";
      ARE_EQUAL(expectedUnorderedMapAsString, unorderedMapAsString);
   }

   RUN_TEMPLATE_TESTS(MapZenUnitPrinterTests, int, int)
   THEN_RUN_TEMPLATE_TESTS(MapZenUnitPrinterTests, unsigned long long, unsigned)
}
