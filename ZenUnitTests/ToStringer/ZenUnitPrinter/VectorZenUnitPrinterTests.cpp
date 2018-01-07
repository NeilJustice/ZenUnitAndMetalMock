#include "pch.h"
#include "ZenUnitTests/Testing/CustomPolicyClasses.h"

namespace ZenUnit
{
   template<typename T>
   TEMPLATETESTS(IntegralVectorZenUnitPrinterTests, T)
   AFACT(ZenUnitPrinter_Print_Empty_PrintsEmptyBrackets)
   AFACT(ZenUnitPrinter_Print_EmptyAndNonConst_PrintsElements)
   AFACT(ZenUnitPrinter_Print_OneElement_PrintsElement)
   AFACT(ZenUnitPrinter_Print_SevenElements_PrintsAllSevenElements)
   AFACT(ZenUnitPrinter_Print_EightElements_PrintsFirstSevenElements)
   EVIDENCE

   const string _expectedVectorTypePrefix = "vector<" + *Type::GetName<T>() + ">: ";

   TEST(ZenUnitPrinter_Print_Empty_PrintsEmptyBrackets)
   {
      const vector<T> v;
      ostringstream oss;
      //
      ZenUnit::Printer<decltype(v)>::Print(oss, v);
      //
      const string str = oss.str();
      ARE_EQUAL(_expectedVectorTypePrefix + "{}", str);
   }

   TEST(ZenUnitPrinter_Print_EmptyAndNonConst_PrintsElements)
   {
      vector<T> v;
      ostringstream oss;
      //
      ZenUnit::Printer<decltype(v)>::Print(oss, v);
      //
      const string str = oss.str();
      ARE_EQUAL(_expectedVectorTypePrefix + "{}", str);
   }

   TEST(ZenUnitPrinter_Print_OneElement_PrintsElement)
   {
      const vector<T> v = { 1 };
      ostringstream oss;
      //
      ZenUnit::Printer<decltype(v)>::Print(oss, v);
      //
      const string str = oss.str();
      ARE_EQUAL(_expectedVectorTypePrefix + "{1}", str);
   }

   TEST(ZenUnitPrinter_Print_SevenElements_PrintsAllSevenElements)
   {
      const vector<T> v = { 1, 2, 3, 4, 5, 6, 7 };
      ostringstream oss;
      //
      ZenUnit::Printer<decltype(v)>::Print(oss, v);
      //
      const string str = oss.str();
      ARE_EQUAL(_expectedVectorTypePrefix + "{1, 2, 3, 4, 5, 6, 7}", str);
   }

   TEST(ZenUnitPrinter_Print_EightElements_PrintsFirstSevenElements)
   {
      const vector<T> v = { 1, 2, 3, 4, 5, 6, 7, 8 };
      ostringstream oss;
      //
      ZenUnit::Printer<decltype(v)>::Print(oss, v);
      //
      const string str = oss.str();
      ARE_EQUAL(_expectedVectorTypePrefix + "{1, 2, 3, 4, 5, 6, 7, ...}", str);
   }

   };
   RUNTEMPLATETESTS(IntegralVectorZenUnitPrinterTests, int)
   RUNTEMPLATETESTS(IntegralVectorZenUnitPrinterTests, unsigned)
}
