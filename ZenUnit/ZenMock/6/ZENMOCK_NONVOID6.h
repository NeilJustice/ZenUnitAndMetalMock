#pragma once
#include "ZenUnit/ZenMock/6/SixArgumentMocker.h"
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/ValueReturner.h"

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type)".
#define ZENMOCK_NONVOID6(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
        ZENMOCK_NONVOID6_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type) const".
#define ZENMOCK_NONVOID6_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
        ZENMOCK_NONVOID6_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type)".
#define ZENMOCK_NONVOID6_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
        ZENMOCK_NONVOID6_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type) const".
#define ZENMOCK_NONVOID6_CONST_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
        ZENMOCK_NONVOID6_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type,        , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type)".
#define ZENMOCK_NONVOID6_FREE(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
   ZenMock::NonVoidSixArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidSixArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type")"));

// Defines a functionName_ZenMock object for mocking a static or namespaced function with signature "returnType qualifiedClassNameOrNamespace::functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type)".
#define ZENMOCK_NONVOID6_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
   ZenMock::NonVoidSixArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidSixArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type")"));

#define ZENMOCK_NONVOID6_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, virtualness, constness, mutableness, finalness, ...) \
returnType functionName(arg1Type firstArgument, arg2Type secondArgument, arg3Type thirdArgument, arg4Type fourthArgument, arg5Type fifthArgument, arg6Type sixthArgument) constness finalness \
{ \
   return functionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidSixArgumentMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidSixArgumentMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   class NonVoidSixArgumentMocker : public SixArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>, protected ValueReturner<FunctionReturnType>
   {
   public:
      explicit NonVoidSixArgumentMocker(const std::string& zenMockedFunctionSignature)
         : SixArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void ExpectAndReturn(ReturnType&& returnValue)
      {
         SixArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>::Expect();
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ExpectAndReturnValues(const FirstReturnValue& firstReturnValue, const SubsequentReturnValues&... subsequentReturnValues)
      {
         SixArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>::Expect();
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(firstReturnValue, subsequentReturnValues...);
      }

      template<typename ContainerType>
      void ExpectAndReturnValues(ContainerType&& returnValues)
      {
         SixArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>::Expect();
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      const DecayedFunctionReturnType& ZenMockItAndReturnValue(
         Arg1Type firstArgument,
         Arg2Type secondArgument,
         Arg3Type thirdArgument,
         Arg4Type fourthArgument,
         Arg5Type fifthArgument,
         Arg6Type sixthArgument)
      {
         SixArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ExceptionThrower>::ZenMockIt(
            firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument);
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   class NonVoidSixArgFunctionPointerMocker : public NonVoidSixArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>
   {
   public:
      explicit NonVoidSixArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidSixArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>(zenMockedFunctionSignature)
      {
      }

      static const DecayedFunctionReturnType& ZenMockItFunctionPointer(
         NonVoidSixArgFunctionPointerMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>* functionMocker,
         Arg1Type firstArgument,
         Arg2Type secondArgument,
         Arg3Type thirdArgument,
         Arg4Type fourthArgument,
         Arg5Type fifthArgument,
         Arg6Type sixthArgument)
      {
         return functionMocker->ZenMockItAndReturnValue(
            firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument);
      }
   };
}
