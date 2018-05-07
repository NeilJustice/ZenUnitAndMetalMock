#pragma once

template<typename ClassType, typename Arg1Type>
struct VoidOneArgMemberFunctionCallerMock : public Zen::Mock<OneArgMemberFunctionCaller<void, ClassType, Arg1Type>>
{
   using ConstMemberFunctionType = void(ClassType::*)(Arg1Type) const;
   ZENMOCK_VOID3_CONST(ConstCall, const ClassType*, ConstMemberFunctionType, Arg1Type)

   using NonConstMemberFunctionType = void(ClassType::*)(Arg1Type);
   ZENMOCK_VOID3_CONST(NonConstCall, ClassType*, NonConstMemberFunctionType, Arg1Type)
};
