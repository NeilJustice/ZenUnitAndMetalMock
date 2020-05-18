#pragma once

class TestClassRunnerMock : public Zen::Mock<TestClassRunner>
{
public:
   ZENMOCK_NONVOID0_CONST(const char*, TestClassName)
   ZENMOCK_NONVOID0_CONST(size_t, NumberOfTestCases)
   ZENMOCK_NONVOID1_CONST(bool, HasTestThatMatchesTestNameFilter, const TestNameFilter&)
   ZENMOCK_NONVOID0(TestClassResult, RunTests)
};
