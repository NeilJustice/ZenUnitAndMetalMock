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

      virtual size_t NumberOfTestCases() const final
      {
         return 1;
      }

      virtual void PrintPostTestNameMessage(const Console* console) const final
      {
         console->Write(" -> ");
      }

      virtual void PrintPostTestCompletionMessage(
         const Console* console, const TestResult& testResult) const final
      {
         testResult.PrintTestOutcome(console);
      }

      virtual std::vector<TestResult> Run() final
      {
         const TestResult testResult = RunTestCase();
         return { testResult };
      }

      virtual void NewTestClass() final
      {
         assert_true(_testClass == nullptr);
         _testClass = std::make_unique<TestClassType>();
      }

      virtual void Startup() final
      {
         _testClass->Startup();
      }

      virtual void TestBody() final
      {
         (_testClass.get()->*_testMemberFunction)();
      }

      virtual void Cleanup() final
      {
         _testClass->Cleanup();
      }

      virtual void DeleteTestClass() final
      {
         _testClass.reset();
      }
   };
}
