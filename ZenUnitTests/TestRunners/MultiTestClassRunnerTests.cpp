#include "pch.h"
#include "ZenUnit/TestRunners/MultiTestClassRunner.h"
#include "ZenUnitTests/TestRunners/Mock/TestClassRunnerMock.h"
#include "ZenUnitTests/Utils/Iteration/Mock/TransformerMock.h"
#include "ZenUnitTests/Utils/Mock/SorterMock.h"

namespace ZenUnit
{
   TESTS(MultiTestClassRunnerTests)
   FACT(Constructor_NewsComponents)
   FACT(NumberOfTestCases_ReturnsSumOfAllTestClassNumberOfTests)
   FACT(AddTestClassRunner_EmplacesBackTestClassRunner_MakesNumberOfTestClassesReturnAnIncreasingNumber)
   FACTS(RunTestClasses_SortsTestClassRunnersByName_RunsTestClassesRandomlyIfRandomOtherwiseSequentially_MoveReturnsTestClassResultsVector)
   FACT(RunTestClassRunner_ReturnsCallToTestClassRunnerRunTests)
   EVIDENCE

   MultiTestClassRunner _multiTestClassRunner;
   SorterMock<std::vector<std::unique_ptr<TestClassRunner>>>* _sorterMock;
   using TransformerMockType = TransformerMock<std::unique_ptr<TestClassRunner>, TestClassResult>;
   TransformerMockType* _transformerMock;

   STARTUP
   {
      _multiTestClassRunner._sorter.reset(_sorterMock
         = new SorterMock<std::vector<std::unique_ptr<TestClassRunner>>>);
      _multiTestClassRunner._transformer.reset(_transformerMock = new TransformerMockType);
   }

   TEST(Constructor_NewsComponents)
   {
      POINTER_WAS_NEWED(_multiTestClassRunner._sorter);
      POINTER_WAS_NEWED(_multiTestClassRunner._transformer);
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

   TEST(NumberOfTestCases_ReturnsSumOfAllTestClassNumberOfTests)
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
      const size_t totalNumberOfTestCases = _multiTestClassRunner.NumberOfTestCases();
      //
      ZEN(testClassRunnerAMock->NumberOfTestCasesMock.AssertCalledOnce());
      ZEN(testClassRunnerBMock->NumberOfTestCasesMock.AssertCalledOnce());
      ZEN(testClassRunnerCMock->NumberOfTestCasesMock.AssertCalledOnce());
      ARE_EQUAL(30, totalNumberOfTestCases);
   }

   TEST2X2(RunTestClasses_SortsTestClassRunnersByName_RunsTestClassesRandomlyIfRandomOtherwiseSequentially_MoveReturnsTestClassResultsVector,
      bool random, bool expectRandomTestClassRun,
      false, false,
      true, true)
   {
      ARE_EQUAL(0, _multiTestClassRunner._testClassResults.size());
      const size_t TestClassRunnersSize = 10;
      _multiTestClassRunner._testClassRunners.resize(TestClassRunnersSize);
      _sorterMock->SortMock.Expect();
      if (expectRandomTestClassRun)
      {
         _transformerMock->RandomTransformMock.Expect();
      }
      else
      {
         _transformerMock->TransformMock.Expect();
      }
      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.random = random;
      zenUnitArgs.randomseed = Random<unsigned short>();
      //
      const vector<TestClassResult> testClassResults = _multiTestClassRunner.RunTestClasses(zenUnitArgs);
      //
      ZEN(_sorterMock->SortMock.AssertCalledOnceWith(&_multiTestClassRunner._testClassRunners));
      if (expectRandomTestClassRun)
      {
         ZEN(_transformerMock->RandomTransformMock.AssertCalledOnceWith(
             &_multiTestClassRunner._testClassRunners,
             &_multiTestClassRunner._testClassResults,
             &MultiTestClassRunner::RunTestClassRunner,
             zenUnitArgs.randomseed));
      }
      else
      {
         ZEN(_transformerMock->TransformMock.AssertCalledOnceWith(
             &_multiTestClassRunner._testClassRunners,
             &_multiTestClassRunner._testClassResults,
             &MultiTestClassRunner::RunTestClassRunner));
      }
      const vector<TestClassResult> expectedTestClassResults(TestClassRunnersSize);
      VECTORS_EQUAL(expectedTestClassResults, testClassResults);
      ARE_EQUAL(0, _multiTestClassRunner._testClassResults.size());
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

   }; RUNTESTS(MultiTestClassRunnerTests)
}
