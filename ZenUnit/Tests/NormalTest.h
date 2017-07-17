#pragma once
#include "ZenUnit/Console/Console.h"
#include "ZenUnit/Tests/Test.h"
#include <iostream>

namespace ZenUnit
{
   template<typename TestClassType>
   class NormalTest : public Test
   {
      friend class NormalTestTests;
   private:
      std::unique_ptr<TestClassType> _testClass;
      void (TestClassType::*_testMemberFunction)();
   public:
      NormalTest(const char* testClassName, const char* testName, void (TestClassType::*testMemberFunction)())
         : Test(testClassName, testName, 0)
         , _testMemberFunction(testMemberFunction)
      {
      }

      size_t NumberOfTestCases() const override
      {
         return 1;
      }

      void OptionallyWritePostTestNameMessage(
         const Console* console, bool doWriteMessage) const override
      {
         if (doWriteMessage)
         {
            console->Write(" -> ");
         }
      }

      void OptionallyWritePostTestCompletionMessage(
         const Console* console, const TestResult& testResult, bool doWriteMessage) const override
      {
         testResult.OptionallyWriteOKIfTestPassed(console, doWriteMessage);
      }

      std::vector<TestResult> Run() override
      {
         const TestResult testResult = RunTestCase();
         return { testResult };
      }

      void NewTestClass() override
      {
         assert_true(_testClass == nullptr);
         _testClass = std::make_unique<TestClassType>();
      }

      void Startup() override
      {
         _testClass->Startup();
      }

      void TestBody() override
      {
         (_testClass.get()->*_testMemberFunction)();
      }

      void Cleanup() override
      {
         _testClass->Cleanup();
      }

      void DeleteTestClass() override
      {
         _testClass.reset();
      }
   };
}
