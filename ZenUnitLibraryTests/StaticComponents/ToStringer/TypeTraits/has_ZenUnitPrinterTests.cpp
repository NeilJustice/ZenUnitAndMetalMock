#include "pch.h"

namespace Namespace
{
   struct StructInsideNamespace_ZenUnitPrintOutsideNamespace {};
}

namespace ZenUnit
{
   struct NonConstReferenceZenUnitPrint {};
   template<>
   class Printer<NonConstReferenceZenUnitPrint>
   {
   public:
      static void Print(ostream&, NonConstReferenceZenUnitPrint&);
   };

   struct RValueReferenceZenUnitPrint {};
   template<>
   class Printer<RValueReferenceZenUnitPrint>
   {
   public:
      static void Print(ostream&, RValueReferenceZenUnitPrint&&);
   };

   template<>
   class Printer<Namespace::StructInsideNamespace_ZenUnitPrintOutsideNamespace>
   {
   public:
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
      IS_FALSE(has_ZenUnitPrinter<NonPrintableUserType>::value);
      IS_FALSE(has_ZenUnitPrinter<NonConstReferenceZenUnitPrint>::value);
      IS_FALSE(has_ZenUnitPrinter<RValueReferenceZenUnitPrint>::value);
   }

   TEST(value_TrueIfZenUnitPrinterIsDefinedForType)
   {
      IS_TRUE(has_ZenUnitPrinter<vector<int>>::value);
      IS_TRUE(has_ZenUnitPrinter<vector<string>>::value);

      using MapIntInt = map<int, int>;
      IS_TRUE(has_ZenUnitPrinter<MapIntInt>::value);

      using UnorderedMapIntInt = unordered_map<int, int>;
      IS_TRUE(has_ZenUnitPrinter<UnorderedMapIntInt>::value);

      using MapCharString = map<char, string>;
      IS_TRUE(has_ZenUnitPrinter<MapCharString>::value);

      using UnorderedMapCharString = unordered_map<char, string>;
      IS_TRUE(has_ZenUnitPrinter<UnorderedMapCharString>::value);

      IS_TRUE(has_ZenUnitPrinter<set<int>>::value);
      IS_TRUE(has_ZenUnitPrinter<unordered_set<int>>::value);
      IS_TRUE(has_ZenUnitPrinter<set<string>>::value);
      IS_TRUE(has_ZenUnitPrinter<unordered_set<string>>::value);

      IS_TRUE(has_ZenUnitPrinter<UserType>::value);
      IS_TRUE(has_ZenUnitPrinter<OnlyZenUnitPrintableUserType>::value);
      IS_TRUE(has_ZenUnitPrinter<DoublyPrintableUserType>::value);
      IS_TRUE(has_ZenUnitPrinter<Namespace::StructInsideNamespace_ZenUnitPrintOutsideNamespace>::value);
   }

   RUN_TESTS(has_ZenUnitPrinterTests)
}
