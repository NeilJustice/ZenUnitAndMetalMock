#pragma once

struct TestCaseIndexGeneratorMock : public Zen::Mock<TestCaseIndexGenerator>
{
   ZENMOCK_VOID2(Initialize, size_t, size_t)
   ZENMOCK_NONVOID0(size_t, NextTestCaseIndex)
   ZENMOCK_VOID(ResetTestCaseArgsIndex)
};
