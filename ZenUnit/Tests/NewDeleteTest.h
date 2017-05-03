#pragma once
#include "ZenUnit/Results/TestResultFactory.h"
#include "ZenUnit/TestRunners/TryCatchCaller.h"
#include "ZenUnit/Tests/Test.h"

namespace ZenUnit
{
   template<typename TestClassType>
   class NewDeleteTest : public Test
   {
      friend class NewDeleteTestTests;
   private:
      std::unique_ptr<const TryCatchCaller> _tryCatchCaller;
      std::unique_ptr<const TestResultFactory> _testResultFactory;
      std::unique_ptr<TestClassType> _firstInstanceOfTestClass;
   public:
      explicit NewDeleteTest(const char* testClassName)
         : Test(testClassName, "TestClassIsNewableAndDeletable", 0)
         , _tryCatchCaller(new TryCatchCaller)
         , _testResultFactory(new TestResultFactory)
      {
      }

      size_t NumberOfTestCases() const override
      {
         return 1;
      }

      std::vector<TestResult> Run() override
      {
         const CallResult constructorCallResult = _tryCatchCaller->
            Call(&Test::CallNewTestClass, this, TestPhase::Constructor);
         if (constructorCallResult.testOutcome != TestOutcome::Success)
         {
            const TestResult constructorFail = _testResultFactory->
               ConstructorFail(_fullTestName, constructorCallResult);
            return { constructorFail };
         }
         const CallResult destructorCallResult = _tryCatchCaller->
            Call(&Test::CallDeleteTestClass, this, TestPhase::Destructor);
         const TestResult testResult = _testResultFactory->
            CtorDtorSuccess(_fullTestName, constructorCallResult, destructorCallResult);
         return { testResult };
      }

      void NewTestClass() override
      {
         _firstInstanceOfTestClass = std::make_unique<TestClassType>();
      }

      void Startup() override {}
      void TestBody() override {}
      void Cleanup() override {}

      void DeleteTestClass() override
      {
         _firstInstanceOfTestClass.reset();
      }
   };
}
