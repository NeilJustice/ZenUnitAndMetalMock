#include "pch.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Results/Mock/TestResultMock.h"
#include "ZenUnitTests/Testing/RandomPrintMode.h"
#include "ZenUnitTests/Tests/TestingTestClass.h"

namespace ZenUnit
{
   TESTS(NormalTestTests)
   AFACT(NumberOfTestCases_Returns1)
   AFACT(NonMinimalWritePostTestNameMessage_WritesSpaceArrowSpace)
   AFACT(NonMinimalWritePostTestCompletionMessage_CallsTestResultPrintOKIfTestPassedAndDoWriteMessageTrue)
   AFACT(Constructor_SetsTestClassNameAndTestName_SetsTestBodyPointer)
   AFACT(NewTestClass_NewsTestClass)
   AFACT(Startup_CallsStartupOnTestClass)
   AFACT(TestBody_CallsMemberTestFunctionBoundToTestClassPointer)
   AFACT(Cleanup_CallsCleanupOnTestClass)
   AFACT(DeleteTestClass_DeletesTestClass)
   EVIDENCE

   unique_ptr<NormalTest<TestingTestClass>> _normalTest;
   const string TestClassName = Random<string>();
   const string TestName = Random<string>();

   STARTUP
   {
      _normalTest = make_unique<NormalTest<TestingTestClass>>(
         TestClassName.c_str(), TestName.c_str(), &TestingTestClass::Test);
   }

   TEST(NumberOfTestCases_Returns1)
   {
      ARE_EQUAL(1, _normalTest->NumberOfTestCases());
   }

   TEST(NonMinimalWritePostTestNameMessage_WritesSpaceArrowSpace)
   {
      ConsoleMock consoleMock;
      consoleMock.NonMinimalWriteMock.Expect();
      const PrintMode printMode = RandomPrintMode();
      //
      _normalTest->NonMinimalWritePostTestNameMessage(&consoleMock, printMode);
      //
      ZEN(consoleMock.NonMinimalWriteMock.CalledOnceWith(" -> ", printMode));
   }

   TEST(NonMinimalWritePostTestCompletionMessage_CallsTestResultPrintOKIfTestPassedAndDoWriteMessageTrue)
   {
      ConsoleMock consoleMock;
      TestResultMock testResultMock;
      testResultMock.NonMinimalWriteLineOKIfSuccessMock.Expect();
      const PrintMode printMode = RandomPrintMode();
      //
      _normalTest->NonMinimalWritePostTestCompletionMessage(&consoleMock, testResultMock, printMode);
      //
      ZEN(testResultMock.NonMinimalWriteLineOKIfSuccessMock.CalledOnceWith(&consoleMock, printMode));
   }

   TEST(Constructor_SetsTestClassNameAndTestName_SetsTestBodyPointer)
   {
      const NormalTest<TestingTestClass> normalTest(TestClassName.c_str(), TestName.c_str(), &TestingTestClass::Test);
      ARE_EQUAL(TestName, normalTest.Name());
      ARE_EQUAL("TESTS(" + TestClassName + ")\nTEST(" + TestName + ")", normalTest.FullTestNameValue());
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
      ZEN(_normalTest->_testClass->StartupMock.CalledOnce());
   }

   TEST(TestBody_CallsMemberTestFunctionBoundToTestClassPointer)
   {
      _normalTest->_testMemberFunction = &TestingTestClass::Test;
      _normalTest->_testClass = make_unique<TestingTestClass>();
      _normalTest->_testClass->TestMock.Expect();
      //
      _normalTest->TestBody();
      //
      ZEN(_normalTest->_testClass->TestMock.CalledOnce());
   }

   TEST(Cleanup_CallsCleanupOnTestClass)
   {
      _normalTest->_testClass = make_unique<TestingTestClass>();
      _normalTest->_testClass->CleanupMock.Expect();
      //
      _normalTest->Cleanup();
      //
      ZEN(_normalTest->_testClass->CleanupMock.CalledOnce());
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

   }; RUNTESTS(NormalTestTests)
}
