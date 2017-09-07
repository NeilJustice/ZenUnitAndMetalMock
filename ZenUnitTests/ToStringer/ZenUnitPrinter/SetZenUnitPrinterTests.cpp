#include "pch.h"
#include "ZenUnit/ToStringer/ZenUnitPrinter/SetZenUnitPrinter.h"
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

      ZenUnitPrinter<set<T>>::Print(oss, {});
      ARE_EQUAL("SetType<T>", oss.str());
      oss = ostringstream();

      ZenUnitPrinter<set<T, CustomLessComparator<T>>>::Print(oss, {});
      ARE_EQUAL("SetType<T>", oss.str());
      oss = ostringstream();

      ZenUnitPrinter<set<T, CustomLessComparator<T>, CustomAllocator<T>>>::Print(oss, {});
      ARE_EQUAL("SetType<T>", oss.str());
   }

   TEST(Print_UnorderedSet_PrintsPlaceholder)
   {
      ostringstream oss;

      ZenUnitPrinter<unordered_set<T>>::Print(oss, {});
      ARE_EQUAL("SetType<T>", oss.str());
      oss = ostringstream();

      ZenUnitPrinter<unordered_set<T, CustomHasher<T>>>::Print(oss, {});
      ARE_EQUAL("SetType<T>", oss.str());
      oss = ostringstream();

      ZenUnitPrinter<unordered_set<T, CustomHasher<T>, CustomEqualityComparator<T>>>::Print(oss, {});
      ARE_EQUAL("SetType<T>", oss.str());
      oss = ostringstream();

      ZenUnitPrinter<unordered_set<T, CustomHasher<T>, CustomEqualityComparator<T>, CustomAllocator<T>>>::Print(oss, {});
      ARE_EQUAL("SetType<T>", oss.str());
   }

   };
   RUNTEMPLATETESTS(SetZenUnitPrinterTests, int)
   RUNTEMPLATETESTS(SetZenUnitPrinterTests, string)
}
