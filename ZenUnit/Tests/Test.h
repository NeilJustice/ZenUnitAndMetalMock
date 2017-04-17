#pragma once
#include "ZenUnit/Results/TestResult.h"
#include "ZenUnit/Tests/FullName.h"

namespace ZenUnit
{
   class TryCatchCaller;
   class TestResultFactory;

   class Test
   {
      friend class TestTests;
   private:
      std::unique_ptr<const TryCatchCaller> _tryCatchCaller;
      std::unique_ptr<const TestResultFactory> _testResultFactory;
   protected:
      FullName _fullName;
      FileLine _fileLine;
   public:
      Test(const char* testClassName, const char* testName);
      virtual ~Test();
      virtual const char* Name() const;
      virtual std::string TestsAndTestLines() const;
      virtual std::string FileLineString() const;
      virtual void PrintPostTestNameMessage(const Console*) const {}
      virtual void PrintPostTestCompletionMessage(const Console*, const TestResult&) const {}
      virtual size_t NumberOfTestCases() const = 0;
      virtual std::vector<TestResult> Run() = 0;

      static void CallNewTestClass(Test* test);
      virtual void NewTestClass() = 0;
      
      static void CallStartup(Test* test);
      virtual void Startup() = 0;

      static void CallTestBody(Test* test);
      virtual void TestBody() = 0;      

      static void CallCleanup(Test* test);
      virtual void Cleanup() = 0;

      static void CallDeleteTestClass(Test* test);
      virtual void DeleteTestClass() = 0;
   protected:
      TestResult RunTestCase();
   };
}
