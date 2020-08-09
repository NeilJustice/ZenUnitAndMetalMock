#pragma once

template<typename ReturnType, typename ClassType, typename Arg1Type, typename Arg2Type>
class NonVoidTwoArgMemberFunctionCallerMock : public Metal::Mock<TwoArgMemberFunctionCaller<ReturnType, ClassType, Arg1Type, Arg2Type>>
{
public:
   using NonVoidTwoArgConstMemberFunctionType = ReturnType (ClassType::*)(Arg1Type, Arg2Type) const;
   METALMOCK_NONVOID4_CONST(ReturnType, ConstCall, const ClassType*, NonVoidTwoArgConstMemberFunctionType, Arg1Type, Arg2Type)
};