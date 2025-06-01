#pragma once

class TestMock : public Metal::Mock<Test>
{
public:
   TestMock() noexcept
      : Metal::Mock<Test>("", "", static_cast<unsigned char>(0))
   {
   }

   METALMOCK_NONVOID0_CONST(const char*, Name)
   METALMOCK_NONVOID0_CONST(size_t, NumberOfTestCases)
   METALMOCK_VOID1_CONST(WritePostTestNameMessage, const Console*)
   METALMOCK_NONVOID0(vector<TestResult>, RunTest)
   METALMOCK_VOID0(NewTestClass)
   METALMOCK_VOID0(Startup)
   METALMOCK_VOID0(TestBody)
   METALMOCK_VOID0(Cleanup)
   METALMOCK_VOID0(DeleteTestClass)
   METALMOCK_VOID2_CONST(WritePostTestCompletionMessage, const Console*, const TestResult&)
};
