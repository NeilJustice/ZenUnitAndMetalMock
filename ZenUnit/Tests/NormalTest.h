#pragma once
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
      template<typename TestMemberFunctionType>
      NormalTest(const char* testClassName, const char* testName, TestMemberFunctionType testMemberFunction)
         : Test(testClassName, testName)
         , _testMemberFunction(testMemberFunction)
      {
      }

      size_t NumberOfTestCases() const final
      {
         return 1;
      }

      void PrintPostTestNameMessage(const Console* console) const final
      {
         console->Write(" -> ");
      }

      void PrintPostTestCompletionMessage(
         const Console* console, const TestResult& testResult) const final
      {
         testResult.PrintTestOutcome(console);
      }

      std::vector<TestResult> Run() final
      {
         const TestResult testResult = RunTestCase();
         return { testResult };
      }

      void NewTestClass() final
      {
         assert_true(_testClass == nullptr);
         _testClass = std::make_unique<TestClassType>();
      }

      void Startup() final
      {
         _testClass->Startup();
      }

      void TestBody() final
      {
         (_testClass.get()->*_testMemberFunction)();
      }

      void Cleanup() final
      {
         _testClass->Cleanup();
      }

      void DeleteTestClass() final
      {
         _testClass.reset();
      }
   };
}
