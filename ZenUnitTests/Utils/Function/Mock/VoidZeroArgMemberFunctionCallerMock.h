#pragma once

template<typename ClassType>
struct VoidZeroArgMemberFunctionCallerMock : public Zen::Mock<ZeroArgMemberFunctionCaller<void, ClassType>>
{
   using VoidZeroArgConstMemberFunctionType = void (ClassType::*)() const;
   ZENMOCK_VOID2_CONST(ConstCall, const ClassType*, VoidZeroArgConstMemberFunctionType)

   using VoidZeroArgNonConstMemberFunctionType = void (ClassType::*)();
   ZENMOCK_VOID2_CONST(NonConstCall, ClassType*, VoidZeroArgNonConstMemberFunctionType)
};