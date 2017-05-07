#include "pch.h"
#include "ZenUnit/Enums/TestPhase.h"
#include "ZenUnit/Enums/TestOutcome.h"
#include "ZenUnit/Tests/Test.h"
#include "ZenUnit/Results/TestResultFactory.h"
#include "ZenUnit/TestRunners/TryCatchCaller.h"

namespace ZenUnit
{
   Test::Test(const char* testClassName, const char* testName, unsigned char arity)
      : _tryCatchCaller(new TryCatchCaller)
      , _testResultFactory(new TestResultFactory)
      , _fullTestName(testClassName, testName, arity)
   {
   }

   Test::~Test() = default;

   const char* Test::Name() const
   {
      return _fullTestName.testName;
   }

   std::string Test::FullTestNameValue() const
   {
      return _fullTestName.Value();
   }

   string Test::FileLineString() const
   {
      string fileLineString = _fileLine.ToString();
      return fileLineString;
   }

   void Test::CallNewTestClass(Test* test)
   {
      test->NewTestClass();
   }

   void Test::CallStartup(Test* test)
   {
      test->Startup();
   }

   void Test::CallTestBody(Test* test)
   {
      test->TestBody();
   }

   void Test::CallCleanup(Test* test)
   {
      test->Cleanup();
   }

   void Test::CallDeleteTestClass(Test* test)
   {
      test->DeleteTestClass();
   }

   TestResult Test::RunTestCase()
   {
      const CallResult constructorCallResult = _tryCatchCaller->
         Call(&Test::CallNewTestClass, this, TestPhase::Constructor);
      if (constructorCallResult.testOutcome != TestOutcome::Success)
      {
         const TestResult constructorFail = _testResultFactory->
            ConstructorFail(_fullTestName, constructorCallResult);
         return constructorFail;
      }
      const CallResult startupCallResult = _tryCatchCaller->
         Call(&Test::CallStartup, this, TestPhase::Startup);
      if (startupCallResult.testOutcome != TestOutcome::Success)
      {
         const CallResult destructorCallResult = _tryCatchCaller->
            Call(&Test::CallDeleteTestClass, this, TestPhase::Destructor);
         const TestResult startupFail = _testResultFactory->
            StartupFail(_fullTestName, constructorCallResult, startupCallResult, destructorCallResult);
         return startupFail;
      }
      const CallResult testBodyCallResult = _tryCatchCaller->
         Call(&Test::CallTestBody, this, TestPhase::TestBody);
      const CallResult cleanupCallResult = _tryCatchCaller->
         Call(&Test::CallCleanup, this, TestPhase::Cleanup);
      const CallResult destructorCallResult = _tryCatchCaller->
         Call(&Test::CallDeleteTestClass, this, TestPhase::Destructor);
      const TestResult testResult = _testResultFactory->
         FullCtor(_fullTestName, constructorCallResult, startupCallResult,
            testBodyCallResult, cleanupCallResult, destructorCallResult);
      return testResult;
   }
}
