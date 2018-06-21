#pragma once

template<typename ClassType>
class VoidZeroArgMemberFunctionCallerMock : public Zen::Mock<ZeroArgMemberFunctionCaller<void, ClassType>>
{
public:
   using VoidZeroArgConstMemberFunctionType = void (ClassType::*)() const;
   ZENMOCK_VOID2_CONST(ConstCall, const ClassType*, VoidZeroArgConstMemberFunctionType)

   using VoidZeroArgNonConstMemberFunctionType = void (ClassType::*)();
   ZENMOCK_VOID2_CONST(NonConstCall, ClassType*, VoidZeroArgNonConstMemberFunctionType)
};