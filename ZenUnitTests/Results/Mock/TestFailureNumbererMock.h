#pragma once
#include "ZenUnit/Results/TestFailureNumberer.h"

struct TestFailureNumbererMock : public Zen::Mock<TestFailureNumberer>
{
   ZENMOCK_NONVOID0(string, Next)
   ZENMOCK_VOID0(Reset)
};
