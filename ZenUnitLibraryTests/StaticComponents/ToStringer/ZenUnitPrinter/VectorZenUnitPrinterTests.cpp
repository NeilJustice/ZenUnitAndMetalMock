#include "pch.h"

namespace ZenUnit
{
   template<typename T>
   TEMPLATE_TESTS(VectorZenUnitPrinterTests, T)
   AFACT(ZenUnitPrinterPrint_VectorIsEmpty_PrintsEmptyBrackets)
   AFACT(ZenUnitPrinterPrint_VectorHasOneElement_PrintsElement)
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

   TEST(ZenUnitPrinterPrint_VectorHasOneElement_PrintsElement)
   {
      const vector<T> vec = { 1 };
      //
      ZenUnit::Printer<decltype(vec)>::Print(_oss, vec);
      //
      const string vectorAsString = _oss.str();
      const string expectedVectorAsString = _expectedVectorTypePrefix + "1):" + TestUtil::NewlineConcat("",
"{",
"   1",
"}");
      ARE_EQUAL(expectedVectorAsString, vectorAsString);
   }

   TEST(ZenUnitPrinterPrint_VectorHasElevenElements_PrintsAllElevenElements)
   {
      const vector<T> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
      //
      ZenUnit::Printer<decltype(vec)>::Print(_oss, vec);
      //
      const string vectorAsString = _oss.str();
      const string expectedVectorAsString = _expectedVectorTypePrefix + "11):" + TestUtil::NewlineConcat("",
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
"}");
      ARE_EQUAL(expectedVectorAsString, vectorAsString);
   }

   RUN_TEMPLATE_TESTS(VectorZenUnitPrinterTests, int)
   THEN_RUN_TEMPLATE_TESTS(VectorZenUnitPrinterTests, unsigned long long)
}
