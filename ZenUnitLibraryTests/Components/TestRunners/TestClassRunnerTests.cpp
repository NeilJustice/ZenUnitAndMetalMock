#include "pch.h"
#include "ZenUnitLibraryTests/Components/Args/MetalMock/TestNameFilterMock.h"
#include "ZenUnitLibraryTests/Components/TestRunners/MetalMock/TestClassRunnerMock.h"

namespace ZenUnit
{
   TESTS(TestClassRunnerTests)
   AFACT(DefaultConstructor_NewsConsoleAndNewArgMemberAnyer)
   AFACT(TestClassName_ReturnNullptr)
   AFACT(NumberOfTestCases_Returns0)
   AFACT(HasTestThatMatchesTestNameFilter_ReturnsFalse)
   AFACT(RunTests_ReturnsDefaultTestClassResult)
   AFACT(TestNameFilterMatchesTestName_ReturnsTrueIfTestNameFilterMatchesTestName)
   FACTS(OperatorLessThan_ReturnsTrueIfTestClassNameStrcmpResultIsLessThanZero)
   EVIDENCE

   TestClassRunner _testClassRunner;

   TEST(DefaultConstructor_NewsConsoleAndNewArgMemberAnyer)
   {
      TestClassRunner testClassRunner;
      // Function Callers
      DELETE_TO_ASSERT_NEWED(testClassRunner.p_twoArgMemberAnyer);
      // Constant Components
      DELETE_TO_ASSERT_NEWED(testClassRunner.p_console);
   }

   TEST(TestClassName_ReturnNullptr)
   {
      IS_NULLPTR(_testClassRunner.TestClassName());
   }

   TEST(NumberOfTestCases_Returns0)
   {
      IS_ZERO(_testClassRunner.NumberOfTestCases());
   }

   TEST(HasTestThatMatchesTestNameFilter_ReturnsFalse)
   {
      IS_FALSE(_testClassRunner.HasTestThatMatchesTestNameFilter(ZenUnit::Random<TestNameFilter>()));
   }

   TEST(RunTests_ReturnsDefaultTestClassResult)
   {
      ARE_EQUAL(TestClassResult{}, _testClassRunner.RunTests());
   }

   TEST(TestNameFilterMatchesTestName_ReturnsTrueIfTestNameFilterMatchesTestName)
   {
      TestNameFilterMock testNameFilterMock;
      const bool matchesTestNameReturnValue = testNameFilterMock.MatchesTestNameMock.ReturnRandom();
      const string testName = ZenUnit::Random<string>();
      //
      const bool testNameFilterMatchesTestName = _testClassRunner.TestNameFilterMatchesTestName(testNameFilterMock, testName.c_str());
      //
      METALMOCK(testNameFilterMock.MatchesTestNameMock.CalledOnceWith(testName.c_str()));
      ARE_EQUAL(matchesTestNameReturnValue, testNameFilterMatchesTestName);
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
      METALMOCK(leftTestClassRunnerMock->TestClassNameMock.CalledOnce());
      METALMOCK(rightTestClassRunnerMock->TestClassNameMock.CalledOnce());
      ARE_EQUAL(expectedIsLessThan, isLessThan);
   }

   RUN_TESTS(TestClassRunnerTests)
}
