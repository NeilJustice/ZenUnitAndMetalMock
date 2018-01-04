#include "pch.h"
#include "ZenUnitTests/Testing/CustomPolicyClasses.h"

namespace ZenUnit
{
   template<typename TKey, typename TValue>
   TEMPLATETESTS(MapZenUnitPrinterTests, TKey, TValue)
   AFACT(Print_Map_PrintsPlaceholder)
   AFACT(Print_UnorderedMap_PrintsPlaceholder)
   EVIDENCE

   TEST(Print_Map_PrintsPlaceholder)
   {
      ostringstream oss;

      ZenUnit::Printer<map<TKey, TValue>>::Print(oss, {});
      ARE_EQUAL("std::map<TKey, TValue>", oss.str());
      oss = ostringstream();

      ZenUnit::Printer<map<TKey, TValue, CustomLessComparator<TKey>>>::Print(oss, {});
      ARE_EQUAL("std::map<TKey, TValue>", oss.str());
      oss = ostringstream();

      ZenUnit::Printer<map<TKey, TValue, CustomLessComparator<TKey>, CustomAllocator<pair<const TKey, TValue>>>>::Print(oss, {});
      ARE_EQUAL("std::map<TKey, TValue>", oss.str());
   }

   TEST(Print_UnorderedMap_PrintsPlaceholder)
   {
      ostringstream oss;

      ZenUnit::Printer<unordered_map<TKey, TValue>>::Print(oss, {});
      ARE_EQUAL("std::unordered_map<TKey, TValue>", oss.str());
      oss = ostringstream();

      ZenUnit::Printer<unordered_map<TKey, TValue, CustomHasher<TKey>>>::Print(oss, {});
      ARE_EQUAL("std::unordered_map<TKey, TValue>", oss.str());
      oss = ostringstream();

      ZenUnit::Printer<unordered_map<TKey, TValue, CustomHasher<TKey>, CustomEqualityComparator<TKey>>>::Print(oss, {});
      ARE_EQUAL("std::unordered_map<TKey, TValue>", oss.str());
      oss = ostringstream();

      ZenUnit::Printer<unordered_map<TKey, TValue, CustomHasher<TKey>, CustomEqualityComparator<TKey>, CustomAllocator<pair<const TKey, TValue>>>>::Print(oss, {});
      ARE_EQUAL("std::unordered_map<TKey, TValue>", oss.str());
   }

   };
   RUNTEMPLATETESTS(MapZenUnitPrinterTests, int, int)
   RUNTEMPLATETESTS(MapZenUnitPrinterTests, char, unsigned)
}
