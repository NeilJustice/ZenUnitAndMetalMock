#pragma once

class TestClassRunnerMock : public Zen::Mock<TestClassRunner>
{
public:
   METALMOCK_NONVOID0_CONST(const char*, TestClassName)
   METALMOCK_NONVOID0_CONST(size_t, NumberOfTestCases)
   METALMOCK_NONVOID1_CONST(bool, HasTestThatMatchesTestNameFilter, const TestNameFilter&)
   METALMOCK_NONVOID0(TestClassResult, RunTests)
};
