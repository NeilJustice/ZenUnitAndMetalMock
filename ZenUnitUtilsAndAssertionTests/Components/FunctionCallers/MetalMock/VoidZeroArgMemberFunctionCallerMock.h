#pragma once

template<typename ClassType>
class VoidZeroArgMemberFunctionCallerMock : public Metal::Mock<ZenUnit::VoidZeroArgMemberFunctionCaller<ClassType>>
{
public:
   using ConstMemberFunctionType = void(ClassType::*)() const;
   METALMOCK_VOID2_CONST(CallConstMemberFunction, const ClassType*, ConstMemberFunctionType)

   using NonConstMemberFunctionType = void(ClassType::*)();
   METALMOCK_VOID2_CONST(CallNonConstMemberFunction, ClassType*, NonConstMemberFunctionType)
};
