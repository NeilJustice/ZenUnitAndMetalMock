//#ifdef __linux__
//#include "ZenUnit/pch.h"
//#elif defined(_WIN64)
#include "pch.h"
//#endif
#include "ZenUnit/Enums/TestOutcome.h"
#include "ZenUnit/Enums/TestPhase.h"
#include "ZenUnit/Results/TestResultFactory.h"
#include "ZenUnit/TestRunners/TryCatchCaller.h"
#include "ZenUnit/Tests/Test.h"

namespace ZenUnit
{
   INLINE Test::Test(const char* testClassName, const char* testName, unsigned char arity)
      : _tryCatchCaller(new TryCatchCaller)
      , _testResultFactory(new TestResultFactory)
      , _fullTestName(testClassName, testName, arity)
   {
   }

   INLINE Test::~Test() = default;

   INLINE const char* Test::Name() const
   {
      return _fullTestName.testName;
   }

   INLINE std::string Test::FullTestNameValue() const
   {
      return _fullTestName.Value();
   }

   INLINE std::string Test::FileLineString() const
   {
      const std::string fileLineString = _fileLine.ToString();
      return fileLineString;
   }

   INLINE void Test::CallNewTestClass(Test* test)
   {
      test->NewTestClass();
   }

   INLINE void Test::CallStartup(Test* test)
   {
      test->Startup();
   }

   INLINE void Test::CallTestBody(Test* test)
   {
      test->TestBody();
   }

   INLINE void Test::CallCleanup(Test* test)
   {
      test->Cleanup();
   }

   INLINE void Test::CallDeleteTestClass(Test* test)
   {
      test->DeleteTestClass();
   }

   INLINE TestResult Test::RunTestCase()
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
