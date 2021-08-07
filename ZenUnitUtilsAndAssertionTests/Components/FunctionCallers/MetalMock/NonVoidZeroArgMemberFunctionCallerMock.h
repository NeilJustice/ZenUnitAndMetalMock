#pragma once

template<typename ReturnType, typename ClassType>
class NonVoidZeroArgMemberFunctionCallerMock : public Metal::Mock<ZenUnit::NonVoidZeroArgMemberFunctionCaller<ReturnType, ClassType>>
{
public:
   using ConstMemberFunctionType = ReturnType(ClassType::*)() const;
   METALMOCK_NONVOID2_CONST(ReturnType, CallConstMemberFunction, const ClassType*, ConstMemberFunctionType)

   using NonConstMemberFunctionType = ReturnType(ClassType::*)();
   METALMOCK_NONVOID2_CONST(ReturnType, CallNonConstMemberFunction, ClassType*, NonConstMemberFunctionType)
};
