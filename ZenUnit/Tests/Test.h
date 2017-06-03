#pragma once
#include "ZenUnit/Results/TestResult.h"
#include "ZenUnit/Tests/FullTestName.h"
#include "ZenUnit/Utils/FileLine.h"

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
      FullTestName _fullTestName;
      FileLine _fileLine;
   public:
      Test(const char* testClassName, const char* testName, unsigned char arity);
      virtual ~Test();
      virtual const char* Name() const;
      virtual std::string FullTestNameValue() const;
      virtual std::string FileLineString() const;
      virtual void PrintPostTestNameMessage(const Console*) const {}
      virtual void PrintPostTestCompletionMessage(const Console*, const TestResult&) const {}
      virtual size_t NumberOfTestCases() const { return 0; }
      virtual std::vector<TestResult> Run() { return {}; }

      static void CallNewTestClass(Test* test);
      virtual void NewTestClass() {}

      static void CallStartup(Test* test);
      virtual void Startup() {}

      static void CallTestBody(Test* test);
      virtual void TestBody() {}

      static void CallCleanup(Test* test);
      virtual void Cleanup() {}

      static void CallDeleteTestClass(Test* test);
      virtual void DeleteTestClass() {}
   protected:
      TestResult RunTestCase();
   };

   #ifdef __linux__
      #if __clang_major__ == 3 && __clang_minor__ == 9
         static_assert(sizeof(Test) == 64, "Debug sizeof(Test) != 64");
      #endif
   #elif _MSC_FULL_VER == 191025019 // VS2017 15.2
      #ifdef _DEBUG
         static_assert(sizeof(Test) == 64, "Debug sizeof(Test) != 64");
      #elif NDEBUG
         static_assert(sizeof(Test) == 64, "Release sizeof(Test) != 64");
      #endif
   #endif
}
