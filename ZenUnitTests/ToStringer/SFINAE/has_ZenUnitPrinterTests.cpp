#include "pch.h"
#include "Testing/UserTypeInsOpAndZenUnitPrintable.h"
#include "Testing/UserTypeOnlyZenUnitPrintable.h"
#include "ZenUnit/ToStringer/SFINAE/has_ZenUnitPrinter.h"

struct NonConstReferenceZenUnitPrint {};
template<>
struct ZenUnitPrinter<NonConstReferenceZenUnitPrint>
{
   static void Print(ostream&, NonConstReferenceZenUnitPrint&);
};

struct RValueReferenceZenUnitPrint {};
template<>
struct ZenUnitPrinter<RValueReferenceZenUnitPrint>
{
   static void Print(ostream&, RValueReferenceZenUnitPrint&&);
};

namespace Namespace
{
   struct StructInsideNamespace_ZenUnitPrintOutsideNamespace {};
}
template<>
struct ZenUnitPrinter<Namespace::StructInsideNamespace_ZenUnitPrintOutsideNamespace>
{
   static void Print(ostream&, const Namespace::StructInsideNamespace_ZenUnitPrintOutsideNamespace&);
};

namespace ZenUnit
{
   TESTS(has_ZenUnitPrinterTests)
   SPEC(value_FalseIfGlobalZenUnitPrinterNotDefinedForType)
   SPEC(value_TrueIfGlobalZenUnitPrinterIsDefinedForType)
   SPECEND

   TEST(value_FalseIfGlobalZenUnitPrinterNotDefinedForType)
   {
      IS_FALSE(has_ZenUnitPrinter<int>::value);
      IS_FALSE(has_ZenUnitPrinter<string>::value);
      IS_FALSE(has_ZenUnitPrinter<UserTypeNonPrintable>::value);
      IS_FALSE(has_ZenUnitPrinter<NonConstReferenceZenUnitPrint>::value);
      IS_FALSE(has_ZenUnitPrinter<RValueReferenceZenUnitPrint>::value);
   }

   TEST(value_TrueIfGlobalZenUnitPrinterIsDefinedForType)
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

   }; RUN(has_ZenUnitPrinterTests)
}
