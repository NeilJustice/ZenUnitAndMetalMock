#include "pch.h"
#include "Testing/CustomPolicyClasses.h"
#include "ZenUnit/ToStringer/ZenUnitPrinter/MapZenUnitPrinter.h"

namespace ZenUnit
{
   template<typename TKey, typename TValue>
   TEMPLATETESTS(MapZenUnitPrinterTests, TKey, TValue)
   FACT(Print_Map_PrintsPlaceholder)
   FACT(Print_UnorderedMap_PrintsPlaceholder)
   BEGINPROOF

   TEST(Print_Map_PrintsPlaceholder)
   {
      ostringstream oss;

      ZenUnitPrinter<map<TKey, TValue>>::Print(oss, {});
      ARE_EQUAL("std::map<TKey, TValue>", oss.str());
      oss = ostringstream();

      ZenUnitPrinter<map<TKey, TValue, CustomLessComparator<TKey>>>::Print(oss, {});
      ARE_EQUAL("std::map<TKey, TValue>", oss.str());
      oss = ostringstream();

      ZenUnitPrinter<map<TKey, TValue, CustomLessComparator<TKey>, CustomAllocator<TKey>>>::Print(oss, {});
      ARE_EQUAL("std::map<TKey, TValue>", oss.str());
   }

   TEST(Print_UnorderedMap_PrintsPlaceholder)
   {
      ostringstream oss;

      ZenUnitPrinter<unordered_map<TKey, TValue>>::Print(oss, {});
      ARE_EQUAL("std::unordered_map<TKey, TValue>", oss.str());
      oss = ostringstream();

      ZenUnitPrinter<unordered_map<TKey, TValue, CustomHasher<TKey>>>::Print(oss, {});
      ARE_EQUAL("std::unordered_map<TKey, TValue>", oss.str());
      oss = ostringstream();

      ZenUnitPrinter<unordered_map<TKey, TValue, CustomHasher<TKey>, CustomEqualityComparator<TKey>>>::Print(oss, {});
      ARE_EQUAL("std::unordered_map<TKey, TValue>", oss.str());
      oss = ostringstream();

      ZenUnitPrinter<unordered_map<TKey, TValue, CustomHasher<TKey>, CustomEqualityComparator<TKey>, CustomAllocator<pair<const TKey, TValue>>>>::Print(oss, {});
      ARE_EQUAL("std::unordered_map<TKey, TValue>", oss.str());
   }

   };
   RUNTEMPLATE(MapZenUnitPrinterTests, int, int)
   RUNTEMPLATE(MapZenUnitPrinterTests, char, unsigned)
}
