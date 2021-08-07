#include "pch.h"

namespace ZenUnit
{
   template<typename T>
   TEMPLATE_TESTS(STD_ARRAYS_ARE_EQUALTests_Size0Arrays, T)
   AFACT(TwoSize0ConstArrays_DoesNotThrowException)
   AFACT(TwoSize0NonConstArrays_DoesNotThrowException)
   EVIDENCE

   TEST(TwoSize0ConstArrays_DoesNotThrowException)
   {
      const array<T, 0> expectedArray{};
      const array<T, 0> actualArray{};
      STD_ARRAYS_ARE_EQUAL(expectedArray, actualArray);
   }

   TEST(TwoSize0NonConstArrays_DoesNotThrowException)
   {
      array<T, 0> expectedArray{};
      array<T, 0> actualArray{};
      STD_ARRAYS_ARE_EQUAL(expectedArray, actualArray);
   }

   RUN_TEMPLATE_TESTS(STD_ARRAYS_ARE_EQUALTests_Size0Arrays, int)
   THEN_RUN_TEMPLATE_TESTS(STD_ARRAYS_ARE_EQUALTests_Size0Arrays, unsigned long long)


   template<typename T>
   TEMPLATE_TESTS(STD_ARRAYS_ARE_EQUALTests_Size1Arrays, T)
   AFACT(ElementsAreDefaultValues_DoesNotThrowException)
   AFACT(ElementAreNonDefaultValuesAndAreNotEqual_ThrowsAnomaly)
   AFACT(ElementsAreNonDefaultValuesAndBothAreEqual_DoesNotThrowException)
   EVIDENCE

   TEST(ElementsAreDefaultValues_DoesNotThrowException)
   {
      const array<T, 1> expectedArray{};
      const array<T, 1> actualArray{};
      STD_ARRAYS_ARE_EQUAL(expectedArray, actualArray);
   }

   TEST(ElementAreNonDefaultValuesAndAreNotEqual_ThrowsAnomaly)
   {
      const string TypeName = *Type::GetName<T>();
      const T randomElement1 = ZenUnit::Random<T>();
      const T randomElement2 = ZenUnit::RandomNotEqualToValue<T>(randomElement1);
      const array<T, 1> expectedArray = { randomElement1 };
      const array<T, 1> actualArray = { randomElement2 };
      //
#if defined __linux__
      THROWS_EXCEPTION(STD_ARRAYS_ARE_EQUAL(expectedArray, actualArray), Anomaly, TestUtil::NewlineConcat("",
"  Failed: STD_ARRAYS_ARE_EQUAL(expectedArray, actualArray)",
"Expected: <std::array<" + TypeName + ", 1ul>>",
"  Actual: <std::array<" + TypeName + ", 1ul>>",
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
"Expected: " + ToStringer::ToString(expectedArray[0]),
"  Actual: " + ToStringer::ToString(actualArray[0]),
" Message: \"i=0\"",
"File.cpp(1)",
"File.cpp(1)"));
#elif defined __APPLE__
      THROWS_EXCEPTION(STD_ARRAYS_ARE_EQUAL(expectedArray, actualArray), Anomaly, TestUtil::NewlineConcat("",
"  Failed: STD_ARRAYS_ARE_EQUAL(expectedArray, actualArray)",
"Expected: <std::__1::array<" + TypeName + ", 1ul>>",
"  Actual: <std::__1::array<" + TypeName + ", 1ul>>",
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
"Expected: " + ToStringer::ToString(expectedArray[0]),
"  Actual: " + ToStringer::ToString(actualArray[0]),
" Message: \"i=0\"",
"File.cpp(1)",
"File.cpp(1)"));
#elif defined _WIN32
      THROWS_EXCEPTION(STD_ARRAYS_ARE_EQUAL(expectedArray, actualArray), Anomaly, TestUtil::NewlineConcat("",
"  Failed: STD_ARRAYS_ARE_EQUAL(expectedArray, actualArray)",
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

   TEST(ElementsAreNonDefaultValuesAndBothAreEqual_DoesNotThrowException)
   {
      const T randomElement = ZenUnit::Random<T>();
      const array<T, 1> expectedArray{ { randomElement } };
      const array<T, 1> actualArray{ { randomElement } };
      STD_ARRAYS_ARE_EQUAL(expectedArray, actualArray);
   }

   RUN_TEMPLATE_TESTS(STD_ARRAYS_ARE_EQUALTests_Size1Arrays, int)
   THEN_RUN_TEMPLATE_TESTS(STD_ARRAYS_ARE_EQUALTests_Size1Arrays, unsigned long long)


   template<typename T>
   TEMPLATE_TESTS(STD_ARRAYS_ARE_EQUALTests_Size2Arrays, T)
   AFACT(ElementsAreDefaultsValues_DoesNotThrowException)
   AFACT(ElementsAreNotDefaultValuesAndAreNotEqualAtIndex0_ThrowsAnomaly)
   AFACT(ElementsAreNotDefaultValuesAndAreNotEqualAtIndex1_ThrowsAnomaly)
   AFACT(ElementsAreNotDefaultValuesAndBothAreEqual_DoesNotThrowException)
   EVIDENCE

   const string TypeName = *Type::GetName<T>();

   TEST(ElementsAreDefaultsValues_DoesNotThrowException)
   {
      const array<T, 2> expectedArray{};
      const array<T, 2> actualArray{};
      STD_ARRAYS_ARE_EQUAL(expectedArray, actualArray);
   }

   TEST(ElementsAreNotDefaultValuesAndAreNotEqualAtIndex0_ThrowsAnomaly)
   {
      const T randomElement1 = ZenUnit::Random<T>();
      const T randomElement2 = ZenUnit::RandomNotEqualToValue<T>(randomElement1);
      const array<T, 2> expectedArray{ { randomElement1, randomElement1 } };
      const array<T, 2> actualArray{ { randomElement2, randomElement1 } };
      //
#if defined __linux__ || defined __APPLE____linux__
      THROWS_EXCEPTION(STD_ARRAYS_ARE_EQUAL(expectedArray, actualArray), Anomaly, TestUtil::NewlineConcat("",
"  Failed: STD_ARRAYS_ARE_EQUAL(expectedArray, actualArray)",
"Expected: <std::array<" + TypeName + ", 2ul>>",
"  Actual: <std::array<" + TypeName + ", 2ul>>",
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
"Expected: " + ToStringer::ToString(expectedArray[0]),
"  Actual: " + ToStringer::ToString(actualArray[0]),
" Message: \"i=0\"",
"File.cpp(1)",
"File.cpp(1)"));
#elif defined __APPLE__
      THROWS_EXCEPTION(STD_ARRAYS_ARE_EQUAL(expectedArray, actualArray), Anomaly, TestUtil::NewlineConcat("",
"  Failed: STD_ARRAYS_ARE_EQUAL(expectedArray, actualArray)",
"Expected: <std::__1::array<" + TypeName + ", 2ul>>",
"  Actual: <std::__1::array<" + TypeName + ", 2ul>>",
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
"Expected: " + ToStringer::ToString(expectedArray[0]),
"  Actual: " + ToStringer::ToString(actualArray[0]),
" Message: \"i=0\"",
"File.cpp(1)",
"File.cpp(1)"));
#elif defined _WIN32
      THROWS_EXCEPTION(STD_ARRAYS_ARE_EQUAL(expectedArray, actualArray), Anomaly, TestUtil::NewlineConcat("",
"  Failed: STD_ARRAYS_ARE_EQUAL(expectedArray, actualArray)",
"Expected: <std::array<" + TypeName + ",2>>",
"  Actual: <std::array<" + TypeName + ",2>>",
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
"Expected: " + ToStringer::ToString(expectedArray[0]),
"  Actual: " + ToStringer::ToString(actualArray[0]),
" Message: \"i=0\"",
"File.cpp(1)",
"File.cpp(1)"));
   #endif
   }

   TEST(ElementsAreNotDefaultValuesAndAreNotEqualAtIndex1_ThrowsAnomaly)
   {
      const T randomElement1 = ZenUnit::Random<T>();
      const T randomElement2 = ZenUnit::Random<T>();
      const T randomElement3 = ZenUnit::RandomNotEqualToValue<T>(randomElement2);
      const array<T, 2> expectedArray = { randomElement1, randomElement2 };
      const array<T, 2> actualArray = { randomElement1, randomElement3 };
      //
#if defined __linux__ || defined __APPLE____linux__
      THROWS_EXCEPTION(STD_ARRAYS_ARE_EQUAL(expectedArray, actualArray), Anomaly, TestUtil::NewlineConcat("",
"  Failed: STD_ARRAYS_ARE_EQUAL(expectedArray, actualArray)",
"Expected: <std::array<" + TypeName + ", 2ul>>",
"  Actual: <std::array<" + TypeName + ", 2ul>>",
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
"Expected: " + ToStringer::ToString(expectedArray[1]),
"  Actual: " + ToStringer::ToString(actualArray[1]),
" Message: \"i=1\"",
"File.cpp(1)",
"File.cpp(1)"));
#elif defined __APPLE__
      THROWS_EXCEPTION(STD_ARRAYS_ARE_EQUAL(expectedArray, actualArray), Anomaly, TestUtil::NewlineConcat("",
"  Failed: STD_ARRAYS_ARE_EQUAL(expectedArray, actualArray)",
"Expected: <std::__1::array<" + TypeName + ", 2ul>>",
"  Actual: <std::__1::array<" + TypeName + ", 2ul>>",
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
"Expected: " + ToStringer::ToString(expectedArray[1]),
"  Actual: " + ToStringer::ToString(actualArray[1]),
" Message: \"i=1\"",
"File.cpp(1)",
"File.cpp(1)"));
#elif defined _WIN32
      THROWS_EXCEPTION(STD_ARRAYS_ARE_EQUAL(expectedArray, actualArray), Anomaly, TestUtil::NewlineConcat("",
"  Failed: STD_ARRAYS_ARE_EQUAL(expectedArray, actualArray)",
"Expected: <std::array<" + TypeName + ",2>>",
"  Actual: <std::array<" + TypeName + ",2>>",
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
"Expected: " + ToStringer::ToString(expectedArray[1]),
"  Actual: " + ToStringer::ToString(actualArray[1]),
" Message: \"i=1\"",
"File.cpp(1)",
"File.cpp(1)"));
   #endif
   }

   TEST(ElementsAreNotDefaultValuesAndBothAreEqual_DoesNotThrowException)
   {
      const T randomElement1 = ZenUnit::Random<T>();
      const T randomElement2 = ZenUnit::Random<T>();
      const array<T, 2> expectedArray = { { randomElement1, randomElement2 } };
      const array<T, 2> actualArray = { { randomElement1, randomElement2 } };
      STD_ARRAYS_ARE_EQUAL(expectedArray, actualArray);
   }

   RUN_TEMPLATE_TESTS(STD_ARRAYS_ARE_EQUALTests_Size2Arrays, int)
   THEN_RUN_TEMPLATE_TESTS(STD_ARRAYS_ARE_EQUALTests_Size2Arrays, size_t)
   THEN_RUN_TEMPLATE_TESTS(STD_ARRAYS_ARE_EQUALTests_Size2Arrays, string)
}
