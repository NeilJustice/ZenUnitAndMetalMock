#pragma once

template<typename ReturnType, typename ClassType, typename Arg1Type, typename Arg2Type>
struct NonVoidTwoArgMemberFunctionCallerMock : public Zen::Mock<TwoArgMemberFunctionCaller<ReturnType, ClassType, Arg1Type, Arg2Type>>
{
   using NonVoidTwoArgConstMemberFunctionType = ReturnType (ClassType::*)(Arg1Type, Arg2Type) const;
   ZENMOCK_NONVOID4_CONST(ReturnType, ConstCall, const ClassType*, NonVoidTwoArgConstMemberFunctionType, Arg1Type, Arg2Type)
};