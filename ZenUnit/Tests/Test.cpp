#include "pch.h"
#include "ZenUnit/Enums/TestOutcome.h"
#include "ZenUnit/Enums/TestPhase.h"
#include "ZenUnit/Results/TestResultFactory.h"
#include "ZenUnit/TestRunners/TryCatchCaller.h"
#include "ZenUnit/Tests/Test.h"

namespace ZenUnit
{
   inline Test::Test(const char* testClassName, const char* testName, unsigned char arity)
      : _tryCatchCaller(new TryCatchCaller)
      , _testResultFactory(new TestResultFactory)
      , _fullTestName(testClassName, testName, arity)
   {
   }

   inline Test::~Test() = default;

   inline const char* Test::Name() const
   {
      return _fullTestName.testName;
   }

   inline std::string Test::FullTestNameValue() const
   {
      return _fullTestName.Value();
   }

   inline std::string Test::FileLineString() const
   {
      const std::string fileLineString = _fileLine.ToString();
      return fileLineString;
   }

   inline void Test::CallNewTestClass(Test* test)
   {
      test->NewTestClass();
   }

   inline void Test::CallStartup(Test* test)
   {
      test->Startup();
   }

   inline void Test::CallTestBody(Test* test)
   {
      test->TestBody();
   }

   inline void Test::CallCleanup(Test* test)
   {
      test->Cleanup();
   }

   inline void Test::CallDeleteTestClass(Test* test)
   {
      test->DeleteTestClass();
   }

   inline TestResult Test::RunTestCase()
   {
      const CallResult constructorCallResult =
         _tryCatchCaller->Call(&Test::CallNewTestClass, this, TestPhase::Constructor);
      if (constructorCallResult.testOutcome != TestOutcome::Success)
      {
         const TestResult constructorFailTestResult =
            _testResultFactory->ConstructorFail(_fullTestName, constructorCallResult);
         return constructorFailTestResult;
      }
      const CallResult startupCallResult =
         _tryCatchCaller->Call(&Test::CallStartup, this, TestPhase::Startup);
      if (startupCallResult.testOutcome != TestOutcome::Success)
      {
         const CallResult destructorCallResult =
            _tryCatchCaller->Call(&Test::CallDeleteTestClass, this, TestPhase::Destructor);
         const TestResult startupFailTestResult =
            _testResultFactory->StartupFail(_fullTestName, constructorCallResult, startupCallResult, destructorCallResult);
         return startupFailTestResult;
      }
      const CallResult testBodyCallResult =
         _tryCatchCaller->Call(&Test::CallTestBody, this, TestPhase::TestBody);
      const CallResult cleanupCallResult =
         _tryCatchCaller->Call(&Test::CallCleanup, this, TestPhase::Cleanup);
      const CallResult destructorCallResult =
         _tryCatchCaller->Call(&Test::CallDeleteTestClass, this, TestPhase::Destructor);
      const TestResult testResult = _testResultFactory->FullCtor(
         _fullTestName, constructorCallResult, startupCallResult,
         testBodyCallResult, cleanupCallResult, destructorCallResult);
      return testResult;
   }
}
