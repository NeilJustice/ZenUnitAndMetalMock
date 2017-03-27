#include "pch.h"
#include "ZenUnit/TestRunners/MultiTestClassRunner.h"
#include "Utils/Iteration/Mock/TransformerMock.h"
#include "TestRunners/Mock/TestClassRunnerMock.h"
#include "Utils/Mock/SorterMock.h"

namespace ZenUnit
{
   TESTS(MultiTestClassRunnerTests)
   SPEC(Constructor_NewsComponents)
   SPEC(TotalNumberOfTestCases_ReturnsSumOfAllTestClassNumberOfTests)
   SPEC(AddTestClassRunner_EmplacesBackTestClassRunner_MakesNumberOfTestClassesReturnAnIncreasingNumber)
   SPEC(RunTestClasses_SortsTestClassRunnersByName_RunsTestClasses_ReturnsTestClassResultsVector)
   SPEC(RunTestClassRunner_ReturnsCallToTestClassRunnerRunTests)
   SPECEND

   MultiTestClassRunner _multiTestClassRunner;

   using TypdefTransformerMock = TransformerMock<
      vector<unique_ptr<TestClassRunner>>::const_iterator,
      std::vector<TestClassResult>,
      TestClassResult (*)(const unique_ptr<TestClassRunner>&)>;
   SorterMock<std::vector<std::unique_ptr<TestClassRunner>>>* _sorterMock;
   TypdefTransformerMock* _transformerMock;

   STARTUP
   {
      _multiTestClassRunner._sorter.reset(_sorterMock = new SorterMock<std::vector<std::unique_ptr<TestClassRunner>>>);
      _multiTestClassRunner._transformer.reset(_transformerMock = new TypdefTransformerMock);
   }

   TEST(Constructor_NewsComponents)
   {
      WAS_NEWED(_multiTestClassRunner._sorter);
      WAS_NEWED(_multiTestClassRunner._transformer);
      IS_EMPTY(_multiTestClassRunner._testClassRunners);
      IS_EMPTY(_multiTestClassRunner._testClassResults);
   }

   TEST(AddTestClassRunner_EmplacesBackTestClassRunner_MakesNumberOfTestClassesReturnAnIncreasingNumber)
   {
      ARE_EQUAL(0, _multiTestClassRunner.NumberOfTestClasses());
      TestClassRunnerMock* testClassRunnerA = new TestClassRunnerMock;
      //
      _multiTestClassRunner.AddTestClassRunner(testClassRunnerA);
      //
      ARE_EQUAL(1, _multiTestClassRunner._testClassRunners.size());
      ARE_EQUAL(testClassRunnerA, _multiTestClassRunner._testClassRunners[0].get());
      ARE_EQUAL(1, _multiTestClassRunner.NumberOfTestClasses());

      TestClassRunnerMock* testClassRunnerB = new TestClassRunnerMock;
      //
      _multiTestClassRunner.AddTestClassRunner(testClassRunnerB);
      //
      ARE_EQUAL(2, _multiTestClassRunner._testClassRunners.size());
      ARE_EQUAL(testClassRunnerA, _multiTestClassRunner._testClassRunners[0].get());
      ARE_EQUAL(testClassRunnerB, _multiTestClassRunner._testClassRunners[1].get());
      ARE_EQUAL(2, _multiTestClassRunner.NumberOfTestClasses());
   }

   TEST(TotalNumberOfTestCases_ReturnsSumOfAllTestClassNumberOfTests)
   {
      TestClassRunnerMock* testClassRunnerAMock = new TestClassRunnerMock;
      TestClassRunnerMock* testClassRunnerBMock = new TestClassRunnerMock;
      TestClassRunnerMock* testClassRunnerCMock = new TestClassRunnerMock;
      testClassRunnerAMock->NumberOfTestCasesMock.ExpectAndReturn(10);
      testClassRunnerBMock->NumberOfTestCasesMock.ExpectAndReturn(0);
      testClassRunnerCMock->NumberOfTestCasesMock.ExpectAndReturn(20);
      _multiTestClassRunner.AddTestClassRunner(testClassRunnerAMock);
      _multiTestClassRunner.AddTestClassRunner(testClassRunnerBMock);
      _multiTestClassRunner.AddTestClassRunner(testClassRunnerCMock);
      //
      const size_t totalNumberOfTestCases = _multiTestClassRunner.TotalNumberOfTestCases();
      //
      ZEN(testClassRunnerAMock->NumberOfTestCasesMock.AssertCalledOnce());
      ZEN(testClassRunnerBMock->NumberOfTestCasesMock.AssertCalledOnce());
      ZEN(testClassRunnerCMock->NumberOfTestCasesMock.AssertCalledOnce());
      ARE_EQUAL(30, totalNumberOfTestCases);
   }

   TEST(RunTestClasses_SortsTestClassRunnersByName_RunsTestClasses_ReturnsTestClassResultsVector)
   {
      ARE_EQUAL(0, _multiTestClassRunner._testClassResults.size());
      const size_t TestClassRunnersSize = 10;
      _multiTestClassRunner._testClassRunners.resize(TestClassRunnersSize);
      _sorterMock->SortMock.Expect();
      _transformerMock->TransformMock.Expect();
      //
      const vector<TestClassResult> testClassResults = _multiTestClassRunner.RunTestClasses();
      //
      ZEN(_sorterMock->SortMock.AssertCalledOnceWith(&_multiTestClassRunner._testClassRunners));
      ZEN(_transformerMock->TransformMock.AssertCalledOnceWith(
         _multiTestClassRunner._testClassRunners.cbegin(), _multiTestClassRunner._testClassRunners.cend(),
         &_multiTestClassRunner._testClassResults, &MultiTestClassRunner::RunTestClassRunner));
      const vector<TestClassResult> expectedTestClassResults(TestClassRunnersSize);
      VECTORS_EQUAL(expectedTestClassResults, testClassResults);
   }

   TEST(RunTestClassRunner_ReturnsCallToTestClassRunnerRunTests)
   {
      TestClassRunnerMock* testClassRunnerMock = new TestClassRunnerMock;
      testClassRunnerMock->RunTestsMock.ExpectAndReturn(TestClassResult::TestingNonDefault());
      const unique_ptr<TestClassRunner> testClassRunnerReallyAMock(testClassRunnerMock);
      //
      const TestClassResult testClassResult = MultiTestClassRunner::RunTestClassRunner(testClassRunnerReallyAMock);
      //
      ZEN(testClassRunnerMock->RunTestsMock.AssertCalledOnce());
      ARE_EQUAL(TestClassResult::TestingNonDefault(), testClassResult);
   }

   }; RUN(MultiTestClassRunnerTests)
}
