#include "pch.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomTestNameFilter.h"
#include "ZenUnitTestUtils/Equalizers/TestNameFilterEqualizer.h"

TESTS(RandomTestNameFilterTests)
AFACT(RandomTestNameFilter_CodeCoverage)
AFACT(TestableRandomTestNameFilter_ReturnsTestNameFilterWithAllRandomFields)
EVIDENCE

TEST(RandomTestNameFilter_CodeCoverage)
{
   const TestNameFilter randomTestNameFilter = ZenUnit::Random<TestNameFilter>();
}

TEST(TestableRandomTestNameFilter_ReturnsTestNameFilterWithAllRandomFields)
{
   ZenUnit::RandomGeneratorMock randomGeneratorMock;

   const string testClassNamePattern = ZenUnit::Random<string>();
   const string testNamePattern = ZenUnit::Random<string>();
   randomGeneratorMock.StringMock.ReturnValues(testClassNamePattern, testNamePattern);

   const size_t testCaseNumber = randomGeneratorMock.SizeTMock.ReturnRandom();
   //
   const TestNameFilter randomTestNameFilter = TestableRandomTestNameFilter(randomGeneratorMock);
   //
   METALMOCK(randomGeneratorMock.StringMock.CalledNTimes(2));
   METALMOCK(randomGeneratorMock.SizeTMock.CalledOnce());
   TestNameFilter expectedRandomTestNameFilter;
   expectedRandomTestNameFilter.testClassNamePattern = testClassNamePattern;
   expectedRandomTestNameFilter.testNamePattern = testNamePattern;
   expectedRandomTestNameFilter.testCaseNumber = testCaseNumber;
   ARE_EQUAL(expectedRandomTestNameFilter, randomTestNameFilter);
}

RUN_TESTS(RandomTestNameFilterTests)
