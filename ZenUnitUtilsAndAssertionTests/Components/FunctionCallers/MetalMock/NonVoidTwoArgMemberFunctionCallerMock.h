#pragma once

template<typename ReturnType, typename ClassType, typename Arg1Type, typename Arg2Type>
class NonVoidTwoArgMemberFunctionCallerMock : public Metal::Mock<ZenUnit::NonVoidTwoArgMemberFunctionCaller<ReturnType, ClassType, Arg1Type, Arg2Type>>
{
public:
   using NonVoidTwoArgConstMemberFunctionType = ReturnType(ClassType::*)(Arg1Type, Arg2Type) const;
   METALMOCK_NONVOID4_CONST(ReturnType, CallConstMemberFunction, const ClassType*, NonVoidTwoArgConstMemberFunctionType, Arg1Type, Arg2Type)

   using NonVoidTwoArgNonConstMemberFunctionType = ReturnType(ClassType::*)(Arg1Type, Arg2Type);
   METALMOCK_NONVOID4_CONST(ReturnType, CallNonConstMemberFunction, ClassType*, NonVoidTwoArgNonConstMemberFunctionType, Arg1Type, Arg2Type)
};
