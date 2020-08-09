#pragma once

class TestFailureNumbererMock : public Metal::Mock<TestFailureNumberer>
{
public:
   METALMOCK_NONVOID0(string, Next)
   METALMOCK_VOID0(Reset)
};
