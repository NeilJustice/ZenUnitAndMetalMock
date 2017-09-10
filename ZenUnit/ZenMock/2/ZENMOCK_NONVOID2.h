#pragma once
#include "ZenUnit/ZenMock/2/TwoArgumentMocker.h"
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/ValueReturner.h"

// Virtual Functions
#define ZENMOCK_NONVOID2(returnType, functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_NONVOID2_DEFINED(returnType, functionName, arg1Type, arg2Type, virtual,      ,        , final, __VA_ARGS__)

#define ZENMOCK_NONVOID2_CONST(returnType, functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_NONVOID2_DEFINED(returnType, functionName, arg1Type, arg2Type, virtual, const, mutable, final, __VA_ARGS__)

// Non-Virtual Functions
#define ZENMOCK_NONVOID2_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_NONVOID2_DEFINED(returnType, functionName, arg1Type, arg2Type,        ,      ,        ,         , __VA_ARGS__)

#define ZENMOCK_NONVOID2_CONST_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_NONVOID2_DEFINED(returnType, functionName, arg1Type, arg2Type,        , const, mutable,         , __VA_ARGS__)

// Free Functions
#define ZENMOCK_NONVOID2_FREE(returnType, functionName, arg1Type, arg2Type, ...) \
   ZenMock::NonVoidTwoArgFunctionPointerMocker<returnType, arg1Type, arg2Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidTwoArgFunctionPointerMocker<returnType, arg1Type, arg2Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type", "#arg2Type")"));

// Static and Namespaced Functions
#define ZENMOCK_NONVOID2_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, ...) \
   ZenMock::NonVoidTwoArgFunctionPointerMocker<returnType, arg1Type, arg2Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidTwoArgFunctionPointerMocker<returnType, arg1Type, arg2Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type")"));

// Implementation
#define ZENMOCK_NONVOID2_DEFINED(returnType, functionName, arg1Type, arg2Type, virtualness, constness, mutableness, finalness, ...) \
returnType functionName(arg1Type argument1, arg2Type argument2) constness finalness \
{ \
   return functionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(argument1, argument2); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidTwoArgumentMocker<returnType, arg1Type, arg2Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidTwoArgumentMocker<returnType, arg1Type, arg2Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type", "#arg2Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename ReturnType, typename Arg1Type, typename Arg2Type>
   class NonVoidTwoArgumentMocker : public TwoArgumentMocker<Arg1Type, Arg2Type>, private ValueReturner<ReturnType>
   {
   public:
      explicit NonVoidTwoArgumentMocker(const std::string& zenMockedFunctionSignature)
         : TwoArgumentMocker<Arg1Type, Arg2Type>(zenMockedFunctionSignature)
         , ValueReturner<ReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnTypeURef>
      void ExpectAndReturn(ReturnTypeURef&& returnValue)
      {
         TwoArgumentMocker<Arg1Type, Arg2Type>::Expect();
         ValueReturner<ReturnType>::ZenMockAddReturnValue(std::forward<ReturnTypeURef>(returnValue));
      }

      template<typename ContainerType>
      void ExpectAndReturnValues(ContainerType&& returnValues)
      {
         TwoArgumentMocker<Arg1Type, Arg2Type>::Expect();
         ValueReturner<ReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ExpectAndReturnValues(const FirstReturnValue& firstReturnValue, const SubsequentReturnValues&... subsequentReturnValues)
      {
         TwoArgumentMocker<Arg1Type, Arg2Type>::Expect();
         ValueReturner<ReturnType>::ZenMockAddReturnValues(
            firstReturnValue,
            subsequentReturnValues...);
      }

      ReturnType ZenMockItAndReturnValue(Arg1Type argument1, Arg2Type argument2)
      {
         TwoArgumentMocker<Arg1Type, Arg2Type>::ZenMockIt(argument1, argument2);
         return ValueReturner<ReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename ReturnType, typename Arg1Type, typename Arg2Type>
   class NonVoidTwoArgFunctionPointerMocker : public NonVoidTwoArgumentMocker<ReturnType, Arg1Type, Arg2Type>
   {
   public:
      explicit NonVoidTwoArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidTwoArgumentMocker<ReturnType, Arg1Type, Arg2Type>(zenMockedFunctionSignature)
      {
      }

      static ReturnType ZenMockItFunctionPointer(
         NonVoidTwoArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type>* functionMocker,
         Arg1Type argument1, Arg2Type argument2)
      {
         return functionMocker->ZenMockItAndReturnValue(argument1, argument2);
      }
   };
}
