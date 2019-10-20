#include "pch.h"
#include "ZenUnitLibraryTests/Components/Args/ZenMock/RunFilterMock.h"
#include "ZenUnitLibraryTests/Components/TestRunners/ZenMock/TestClassRunnerMock.h"
#include "ZenUnitTestUtils/Equalizers/TestClassResultEqualizer.h"

namespace ZenUnit
{
   TESTS(TestClassRunnerTests)
   AFACT(DefaultConstructor_NewsConsoleAndNewArgMemberAnyer)
   AFACT(TestClassName_ReturnNullptr)
   AFACT(NumberOfTestCases_Returns0)
   AFACT(HasTestThatMatchesRunFilter_ReturnsFalse)
   AFACT(RunTests_ReturnsDefaultTestClassResult)
   AFACT(RunFilterMatchesTestName_ReturnsTrueIfRunFilterMatchesTestName)
   FACTS(OperatorLessThan_ReturnsTrueIfTestClassNameStrcmpResultIsLessThanZero)
   EVIDENCE

   TestClassRunner _testClassRunner;

   TEST(DefaultConstructor_NewsConsoleAndNewArgMemberAnyer)
   {
      TestClassRunner testClassRunner;
      POINTER_WAS_NEWED(testClassRunner._protected_console);
      POINTER_WAS_NEWED(testClassRunner._protected_twoArgMemberAnyer);
   }

   TEST(TestClassName_ReturnNullptr)
   {
      POINTER_IS_NULL(_testClassRunner.TestClassName());
   }

   TEST(NumberOfTestCases_Returns0)
   {
      ARE_EQUAL(0, _testClassRunner.NumberOfTestCases());
   }

   TEST(HasTestThatMatchesRunFilter_ReturnsFalse)
   {
      IS_FALSE(_testClassRunner.HasTestThatMatchesRunFilter(ZenUnit::Random<RunFilter>()));
   }

   TEST(RunTests_ReturnsDefaultTestClassResult)
   {
      ARE_EQUAL(TestClassResult{}, _testClassRunner.RunTests());
   }

   TEST(RunFilterMatchesTestName_ReturnsTrueIfRunFilterMatchesTestName)
   {
      RunFilterMock runFilterMock;
      const bool runFilterMatchesTestName = runFilterMock.MatchesTestNameMock.ReturnRandom();
      const string testName = ZenUnit::Random<string>();
      //
      const bool returnedRunFilterMatchesTestName = _testClassRunner.RunFilterMatchesTestName(runFilterMock, testName.c_str());
      //
      ZENMOCK(runFilterMock.MatchesTestNameMock.CalledOnceWith(testName.c_str()));
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
      ZENMOCK(leftTestClassRunnerMock->TestClassNameMock.CalledOnce());
      ZENMOCK(rightTestClassRunnerMock->TestClassNameMock.CalledOnce());
      ARE_EQUAL(expectedIsLessThan, isLessThan);
   }

   RUN_TESTS(TestClassRunnerTests)
}
