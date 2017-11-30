#pragma once
#include "ZenUnit/ZenMock/4/FourArgumentMocker.h"
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/ValueReturner.h"

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type)".
#define ZENMOCK_NONVOID4(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
        ZENMOCK_NONVOID4_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type) const".
#define ZENMOCK_NONVOID4_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
        ZENMOCK_NONVOID4_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type)".
#define ZENMOCK_NONVOID4_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
        ZENMOCK_NONVOID4_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type) const".
#define ZENMOCK_NONVOID4_CONST_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
        ZENMOCK_NONVOID4_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type,        , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type)".
#define ZENMOCK_NONVOID4_FREE(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
   ZenMock::NonVoidFourArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidFourArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type")"));

// Defines a functionName_ZenMock object for mocking a static or namespaced function with signature "returnType qualifiedClassNameOrNamespace::functionName(arg1Type, arg2Type, arg3Type, arg4Type)".
#define ZENMOCK_NONVOID4_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
   ZenMock::NonVoidFourArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidFourArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type")"));

#define ZENMOCK_NONVOID4_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, virtualness, constness, mutableness, finalness, ...) \
returnType functionName(arg1Type firstArgument, arg2Type secondArgument, arg3Type thirdArgument, arg4Type fourthArgument) constness finalness \
{ \
   return functionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidFourArgumentMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidFourArgumentMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class NonVoidFourArgumentMocker : public FourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>, protected ValueReturner<FunctionReturnType>
   {
   public:
      explicit NonVoidFourArgumentMocker(const std::string& zenMockedFunctionSignature)
         : FourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void ExpectAndReturn(ReturnType&& returnValue)
      {
         _expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ExpectAndReturnValues(const FirstReturnValue& firstReturnValue, const SubsequentReturnValues&... subsequentReturnValues)
      {
         _expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(firstReturnValue, subsequentReturnValues...);
      }

      template<typename ContainerType>
      void ExpectAndReturnValues(ContainerType&& returnValues)
      {
         _expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      const DecayedFunctionReturnType& ZenMockItAndReturnValue(
         Arg1Type firstArgument,
         Arg2Type secondArgument,
         Arg3Type thirdArgument,
         Arg4Type fourthArgument)
      {
         FourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument);
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class NonVoidFourArgFunctionPointerMocker : public NonVoidFourArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>
   {
   public:
      explicit NonVoidFourArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidFourArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>(zenMockedFunctionSignature)
      {
      }

      static const DecayedFunctionReturnType& ZenMockItFunctionPointer(
         NonVoidFourArgFunctionPointerMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>* functionMocker,
         Arg1Type firstArgument,
         Arg2Type secondArgument,
         Arg3Type thirdArgument,
         Arg4Type fourthArgument)
      {
         return functionMocker->ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument);
      }
   };
}
