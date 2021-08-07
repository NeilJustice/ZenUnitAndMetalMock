#pragma once

class TestFailureNumbererMock : public Metal::Mock<TestFailureNumberer>
{
public:
   METALMOCK_NONVOID0(string, NextNumberedTestFailureArrow)
   METALMOCK_VOID0(ResetTestFailureNumber)
};
