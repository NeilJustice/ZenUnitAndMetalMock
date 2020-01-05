#include "pch.h"

template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
class NonVoidFourArgFunctionPointerZenMockerMock : public Zen::Mock<
   ZenMock::NonVoidFourArgFunctionPointerZenMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
{
public:
   ZENMOCK_NONVOID4(const FunctionReturnType&, ZenMockItAndReturnValue, Arg1Type, Arg2Type, Arg3Type, Arg4Type)
};

template<
   typename FunctionReturnType,
   typename Arg1Type,
   typename Arg2Type,
   typename Arg3Type,
   typename Arg4Type>
TEMPLATE_TESTS(NonVoidFourArgFunctionPointerZenMockerTests,
   FunctionReturnType,
   Arg1Type,
   Arg2Type,
   Arg3Type,
   Arg4Type)
AFACT(ZenMockItFunctionPointer_ReturnsResultOfCallingToZenMockItAndReturnValue)
EVIDENCE

using NonVoidFourArgFunctionPointerZenMockerType = ZenMock::NonVoidFourArgFunctionPointerZenMocker<
   FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>;
NonVoidFourArgFunctionPointerZenMockerType* _nonVoidFourArgFunctionPointerZenMocker = nullptr;

TEST(ZenMockItFunctionPointer_ReturnsResultOfCallingToZenMockItAndReturnValue)
{
   NonVoidFourArgFunctionPointerZenMockerMock<
      FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>
      nonVoidFourArgFunctionPointerZenMockerMock;
   const FunctionReturnType& functionReturnValue =
      nonVoidFourArgFunctionPointerZenMockerMock.ZenMockItAndReturnValueMock.ReturnRandom();

   const Arg1Type firstArgument = ZenUnit::Random<Arg1Type>();
   const Arg2Type secondArgument = ZenUnit::Random<Arg2Type>();
   const Arg3Type thirdArgument = ZenUnit::Random<Arg3Type>();
   const Arg4Type fourthArgument = ZenUnit::Random<Arg4Type>();
   //
   const FunctionReturnType& returnedFunctionReturnValue =
      NonVoidFourArgFunctionPointerZenMockerType::ZenMockItFunctionPointer(
         &nonVoidFourArgFunctionPointerZenMockerMock,
         firstArgument, secondArgument, thirdArgument, fourthArgument);
   //
   ZENMOCK(nonVoidFourArgFunctionPointerZenMockerMock.ZenMockItAndReturnValueMock.CalledOnceWith(
      firstArgument, secondArgument, thirdArgument, fourthArgument));
   ARE_EQUAL(functionReturnValue, returnedFunctionReturnValue);
}

RUN_TEMPLATE_TESTS(NonVoidFourArgFunctionPointerZenMockerTests, int, int, int, int, int)
