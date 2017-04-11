#pragma once
#include <iostream>
#include "ZenUnit/Tests/Test.h"

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
      template<typename TestMemberFunctionType>
      NormalTest(const char* testClassName, const char* testName, TestMemberFunctionType testMemberFunction)
         : Test(testClassName, testName)
         , _testMemberFunction(testMemberFunction)
      {
      }

      size_t NumberOfTestCases() const override final
      {
         return 1;
      }

      void PrintPostTestNameMessage(const Console* console) const override final
      {
         console->Write(" -> ");
      }

      void PrintPostTestCompletionMessage(
         const Console* console, const TestResult& testResult) const override final
      {
         testResult.PrintTestOutcome(console);
      }

      std::vector<TestResult> Run() override final
      {
         const TestResult testResult = RunTestCase();
         return { testResult };
      }

      void NewTestClass() override final
      {
         assert_true(_testClass == nullptr);
         _testClass = std::make_unique<TestClassType>();
      }

      void Startup() override final
      {
         _testClass->Startup();
      }

      void TestBody() override final
      {
         (_testClass.get()->*_testMemberFunction)();
      }

      void Cleanup() override final
      {
         _testClass->Cleanup();
      }

      void DeleteTestClass() override final
      {
         _testClass.reset();
      }
   };
}
