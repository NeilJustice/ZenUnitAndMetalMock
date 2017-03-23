#include "pch.h"
#include "ZenUnit/ToStringer/ZenUnitPrinter/MapZenUnitPrinter.h"
#include "Testing/CustomPolicyClasses.h"

namespace ZenUnit
{
   template<typename TKey, typename TValue>
   TEMPLATETESTS(MapZenUnitPrinterTests, TKey, TValue)
   SPEC(Print_Map_PrintsPlaceholder)
   SPEC(Print_UnorderedMap_PrintsPlaceholder)
   SPECEND

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
   TEMPLATERUN(MapZenUnitPrinterTests, int, int)
   TEMPLATERUN(MapZenUnitPrinterTests, char, unsigned)
}
