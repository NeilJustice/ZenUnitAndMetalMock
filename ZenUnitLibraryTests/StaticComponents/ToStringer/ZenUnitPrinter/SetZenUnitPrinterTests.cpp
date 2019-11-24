#include "pch.h"
//#include "ZenUnitTestUtils/CustomPolicyClasses.h"

namespace ZenUnit
{
   template<
      template<typename...>
   typename SetType, typename T>
   TEMPLATE_TESTS(SetZenUnitPrinterTests, SetType, T)
   AFACT(Print_PrintsEachSetElementsUsingZenUnitPrinterPrint)
   EVIDENCE

   TEST(Print_PrintsEachSetElementsUsingZenUnitPrinterPrint)
   {
      ostringstream expectedMessageBuilder;

      const string expectedSetTypeName = *Type::GetName<SetType<T>>();

      ZenUnit::Printer<SetType<T>>::Print(expectedMessageBuilder, {});
      ARE_EQUAL(expectedSetTypeName + R"(
{
})", expectedMessageBuilder.str());
      expectedMessageBuilder = ostringstream();

      ZenUnit::Printer<SetType<T>>::Print(expectedMessageBuilder, { 1 });
      ARE_EQUAL(expectedSetTypeName + R"(
{
   1
})", expectedMessageBuilder.str());
      expectedMessageBuilder = ostringstream();

      ZenUnit::Printer<SetType<T>>::Print(expectedMessageBuilder, { 1, 2 });
      const string zenUnitPrintedSetPossibility1 = expectedSetTypeName + R"(
{
   1,
   2
})";
      const string zenUnitPrintedSetPossibility2 = expectedSetTypeName + R"(
{
   2,
   1
})";
      const string zenUnitPrintedSet = expectedMessageBuilder.str();
      if (zenUnitPrintedSet != zenUnitPrintedSetPossibility1 &&
          zenUnitPrintedSet != zenUnitPrintedSetPossibility2)
      {
         FAIL_TEST("Unexpected ZenUnit::Printer::Print() set string: " + zenUnitPrintedSet); // LCOV_EXCL_LINE
      }

//      // Does-compile confirmation
//      const string expectedSetTypeNameWithCustomLessCompator = *Type::GetName<SetType<T, CustomLessComparator<T>>>();
//      ZenUnit::Printer<SetType<T, CustomLessComparator<T>>>::Print(expectedMessageBuilder, {});
//      ARE_EQUAL(expectedSetTypeNameWithCustomLessCompator + R"(
//{
//})", expectedMessageBuilder.str());
//      expectedMessageBuilder = ostringstream();
//
//      // Does-compile confirmation
//      const string expectedSetTypeNameWithCustomLessCompatorAndAllocator = *Type::GetName<SetType<T, CustomLessComparator<T>, CustomAllocator<T>>>();
//      ZenUnit::Printer<SetType<T, CustomLessComparator<T>, CustomAllocator<T>>>::Print(expectedMessageBuilder, {});
//      ARE_EQUAL(expectedSetTypeNameWithCustomLessCompatorAndAllocator + R"(
//{
//})", expectedMessageBuilder.str());
   }

   RUN_TEMPLATE_TESTS(SetZenUnitPrinterTests, set, int)
   THEN_RUN_TEMPLATE_TESTS(SetZenUnitPrinterTests, set, unsigned long long)
   THEN_RUN_TEMPLATE_TESTS(SetZenUnitPrinterTests, unordered_set, int)
   THEN_RUN_TEMPLATE_TESTS(SetZenUnitPrinterTests, unordered_set, unsigned long long)
}
