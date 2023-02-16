#include "pch.h"

template<
   template<typename...>
   typename IndexableType, typename T>
TEMPLATE_TESTS(INDEXABLES_ARE_EQUAL_IN_ANY_ORDERTests, IndexableType, T)
AFACT(ExpectedAndActualElementsAreBothEmpty_DoesNothing)
AFACT(ExpectedAndActualElementsHaveDifferentSizes_ThrowsAnomaly__TestCaseExpectedSize0ActualSize1)
AFACT(ExpectedAndActualElementsHaveDifferentSizes_ThrowsAnomaly__TestCaseExpectedSize1ActualSize0)
AFACT(ExpectedAndActualElementsHaveTheSameSizes_ElementsAreEqualAndInTheSameOrder_DoesNothing)
AFACT(ExpectedAndActualElementsHaveTheSameSizes_ElementsAreEqualAndInDifferentOrder_DoesNothing)
AFACT(ExpectedAndActualElementsHaveTheSameSizes_ElementsAreNotEqual_ThrowsAnomaly__TestCase1stElementNotEqual)
AFACT(ExpectedAndActualElementsHaveTheSameSizes_ElementsAreNotEqual_ThrowsAnomaly__TestCase2ndElementNotEqual)
AFACT(ExpectedAndActualElementsHaveTheSameSizes_AllExpectedElementsAreContainedInActualElements_ActualElementsContainsElementsNotContainedInExpectedElements_ThrowsAnomaly)
EVIDENCE

TEST(ExpectedAndActualElementsAreBothEmpty_DoesNothing)
{
   const IndexableType<T> expectedElements;
   const IndexableType<T> actualElements;
   INDEXABLES_ARE_EQUAL_IN_ANY_ORDER(expectedElements, actualElements);
}

TEST(ExpectedAndActualElementsHaveDifferentSizes_ThrowsAnomaly__TestCaseExpectedSize0ActualSize1)
{
   const IndexableType<T> expectedElements;
   const IndexableType<T> actualElements = { ZenUnit::Random<T>() };
   THROWS_EXCEPTION(INDEXABLES_ARE_EQUAL_IN_ANY_ORDER(expectedElements, actualElements), ZenUnit::Anomaly,
      R"(
  Failed: INDEXABLES_ARE_EQUAL_IN_ANY_ORDER(expectedElements, actualElements)
Expected: expectedElements.size() == actualElements.size()
  Actual: expectedElements.size() != actualElements.size()
 Because: ARE_EQUAL(expectedElements.size(), actualElements.size()) failed
Expected: 0
  Actual: 1
File.cpp(1)
File.cpp(1))");
}

TEST(ExpectedAndActualElementsHaveDifferentSizes_ThrowsAnomaly__TestCaseExpectedSize1ActualSize0)
{
   const IndexableType<T> expectedElements = { ZenUnit::Random<T>() };
   const IndexableType<T> actualElements;
   THROWS_EXCEPTION(INDEXABLES_ARE_EQUAL_IN_ANY_ORDER(expectedElements, actualElements), ZenUnit::Anomaly,
      R"(
  Failed: INDEXABLES_ARE_EQUAL_IN_ANY_ORDER(expectedElements, actualElements)
Expected: expectedElements.size() == actualElements.size()
  Actual: expectedElements.size() != actualElements.size()
 Because: ARE_EQUAL(expectedElements.size(), actualElements.size()) failed
Expected: 1
  Actual: 0
File.cpp(1)
File.cpp(1))");
}

TEST(ExpectedAndActualElementsHaveTheSameSizes_ElementsAreEqualAndInTheSameOrder_DoesNothing)
{
   const T randomElement1 = ZenUnit::Random<T>();
   const T randomElement2 = ZenUnit::Random<T>();
   const IndexableType<T> expectedElements = { randomElement1, randomElement2 };
   const IndexableType<T> actualElements = { randomElement1, randomElement2 };
   INDEXABLES_ARE_EQUAL_IN_ANY_ORDER(expectedElements, actualElements);
}

TEST(ExpectedAndActualElementsHaveTheSameSizes_ElementsAreEqualAndInDifferentOrder_DoesNothing)
{
   const T randomElement1 = ZenUnit::Random<T>();
   const T randomElement2 = ZenUnit::Random<T>();
   const IndexableType<T> expectedElements = { randomElement1, randomElement2 };
   const IndexableType<T> actualElements = { randomElement2, randomElement1 };
   INDEXABLES_ARE_EQUAL_IN_ANY_ORDER(expectedElements, actualElements);
}

TEST(ExpectedAndActualElementsHaveTheSameSizes_ElementsAreNotEqual_ThrowsAnomaly__TestCase1stElementNotEqual)
{
   const T element1 = ZenUnit::Random<T>();
   const T element2 = ZenUnit::RandomNotEqualTo<T>(element1);
   const IndexableType<T> expectedElements = { element1 };
   const IndexableType<T> actualElements = { element2 };
   THROWS_EXCEPTION(INDEXABLES_ARE_EQUAL_IN_ANY_ORDER(expectedElements, actualElements), ZenUnit::Anomaly,
      R"(
  Failed: INDEXABLES_ARE_EQUAL_IN_ANY_ORDER(expectedElements, actualElements)
Expected:      To find ith expected element [)" + ZenUnit::ToStringer::ToString(element1) + R"(] in actualElements (i=0)
  Actual: Did not find ith expected element [)" + ZenUnit::ToStringer::ToString(element1) + R"(] in actualElements (i=0)
File.cpp(1))");
}

TEST(ExpectedAndActualElementsHaveTheSameSizes_ElementsAreNotEqual_ThrowsAnomaly__TestCase2ndElementNotEqual)
{
   const T element1 = ZenUnit::Random<T>();
   const T element2 = ZenUnit::RandomNotEqualTo<T>(element1);
   const IndexableType<T> expectedElements = { element1, element2 };
   const IndexableType<T> actualElements = { element1, element1 };
   THROWS_EXCEPTION(INDEXABLES_ARE_EQUAL_IN_ANY_ORDER(expectedElements, actualElements), ZenUnit::Anomaly,
      R"(
  Failed: INDEXABLES_ARE_EQUAL_IN_ANY_ORDER(expectedElements, actualElements)
Expected:      To find ith expected element [)" + ZenUnit::ToStringer::ToString(element2) + R"(] in actualElements (i=1)
  Actual: Did not find ith expected element [)" + ZenUnit::ToStringer::ToString(element2) + R"(] in actualElements (i=1)
File.cpp(1))");
}

TEST(ExpectedAndActualElementsHaveTheSameSizes_AllExpectedElementsAreContainedInActualElements_ActualElementsContainsElementsNotContainedInExpectedElements_ThrowsAnomaly)
{
   const T element1 = ZenUnit::Random<T>();
   const T element2 = ZenUnit::RandomNotEqualTo<T>(element1);
   const IndexableType<T> expectedElements = { element1, element1 };
   const IndexableType<T> actualElements = { element1, element2 };
   THROWS_EXCEPTION(INDEXABLES_ARE_EQUAL_IN_ANY_ORDER(expectedElements, actualElements), ZenUnit::Anomaly,
      R"(
  Failed: INDEXABLES_ARE_EQUAL_IN_ANY_ORDER(expectedElements, actualElements)
Expected:      To find ith actual element [)" + ZenUnit::ToStringer::ToString(element2) + R"(] in expectedElements (i=1)
  Actual: Did not find ith actual element [)" + ZenUnit::ToStringer::ToString(element2) + R"(] in expectedElements (i=1)
File.cpp(1))");
}

RUN_TEMPLATE_TESTS(INDEXABLES_ARE_EQUAL_IN_ANY_ORDERTests, vector, int)
THEN_RUN_TEMPLATE_TESTS(INDEXABLES_ARE_EQUAL_IN_ANY_ORDERTests, deque, string)
