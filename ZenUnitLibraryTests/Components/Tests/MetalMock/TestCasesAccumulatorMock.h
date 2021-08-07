#pragma once

class TestCasesAccumulatorMock : public Metal::Mock<TestCasesAccumulator>
{
public:
   METALMOCK_NONVOID1_CONST(size_t, SumNumberOfTestCases, const std::vector<std::unique_ptr<Test>>*)
};
