#pragma once
#include "ZenUnit/Tests/Test.h"
#include "ZenUnit/Utils/PmfToken.h"

namespace ZenUnit
{
   template<typename TestClassType>
   class SpecSectionTestNXN : public Test
   {
      friend class SpecSectionTestNXNTests;
   private:
      const PmfToken* const _testNXNPmfToken;
   public:
      SpecSectionTestNXN(const char* testClassName, const char* testName, const PmfToken* pmfToken)
         : Test(testClassName, testName, 0)
         , _testNXNPmfToken(pmfToken)
      {
      }

      size_t NumberOfTestCases() const override
      {
         const std::unique_ptr<Test>* const testNXN = PmfTokenToTest();
         const size_t numberOfTestCases = (*testNXN)->NumberOfTestCases();
         return numberOfTestCases;
      }

      void PrintPostTestNameMessage(const Console* console) const override
      {
         console->WriteLine("...");
      }

      std::vector<TestResult> Run() override
      {
         const std::unique_ptr<Test>* const test = PmfTokenToTest();
         const std::vector<TestResult> testResults = (*test)->Run();
         return testResults;
      }
   private:
      virtual const std::unique_ptr<Test>* PmfTokenToTest() const
      {
         const std::unique_ptr<Test>* const test = TestClassType::TestNXNPmfToTest(_testNXNPmfToken);
         assert_true(test != nullptr);
         return test;
      }
   };
}
