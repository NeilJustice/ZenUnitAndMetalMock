#include "pch.h"

namespace ZenUnit
{
   template<typename T>
   TEMPLATE_TESTS(IntegralVectorZenUnitPrinterTests, T)
   AFACT(ZenUnitPrinter_Print_Empty_PrintsEmptyBrackets)
   AFACT(ZenUnitPrinter_Print_EmptyAndNonConst_PrintsElements)
   AFACT(ZenUnitPrinter_Print_OneElement_PrintsElement)
   AFACT(ZenUnitPrinter_Print_TwoElements_PrintsElements)
   AFACT(ZenUnitPrinter_Print_TenElements_PrintsAllTenElements)
   AFACT(ZenUnitPrinter_Print_ElevenElements_PrintsFirstTenElements)
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

   TEST(ZenUnitPrinter_Print_TenElements_PrintsAllTenElements)
   {
      const vector<T> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
      //
      ZenUnit::Printer<decltype(v)>::Print(_oss, v);
      //
      const string printString = _oss.str();
      ARE_EQUAL(_expectedVectorTypePrefix + "10):" + TestUtil::NewlineConcat("",
"{",
"   1,",
"   2,",
"   3,",
"   4,",
"   5,",
"   6,",
"   7,",
"   8,",
"   9,",
"   10",
"}"), printString);
   }

   TEST(ZenUnitPrinter_Print_ElevenElements_PrintsFirstTenElements)
   {
      const vector<T> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
      //
      ZenUnit::Printer<decltype(v)>::Print(_oss, v);
      //
      const string printString = _oss.str();
      ARE_EQUAL(_expectedVectorTypePrefix + "11):" + TestUtil::NewlineConcat("",
"{",
"   1,",
"   2,",
"   3,",
"   4,",
"   5,",
"   6,",
"   7,",
"   8,",
"   9,",
"   10,",
"   ...elements beyond 10 elided for brevity...",
"}"), printString);
   }

   RUN_TEMPLATE_TESTS(IntegralVectorZenUnitPrinterTests, int)
   THEN_RUN_TEMPLATE_TESTS(IntegralVectorZenUnitPrinterTests, unsigned long long)
}
