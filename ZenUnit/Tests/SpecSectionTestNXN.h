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
      const PmfToken* _testNXNPmfToken;
   public:
      SpecSectionTestNXN(const char* testClassName, const char* testName, const PmfToken* pmfToken)
         : Test(testClassName, testName)
         , _testNXNPmfToken(pmfToken)
      {
      }

      virtual size_t NumberOfTestCases() const override
      {
         const std::unique_ptr<Test>* testNXN = GetTestNXNFromPmfToken();
         const size_t numberOfTestCases = (*testNXN)->NumberOfTestCases();
         return numberOfTestCases;
      }

      virtual void PrintPostTestNameMessage(const Console* console) const override
      {
         console->WriteLine("...");
      }

      virtual std::vector<TestResult> Run() override
      {
         const std::unique_ptr<Test>* testNXN = GetTestNXNFromPmfToken();
         const std::vector<TestResult> testResults = (*testNXN)->Run();
         return testResults;
      }

      virtual void NewTestClass() override { throw std::logic_error("N/A"); }
      virtual void Startup() override { throw std::logic_error("N/A"); }
      virtual void TestBody() override { throw std::logic_error("N/A"); }
      virtual void Cleanup() override { throw std::logic_error("N/A"); }
      virtual void DeleteTestClass() override { throw std::logic_error("N/A"); }
   private:
      virtual const std::unique_ptr<Test>* GetTestNXNFromPmfToken() const
      {
         const std::unique_ptr<Test>* testNXN = TestClassType::TestNXNPmfToTest(_testNXNPmfToken);
         assert_true(testNXN != nullptr);
         return testNXN;
      }
   };
}
