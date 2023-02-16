#include "pch.h"

template<
   template<typename...>
   typename IndexableType,
   typename T>
TEMPLATE_TESTS(INDEXABLES_ARE_EQUALTests, IndexableType, T)
AFACT(ExpectedAndActualElementsAreBothEmpty_DoesNothing)
AFACT(ExpectedAndActualElementsHaveDifferentSizes_ThrowsAnomaly__TestCaseExpectedSize0ActualSize1)
AFACT(ExpectedAndActualElementsHaveDifferentSizes_ThrowsAnomaly__TestCaseExpectedSize1ActualSize0)
AFACT(ExpectedAndActualElementsHaveTheSameSizes_ElementsAreEqualAndInTheSameOrder_DoesNothing)
AFACT(ExpectedAndActualElementsHaveTheSameSizes_ElementsAreNotEqual_ThrowsAnomaly__TestCase1stElementNotEqual)
AFACT(ExpectedAndActualElementsHaveTheSameSizes_ElementsAreNotEqual_ThrowsAnomaly__TestCase2ndElementNotEqual)
AFACT(ExpectedAndActualElementsHaveTheSameSizes_ElementsAreEqual_DoesNothing)
EVIDENCE

TEST(ExpectedAndActualElementsAreBothEmpty_DoesNothing)
{
   const IndexableType<T> expectedElements;
   const IndexableType<T> actualEmptyElements;
   INDEXABLES_ARE_EQUAL(expectedElements, actualEmptyElements);
}

TEST(ExpectedAndActualElementsHaveDifferentSizes_ThrowsAnomaly__TestCaseExpectedSize0ActualSize1)
{
   const IndexableType<T> expectedElements;
   const IndexableType<T> actualElements = { ZenUnit::Random<T>() };
   THROWS_EXCEPTION(INDEXABLES_ARE_EQUAL(expectedElements, actualElements), ZenUnit::Anomaly,
      R"(
  Failed: INDEXABLES_ARE_EQUAL(expectedElements, actualElements)
Expected: std::vector<int,std::allocator<int> > (size 0):
{
}
  Actual: std::vector<int,std::allocator<int> > (size 1):
{
   )" + to_string(actualElements[0]) + R"(
}
 Because: ARE_EQUAL(expectedIndexable.size(), actualIndexable.size()) failed
Expected: 0
  Actual: 1
File.cpp(1)
File.cpp(1))");
}

TEST(ExpectedAndActualElementsHaveDifferentSizes_ThrowsAnomaly__TestCaseExpectedSize1ActualSize0)
{
   const IndexableType<T> expectedElements = { ZenUnit::Random<T>() };
   const IndexableType<T> actualElements;
   THROWS_EXCEPTION(INDEXABLES_ARE_EQUAL(expectedElements, actualElements), ZenUnit::Anomaly,
      R"(
  Failed: INDEXABLES_ARE_EQUAL(expectedElements, actualElements)
Expected: std::vector<int,std::allocator<int> > (size 1):
{
   )" + to_string(expectedElements[0]) + R"(
}
  Actual: std::vector<int,std::allocator<int> > (size 0):
{
}
 Because: ARE_EQUAL(expectedIndexable.size(), actualIndexable.size()) failed
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
   INDEXABLES_ARE_EQUAL(expectedElements, actualElements);
}

TEST(ExpectedAndActualElementsHaveTheSameSizes_ElementsAreNotEqual_ThrowsAnomaly__TestCase1stElementNotEqual)
{
   const T element1 = ZenUnit::Random<T>();
   const T element2 = ZenUnit::RandomNotEqualTo<T>(element1);
   const IndexableType<T> expectedElements = { element1 };
   const IndexableType<T> actualElements = { element2 };
   THROWS_EXCEPTION(INDEXABLES_ARE_EQUAL(expectedElements, actualElements), ZenUnit::Anomaly,
   R"(
  Failed: INDEXABLES_ARE_EQUAL(expectedElements, actualElements)
Expected: std::vector<int,std::allocator<int> > (size 1):
{
   )" + to_string(element1) + R"(
}
  Actual: std::vector<int,std::allocator<int> > (size 1):
{
   )" + to_string(element2) + R"(
}
 Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed
Expected: )" + to_string(element1) + R"(
  Actual: )" + to_string(element2) + R"(
 Message: "i=0"
File.cpp(1)
File.cpp(1))");
}

TEST(ExpectedAndActualElementsHaveTheSameSizes_ElementsAreNotEqual_ThrowsAnomaly__TestCase2ndElementNotEqual)
{
   const T element1 = ZenUnit::Random<T>();
   const T element2 = ZenUnit::RandomNotEqualTo<T>(element1);
   const IndexableType<T> expectedElements = { element1, element1 };
   const IndexableType<T> actualElements = { element1, element2 };
   THROWS_EXCEPTION(INDEXABLES_ARE_EQUAL(expectedElements, actualElements), ZenUnit::Anomaly,
   R"(
  Failed: INDEXABLES_ARE_EQUAL(expectedElements, actualElements)
Expected: std::vector<int,std::allocator<int> > (size 2):
{
   )" + to_string(element1) + R"(,
   )" + to_string(element1) + R"(
}
  Actual: std::vector<int,std::allocator<int> > (size 2):
{
   )" + to_string(element1) + R"(,
   )" + to_string(element2) + R"(
}
 Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed
Expected: )" + to_string(element1) + R"(
  Actual: )" + to_string(element2) + R"(
 Message: "i=1"
File.cpp(1)
File.cpp(1))");
}

TEST(ExpectedAndActualElementsHaveTheSameSizes_ElementsAreEqual_DoesNothing)
{
   const T element1 = ZenUnit::Random<T>();
   const IndexableType<T> expectedElements = { element1, element1 };
   const IndexableType<T> actualElements = { element1, element1 };
   INDEXABLES_ARE_EQUAL(expectedElements, actualElements);
}

RUN_TEMPLATE_TESTS(INDEXABLES_ARE_EQUALTests, vector, int)
