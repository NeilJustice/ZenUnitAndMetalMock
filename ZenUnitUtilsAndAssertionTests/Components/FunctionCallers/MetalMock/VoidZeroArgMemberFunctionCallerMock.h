#pragma once

template<typename ClassType>
class VoidZeroArgMemberFunctionCallerMock : public Metal::Mock<ZeroArgMemberFunctionCaller<void, ClassType>>
{
public:
   using VoidZeroArgConstMemberFunctionType = void (ClassType::*)() const;
   METALMOCK_VOID2_CONST(ConstCall, const ClassType*, VoidZeroArgConstMemberFunctionType)

   using VoidZeroArgNonConstMemberFunctionType = void (ClassType::*)();
   METALMOCK_VOID2_CONST(NonConstCall, ClassType*, VoidZeroArgNonConstMemberFunctionType)
};