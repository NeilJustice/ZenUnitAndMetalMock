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

   static_assert(has_ZenUnitPrinter<vector<int>>);
   static_assert(has_ZenUnitPrinter<vector<string>>);

   using MapIntInt = map<int, int>;
   static_assert(has_ZenUnitPrinter<MapIntInt>);

   using UnorderedMapIntInt = unordered_map<int, int>;
   static_assert(has_ZenUnitPrinter<UnorderedMapIntInt>);

   using MapCharString = map<char, string>;
   static_assert(has_ZenUnitPrinter<MapCharString>);

   using UnorderedMapCharString = unordered_map<char, string>;
   static_assert(has_ZenUnitPrinter<UnorderedMapCharString>);

   static_assert(has_ZenUnitPrinter<set<int>>);
   static_assert(has_ZenUnitPrinter<unordered_set<int>>);
   static_assert(has_ZenUnitPrinter<set<string>>);
   static_assert(has_ZenUnitPrinter<unordered_set<string>>);

   static_assert(has_ZenUnitPrinter<UserType>);
   static_assert(has_ZenUnitPrinter<OnlyZenUnitPrintableUserType>);
   static_assert(has_ZenUnitPrinter<DoublyPrintableUserType>);
   static_assert(has_ZenUnitPrinter<Namespace::StructInsideNamespace_ZenUnitPrintOutsideNamespace>);

   static_assert(has_ZenUnitPrinter<NonConstReferenceZenUnitPrint>);


   static_assert(!has_ZenUnitPrinter<int>);
   static_assert(!has_ZenUnitPrinter<string>);
   static_assert(!has_ZenUnitPrinter<NonPrintableUserType>);
   static_assert(!has_ZenUnitPrinter<RValueReferenceZenUnitPrint>);
}
