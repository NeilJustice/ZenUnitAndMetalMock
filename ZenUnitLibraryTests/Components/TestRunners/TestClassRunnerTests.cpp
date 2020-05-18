#include "pch.h"
#include "ZenUnitLibraryTests/Components/Args/ZenMock/TestNameFilterMock.h"
#include "ZenUnitLibraryTests/Components/TestRunners/ZenMock/TestClassRunnerMock.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomTestNameFilter.h"
#include "ZenUnitTestUtils/Equalizers/TestClassResultEqualizer.h"

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
      DELETE_TO_ASSERT_NEWED(testClassRunner._protected_console);
      DELETE_TO_ASSERT_NEWED(testClassRunner._protected_twoArgMemberAnyer);
   }

   TEST(TestClassName_ReturnNullptr)
   {
      POINTER_IS_NULL(_testClassRunner.TestClassName());
   }

   TEST(NumberOfTestCases_Returns0)
   {
      ARE_EQUAL(0, _testClassRunner.NumberOfTestCases());
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
      ZENMOCK(testNameFilterMock.MatchesTestNameMock.CalledOnceWith(testName.c_str()));
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
      ZENMOCK(leftTestClassRunnerMock->TestClassNameMock.CalledOnce());
      ZENMOCK(rightTestClassRunnerMock->TestClassNameMock.CalledOnce());
      ARE_EQUAL(expectedIsLessThan, isLessThan);
   }

   RUN_TESTS(TestClassRunnerTests)
}
