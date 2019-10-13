#include "pch.h"
#include "ZenUnitLibraryTests/Components/Args/ZenMock/RunFilterMock.h"
#include "ZenUnitLibraryTests/Components/TestRunners/ZenMock/TestClassRunnerMock.h"

namespace ZenUnit
{
   class TestingTestClassRunner : public TestClassRunner
   {
   public:
      const char* TestClassName() const override { return nullptr; }
      size_t NumberOfTestCases() const override { return 0; }
      TestClassResult RunTests() override { return TestClassResult(); }
      bool HasTestThatMatchesRunFilter(const RunFilter&) const override { return false; }
   };

   TESTS(TestClassRunnerTests)
   AFACT(DefaultConstructor_NewsComponents)
   AFACT(RunFilterMatchesTestName_ReturnsTrueIfRunFilterMatchesTestName)
   FACTS(OperatorLessThan_ReturnsTrueIfTestClassNameStrcmpResultIsLessThanZero)
   AFACT(TestingTestClassRunnerCodeCoverage)
   EVIDENCE

   TestingTestClassRunner _testingTestClassRunner;

   TEST(DefaultConstructor_NewsComponents)
   {
      TestingTestClassRunner testingTestClassRunner;
      POINTER_WAS_NEWED(testingTestClassRunner._protected_console);
      POINTER_WAS_NEWED(testingTestClassRunner._protected_twoArgMemberAnyer);
   }

   TEST(RunFilterMatchesTestName_ReturnsTrueIfRunFilterMatchesTestName)
   {
      RunFilterMock runFilterMock;
      const bool runFilterMatchesTestName = runFilterMock.MatchesTestNameMock.ReturnRandom();
      const string testName = ZenUnit::Random<string>();
      //
      const bool returnedRunFilterMatchesTestName = _testingTestClassRunner.RunFilterMatchesTestName(runFilterMock, testName.c_str());
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

   TEST(TestingTestClassRunnerCodeCoverage)
   {
      TestingTestClassRunner testingTestClassRunner;
      testingTestClassRunner.TestClassName();
      testingTestClassRunner.NumberOfTestCases();
      const TestClassResult testClassResult = testingTestClassRunner.RunTests();
      testingTestClassRunner.HasTestThatMatchesRunFilter(RunFilter());
   }

   RUN_TESTS(TestClassRunnerTests)
}
