#include "pch.h"
#include "ZenUnitTestUtils/CustomPolicyClasses.h"

namespace ZenUnit
{
   template<typename T>
   TEMPLATE_TESTS(IntegralVectorZenUnitPrinterTests, T)
   AFACT(ZenUnitPrinter_Print_Empty_PrintsEmptyBrackets)
   AFACT(ZenUnitPrinter_Print_EmptyAndNonConst_PrintsElements)
   AFACT(ZenUnitPrinter_Print_OneElement_PrintsElement)
   AFACT(ZenUnitPrinter_Print_TwoElements_PrintsElements)
   AFACT(ZenUnitPrinter_Print_SevenElements_PrintsAllSevenElements)
   AFACT(ZenUnitPrinter_Print_EightElements_PrintsFirstSevenElements)
   EVIDENCE

   const string _expectedVectorTypePrefix = "std::vector<" + *Type::GetName<T>() + "> (size ";
   ostringstream _oss;

   TEST(ZenUnitPrinter_Print_Empty_PrintsEmptyBrackets)
   {
      const vector<T> v;
      //
      ZenUnit::Printer<decltype(v)>::Print(_oss, v);
      //
      const string printString = _oss.str();
      ARE_EQUAL(_expectedVectorTypePrefix + "0):" + TestUtil::NewlineConcat("",
"{",
"}"), printString);
   }

   TEST(ZenUnitPrinter_Print_EmptyAndNonConst_PrintsElements)
   {
      vector<T> v;
      //
      ZenUnit::Printer<decltype(v)>::Print(_oss, v);
      //
      const string printString = _oss.str();
      ARE_EQUAL(_expectedVectorTypePrefix + "0):" + TestUtil::NewlineConcat("",
"{",
"}"), printString);
   }

   TEST(ZenUnitPrinter_Print_OneElement_PrintsElement)
   {
      const vector<T> v = { 1 };
      //
      ZenUnit::Printer<decltype(v)>::Print(_oss, v);
      //
      const string printString = _oss.str();
      ARE_EQUAL(_expectedVectorTypePrefix + "1):" + TestUtil::NewlineConcat("",
"{",
"   1",
"}"), printString);
   }

   TEST(ZenUnitPrinter_Print_TwoElements_PrintsElements)
   {
      const vector<T> v = { 1, 2 };
      //
      ZenUnit::Printer<decltype(v)>::Print(_oss, v);
      //
      const string printString = _oss.str();
      ARE_EQUAL(_expectedVectorTypePrefix + "2):" + TestUtil::NewlineConcat("",
"{",
"   1,",
"   2",
"}"), printString);
   }

   TEST(ZenUnitPrinter_Print_SevenElements_PrintsAllSevenElements)
   {
      const vector<T> v = { 1, 2, 3, 4, 5, 6, 7 };
      //
      ZenUnit::Printer<decltype(v)>::Print(_oss, v);
      //
      const string printString = _oss.str();
      ARE_EQUAL(_expectedVectorTypePrefix + "7):" + TestUtil::NewlineConcat("",
"{",
"   1,",
"   2,",
"   3,",
"   4,",
"   5,",
"   6,",
"   7",
"}"), printString);
   }

   TEST(ZenUnitPrinter_Print_EightElements_PrintsFirstSevenElements)
   {
      const vector<T> v = { 1, 2, 3, 4, 5, 6, 7, 8 };
      //
      ZenUnit::Printer<decltype(v)>::Print(_oss, v);
      //
      const string printString = _oss.str();
      ARE_EQUAL(_expectedVectorTypePrefix + "8):" + TestUtil::NewlineConcat("",
"{",
"   1,",
"   2,",
"   3,",
"   4,",
"   5,",
"   6,",
"   7,",
"   ...elements beyond 7 elided for brevity...",
"}"), printString);
   }

   RUN_TEMPLATE_TESTS(IntegralVectorZenUnitPrinterTests, int)
   THEN_RUN_TEMPLATE_TESTS(IntegralVectorZenUnitPrinterTests, unsigned)
}