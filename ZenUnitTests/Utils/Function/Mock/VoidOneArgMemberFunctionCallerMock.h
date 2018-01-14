#pragma once

template<typename ClassType, typename Arg1Type>
struct VoidOneArgMemberFunctionCallerMock : public Zen::Mock<OneArgMemberFunctionCaller<void, ClassType, Arg1Type>>
{
   using VoidOneArgMemberFunctionType = void(ClassType::*)(Arg1Type);
   ZENMOCK_VOID3_CONST(NonConstCall, ClassType*, VoidOneArgMemberFunctionType, Arg1Type)
};
