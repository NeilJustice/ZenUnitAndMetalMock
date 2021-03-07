#include "pch.h"

namespace ZenUnit
{
   template<typename T>
   TEMPLATE_TESTS(VectorZenUnitPrinterTests, T)
   AFACT(ZenUnitPrinterPrint_VectorIsEmpty_PrintsEmptyBrackets)
   AFACT(ZenUnitPrinterPrint_VectorHasOneElement_PrintsElement)
   AFACT(ZenUnitPrinterPrint_VectorHasElevenElements_PrintsAllElevenElements)
   EVIDENCE

   const string _expectedVectorTypeName = *Type::GetName<vector<T>>();
   ostringstream _oss;

   TEST(ZenUnitPrinterPrint_VectorIsEmpty_PrintsEmptyBrackets)
   {
      const vector<T> vec;
      //
      ZenUnit::Printer<vector<T>>::Print(_oss, vec);
      //
      const string vectorAsString = _oss.str();
      ARE_EQUAL(_expectedVectorTypeName + " (size 0):" + TestUtil::NewlineConcat("",
         "{",
         "}"), vectorAsString);
   }

   TEST(ZenUnitPrinterPrint_VectorHasOneElement_PrintsElement)
   {
      const vector<T> vec = { 1 };
      //
      ZenUnit::Printer<vector<T>>::Print(_oss, vec);
      //
      const string vectorAsString = _oss.str();
      const string expectedVectorAsString = _expectedVectorTypeName + " (size 1):" + TestUtil::NewlineConcat("",
         "{",
         "   1",
         "}");
      ARE_EQUAL(expectedVectorAsString, vectorAsString);
   }

   TEST(ZenUnitPrinterPrint_VectorHasElevenElements_PrintsAllElevenElements)
   {
      const vector<T> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
      //
      ZenUnit::Printer<vector<T>>::Print(_oss, vec);
      //
      const string vectorAsString = _oss.str();
      const string expectedVectorAsString = _expectedVectorTypeName + " (size 11):" + TestUtil::NewlineConcat("",
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


   TESTS(VectorOfUserTypesZenUnitPrinterTests)
   AFACT(ZenUnitPrinterPrint_VectorIsEmpty_PrintsEmptyBrackets)
   AFACT(ZenUnitPrinterPrint_VectorHasOneElement_PrintsElement)
   AFACT(ZenUnitPrinterPrint_VectorHasElevenElements_PrintsAllElevenElements)
   EVIDENCE

   const string _expectedVectorTypeName = *Type::GetName<vector<UserType>>();
   ostringstream _oss;

   TEST(ZenUnitPrinterPrint_VectorIsEmpty_PrintsEmptyBrackets)
   {
      const vector<UserType> vec;
      //
      ZenUnit::Printer<vector<UserType>>::Print(_oss, vec);
      //
      const string vectorAsString = _oss.str();
      ARE_EQUAL(_expectedVectorTypeName + " (size 0):" + TestUtil::NewlineConcat("",
         "{",
         "}"), vectorAsString);
   }

   TEST(ZenUnitPrinterPrint_VectorHasOneElement_PrintsElement)
   {
      const vector<UserType> vec = { UserType(1) };
      //
      ZenUnit::Printer<vector<UserType>>::Print(_oss, vec);
      //
      const string vectorAsString = _oss.str();
      const string expectedVectorAsString = _expectedVectorTypeName + " (size 1):" + TestUtil::NewlineConcat("",
         "{",
         "   UserType@1",
         "}");
      ARE_EQUAL(expectedVectorAsString, vectorAsString);
   }

   TEST(ZenUnitPrinterPrint_VectorHasElevenElements_PrintsAllElevenElements)
   {
      const vector<UserType> vec =
      {
         UserType(1),
         UserType(2),
         UserType(3),
         UserType(4),
         UserType(5),
         UserType(6),
         UserType(7),
         UserType(8),
         UserType(9),
         UserType(10),
         UserType(11)
      };
      //
      ZenUnit::Printer<vector<UserType>>::Print(_oss, vec);
      //
      const string vectorAsString = _oss.str();
      const string expectedVectorAsString = _expectedVectorTypeName + " (size 11):" + TestUtil::NewlineConcat("",
         "{",
         "   UserType@1,",
         "   UserType@2,",
         "   UserType@3,",
         "   UserType@4,",
         "   UserType@5,",
         "   UserType@6,",
         "   UserType@7,",
         "   UserType@8,",
         "   UserType@9,",
         "   UserType@10,",
         "   UserType@11",
         "}");
      ARE_EQUAL(expectedVectorAsString, vectorAsString);
   }

   RUN_TESTS(VectorOfUserTypesZenUnitPrinterTests)
}
