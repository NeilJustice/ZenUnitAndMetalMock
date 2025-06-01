#include "pch.h"
#include "ZenUnitLibraryTests/ValueTypes/TestResults/MetalMock/TestResultMock.h"

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
      _normalTest = make_unique<NormalTest<TestingTestClass>>(TestClassName.c_str(), TestName.c_str(), &TestingTestClass::TestFunction);
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
      METALMOCK(consoleMock.WriteMock.CalledOnceWith(" -> "));
   }

   TEST(WritePostTestCompletionMessage_CallsTestResultPrintOKIfTestPassedAndDoWriteMessageTrue)
   {
      ConsoleMock consoleMock;
      TestResultMock testResultMock;
      testResultMock.WriteLineOKIfSuccessOrSuccessButPastDeadlineMock.Expect();
      //
      _normalTest->WritePostTestCompletionMessage(&consoleMock, testResultMock);
      //
      METALMOCK(testResultMock.WriteLineOKIfSuccessOrSuccessButPastDeadlineMock.CalledOnceWith(&consoleMock));
   }

   TEST(Constructor_SetsTestClassNameAndTestName_SetsTestBodyPointer)
   {
      const NormalTest<TestingTestClass> normalTest(TestClassName.c_str(), TestName.c_str(), &TestingTestClass::TestFunction);
      ARE_EQUAL(TestName, normalTest.Name());
      ARE_EQUAL(&TestingTestClass::TestFunction, normalTest._testMemberFunction);
      IS_NULLPTR(normalTest._testClass);
   }

   TEST(NewTestClass_NewsTestClass)
   {
      IS_NULLPTR(_normalTest->_testClass);
      //
      _normalTest->NewTestClass();
      //
      IS_NOT_NULLPTR(_normalTest->_testClass);
      _normalTest->_testClass.reset();
   }

   TEST(Startup_CallsStartupOnTestClass)
   {
      _normalTest->_testClass = make_unique<TestingTestClass>();
      _normalTest->_testClass->StartupMock.Expect();
      //
      _normalTest->Startup();
      //
      METALMOCK(_normalTest->_testClass->StartupMock.CalledOnce());
   }

   TEST(TestBody_CallsMemberTestFunctionBoundToTestClassPointer)
   {
      _normalTest->_testMemberFunction = &TestingTestClass::TestFunction;
      _normalTest->_testClass = make_unique<TestingTestClass>();
      _normalTest->_testClass->TestFunctionMock.Expect();
      //
      _normalTest->TestBody();
      //
      METALMOCK(_normalTest->_testClass->TestFunctionMock.CalledOnce());
   }

   TEST(Cleanup_CallsCleanupOnTestClass)
   {
      _normalTest->_testClass = make_unique<TestingTestClass>();
      _normalTest->_testClass->CleanupMock.Expect();
      //
      _normalTest->Cleanup();
      //
      METALMOCK(_normalTest->_testClass->CleanupMock.CalledOnce());
   }

   TEST(DeleteTestClass_DeletesTestClass)
   {
      _normalTest->_testClass = make_unique<TestingTestClass>();
      IS_FALSE(TestingTestClass::s_destructorHasBeenCalled);
      //
      _normalTest->DeleteTestClass();
      //
      IS_TRUE(TestingTestClass::s_destructorHasBeenCalled);
   }

   RUN_TESTS(NormalTestTests)
}
