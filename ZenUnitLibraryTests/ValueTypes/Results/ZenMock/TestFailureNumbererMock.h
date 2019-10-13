#pragma once

class TestFailureNumbererMock : public Zen::Mock<TestFailureNumberer>
{
public:
   ZENMOCK_NONVOID0(string, Next)
   ZENMOCK_VOID0(Reset)
};
