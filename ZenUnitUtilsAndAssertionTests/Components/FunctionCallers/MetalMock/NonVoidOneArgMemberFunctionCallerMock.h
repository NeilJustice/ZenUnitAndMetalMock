#pragma once

template<typename ReturnType, typename ClassType, typename Arg1Type>
class NonVoidOneArgMemberFunctionCallerMock : public Metal::Mock<ZenUnit::NonVoidOneArgMemberFunctionCaller<ReturnType, ClassType, Arg1Type>>
{
public:
   using NonVoidOneArgMemberFunctionType_Const = ReturnType(ClassType::*)(Arg1Type) const;
   METALMOCK_NONVOID3_CONST(ReturnType, CallConstMemberFunction, const ClassType*, NonVoidOneArgMemberFunctionType_Const, Arg1Type)

   using NonVoidOneArgMemberFunctionType_NonConst = ReturnType(ClassType::*)(Arg1Type);
   METALMOCK_NONVOID3_CONST(ReturnType, CallNonConstMemberFunction, ClassType*, NonVoidOneArgMemberFunctionType_NonConst, Arg1Type)
};
