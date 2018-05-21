#pragma once

template<typename ClassType, typename Arg1Type, typename Arg2Type>
struct VoidTwoArgMemberFunctionCallerMock : public Zen::Mock<TwoArgMemberFunctionCaller<void, ClassType, Arg1Type, Arg2Type>>
{
   using VoidTwoArgConstMemberFunctionType = void (ClassType::*)(Arg1Type, Arg2Type) const;
   ZENMOCK_VOID4_CONST(ConstCall, const ClassType*, VoidTwoArgConstMemberFunctionType, Arg1Type, Arg2Type)
};