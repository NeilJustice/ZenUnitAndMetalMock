#pragma once
#include "ZenUnit/ZenMock/3/ThreeArgumentMocker.h"
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/ValueReturner.h"

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type, arg2Type, arg3Type)".
#define ZENMOCK_NONVOID3(returnType, functionName, arg1Type, arg2Type, arg3Type, ...) \
        ZENMOCK_NONVOID3_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type, arg2Type, arg3Type) const".
#define ZENMOCK_NONVOID3_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, ...) \
        ZENMOCK_NONVOID3_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type, arg2Type, arg3Type)".
#define ZENMOCK_NONVOID3_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, ...) \
        ZENMOCK_NONVOID3_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type, arg2Type, arg3Type) const".
#define ZENMOCK_NONVOID3_CONST_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, ...) \
        ZENMOCK_NONVOID3_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type,        , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "returnType functionName(arg1Type, arg2Type, arg3Type)".
#define ZENMOCK_NONVOID3_FREE(returnType, functionName, arg1Type, arg2Type, arg3Type, ...) \
   ZenMock::NonVoidThreeArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidThreeArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type")"));

// Defines a functionName_ZenMock object for mocking a static or namespaced function with signature "returnType qualifiedClassNameOrNamespace::functionName(arg1Type, arg2Type, arg3Type)".
#define ZENMOCK_NONVOID3_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, ...) \
   ZenMock::NonVoidThreeArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidThreeArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type")"));

#define ZENMOCK_NONVOID3_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, virtualness, constness, mutableness, finalness, ...) \
returnType functionName(arg1Type firstArgument, arg2Type secondArgument, arg3Type thirdArgument) constness finalness \
{ \
   return functionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidThreeArgumentMocker<returnType, arg1Type, arg2Type, arg3Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidThreeArgumentMocker<returnType, arg1Type, arg2Type, arg3Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class NonVoidThreeArgumentMocker : public ThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>, protected ValueReturner<FunctionReturnType>
   {
   public:
      explicit NonVoidThreeArgumentMocker(const std::string& zenMockedFunctionSignature)
         : ThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void ExpectAndReturn(ReturnType&& returnValue)
      {
         ThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>::Expect();
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename ContainerType>
      void ExpectAndReturnValues(ContainerType&& returnValues)
      {
         ThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>::Expect();
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ExpectAndReturnValues(const FirstReturnValue& firstReturnValue, const SubsequentReturnValues&... subsequentReturnValues)
      {
         ThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>::Expect();
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(firstReturnValue, subsequentReturnValues...);
      }

      const DecayedFunctionReturnType& ZenMockItAndReturnValue(
         Arg1Type firstArgument,
         Arg2Type secondArgument,
         Arg3Type thirdArgument)
      {
         ThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>::ZenMockIt(firstArgument, secondArgument, thirdArgument);
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class NonVoidThreeArgFunctionPointerMocker : public NonVoidThreeArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type>
   {
   public:
      explicit NonVoidThreeArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidThreeArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type>(zenMockedFunctionSignature)
      {
      }

      static const DecayedFunctionReturnType& ZenMockItFunctionPointer(
         NonVoidThreeArgFunctionPointerMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type>* functionMocker,
         Arg1Type firstArgument,
         Arg2Type secondArgument,
         Arg3Type thirdArgument)
      {
         return functionMocker->ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument);
      }
   };
}
