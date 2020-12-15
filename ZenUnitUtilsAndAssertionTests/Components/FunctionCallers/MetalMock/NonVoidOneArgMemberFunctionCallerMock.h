#pragma once

template<typename ReturnType, typename ClassType, typename Arg1Type>
class NonVoidOneArgMemberFunctionCallerMock : public Metal::Mock<ZenUnit::NonVoidOneArgMemberFunctionCaller<ReturnType, ClassType, Arg1Type>>
{
public:
   using NonVoidOneArgMemberFunctionType = ReturnType(ClassType::*)(Arg1Type);
   METALMOCK_NONVOID3_CONST(ReturnType, CallNonConstMemberFunction, ClassType*, NonVoidOneArgMemberFunctionType, Arg1Type)
};
