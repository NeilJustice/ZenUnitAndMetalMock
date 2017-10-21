#pragma once
#include "ZenUnit/ZenMock/2/TwoArgumentMocker.h"
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/ValueReturner.h"

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type, arg2Type)".
#define ZENMOCK_NONVOID2(returnType, functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_NONVOID2_DEFINED(returnType, functionName, arg1Type, arg2Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type, arg2Type) const".
#define ZENMOCK_NONVOID2_CONST(returnType, functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_NONVOID2_DEFINED(returnType, functionName, arg1Type, arg2Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type, arg2Type)".
#define ZENMOCK_NONVOID2_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_NONVOID2_DEFINED(returnType, functionName, arg1Type, arg2Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type, arg2Type) const".
#define ZENMOCK_NONVOID2_CONST_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_NONVOID2_DEFINED(returnType, functionName, arg1Type, arg2Type,        , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "returnType functionName(arg1Type, arg2Type)".
#define ZENMOCK_NONVOID2_FREE(returnType, functionName, arg1Type, arg2Type, ...) \
   ZenMock::NonVoidTwoArgFunctionPointerMocker<returnType, arg1Type, arg2Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidTwoArgFunctionPointerMocker<returnType, arg1Type, arg2Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type", "#arg2Type")"));

// Defines a functionName_ZenMock object for mocking a static or namespaced function with signature "returnType qualifiedClassNameOrNamespace::functionName(arg1Type, arg2Type)".
#define ZENMOCK_NONVOID2_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, ...) \
   ZenMock::NonVoidTwoArgFunctionPointerMocker<returnType, arg1Type, arg2Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidTwoArgFunctionPointerMocker<returnType, arg1Type, arg2Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type")"));

#define ZENMOCK_NONVOID2_DEFINED(returnType, functionName, arg1Type, arg2Type, virtualness, constness, mutableness, finalness, ...) \
returnType functionName(arg1Type firstArgument, arg2Type secondArgument) constness finalness \
{ \
   return functionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(firstArgument, secondArgument); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidTwoArgumentMocker<returnType, arg1Type, arg2Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidTwoArgumentMocker<returnType, arg1Type, arg2Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type", "#arg2Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type>
   class NonVoidTwoArgumentMocker : public TwoArgumentMocker<Arg1Type, Arg2Type>, private ValueReturner<FunctionReturnType>
   {
   public:
      explicit NonVoidTwoArgumentMocker(const std::string& zenMockedFunctionSignature)
         : TwoArgumentMocker<Arg1Type, Arg2Type>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void ExpectAndReturn(ReturnType&& returnValue)
      {
         TwoArgumentMocker<Arg1Type, Arg2Type>::Expect();
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename ContainerType>
      void ExpectAndReturnValues(ContainerType&& returnValues)
      {
         TwoArgumentMocker<Arg1Type, Arg2Type>::Expect();
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ExpectAndReturnValues(const FirstReturnValue& firstReturnValue, const SubsequentReturnValues&... subsequentReturnValues)
      {
         TwoArgumentMocker<Arg1Type, Arg2Type>::Expect();
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(
            firstReturnValue,
            subsequentReturnValues...);
      }

      FunctionReturnType ZenMockItAndReturnValue(Arg1Type firstArgument, Arg2Type secondArgument)
      {
         TwoArgumentMocker<Arg1Type, Arg2Type>::ZenMockIt(firstArgument, secondArgument);
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type>
   class NonVoidTwoArgFunctionPointerMocker : public NonVoidTwoArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type>
   {
   public:
      explicit NonVoidTwoArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidTwoArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type>(zenMockedFunctionSignature)
      {
      }

      static FunctionReturnType ZenMockItFunctionPointer(
         NonVoidTwoArgFunctionPointerMocker<FunctionReturnType, Arg1Type, Arg2Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument)
      {
         return functionMocker->ZenMockItAndReturnValue(firstArgument, secondArgument);
      }
   };
}
