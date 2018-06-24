#include "pch.h"
#include "ZenUnitTestUtils/UserTypeInsOpAndZenUnitPrintable.h"
#include "ZenUnitTestUtils/UserTypeNonPrintable.h"
#include "ZenUnitTestUtils/UserTypeOnlyZenUnitPrintable.h"

namespace Namespace
{
   struct StructInsideNamespace_ZenUnitPrintOutsideNamespace {};
}

namespace ZenUnit
{
   struct NonConstReferenceZenUnitPrint {};
   template<>
   struct Printer<NonConstReferenceZenUnitPrint>
   {
      static void Print(ostream&, NonConstReferenceZenUnitPrint&);
   };

   struct RValueReferenceZenUnitPrint {};
   template<>
   struct Printer<RValueReferenceZenUnitPrint>
   {
      static void Print(ostream&, RValueReferenceZenUnitPrint&&);
   };

   template<>
   struct Printer<Namespace::StructInsideNamespace_ZenUnitPrintOutsideNamespace>
   {
      static void Print(ostream&, const Namespace::StructInsideNamespace_ZenUnitPrintOutsideNamespace&);
   };

   TESTS(has_ZenUnitPrinterTests)
   AFACT(value_FalseIfZenUnitPrinterNotDefinedForType)
   AFACT(value_TrueIfZenUnitPrinterIsDefinedForType)
   EVIDENCE

   TEST(value_FalseIfZenUnitPrinterNotDefinedForType)
   {
      IS_FALSE(has_ZenUnitPrinter<int>::value);
      IS_FALSE(has_ZenUnitPrinter<string>::value);
      IS_FALSE(has_ZenUnitPrinter<UserTypeNonPrintable>::value);
      IS_FALSE(has_ZenUnitPrinter<NonConstReferenceZenUnitPrint>::value);
      IS_FALSE(has_ZenUnitPrinter<RValueReferenceZenUnitPrint>::value);
   }

   TEST(value_TrueIfZenUnitPrinterIsDefinedForType)
   {
      IS_TRUE(has_ZenUnitPrinter<vector<int>>::value);
      IS_TRUE(has_ZenUnitPrinter<vector<string>>::value);

      IS_TRUE(has_ZenUnitPrinter<map<int Comma int>>::value);
      IS_TRUE(has_ZenUnitPrinter<unordered_map<int Comma int>>::value);
      IS_TRUE(has_ZenUnitPrinter<map<char Comma string>>::value);
      IS_TRUE(has_ZenUnitPrinter<unordered_map<char Comma string>>::value);

      IS_TRUE(has_ZenUnitPrinter<set<int>>::value);
      IS_TRUE(has_ZenUnitPrinter<unordered_set<int>>::value);
      IS_TRUE(has_ZenUnitPrinter<set<string>>::value);
      IS_TRUE(has_ZenUnitPrinter<unordered_set<string>>::value);

      IS_TRUE(has_ZenUnitPrinter<UserType>::value);
      IS_TRUE(has_ZenUnitPrinter<UserTypeOnlyZenUnitPrintable>::value);
      IS_TRUE(has_ZenUnitPrinter<UserTypeInsOpAndZenUnitPrintable>::value);
      IS_TRUE(has_ZenUnitPrinter<Namespace::StructInsideNamespace_ZenUnitPrintOutsideNamespace>::value);
   }

   RUN_TESTS(has_ZenUnitPrinterTests)
}
