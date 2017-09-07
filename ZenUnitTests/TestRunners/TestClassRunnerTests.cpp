#include "pch.h"
#include "ZenUnit/TestRunners/TestClassRunner.h"
#include "ZenUnitTests/TestRunners/Mock/TestClassRunnerMock.h"

namespace ZenUnit
{
   TESTS(TestClassRunnerTests)
   FACTS(OperatorLessThan_ReturnsTrueIfTestClassNameStrcmpResultIsLessThanZero)
   EVIDENCE

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
      leftTestClassRunnerMock->TestClassNameForSortingMock.ExpectAndReturn(leftTestClassName);
      rightTestClassRunnerMock->TestClassNameForSortingMock.ExpectAndReturn(rightTestClassName);
      const unique_ptr<TestClassRunner> leftTestClassRunner(leftTestClassRunnerMock);
      const unique_ptr<TestClassRunner> rightTestClassRunner(rightTestClassRunnerMock);
      //
      const bool isLessThan = leftTestClassRunner < rightTestClassRunner;
      //
      ZEN(leftTestClassRunnerMock->TestClassNameForSortingMock.AssertCalledOnce());
      ZEN(rightTestClassRunnerMock->TestClassNameForSortingMock.AssertCalledOnce());
      ARE_EQUAL(expectedIsLessThan, isLessThan);
   }

   }; RUNTESTS(TestClassRunnerTests)
}
