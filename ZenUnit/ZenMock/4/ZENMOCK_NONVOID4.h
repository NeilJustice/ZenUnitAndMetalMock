#pragma once
#include "ZenUnit/ZenMock/4/FourArgumentMocker.h"
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/ValueReturner.h"

// Virtual Functions
#define ZENMOCK_NONVOID4(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
        ZENMOCK_NONVOID4_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, virtual,      ,        , final, __VA_ARGS__)

#define ZENMOCK_NONVOID4_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
        ZENMOCK_NONVOID4_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, virtual, const, mutable, final, __VA_ARGS__)

// Non-Virtual Functions
#define ZENMOCK_NONVOID4_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
        ZENMOCK_NONVOID4_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type,        ,      ,        ,         , __VA_ARGS__)

#define ZENMOCK_NONVOID4_CONST_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
        ZENMOCK_NONVOID4_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type,        , const, mutable,         , __VA_ARGS__)

// Free Functions
#define ZENMOCK_NONVOID4_FREE(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
   ZenMock::NonVoidFourArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidFourArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type")"));

// Static and Namespaced Functions
#define ZENMOCK_NONVOID4_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
   ZenMock::NonVoidFourArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidFourArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type")"));

// Implementation
#define ZENMOCK_NONVOID4_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, virtualness, constness, mutableness, finalness, ...) \
returnType functionName(arg1Type argument1, arg2Type argument2, arg3Type argument3, arg4Type argument4) constness finalness \
{ \
   return functionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(argument1, argument2, argument3, argument4); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidFourArgumentMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidFourArgumentMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename ReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class NonVoidFourArgumentMocker : public FourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>, private ValueReturner<ReturnType>
   {
   public:
      explicit NonVoidFourArgumentMocker(const std::string& zenMockedFunctionSignature)
         : FourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>(zenMockedFunctionSignature)
         , ValueReturner<ReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnTypeURef>
      void ExpectAndReturn(ReturnTypeURef&& returnValue)
      {
         FourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::Expect();
         ValueReturner<ReturnType>::ZenMockAddReturnValue(std::forward<ReturnTypeURef>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ExpectAndReturnValues(const FirstReturnValue& firstReturnValue, const SubsequentReturnValues&... subsequentReturnValues)
      {
         FourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::Expect();
         ValueReturner<ReturnType>::ZenMockAddReturnValues(firstReturnValue, subsequentReturnValues...);
      }

      template<typename ContainerType>
      void ExpectAndReturnValues(ContainerType&& returnValues)
      {
         FourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::Expect();
         ValueReturner<ReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      ReturnType ZenMockItAndReturnValue(Arg1Type argument1, Arg2Type argument2, Arg3Type argument3, Arg4Type argument4)
      {
         FourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::ZenMockIt(argument1, argument2, argument3, argument4);
         return ValueReturner<ReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename ReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class NonVoidFourArgFunctionPointerMocker : public NonVoidFourArgumentMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>
   {
   public:
      explicit NonVoidFourArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidFourArgumentMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>(zenMockedFunctionSignature)
      {
      }

      static ReturnType ZenMockItFunctionPointer(
         NonVoidFourArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>* functionMocker,
         Arg1Type argument1, Arg2Type argument2, Arg3Type argument3, Arg4Type argument4)
      {
         return functionMocker->ZenMockItAndReturnValue(argument1, argument2, argument3, argument4);
      }
   };
}
