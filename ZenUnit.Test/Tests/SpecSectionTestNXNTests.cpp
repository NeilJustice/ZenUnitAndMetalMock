#include "pch.h"
#include "ZenUnit/Tests/SpecSectionTestNXN.h"
#include "Mock/TestMock.h"
#include "ZenUnit.Test/Console/Mock/ConsoleMock.h"

class TestingTestClass_SpecSectionTestNXNTests
{
public:
   static bool didCallTestNXNPmfToTest;
   static unique_ptr<Test> TestNXNPmfToTestReturnValue;

   static const unique_ptr<Test>* TestNXNPmfToTest(const ZenUnit::PmfToken*)
   {
      didCallTestNXNPmfToTest = true;
      return &TestNXNPmfToTestReturnValue;
   }

   void TestFunction(int) {}
   virtual ~TestingTestClass_SpecSectionTestNXNTests() = default;
};

bool TestingTestClass_SpecSectionTestNXNTests::didCallTestNXNPmfToTest;
unique_ptr<Test> TestingTestClass_SpecSectionTestNXNTests::TestNXNPmfToTestReturnValue;

namespace ZenUnit
{
   TESTS(SpecSectionTestNXNTests)
   SPEC(ThreeArgConstructor_SetsTestName_SetsTestNXNPmf)
   SPECX(NumberOfTestCases_GetsTestFromAddress_ReturnsTestNumberOfTestCases)
   SPEC(PrintPostTestNameMessage_WriteNewline)
   SPEC(Run_GetsTestFromAddress_RunsTest_ReturnsTestResults)
   SPEC(GetTestNXNFromPmfToken_ReturnsTestClassTypeTestNXNPmfToTestReturnValue);
   SPEC(TestOverrides_EachThrow)
   SPECEND

   class SpecSectionTestNXNSelfMocked : public Zen::Mock<SpecSectionTestNXN<TestingTestClass_SpecSectionTestNXNTests>>
   {
   public:
      SpecSectionTestNXNSelfMocked() : Zen::Mock<SpecSectionTestNXN<
         TestingTestClass_SpecSectionTestNXNTests>>("", "", nullptr) {}
      ZENMOCK_NONVOID0_CONST(const std::unique_ptr<Test>*, GetTestNXNFromPmfToken)
   };

   unique_ptr<SpecSectionTestNXN<TestingTestClass_SpecSectionTestNXNTests>> _specSectionTestNXN;
   unique_ptr<SpecSectionTestNXNSelfMocked> _specSectionTestNXNSelfMocked;

   STARTUP
   {
      _specSectionTestNXN.reset(new SpecSectionTestNXN<TestingTestClass_SpecSectionTestNXNTests>("", "", nullptr));
      _specSectionTestNXNSelfMocked.reset(new SpecSectionTestNXNSelfMocked);
   }

   TEST(ThreeArgConstructor_SetsTestName_SetsTestNXNPmf)
   {
      const char* const TestClassName = "TestClassName";
      const char* const TestName = "TestName";
      //
      const SpecSectionTestNXN<TestingTestClass_SpecSectionTestNXNTests> specifiedTestNXN(
         TestClassName, TestName, PmfToken::Instantiate<decltype(
            &TestingTestClass_SpecSectionTestNXNTests::TestFunction),
            &TestingTestClass_SpecSectionTestNXNTests::TestFunction>());
      //
      ARE_EQUAL(TestName, specifiedTestNXN.Name());
      ARE_EQUAL("TESTS(TestClassName)\nTEST(TestName)", specifiedTestNXN.TestClassTestNameLines());
      ARE_EQUAL("(0)", specifiedTestNXN.FileLineString());
      const PmfToken* const expectedTestNXNPmfToken = ZenUnit::PmfToken::Instantiate<
         decltype(&TestingTestClass_SpecSectionTestNXNTests::TestFunction),
         &TestingTestClass_SpecSectionTestNXNTests::TestFunction>();
      ARE_EQUAL(expectedTestNXNPmfToken, specifiedTestNXN._testNXNPmfToken);
   }

   TEST1X1(NumberOfTestCases_GetsTestFromAddress_ReturnsTestNumberOfTestCases,
      size_t testNumberOfTestCases,
      1ULL,
      2ULL)
   {
      TestMock* testMock = new TestMock;
      testMock->NumberOfTestCasesMock.ExpectAndReturn(testNumberOfTestCases);
      const unique_ptr<Test> testMockUniquePtr((Test*)testMock);
      _specSectionTestNXNSelfMocked->GetTestNXNFromPmfTokenMock.ExpectAndReturn(&testMockUniquePtr);
      //
      const size_t numberOfTestCases = _specSectionTestNXNSelfMocked->NumberOfTestCases();
      //
      ZEN(_specSectionTestNXNSelfMocked->GetTestNXNFromPmfTokenMock.AssertCalledOnce());
      ZEN(testMock->NumberOfTestCasesMock.AssertCalledOnce());
      ARE_EQUAL(testNumberOfTestCases, numberOfTestCases);
   }

   TEST(PrintPostTestNameMessage_WriteNewline)
   {
      ConsoleMock consoleMock;
      consoleMock.WriteLineMock.Expect();
      //
      _specSectionTestNXN->PrintPostTestNameMessage(&consoleMock);
      //
      ZEN(consoleMock.WriteLineMock.AssertCalledOnceWith("..."));
   }

   TEST(Run_GetsTestFromAddress_RunsTest_ReturnsTestResults)
   {
      TestMock* const testMock = new TestMock;
      const vector<TestResult> testTestResults = { TestResult::TestingNonDefault };
      testMock->RunMock.ExpectAndReturn(testTestResults);
      const unique_ptr<Test> testMockUniquePtr((Test*)testMock);
      _specSectionTestNXNSelfMocked->GetTestNXNFromPmfTokenMock.ExpectAndReturn(&testMockUniquePtr);
      //
      const vector<TestResult> testResults = _specSectionTestNXNSelfMocked->Run();
      //
      ZEN(_specSectionTestNXNSelfMocked->GetTestNXNFromPmfTokenMock.AssertCalledOnce());
      ZEN(testMock->RunMock.AssertCalledOnce());
      VECTORS_EQUAL(testTestResults, testResults);
   }

   TEST(GetTestNXNFromPmfToken_ReturnsTestClassTypeTestNXNPmfToTestReturnValue)
   {
      TestingTestClass_SpecSectionTestNXNTests::didCallTestNXNPmfToTest = false;
      //
      const std::unique_ptr<Test>* testNXN = _specSectionTestNXN->GetTestNXNFromPmfToken();
      //
      IS_TRUE(TestingTestClass_SpecSectionTestNXNTests::didCallTestNXNPmfToTest);
      ARE_EQUAL(testNXN, &TestingTestClass_SpecSectionTestNXNTests::TestNXNPmfToTestReturnValue);
   }

   TEST(TestOverrides_EachThrow)
   {
      THROWS(_specSectionTestNXN->NewTestClass(), logic_error, "N/A");
      THROWS(_specSectionTestNXN->Startup(), logic_error, "N/A");
      THROWS(_specSectionTestNXN->TestBody(), logic_error, "N/A");
      THROWS(_specSectionTestNXN->Cleanup(), logic_error, "N/A");
      THROWS(_specSectionTestNXN->DeleteTestClass(), logic_error, "N/A");
   }

   }; RUN(SpecSectionTestNXNTests)
}
