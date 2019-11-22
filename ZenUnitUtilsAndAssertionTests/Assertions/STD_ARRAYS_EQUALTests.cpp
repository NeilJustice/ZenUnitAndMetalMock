#include "pch.h"

namespace ZenUnit
{
   template<typename T>
   TEMPLATE_TESTS(STD_ARRAYS_EQUALTests_Size0Arrays, T)
   AFACT(TwoSize0Arrays_DoesNotThrow)
   EVIDENCE

   TEST(TwoSize0Arrays_DoesNotThrow)
   {
      const array<T, 0> expectedArray{};
      const array<T, 0> actualArray{};
      STD_ARRAYS_EQUAL(expectedArray, actualArray);
   }

   RUN_TEMPLATE_TESTS(STD_ARRAYS_EQUALTests_Size0Arrays, int)
   THEN_RUN_TEMPLATE_TESTS(STD_ARRAYS_EQUALTests_Size0Arrays, unsigned long long)


   template<typename T>
   TEMPLATE_TESTS(STD_ARRAYS_EQUALTests_Size1Arrays, T)
   AFACT(ElementsAreDefaults_DoesNotThrow)
   AFACT(ElementAreNonDefaultAndNotEqual_Throws)
   AFACT(ElementAreNonDefaultAndEqual_DoesNotThrow)
   EVIDENCE

   TEST(ElementsAreDefaults_DoesNotThrow)
   {
      const array<T, 1> expectedArray{};
      const array<T, 1> actualArray{};
      STD_ARRAYS_EQUAL(expectedArray, actualArray);
   }

   TEST(ElementAreNonDefaultAndNotEqual_Throws)
   {
      const string TypeName = *Type::GetName<T>();
      const T randomElement = ZenUnit::Random<T>();
      const array<T, 1> expectedArray = { { randomElement } };
      const array<T, 1> actualArray = { { randomElement + T{ 1 } } };
      //
#if defined __linux__
      THROWS_EXCEPTION(STD_ARRAYS_EQUAL(expectedArray, actualArray), Anomaly, TestUtil::NewlineConcat("",
"  Failed: STD_ARRAYS_EQUAL(expectedArray, actualArray)",
"Expected: <std::array<" + TypeName + ", 1ul>>",
"  Actual: <std::array<" + TypeName + ", 1ul>>",
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
"Expected: " + ToStringer::ToString(expectedArray[0]),
"  Actual: " + ToStringer::ToString(actualArray[0]),
" Message: \"i=0\"",
"File.cpp(1)",
"File.cpp(1)"));
#elif defined __APPLE__
      THROWS_EXCEPTION(STD_ARRAYS_EQUAL(expectedArray, actualArray), Anomaly, TestUtil::NewlineConcat("",
"  Failed: STD_ARRAYS_EQUAL(expectedArray, actualArray)",
"Expected: <std::__1::array<" + TypeName + ", 1ul>>",
"  Actual: <std::__1::array<" + TypeName + ", 1ul>>",
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
"Expected: " + ToStringer::ToString(expectedArray[0]),
"  Actual: " + ToStringer::ToString(actualArray[0]),
" Message: \"i=0\"",
"File.cpp(1)",
"File.cpp(1)"));
#elif defined _WIN32
      THROWS_EXCEPTION(STD_ARRAYS_EQUAL(expectedArray, actualArray), Anomaly, TestUtil::NewlineConcat("",
"  Failed: STD_ARRAYS_EQUAL(expectedArray, actualArray)",
"Expected: <std::array<" + TypeName + ",1>>",
"  Actual: <std::array<" + TypeName + ",1>>",
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
"Expected: " + ToStringer::ToString(expectedArray[0]),
"  Actual: " + ToStringer::ToString(actualArray[0]),
" Message: \"i=0\"",
"File.cpp(1)",
"File.cpp(1)"));
   #endif
   }

   TEST(ElementAreNonDefaultAndEqual_DoesNotThrow)
   {
      const T randomElement = ZenUnit::Random<T>();
      const array<T, 1> expectedArray = { { randomElement } };
      const array<T, 1> actualArray = { { randomElement } };
      STD_ARRAYS_EQUAL(expectedArray, actualArray);
   }

   RUN_TEMPLATE_TESTS(STD_ARRAYS_EQUALTests_Size1Arrays, int)
   THEN_RUN_TEMPLATE_TESTS(STD_ARRAYS_EQUALTests_Size1Arrays, unsigned long long)


   template<typename T>
   TEMPLATE_TESTS(STD_ARRAYS_EQUALTests_Size2Arrays, T)
   AFACT(ElementsAreDefaults_DoesNotThrow)
   AFACT(ElementsAreNonDefaultAndNotEqualAtIndex0_Throws)
   AFACT(ElementsAreNonDefaultAndNotEqualAtIndex1_Throws)
   AFACT(ElementsAreNonDefaultAndBothEqual_DoesNotThrow)
   EVIDENCE

   const string TypeName = *Type::GetName<T>();
   const T _randomElementA = ZenUnit::Random<T>();
   const T _randomElementB = ZenUnit::Random<T>();

   TEST(ElementsAreDefaults_DoesNotThrow)
   {
      const array<T, 2> expectedArray{};
      const array<T, 2> actualArray{};
      STD_ARRAYS_EQUAL(expectedArray, actualArray);
   }

   TEST(ElementsAreNonDefaultAndNotEqualAtIndex0_Throws)
   {
      const array<T, 2> expectedArray_index0 = { { _randomElementA, _randomElementB } };
      const T randomT = ZenUnit::Random<T>();
      const array<T, 2> actualArray_index0 = { { _randomElementA + randomT, _randomElementB } };
      //
#if defined __linux__
      THROWS_EXCEPTION(STD_ARRAYS_EQUAL(expectedArray_index0, actualArray_index0), Anomaly, TestUtil::NewlineConcat("",
"  Failed: STD_ARRAYS_EQUAL(expectedArray_index0, actualArray_index0)",
"Expected: <std::array<" + TypeName + ", 2ul>>",
"  Actual: <std::array<" + TypeName + ", 2ul>>",
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
"Expected: " + ToStringer::ToString(expectedArray_index0[0]),
"  Actual: " + ToStringer::ToString(actualArray_index0[0]),
" Message: \"i=0\"",
"File.cpp(1)",
"File.cpp(1)"));
#elif defined __APPLE__
      THROWS_EXCEPTION(STD_ARRAYS_EQUAL(expectedArray_index0, actualArray_index0), Anomaly, TestUtil::NewlineConcat("",
"  Failed: STD_ARRAYS_EQUAL(expectedArray_index0, actualArray_index0)",
"Expected: <std::__1::array<" + TypeName + ", 2ul>>",
"  Actual: <std::__1::array<" + TypeName + ", 2ul>>",
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
"Expected: " + ToStringer::ToString(expectedArray_index0[0]),
"  Actual: " + ToStringer::ToString(actualArray_index0[0]),
" Message: \"i=0\"",
"File.cpp(1)",
"File.cpp(1)"));
#elif defined _WIN32
      THROWS_EXCEPTION(STD_ARRAYS_EQUAL(expectedArray_index0, actualArray_index0), Anomaly, TestUtil::NewlineConcat("",
"  Failed: STD_ARRAYS_EQUAL(expectedArray_index0, actualArray_index0)",
"Expected: <std::array<" + TypeName + ",2>>",
"  Actual: <std::array<" + TypeName + ",2>>",
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
"Expected: " + ToStringer::ToString(expectedArray_index0[0]),
"  Actual: " + ToStringer::ToString(actualArray_index0[0]),
" Message: \"i=0\"",
"File.cpp(1)",
"File.cpp(1)"));
   #endif
   }

   TEST(ElementsAreNonDefaultAndNotEqualAtIndex1_Throws)
   {
      const array<T, 2> expectedArray_index1 = { { _randomElementA, _randomElementB } };
      const T randomT = ZenUnit::RandomNon0<T>();
      const array<T, 2> actualArray_index1 = { { _randomElementA, _randomElementB + randomT } };
      //
#if defined __linux__
      THROWS_EXCEPTION(STD_ARRAYS_EQUAL(expectedArray_index1, actualArray_index1), Anomaly, TestUtil::NewlineConcat("",
"  Failed: STD_ARRAYS_EQUAL(expectedArray_index1, actualArray_index1)",
"Expected: <std::array<" + TypeName + ", 2ul>>",
"  Actual: <std::array<" + TypeName + ", 2ul>>",
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
"Expected: " + ToStringer::ToString(expectedArray_index1[1]),
"  Actual: " + ToStringer::ToString(actualArray_index1[1]),
" Message: \"i=1\"",
"File.cpp(1)",
"File.cpp(1)"));
#elif defined __APPLE__
      THROWS_EXCEPTION(STD_ARRAYS_EQUAL(expectedArray_index1, actualArray_index1), Anomaly, TestUtil::NewlineConcat("",
"  Failed: STD_ARRAYS_EQUAL(expectedArray_index1, actualArray_index1)",
"Expected: <std::__1::array<" + TypeName + ", 2ul>>",
"  Actual: <std::__1::array<" + TypeName + ", 2ul>>",
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
"Expected: " + ToStringer::ToString(expectedArray_index1[1]),
"  Actual: " + ToStringer::ToString(actualArray_index1[1]),
" Message: \"i=1\"",
"File.cpp(1)",
"File.cpp(1)"));
#elif defined _WIN32
      THROWS_EXCEPTION(STD_ARRAYS_EQUAL(expectedArray_index1, actualArray_index1), Anomaly, TestUtil::NewlineConcat("",
"  Failed: STD_ARRAYS_EQUAL(expectedArray_index1, actualArray_index1)",
"Expected: <std::array<" + TypeName + ",2>>",
"  Actual: <std::array<" + TypeName + ",2>>",
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
"Expected: " + ToStringer::ToString(expectedArray_index1[1]),
"  Actual: " + ToStringer::ToString(actualArray_index1[1]),
" Message: \"i=1\"",
"File.cpp(1)",
"File.cpp(1)"));
   #endif
   }

   TEST(ElementsAreNonDefaultAndBothEqual_DoesNotThrow)
   {
      const T randomElementA = ZenUnit::Random<T>();
      const T randomElementB = ZenUnit::Random<T>();
      const array<T, 2> expectedArray = { { randomElementA, randomElementB } };
      const array<T, 2> actualArray = { { randomElementA, randomElementB } };
      STD_ARRAYS_EQUAL(expectedArray, actualArray);
   }

   RUN_TEMPLATE_TESTS(STD_ARRAYS_EQUALTests_Size2Arrays, int)
   THEN_RUN_TEMPLATE_TESTS(STD_ARRAYS_EQUALTests_Size2Arrays, size_t)
   THEN_RUN_TEMPLATE_TESTS(STD_ARRAYS_EQUALTests_Size2Arrays, string)
}
