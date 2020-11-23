#include "pch.h"

namespace ZenUnit
{
   template<typename T>
   TEMPLATE_TESTS(VectorZenUnitPrinterTests, T)
   AFACT(ZenUnitPrinterPrint_VectorIsEmpty_PrintsEmptyBrackets)
   AFACT(ZenUnitPrinterPrint_VectorIsEmptyAndNonConst_PrintsElements)
   AFACT(ZenUnitPrinterPrint_VectorHasOneElement_PrintsElement)
   AFACT(ZenUnitPrinterPrint_VectorHasTwoElements_PrintsElements)
   AFACT(ZenUnitPrinterPrint_VectorHasTenElements_PrintsAllTenElements)
   AFACT(ZenUnitPrinterPrint_VectorHasElevenElements_PrintsAllElevenElements)
   EVIDENCE

   const string _expectedVectorTypePrefix = "std::vector<" + *Type::GetName<T>() + "> (size ";
   ostringstream _oss;

   TEST(ZenUnitPrinterPrint_VectorIsEmpty_PrintsEmptyBrackets)
   {
      const vector<T> vec;
      //
      ZenUnit::Printer<decltype(vec)>::Print(_oss, vec);
      //
      const string vectorAsString = _oss.str();
      ARE_EQUAL(_expectedVectorTypePrefix + "0):" + TestUtil::NewlineConcat("",
"{",
"}"), vectorAsString);
   }

   TEST(ZenUnitPrinterPrint_VectorIsEmptyAndNonConst_PrintsElements)
   {
      vector<T> vec;
      //
      ZenUnit::Printer<decltype(vec)>::Print(_oss, vec);
      //
      const string vectorAsString = _oss.str();
      ARE_EQUAL(_expectedVectorTypePrefix + "0):" + TestUtil::NewlineConcat("",
"{",
"}"), vectorAsString);
   }

   TEST(ZenUnitPrinterPrint_VectorHasOneElement_PrintsElement)
   {
      const vector<T> vec = { 1 };
      //
      ZenUnit::Printer<decltype(vec)>::Print(_oss, vec);
      //
      const string vectorAsString = _oss.str();
      ARE_EQUAL(_expectedVectorTypePrefix + "1):" + TestUtil::NewlineConcat("",
"{",
"   1",
"}"), vectorAsString);
   }

   TEST(ZenUnitPrinterPrint_VectorHasTwoElements_PrintsElements)
   {
      const vector<T> vec = { 1, 2 };
      //
      ZenUnit::Printer<decltype(vec)>::Print(_oss, vec);
      //
      const string vectorAsString = _oss.str();
      ARE_EQUAL(_expectedVectorTypePrefix + "2):" + TestUtil::NewlineConcat("",
"{",
"   1,",
"   2",
"}"), vectorAsString);
   }

   TEST(ZenUnitPrinterPrint_VectorHasTenElements_PrintsAllTenElements)
   {
      const vector<T> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
      //
      ZenUnit::Printer<decltype(vec)>::Print(_oss, vec);
      //
      const string vectorAsString = _oss.str();
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
"}"), vectorAsString);
   }

   TEST(ZenUnitPrinterPrint_VectorHasElevenElements_PrintsAllElevenElements)
   {
      const vector<T> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
      //
      ZenUnit::Printer<decltype(vec)>::Print(_oss, vec);
      //
      const string vectorAsString = _oss.str();
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
"   11",
"}"), vectorAsString);
   }

   RUN_TEMPLATE_TESTS(VectorZenUnitPrinterTests, int)
   THEN_RUN_TEMPLATE_TESTS(VectorZenUnitPrinterTests, unsigned long long)
}
