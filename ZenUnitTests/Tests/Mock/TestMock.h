#pragma once

struct TestMock : public Zen::Mock<Test>
{
   TestMock() noexcept
      : Zen::Mock<Test>("", "", static_cast<unsigned char>(0))
   {
   }

   ZENMOCK_NONVOID0_CONST(const char*, Name)
   ZENMOCK_NONVOID0_CONST(string, FullTestNameValue)
   ZENMOCK_NONVOID0_CONST(string, FileLineString)
   ZENMOCK_NONVOID0_CONST(size_t, NumberOfTestCases)
   ZENMOCK_VOID1_CONST(WritePostTestNameMessage, const Console*)
   ZENMOCK_NONVOID0(vector<TestResult>, RunTest)
   ZENMOCK_VOID0(NewTestClass)
   ZENMOCK_VOID0(Startup)
   ZENMOCK_VOID0(TestBody)
   ZENMOCK_VOID0(Cleanup)
   ZENMOCK_VOID0(DeleteTestClass)
   ZENMOCK_VOID2_CONST(WritePostTestCompletionMessage, const Console*, const TestResult&)
};
