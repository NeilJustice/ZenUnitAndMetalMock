#include "pch.h"
#include "ZenUnit/Tests/NormalTest.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Results/Mock/TestResultMock.h"
#include "ZenUnitTests/Tests/TestingTestClass.h"

namespace ZenUnit
{
   TESTS(NormalTestTests)
   SPEC(NumberOfTestCases_Returns1)
   SPEC(PrintPostTestNameMessage_WritesSpaceArrowSpace)
   SPEC(PrintPostTestCompletionMessage_CallsTestResultPrintTestOutcome)
   SPEC(Constructor_SetsTestClassNameAndTestName_SetsTestBodyPointer)
   SPEC(NewTestClass_NewsTestClass)
   SPEC(Startup_CallsStartupOnTestClass)
   SPEC(TestBody_CallsMemberTestFunctionBoundToTestClassPointer)
   SPEC(Cleanup_CallsCleanupOnTestClass)
   SPEC(DeleteTestClass_DeletesTestClass)
   SPECEND

   unique_ptr<NormalTest<TestingTestClass>> _normalTest;
   const char* TestClassName = "TestClassName";
   const char* TestName = "TestName";

   STARTUP
   {
      _normalTest = make_unique<NormalTest<TestingTestClass>>(TestClassName, TestName, &TestingTestClass::Test);
   }

   TEST(NumberOfTestCases_Returns1)
   {
      ARE_EQUAL(1, _normalTest->NumberOfTestCases());
   }

   TEST(PrintPostTestNameMessage_WritesSpaceArrowSpace)
   {
      ConsoleMock consoleMock;
      consoleMock.WriteMock.Expect();
      //
      _normalTest->PrintPostTestNameMessage(&consoleMock);
      //
      ZEN(consoleMock.WriteMock.AssertCalledOnceWith(" -> "));
   }

   TEST(PrintPostTestCompletionMessage_CallsTestResultPrintTestOutcome)
   {
      ConsoleMock consoleMock;
      TestResultMock testResultMock;
      testResultMock.PrintTestOutcomeMock.Expect();
      //
      _normalTest->PrintPostTestCompletionMessage(&consoleMock, testResultMock);
      //
      ZEN(testResultMock.PrintTestOutcomeMock.AssertCalledOnceWith(&consoleMock));
   }

   TEST(Constructor_SetsTestClassNameAndTestName_SetsTestBodyPointer)
   {
      const NormalTest<TestingTestClass> normalTest(TestClassName, TestName, &TestingTestClass::Test);
      ARE_EQUAL(TestName, normalTest.Name());
      ARE_EQUAL("TESTS(TestClassName)\nTEST(TestName)", normalTest.TestsAndTestLines());
      ARE_EQUAL("(0)", normalTest.FileLineString());
      ARE_EQUAL(&TestingTestClass::Test, normalTest._testMemberFunction);
      IS_NULL(normalTest._testClass);
   }

   TEST(NewTestClass_NewsTestClass)
   {
      IS_NULL(_normalTest->_testClass);
      //
      _normalTest->NewTestClass();
      //
      IS_NOT_NULL(_normalTest->_testClass);
      _normalTest->_testClass.reset();
   }

   TEST(Startup_CallsStartupOnTestClass)
   {
      _normalTest->_testClass = make_unique<TestingTestClass>();
      _normalTest->_testClass->StartupMock.Expect();
      //
      _normalTest->Startup();
      //
      ZEN(_normalTest->_testClass->StartupMock.AssertCalledOnce());
   }

   TEST(TestBody_CallsMemberTestFunctionBoundToTestClassPointer)
   {
      _normalTest->_testMemberFunction = &TestingTestClass::Test;
      _normalTest->_testClass = make_unique<TestingTestClass>();
      _normalTest->_testClass->TestMock.Expect();
      //
      _normalTest->TestBody();
      //
      ZEN(_normalTest->_testClass->TestMock.AssertCalledOnce());
   }

   TEST(Cleanup_CallsCleanupOnTestClass)
   {
      _normalTest->_testClass = make_unique<TestingTestClass>();
      _normalTest->_testClass->CleanupMock.Expect();
      //
      _normalTest->Cleanup();
      //
      ZEN(_normalTest->_testClass->CleanupMock.AssertCalledOnce());
   }

   TEST(DeleteTestClass_DeletesTestClass)
   {
      _normalTest->_testClass = make_unique<TestingTestClass>();
      IS_FALSE(TestingTestClass::s_destructorCalled);
      //
      _normalTest->DeleteTestClass();
      //
      IS_TRUE(TestingTestClass::s_destructorCalled);
   }

   const FullName FullNameValue = FullName("TestClass", "Test");

   }; RUN(NormalTestTests)
}
