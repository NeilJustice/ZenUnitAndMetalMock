#pragma once
#include "ZenUnit/ZenMock/5/FiveArgMocker.h"
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/ValueReturner.h"

// Virtual Functions
#define ZENMOCK_NONVOID5(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
        ZENMOCK_NONVOID5_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, virtual,      ,        , final, __VA_ARGS__)

#define ZENMOCK_NONVOID5_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
        ZENMOCK_NONVOID5_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, virtual, const, mutable, final, __VA_ARGS__)

// Non-Virtual Functions
#define ZENMOCK_NONVOID5_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
        ZENMOCK_NONVOID5_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type,        ,      ,        ,         , __VA_ARGS__)

#define ZENMOCK_NONVOID5_CONST_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
        ZENMOCK_NONVOID5_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type,        , const, mutable,         , __VA_ARGS__)

// Free Functions
#define ZENMOCK_NONVOID5_FREE(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
   ZenMock::NonVoidFiveArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidFiveArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type")"));

// Static and Namespaced Functions
#define ZENMOCK_NONVOID5_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
   ZenMock::NonVoidFiveArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidFiveArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type")"));

// Implementation
#define ZENMOCK_NONVOID5_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, virtualness, constness, mutableness, finalness, ...) \
returnType functionName(arg1Type arg1, arg2Type arg2, arg3Type arg3, arg4Type arg4, arg5Type arg5) constness finalness \
{ \
   return functionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(arg1, arg2, arg3, arg4, arg5); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidFiveArgMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidFiveArgMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename ReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   class NonVoidFiveArgMocker : public FiveArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>, private ValueReturner<ReturnType>
   {
   public:
      explicit NonVoidFiveArgMocker(const std::string& zenMockedFunctionSignature)
         : FiveArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>(zenMockedFunctionSignature)
         , ValueReturner<ReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnTypeURef>
      void ExpectAndReturn(ReturnTypeURef&& returnValue)
      {
         FiveArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::Expect();
         ValueReturner<ReturnType>::ZenMockAddReturnValue(std::forward<ReturnTypeURef>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ExpectAndReturnValues(const FirstReturnValue& firstReturnValue, const SubsequentReturnValues&... subsequentReturnValues)
      {
         FiveArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::Expect();
         ValueReturner<ReturnType>::ZenMockAddReturnValues(
            firstReturnValue,
            subsequentReturnValues...);
      }

      template<typename ContainerType>
      void ExpectAndReturnValues(ContainerType&& returnValues)
      {
         FiveArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::Expect();
         ValueReturner<ReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      ReturnType ZenMockItAndReturnValue(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4, Arg5Type arg5)
      {
         FiveArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::ZenMockIt(arg1, arg2, arg3, arg4, arg5);
         return ValueReturner<ReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename ReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   class NonVoidFiveArgFunctionPointerMocker : public NonVoidFiveArgMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>
   {
   public:
      explicit NonVoidFiveArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidFiveArgMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>(zenMockedFunctionSignature)
      {
      }

      static ReturnType ZenMockItFunctionPointer(
         NonVoidFiveArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>* functionMocker,
         Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4, Arg5Type arg5)
      {
         return functionMocker->ZenMockItAndReturnValue(arg1, arg2, arg3, arg4, arg5);
      }
   };
}
