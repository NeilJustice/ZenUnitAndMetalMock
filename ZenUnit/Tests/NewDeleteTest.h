#pragma once
#include "Test.h"
#include "ZenUnit/TestRunners/TryCatchCaller.h"
#include "ZenUnit/Results/TestResultFactory.h"

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
         : Test(testClassName, "ImplicitFirstTestForNewabilityAndDeletability")
         , _tryCatchCaller(new TryCatchCaller)
         , _testResultFactory(new TestResultFactory)
      {
      }

      size_t NumberOfTestCases() const override final
      {
         return 1;
      }

      std::vector<TestResult> Run() override final
      {
         const CallResult constructorCallResult = _tryCatchCaller->
            Call(&Test::CallNewTestClass, this, TestPhase::Constructor);
         if (constructorCallResult.testOutcome != TestOutcome::Success)
         {
            const TestResult constructorFail = _testResultFactory->
               ConstructorFail(_fullName, constructorCallResult);
            return { constructorFail };
         }
         const CallResult destructorCallResult = _tryCatchCaller->
            Call(&Test::CallDeleteTestClass, this, TestPhase::Destructor);
         const TestResult testResult = _testResultFactory->
            CtorDtorSuccess(_fullName, constructorCallResult, destructorCallResult);
         return { testResult };
      }

      void NewTestClass() override final
      {
         _firstInstanceOfTestClass = std::make_unique<TestClassType>();
      }

      void Startup() override final {}
      void TestBody() override final {}
      void Cleanup() override final {}

      void DeleteTestClass() override final
      {
         _firstInstanceOfTestClass.reset();
      }
   };
}
