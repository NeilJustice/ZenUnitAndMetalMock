#include "pch.h"
#include "ZenUnit/Tests/SpecSectionTestNXN.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Tests/Mock/TestMock.h"

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
   SPEC(PmfTokenToTest_ReturnsTestClassTypeTestNXNPmfToTestReturnValue);
   SPEC(TestOverrides_EachThrow)
   SPEC(CodeCoverage_TestFunction)
   SPECEND

   class SpecSectionTestNXNSelfMocked : public Zen::Mock<SpecSectionTestNXN<TestingTestClass_SpecSectionTestNXNTests>>
   {
   public:
      SpecSectionTestNXNSelfMocked() : Zen::Mock<SpecSectionTestNXN<
         TestingTestClass_SpecSectionTestNXNTests>>("", "", nullptr) {}
      ZENMOCK_NONVOID0_CONST(const std::unique_ptr<Test>*, PmfTokenToTest)
   };

   unique_ptr<SpecSectionTestNXN<TestingTestClass_SpecSectionTestNXNTests>> _specSectionTestNXN;
   unique_ptr<SpecSectionTestNXNSelfMocked> _specSectionTestNXNSelfMocked;

   STARTUP
   {
      _specSectionTestNXN = make_unique<SpecSectionTestNXN<TestingTestClass_SpecSectionTestNXNTests>>("", "", nullptr);
      _specSectionTestNXNSelfMocked = make_unique<SpecSectionTestNXNSelfMocked>();
   }

   TEST(ThreeArgConstructor_SetsTestName_SetsTestNXNPmf)
   {
      const char* const TestClassName = "Tests";
      const char* const TestName = "Test";
      //
      const SpecSectionTestNXN<TestingTestClass_SpecSectionTestNXNTests> specifiedTestNXN(
         TestClassName, TestName, PmfToken::Instantiate<decltype(
            &TestingTestClass_SpecSectionTestNXNTests::TestFunction),
            &TestingTestClass_SpecSectionTestNXNTests::TestFunction>());
      //
      ARE_EQUAL(TestName, specifiedTestNXN.Name());
      ARE_EQUAL("TESTS(Tests)\nTEST(Test)", specifiedTestNXN.FullTestName());
      ARE_EQUAL("(0)", specifiedTestNXN.FileLineString());
      const PmfToken* const expectedTestNXNPmfToken = ZenUnit::PmfToken::Instantiate<
         decltype(&TestingTestClass_SpecSectionTestNXNTests::TestFunction),
         &TestingTestClass_SpecSectionTestNXNTests::TestFunction>();
      ARE_EQUAL(expectedTestNXNPmfToken, specifiedTestNXN._testNXNPmfToken);
   }

   TEST1X1(NumberOfTestCases_GetsTestFromAddress_ReturnsTestNumberOfTestCases,
      size_t testNumberOfTestCases,
      1ull,
      2ull)
   {
      TestMock* testMock = new TestMock;
      testMock->NumberOfTestCasesMock.ExpectAndReturn(testNumberOfTestCases);
      const unique_ptr<Test> testMockUniquePtr(testMock);
      _specSectionTestNXNSelfMocked->PmfTokenToTestMock.ExpectAndReturn(&testMockUniquePtr);
      //
      const size_t numberOfTestCases = _specSectionTestNXNSelfMocked->NumberOfTestCases();
      //
      ZEN(_specSectionTestNXNSelfMocked->PmfTokenToTestMock.AssertCalledOnce());
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
      const unique_ptr<Test> testMockUniquePtr(testMock);
      _specSectionTestNXNSelfMocked->PmfTokenToTestMock.ExpectAndReturn(&testMockUniquePtr);
      //
      const vector<TestResult> testResults = _specSectionTestNXNSelfMocked->Run();
      //
      ZEN(_specSectionTestNXNSelfMocked->PmfTokenToTestMock.AssertCalledOnce());
      ZEN(testMock->RunMock.AssertCalledOnce());
      VECTORS_EQUAL(testTestResults, testResults);
   }

   TEST(PmfTokenToTest_ReturnsTestClassTypeTestNXNPmfToTestReturnValue)
   {
      TestingTestClass_SpecSectionTestNXNTests::didCallTestNXNPmfToTest = false;
      //
      const std::unique_ptr<Test>* testNXN = _specSectionTestNXN->PmfTokenToTest();
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

   TEST(CodeCoverage_TestFunction)
   {
      TestingTestClass_SpecSectionTestNXNTests t;
      t.TestFunction(0);
   }

   }; RUN(SpecSectionTestNXNTests)
}
