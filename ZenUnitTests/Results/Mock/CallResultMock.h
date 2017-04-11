#pragma once
#include "ZenUnit/Results/CallResult.h"

struct CallResultMock : public Zen::Mock<CallResult>
{
   ZENMOCK_VOID1(Assign, const CallResult&)
};
