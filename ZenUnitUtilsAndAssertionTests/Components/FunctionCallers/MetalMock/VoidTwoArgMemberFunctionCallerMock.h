#pragma once

template<typename ClassType, typename Arg1Type, typename Arg2Type>
class VoidTwoArgMemberFunctionCallerMock : public Metal::Mock<ZenUnit::VoidTwoArgMemberFunctionCaller<ClassType, Arg1Type, Arg2Type>>
{
public:
   using VoidTwoArgConstMemberFunctionType = void(ClassType::*)(Arg1Type, Arg2Type) const;
   METALMOCK_VOID4_CONST(CallConstMemberFunction, const ClassType*, VoidTwoArgConstMemberFunctionType, Arg1Type, Arg2Type)
};
