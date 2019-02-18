#include "pch.h"
#include "ZenUnitLibraryTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitLibraryTests/Results/Mock/TestResultMock.h"
#include "ZenUnitLibraryTests/Tests/TestingTestClass.h"

namespace ZenUnit
{
   TESTS(NormalTestTests)
   AFACT(NumberOfTestCases_Returns1)
   AFACT(WritePostTestNameMessage_WritesSpaceArrowSpace)
   AFACT(WritePostTestCompletionMessage_CallsTestResultPrintOKIfTestPassedAndDoWriteMessageTrue)
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
         TestClassName.c_str(), TestName.c_str(), &TestingTestClass::TestFunction);
   }

   TEST(NumberOfTestCases_Returns1)
   {
      ARE_EQUAL(1, _normalTest->NumberOfTestCases());
   }

   TEST(WritePostTestNameMessage_WritesSpaceArrowSpace)
   {
      ConsoleMock consoleMock;
      consoleMock.WriteMock.Expect();
      //
      _normalTest->WritePostTestNameMessage(&consoleMock);
      //
      ZENMOCK(consoleMock.WriteMock.CalledOnceWith(" -> "));
   }

   TEST(WritePostTestCompletionMessage_CallsTestResultPrintOKIfTestPassedAndDoWriteMessageTrue)
   {
      ConsoleMock consoleMock;
      TestResultMock testResultMock;
      testResultMock.WriteLineOKIfSuccessMock.Expect();
      //
      _normalTest->WritePostTestCompletionMessage(&consoleMock, testResultMock);
      //
      ZENMOCK(testResultMock.WriteLineOKIfSuccessMock.CalledOnceWith(&consoleMock));
   }

   TEST(Constructor_SetsTestClassNameAndTestName_SetsTestBodyPointer)
   {
      const NormalTest<TestingTestClass> normalTest(TestClassName.c_str(), TestName.c_str(), &TestingTestClass::TestFunction);
      ARE_EQUAL(TestName, normalTest.Name());
      ARE_EQUAL("TESTS(" + TestClassName + ")\nTEST(" + TestName + ")", normalTest.FullTestNameValue());
      ARE_EQUAL("(0)", normalTest.FileLineString());
      ARE_EQUAL(&TestingTestClass::TestFunction, normalTest._testMemberFunction);
      POINTER_IS_NULL(normalTest._testClass);
   }

   TEST(NewTestClass_NewsTestClass)
   {
      POINTER_IS_NULL(_normalTest->_testClass);
      //
      _normalTest->NewTestClass();
      //
      POINTER_IS_NOT_NULL(_normalTest->_testClass);
      _normalTest->_testClass.reset();
   }

   TEST(Startup_CallsStartupOnTestClass)
   {
      _normalTest->_testClass = make_unique<TestingTestClass>();
      _normalTest->_testClass->StartupMock.Expect();
      //
      _normalTest->Startup();
      //
      ZENMOCK(_normalTest->_testClass->StartupMock.CalledOnce());
   }

   TEST(TestBody_CallsMemberTestFunctionBoundToTestClassPointer)
   {
      _normalTest->_testMemberFunction = &TestingTestClass::TestFunction;
      _normalTest->_testClass = make_unique<TestingTestClass>();
      _normalTest->_testClass->TestFunctionMock.Expect();
      //
      _normalTest->TestBody();
      //
      ZENMOCK(_normalTest->_testClass->TestFunctionMock.CalledOnce());
   }

   TEST(Cleanup_CallsCleanupOnTestClass)
   {
      _normalTest->_testClass = make_unique<TestingTestClass>();
      _normalTest->_testClass->CleanupMock.Expect();
      //
      _normalTest->Cleanup();
      //
      ZENMOCK(_normalTest->_testClass->CleanupMock.CalledOnce());
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

   RUN_TESTS(NormalTestTests)
}
