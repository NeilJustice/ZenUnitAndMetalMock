#include "pch.h"
#include "ZenUnit/TestRunners/TestClassRunner.h"
#include "Mock/TestClassRunnerMock.h"

namespace ZenUnit
{
   TESTS(TestClassRunnerTests)
   SPECX(OperatorLessThan_ReturnsTrueIfTestClassNameStrcmpResultIsLessThanZero)
   SPECEND

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
      leftTestClassRunnerMock->TestClassNameMock.ExpectAndReturn(leftTestClassName);
      rightTestClassRunnerMock->TestClassNameMock.ExpectAndReturn(rightTestClassName);
      unique_ptr<TestClassRunner> leftTestClassRunner(leftTestClassRunnerMock);
      unique_ptr<TestClassRunner> rightTestClassRunner(rightTestClassRunnerMock);
      //
      bool isLessThan = leftTestClassRunner < rightTestClassRunner;
      //
      ZEN(leftTestClassRunnerMock->TestClassNameMock.AssertCalledOnce());
      ZEN(rightTestClassRunnerMock->TestClassNameMock.AssertCalledOnce());
      ARE_EQUAL(expectedIsLessThan, isLessThan);
   }

   }; RUN(TestClassRunnerTests)
}
