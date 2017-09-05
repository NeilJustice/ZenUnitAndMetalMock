#pragma once
#include "ZenUnit/Console/Console.h"
#include "ZenUnit/Tests/Test.h"
#include <iostream>
#include <memory>

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

      void NonMinimalWritePostTestNameMessage(
         const Console* console, PrintMode printMode) const override
      {
         console->NonMinimalWrite(" -> ", printMode);
      }

      void NonMinimalWritePostTestCompletionMessage(
         const Console* console, const TestResult& testResult, PrintMode printMode) const override
      {
         testResult.NonMinimalWriteLineOKIfSuccess(console, printMode);
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
