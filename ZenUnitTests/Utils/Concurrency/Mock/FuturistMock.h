#pragma once
#include "ZenUnit/Utils/Concurrency/Futurist.h"

template<typename ThisPointerType>
struct FuturistMock : public Zen::Mock<Futurist<ThisPointerType>>
{
   using VoidMemberFunctionType = void(ThisPointerType::*)();
   ZENMOCK_NONVOID2_CONST(shared_ptr<VoidFuture>, Async, VoidMemberFunctionType, ThisPointerType*)
   ZENMOCK_NONVOID2_CONST(future_status, WaitMilliseconds, future<void>*, unsigned)
};
