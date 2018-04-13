#include "pch.h"
#include "ZenUnitTests/Args/Mock/RunFilterMock.h"
#include "ZenUnitTests/TestRunners/Mock/TestClassRunnerMock.h"

namespace ZenUnit
{
   class TestingTestClassRunner : public TestClassRunner
   {
      const char* TestClassName() const override { return nullptr; }
      size_t NumberOfTestCases() const override { return 0; }
      TestClassResult RunTests() override { return TestClassResult(); }
      bool HasTestThatMatchesRunFilter(const RunFilter&) const override { return false; }
   };

   TESTS(TestClassRunnerTests)
   AFACT(DefaultConstructor_NewsComponents)
   AFACT(RunFilterMatchesTestName_ReturnsTrueIfRunFilterMatchesTestName)
   FACTS(OperatorLessThan_ReturnsTrueIfTestClassNameStrcmpResultIsLessThanZero)
   EVIDENCE

   TestingTestClassRunner _testingTestClassRunner;

   TEST(DefaultConstructor_NewsComponents)
   {
      TestingTestClassRunner testingTestClassRunner;
      POINTER_WAS_NEWED(testingTestClassRunner.p_console);
      POINTER_WAS_NEWED(testingTestClassRunner.p_twoArgMemberAnyer);
   }

   TEST(RunFilterMatchesTestName_ReturnsTrueIfRunFilterMatchesTestName)
   {
      RunFilterMock runFilterMock;
      const bool runFilterMatchesTestName = runFilterMock.MatchesTestNameMock.ReturnRandom();
      const string testName = ZenUnit::Random<string>();
      //
      bool returnedRunFilterMatchesTestName = _testingTestClassRunner.RunFilterMatchesTestName(runFilterMock, testName.c_str());
      //
      ZEN(runFilterMock.MatchesTestNameMock.CalledOnceWith(testName.c_str()));
      ARE_EQUAL(runFilterMatchesTestName, returnedRunFilterMatchesTestName);
   }

   TEST3X3(OperatorLessThan_ReturnsTrueIfTestClassNameStrcmpResultIsLessThanZero,
      bool expectedIsLessThan, const char* leftTestClassName, const char* rightTestClassName,
      false, "", "",
      false, "b", "a",
      true, "a", "b",
      true, "WidgetATests", "WidgetBTests",
      false, "WidgetATests", "WidgetATests",
      false, "WidgetBTests", "WidgetATests",
      true, "widgetATests", "WidgetBTests",
      true, "assert_trueTests", "VectorTests",
      false, "is_quoted_when_printedTests", "ConsoleColorerTests")
   {
      TestClassRunnerMock* leftTestClassRunnerMock = new TestClassRunnerMock;
      TestClassRunnerMock* rightTestClassRunnerMock = new TestClassRunnerMock;
      leftTestClassRunnerMock->TestClassNameMock.Return(leftTestClassName);
      rightTestClassRunnerMock->TestClassNameMock.Return(rightTestClassName);
      const unique_ptr<TestClassRunner> leftTestClassRunner(leftTestClassRunnerMock);
      const unique_ptr<TestClassRunner> rightTestClassRunner(rightTestClassRunnerMock);
      //
      const bool isLessThan = leftTestClassRunner < rightTestClassRunner;
      //
      ZEN(leftTestClassRunnerMock->TestClassNameMock.CalledOnce());
      ZEN(rightTestClassRunnerMock->TestClassNameMock.CalledOnce());
      ARE_EQUAL(expectedIsLessThan, isLessThan);
   }

   RUN_TESTS(TestClassRunnerTests)
}
