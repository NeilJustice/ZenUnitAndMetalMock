#include "pch.h"
#include "ZenUnitLibraryTests/Components/Tests/MetalMock/TestMock.h"

TESTS(TestCasesAccumulatorTests)
AFACT(SumNumberOfTestCases_TestsAreEmpty_Returns0)
AFACT(SumNumberOfTestCases_TestsAreSize2_ReturnsSumOfNumberOfTestCases)
EVIDENCE

TestCasesAccumulator _testCasesAccumulator;

TEST(SumNumberOfTestCases_TestsAreEmpty_Returns0)
{
   const std::vector<std::unique_ptr<Test>> emptyTests;
   //
   const size_t numberOfTestCases = _testCasesAccumulator.SumNumberOfTestCases(&emptyTests);
   //
   IS_ZERO(numberOfTestCases);
}

TEST(SumNumberOfTestCases_TestsAreSize2_ReturnsSumOfNumberOfTestCases)
{
   TestMock* testMock1 = new TestMock;
   const size_t numberOfTestCases1 = ZenUnit::RandomBetween<size_t>(1, 3);
   testMock1->NumberOfTestCasesMock.Return(numberOfTestCases1);

   TestMock* testMock2 = new TestMock;
   const size_t numberOfTestCases2 = ZenUnit::RandomBetween<size_t>(1, 3);
   testMock2->NumberOfTestCasesMock.Return(numberOfTestCases2);

   std::vector<std::unique_ptr<Test>> tests;
   tests.emplace_back(testMock1);
   tests.emplace_back(testMock2);
   //
   const size_t numberOfTestCases = _testCasesAccumulator.SumNumberOfTestCases(&tests);
   //
   METALMOCK(testMock1->NumberOfTestCasesMock.CalledOnce());
   METALMOCK(testMock2->NumberOfTestCasesMock.CalledOnce());
   const size_t expectedNumberOfTestCases = numberOfTestCases1 + numberOfTestCases2;
   ARE_EQUAL(expectedNumberOfTestCases, numberOfTestCases);
}

RUN_TESTS(TestCasesAccumulatorTests)
