#include "pch.h"

namespace ZenUnit
{
   template<typename T>
   TEMPLATE_TESTS(ARRAYS_ARE_EQUALTests, T)
   AFACT(NumberOfElementsToCompareIs0_DoesNotThrowException)
   AFACT(NumberOfElementsToCompareIs1_FirstElementsAreEqual_DoesNotThrowException)
   AFACT(NumberOfElementsToCompareIs1_FirstElementsAreNotEqual_ThrowsAnomaly)
   AFACT(NumberOfElementsToCompareIs2_FirstElementsAreEqual_SecondElementsAreEqual_DoesNotThrowException)
   AFACT(NumberOfElementsToCompareIs2_FirstElementsAreEqual_SecondElementsAreNotEqual_ThrowsAnomaly)
   EVIDENCE

   TEST(NumberOfElementsToCompareIs0_DoesNotThrowException)
   {
      const T expectedArray[1] { ZenUnit::Random<T>() };
      const T actualArray[1] { ZenUnit::Random<T>() };
      //
      ARRAYS_ARE_EQUAL(expectedArray, actualArray, 0);
   }

   TEST(NumberOfElementsToCompareIs1_FirstElementsAreEqual_DoesNotThrowException)
   {
      const T expectedArray[1] { ZenUnit::Random<T>() };
      const T actualArray[1] { expectedArray[0] };
      //
      ARRAYS_ARE_EQUAL(expectedArray, actualArray, 1);
   }

   TEST(NumberOfElementsToCompareIs1_FirstElementsAreNotEqual_ThrowsAnomaly)
   {
      const string typeName = *Type::GetName<T>();
      const T randomElement1 = ZenUnit::Random<T>();
      const T randomElement2 = ZenUnit::RandomNotEqualToValue<T>(randomElement1);
      const T expectedArray[1] { randomElement1 };
      const T actualArray[1] { randomElement2 };
      //
      const string expectedExceptionMessage = TestUtil::NewlineConcat("",
         "  Failed: ARRAYS_ARE_EQUAL(expectedArray, actualArray, 1)",
         "Expected: " + typeName + " [1]",
         "  Actual: " + typeName + " [1]",
         " Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
         "Expected: " + ToStringer::ToString(expectedArray[0]),
         "  Actual: " + ToStringer::ToString(actualArray[0]),
         " Message: \"i=0\"",
         "File.cpp(1)",
         "File.cpp(1)");
      THROWS_EXCEPTION(ARRAYS_ARE_EQUAL(expectedArray, actualArray, 1),
         Anomaly, expectedExceptionMessage);
   }

   TEST(NumberOfElementsToCompareIs2_FirstElementsAreEqual_SecondElementsAreEqual_DoesNotThrowException)
   {
      const T expectedArray[2] { ZenUnit::Random<T>(), ZenUnit::Random<T>() };
      const T actualArray[2] { expectedArray[0], expectedArray[1] };
      //
      ARRAYS_ARE_EQUAL(expectedArray, actualArray, 2);
   }

   TEST(NumberOfElementsToCompareIs2_FirstElementsAreEqual_SecondElementsAreNotEqual_ThrowsAnomaly)
   {
      const string typeName = *Type::GetName<T>();
      const T randomElement1 = ZenUnit::Random<T>();
      const T randomElement2 = ZenUnit::RandomNotEqualToValue<T>(randomElement1);
      const T expectedArray[2] { randomElement1, randomElement1 };
      const T actualArray[2] { randomElement1, randomElement2 };
      //
      const string expectedExceptionMessage = TestUtil::NewlineConcat("",
         "  Failed: ARRAYS_ARE_EQUAL(expectedArray, actualArray, 2)",
         "Expected: " + typeName + " [2]",
         "  Actual: " + typeName + " [2]",
         " Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
         "Expected: " + ToStringer::ToString(expectedArray[1]),
         "  Actual: " + ToStringer::ToString(actualArray[1]),
         " Message: \"i=1\"",
         "File.cpp(1)",
         "File.cpp(1)");
      THROWS_EXCEPTION(ARRAYS_ARE_EQUAL(expectedArray, actualArray, 2),
         Anomaly, expectedExceptionMessage);
   }

   RUN_TEMPLATE_TESTS(ARRAYS_ARE_EQUALTests, int)
   THEN_RUN_TEMPLATE_TESTS(ARRAYS_ARE_EQUALTests, unsigned)
   THEN_RUN_TEMPLATE_TESTS(ARRAYS_ARE_EQUALTests, unsigned long long)


   TESTS(NonConstCharARRAYS_ARE_EQUALTests)
   AFACT(NonConstCharArraysAreEqual_Returns)
   EVIDENCE

   TEST(NonConstCharArraysAreEqual_Returns)
   {
      char expectedNonConstCharArray[2]{ ZenUnit::Random<char>(), ZenUnit::Random<char>() };
      char actualNonConstCharArray[2]{ ZenUnit::Random<char>(), ZenUnit::Random<char>() };
      //
      ARRAYS_ARE_EQUAL(expectedNonConstCharArray, actualNonConstCharArray, 0);
   }

   RUN_TESTS(NonConstCharARRAYS_ARE_EQUALTests)
}
