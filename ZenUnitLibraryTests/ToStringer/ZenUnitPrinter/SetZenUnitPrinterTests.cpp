#include "pch.h"
#include "ZenUnitTestUtils/CustomPolicyClasses.h"

namespace ZenUnit
{
   template<
      template<typename...>
   typename SetType, typename T>
   TEMPLATE_TESTS(SetZenUnitPrinterTests, SetType, T)
   AFACT(Print_StdSet_PrintsExpectedStringRepresentationOfTheSet)
   EVIDENCE

   TEST(Print_StdSet_PrintsExpectedStringRepresentationOfTheSet)
   {
      ostringstream oss;

      const string expectedSetTypeName = *Type::GetName<SetType<T>>();

      ZenUnit::Printer<set<T>>::Print(oss, {});
      ARE_EQUAL(expectedSetTypeName + R"(
{
})", oss.str());
      oss = ostringstream();

      ZenUnit::Printer<set<T>>::Print(oss, { 1 });
      ARE_EQUAL(expectedSetTypeName + R"(
{
   1
})", oss.str());
      oss = ostringstream();

      ZenUnit::Printer<set<T>>::Print(oss, { 1, 2 });
      ARE_EQUAL(expectedSetTypeName + R"(
{
   1,
   2
})", oss.str());
      oss = ostringstream();

      ZenUnit::Printer<set<T>>::Print(oss, { 1, 2, 3 });
      ARE_EQUAL(expectedSetTypeName + R"(
{
   1,
   2,
   3
})", oss.str());
      oss = ostringstream();

      // Does-compile confirmation
      const string expectedSetTypeNameWithCustomLessCompator = *Type::GetName<SetType<T, CustomLessComparator<T>>>();
      ZenUnit::Printer<set<T, CustomLessComparator<T>>>::Print(oss, {});
      ARE_EQUAL(expectedSetTypeNameWithCustomLessCompator + R"(
{
})", oss.str());
      oss = ostringstream();

      // Does-compile confirmation
      const string expectedSetTypeNameWithCustomLessCompatorAndAllocator = *Type::GetName<SetType<T, CustomLessComparator<T>, CustomAllocator<T>>>();
      ZenUnit::Printer<set<T, CustomLessComparator<T>, CustomAllocator<T>>>::Print(oss, {});
      ARE_EQUAL(expectedSetTypeNameWithCustomLessCompatorAndAllocator + R"(
{
})", oss.str());
   }

   RUN_TEMPLATE_TESTS(SetZenUnitPrinterTests, set, int);
   THEN_RUN_TEMPLATE_TESTS(SetZenUnitPrinterTests, set, unsigned long long);


   /*template<typename T>
   TEMPLATE_TESTS(UnorderedSetZenUnitPrinterTests, T)
   AFACT(Print_StdSet_PrintsExpectedStringRepresentationOfTheSet)
   EVIDENCE

   TEST(Print_StdSet_PrintsExpectedStringRepresentationOfTheSet)
   {
      ostringstream oss;

      const string expectedSetTypeName = *Type::GetName<unordered_set<T>>();

      ZenUnit::Printer<unordered_set<T>>::Print(oss, {});
      ARE_EQUAL(expectedSetTypeName + R"(
{
})", oss.str());
      oss = ostringstream();

      ZenUnit::Printer<unordered_set<T>>::Print(oss, { 1 });
      ARE_EQUAL(expectedSetTypeName + R"(
{
   1
})", oss.str());
      oss = ostringstream();

      ZenUnit::Printer<unordered_set<T>>::Print(oss, { 1, 2 });
      ARE_EQUAL(expectedSetTypeName + R"(
{
   1,
   2
})", oss.str());
      oss = ostringstream();

      ZenUnit::Printer<unordered_set<T>>::Print(oss, { 1, 2, 3 });
      ARE_EQUAL(expectedSetTypeName + R"(
{
   1,
   2,
   3
})", oss.str());
      oss = ostringstream();

      // Does-compile confirmation
      const string expectedUnorderedSetTypeNameWithCustomHasher = *Type::GetName<unordered_set<T, CustomHasher<T>>>();
      ZenUnit::Printer<unordered_set<T, CustomHasher<T>>>::Print(oss, {});
      ARE_EQUAL(expectedUnorderedSetTypeNameWithCustomHasher + R"(
{
})", oss.str());
      oss = ostringstream();

      // Does-compile confirmation
      const string expectedUnorderedSetTypeNameWithCustomHasherAndCustomerEqualityComparator =
         *Type::GetName<unordered_set<T, CustomHasher<T>, CustomEqualityComparator<T>>>();
      ZenUnit::Printer<unordered_set<T, CustomHasher<T>, CustomEqualityComparator<T>>>::Print(oss, {});
      ARE_EQUAL(expectedUnorderedSetTypeNameWithCustomHasherAndCustomerEqualityComparator + R"(
{
})", oss.str());
   }

   RUN_TEMPLATE_TESTS(UnorderedSetZenUnitPrinterTests, int);
   THEN_RUN_TEMPLATE_TESTS(UnorderedSetZenUnitPrinterTests, unsigned long long);*/
}
