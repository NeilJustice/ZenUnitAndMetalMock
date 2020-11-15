#include "pch.h"

namespace MetalMock
{
   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class NonVoidFourArgFunctionPointerMetalMockerMock : public Metal::Mock<
      NonVoidFourArgFunctionPointerMetalMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
   {
   public:
      NonVoidFourArgFunctionPointerMetalMockerMock()
         : Metal::Mock<NonVoidFourArgFunctionPointerMetalMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>>(
            "FunctionSignature_NonVoidFourArgFunctionPointerMetalMockerMock")
      {
      }

      METALMOCK_NONVOID4(FunctionReturnType, MetalMockItAndReturnValue, Arg1Type, Arg2Type, Arg3Type, Arg4Type)
   };
}

template<
   typename FunctionReturnType,
   typename Arg1Type,
   typename Arg2Type,
   typename Arg3Type,
   typename Arg4Type>
TEMPLATE_TESTS(NonVoidFourArgFunctionPointerMetalMockerTests,
   FunctionReturnType,
   Arg1Type,
   Arg2Type,
   Arg3Type,
   Arg4Type)
AFACT(MetalMockItFunctionPointer_ReturnsResultOfCallingToMetalMockItAndReturnValue)
EVIDENCE

using NonVoidFourArgFunctionPointerMetalMockerType = MetalMock::NonVoidFourArgFunctionPointerMetalMocker<
   FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>;

TEST(MetalMockItFunctionPointer_ReturnsResultOfCallingToMetalMockItAndReturnValue)
{
   MetalMock::NonVoidFourArgFunctionPointerMetalMockerMock<
      FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>
      nonVoidFourArgFunctionPointerMetalMockerMock;
   const FunctionReturnType& functionReturnValue =
      nonVoidFourArgFunctionPointerMetalMockerMock.MetalMockItAndReturnValueMock.ReturnRandom();

   const Arg1Type firstArgument = ZenUnit::Random<Arg1Type>();
   const Arg2Type secondArgument = ZenUnit::Random<Arg2Type>();
   const Arg3Type thirdArgument = ZenUnit::Random<Arg3Type>();
   const Arg4Type fourthArgument = ZenUnit::Random<Arg4Type>();
   //
   const FunctionReturnType& returnedFunctionReturnValue =
      NonVoidFourArgFunctionPointerMetalMockerType::MetalMockItFunctionPointer(
         &nonVoidFourArgFunctionPointerMetalMockerMock,
         firstArgument, secondArgument, thirdArgument, fourthArgument);
   //
   METALMOCK(nonVoidFourArgFunctionPointerMetalMockerMock.MetalMockItAndReturnValueMock.CalledOnceWith(
      firstArgument, secondArgument, thirdArgument, fourthArgument));
   ARE_EQUAL(functionReturnValue, returnedFunctionReturnValue);
}

RUN_TEMPLATE_TESTS(NonVoidFourArgFunctionPointerMetalMockerTests, int, int, int, int, int)
