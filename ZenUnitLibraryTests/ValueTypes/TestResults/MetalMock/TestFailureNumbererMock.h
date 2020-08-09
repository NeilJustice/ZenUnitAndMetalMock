#pragma once

class TestFailureNumbererMock : public Zen::Mock<TestFailureNumberer>
{
public:
   METALMOCK_NONVOID0(string, Next)
   METALMOCK_VOID0(Reset)
};
