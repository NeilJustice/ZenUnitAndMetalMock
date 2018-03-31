#include "pch.h"

template<typename T>
TEMPLATE_TESTS(STD_ARRAYS_EQUALTests_Size0Arrays, T)
AFACT(TwoSize0Arrays_DoesNotThrow)
EVIDENCE

TEST(TwoSize0Arrays_DoesNotThrow)
{
   array<T, 0> expectedArray;
   array<T, 0> actualArray;
   STD_ARRAYS_EQUAL(expectedArray, actualArray);
}

RUN_TEMPLATE_TESTS(STD_ARRAYS_EQUALTests_Size0Arrays, char)
THEN_RUN_TEMPLATE_TESTS(STD_ARRAYS_EQUALTests_Size0Arrays, int)


template<typename T>
TEMPLATE_TESTS(STD_ARRAYS_EQUALTests_Size1Arrays, T)
AFACT(ElementsAreDefaults_DoesNotThrow)
AFACT(ElementAreNonDefaultAndNotEqual_Throws)
AFACT(ElementAreNonDefaultAndEqual_DoesNotThrow)
EVIDENCE

TEST(ElementsAreDefaults_DoesNotThrow)
{
   array<T, 1> expectedArray;
   array<T, 1> actualArray;
   STD_ARRAYS_EQUAL(expectedArray, actualArray);
}

const string TypeName = *Type::GetName<T>();
const T _randomElement = ZenUnit::Random<T>();
array<T, 1> _expectedArray = { _randomElement };
array<T, 1> _actualArray = { _randomElement + T{ 1 } };

TEST(ElementAreNonDefaultAndNotEqual_Throws)
{
   THROWS(STD_ARRAYS_EQUAL(_expectedArray, _actualArray), Anomaly, R"(
  Failed: STD_ARRAYS_EQUAL(_expectedArray, _actualArray)
Expected: <std::array<)" + TypeName + R"(,1>>
  Actual: <std::array<)" + TypeName + R"(,1>>
 Because: ARE_EQUAL(ithExpectedElement, ithActualElement, iEqualsIndexMessage) failed
Expected: )" + ToStringer::ToString(_expectedArray[0]) + R"(
  Actual: )" + ToStringer::ToString(_actualArray[0]) + R"(
 Message: "i=0"
File.cpp(1)
File.cpp(1))");
}

TEST(ElementAreNonDefaultAndEqual_DoesNotThrow)
{
   const T randomElement = ZenUnit::Random<T>();
   array<T, 1> expectedArray = { randomElement };
   array<T, 1> actualArray = { randomElement };
   STD_ARRAYS_EQUAL(expectedArray, actualArray);
}

RUN_TEMPLATE_TESTS(STD_ARRAYS_EQUALTests_Size1Arrays, char)
THEN_RUN_TEMPLATE_TESTS(STD_ARRAYS_EQUALTests_Size1Arrays, int)


template<typename T>
TEMPLATE_TESTS(STD_ARRAYS_EQUALTests_Size2Arrays, T)
AFACT(ElementsAreDefaults_DoesNotThrow)
AFACT(ElementsAreNonDefaultAndNotEqualAtIndex0_Throws)
AFACT(ElementsAreNonDefaultAndNotEqualAtIndex1_Throws)
AFACT(ElementsAreNonDefaultAndBothEqual_DoesNotThrow)
EVIDENCE

TEST(ElementsAreDefaults_DoesNotThrow)
{
   array<T, 2> expectedArray;
   array<T, 2> actualArray;
   STD_ARRAYS_EQUAL(expectedArray, actualArray);
}

const string TypeName = *Type::GetName<T>();
const T _randomElementA = ZenUnit::Random<T>();
const T _randomElementB = ZenUnit::Random<T>();
array<T, 2> _expectedArray_index0 = { _randomElementA, _randomElementB };
array<T, 2> _actualArray_index0 = { _randomElementA + T{ 1 }, _randomElementB };

TEST(ElementsAreNonDefaultAndNotEqualAtIndex0_Throws)
{
   THROWS(STD_ARRAYS_EQUAL(_expectedArray_index0, _actualArray_index0), Anomaly, R"(
  Failed: STD_ARRAYS_EQUAL(_expectedArray_index0, _actualArray_index0)
Expected: <std::array<)" + TypeName + R"(,2>>
  Actual: <std::array<)" + TypeName + R"(,2>>
 Because: ARE_EQUAL(ithExpectedElement, ithActualElement, iEqualsIndexMessage) failed
Expected: )" + ToStringer::ToString(_expectedArray_index0[0]) + R"(
  Actual: )" + ToStringer::ToString(_actualArray_index0[0]) + R"(
 Message: "i=0"
File.cpp(1)
File.cpp(1))");
}

array<T, 2> _expectedArray_index1 = { _randomElementA, _randomElementB };
array<T, 2> _actualArray_index1 = { _randomElementA, _randomElementB + T{ 1 } };

TEST(ElementsAreNonDefaultAndNotEqualAtIndex1_Throws)
{
   THROWS(STD_ARRAYS_EQUAL(_expectedArray_index1, _actualArray_index1), Anomaly, R"(
  Failed: STD_ARRAYS_EQUAL(_expectedArray_index1, _actualArray_index1)
Expected: <std::array<)" + TypeName + R"(,2>>
  Actual: <std::array<)" + TypeName + R"(,2>>
 Because: ARE_EQUAL(ithExpectedElement, ithActualElement, iEqualsIndexMessage) failed
Expected: )" + ToStringer::ToString(_expectedArray_index1[1]) + R"(
  Actual: )" + ToStringer::ToString(_actualArray_index1[1]) + R"(
 Message: "i=1"
File.cpp(1)
File.cpp(1))");
}

TEST(ElementsAreNonDefaultAndBothEqual_DoesNotThrow)
{
   const T randomElementA = ZenUnit::Random<T>();
   const T randomElementB = ZenUnit::Random<T>();
   array<T, 2> expectedArray = { randomElementA, randomElementB };
   array<T, 2> actualArray = { randomElementA, randomElementB };
   STD_ARRAYS_EQUAL(expectedArray, actualArray);
}

RUN_TEMPLATE_TESTS(STD_ARRAYS_EQUALTests_Size2Arrays, char)
THEN_RUN_TEMPLATE_TESTS(STD_ARRAYS_EQUALTests_Size2Arrays, int)
