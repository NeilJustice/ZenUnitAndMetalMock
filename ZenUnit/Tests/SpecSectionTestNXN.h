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

      size_t NumberOfTestCases() const final
      {
         const std::unique_ptr<Test>* testNXN = GetTestNXNFromPmfToken();
         const size_t numberOfTestCases = (*testNXN)->NumberOfTestCases();
         return numberOfTestCases;
      }

      void PrintPostTestNameMessage(const Console* console) const final
      {
         console->WriteLine("...");
      }

      std::vector<TestResult> Run() final
      {
         const std::unique_ptr<Test>* testNXN = GetTestNXNFromPmfToken();
         const std::vector<TestResult> testResults = (*testNXN)->Run();
         return testResults;
      }

      void NewTestClass() final { throw std::logic_error("N/A"); }
      void Startup() final { throw std::logic_error("N/A"); }
      void TestBody() final { throw std::logic_error("N/A"); }
      void Cleanup() final { throw std::logic_error("N/A"); }
      void DeleteTestClass() final { throw std::logic_error("N/A"); }
   private:
      virtual const std::unique_ptr<Test>* GetTestNXNFromPmfToken() const
      {
         const std::unique_ptr<Test>* testNXN = TestClassType::TestNXNPmfToTest(_testNXNPmfToken);
         assert_true(testNXN != nullptr);
         return testNXN;
      }
   };
}
