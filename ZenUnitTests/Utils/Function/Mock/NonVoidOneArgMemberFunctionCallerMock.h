#pragma once

template<typename ReturnType, typename ClassType, typename Arg1Type>
struct NonVoidOneArgMemberFunctionCallerMock : public Zen::Mock<OneArgMemberFunctionCaller<ReturnType, ClassType, Arg1Type>>
{
   using NonVoidOneArgMemberFunctionType = ReturnType(ClassType::*)(Arg1Type);
   ZENMOCK_NONVOID3_CONST(ReturnType, NonConstCall, ClassType*, NonVoidOneArgMemberFunctionType, Arg1Type)
};
