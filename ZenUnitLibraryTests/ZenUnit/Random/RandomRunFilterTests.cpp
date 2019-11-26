#include "pch.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomRunFilter.h"
#include "ZenUnitTestUtils/Equalizers/RunFilterEqualizer.h"

TESTS(RandomRunFilterTests)
AFACT(RandomRunFilter_CodeCoverage)
AFACT(TestableRandomRunFilter_ReturnsRunFilterWithAllRandomFields)
EVIDENCE

TEST(RandomRunFilter_CodeCoverage)
{
   const RunFilter randomRunFilter = ZenUnit::Random<RunFilter>();
}

TEST(TestableRandomRunFilter_ReturnsRunFilterWithAllRandomFields)
{
   ZenMock::RandomGeneratorMock randomGeneratorMock;

   const string testClassNamePattern = ZenUnit::Random<string>();
   const string testNamePattern = ZenUnit::Random<string>();
   randomGeneratorMock.StringMock.ReturnValues(testClassNamePattern, testNamePattern);

   const size_t testCaseNumber = randomGeneratorMock.SizeTMock.ReturnRandom();
   //
   const RunFilter randomRunFilter = TestableRandomRunFilter(randomGeneratorMock);
   //
   ZENMOCK(randomGeneratorMock.StringMock.CalledNTimes(2));
   ZENMOCK(randomGeneratorMock.SizeTMock.CalledOnce());
   RunFilter expectedRandomRunFilter;
   expectedRandomRunFilter.testClassNamePattern = testClassNamePattern;
   expectedRandomRunFilter.testNamePattern = testNamePattern;
   expectedRandomRunFilter.testCaseNumber = testCaseNumber;
   ARE_EQUAL(expectedRandomRunFilter, randomRunFilter);
}

RUN_TESTS(RandomRunFilterTests)
