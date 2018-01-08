#include "pch.h"
#include "ZenUnitTests/Testing/CustomPolicyClasses.h"

namespace ZenUnit
{
   template<typename T>
   TEMPLATETESTS(SetZenUnitPrinterTests, T)
   AFACT(Print_Set_PrintsPlaceholder)
   AFACT(Print_UnorderedSet_PrintsPlaceholder)
   EVIDENCE

   TEST(Print_Set_PrintsPlaceholder)
   {
      ostringstream oss;

      ZenUnit::Printer<set<T>>::Print(oss, {});
      ARE_EQUAL("SetType<T>", oss.str());
      oss = ostringstream();

      ZenUnit::Printer<set<T, CustomLessComparator<T>>>::Print(oss, {});
      ARE_EQUAL("SetType<T>", oss.str());
      oss = ostringstream();

      ZenUnit::Printer<set<T, CustomLessComparator<T>, CustomAllocator<T>>>::Print(oss, {});
      ARE_EQUAL("SetType<T>", oss.str());
   }

   TEST(Print_UnorderedSet_PrintsPlaceholder)
   {
      ostringstream oss;

      ZenUnit::Printer<unordered_set<T>>::Print(oss, {});
      ARE_EQUAL("SetType<T>", oss.str());
      oss = ostringstream();

      ZenUnit::Printer<unordered_set<T, CustomHasher<T>>>::Print(oss, {});
      ARE_EQUAL("SetType<T>", oss.str());
      oss = ostringstream();

      ZenUnit::Printer<unordered_set<T, CustomHasher<T>, CustomEqualityComparator<T>>>::Print(oss, {});
      ARE_EQUAL("SetType<T>", oss.str());
      oss = ostringstream();

      ZenUnit::Printer<unordered_set<T, CustomHasher<T>, CustomEqualityComparator<T>, CustomAllocator<T>>>::Print(oss, {});
      ARE_EQUAL("SetType<T>", oss.str());
   }

   };
   RUNTEMPLATETESTS(SetZenUnitPrinterTests, int)
   RUNTEMPLATETESTS(SetZenUnitPrinterTests, string)
}
