#pragma once

struct TestClassRunnerMock : public Zen::Mock<TestClassRunner>
{
   ZENMOCK_NONVOID0_CONST(const char*, TestClassName)
   ZENMOCK_NONVOID0_CONST(size_t, NumberOfTestCases)
   ZENMOCK_NONVOID0(TestClassResult, RunTests)
};
