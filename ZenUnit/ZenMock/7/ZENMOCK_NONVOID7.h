#pragma once
#include "ZenUnit/ZenMock/7/SevenArgumentMocker.h"
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/ValueReturner.h"

// Virtual Functions
#define ZENMOCK_NONVOID7(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
        ZENMOCK_NONVOID7_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, virtual,      ,        , final, __VA_ARGS__)

#define ZENMOCK_NONVOID7_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
        ZENMOCK_NONVOID7_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, virtual, const, mutable, final, __VA_ARGS__)

// Non-Virtual Functions
#define ZENMOCK_NONVOID7_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
        ZENMOCK_NONVOID7_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type,        ,      ,        ,         , __VA_ARGS__)

#define ZENMOCK_NONVOID7_CONST_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
        ZENMOCK_NONVOID7_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type,        , const, mutable,         , __VA_ARGS__)

// Free Functions
#define ZENMOCK_NONVOID7_FREE(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
   ZenMock::NonVoidSevenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidSevenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type")"));

// Static and Namespaced Functions
#define ZENMOCK_NONVOID7_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
   ZenMock::NonVoidSevenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidSevenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type")"));

// Implementation
#define ZENMOCK_NONVOID7_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, virtualness, constness, mutableness, finalness, ...) \
returnType functionName(arg1Type argument1, arg2Type argument2, arg3Type argument3, arg4Type argument4, arg5Type argument5, arg6Type argument6, arg7Type argument7) constness finalness \
{ \
   return functionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(argument1, argument2, argument3, argument4, argument5, argument6, argument7); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidSevenArgumentMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidSevenArgumentMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename ReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   class NonVoidSevenArgumentMocker : public SevenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ExceptionThrower>, private ValueReturner<ReturnType>
   {
   public:
      explicit NonVoidSevenArgumentMocker(const std::string& zenMockedFunctionSignature)
         : SevenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>(zenMockedFunctionSignature)
         , ValueReturner<ReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnTypeURef>
      void ExpectAndReturn(ReturnTypeURef&& returnValue)
      {
         SevenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>::Expect();
         ValueReturner<ReturnType>::ZenMockAddReturnValue(std::forward<ReturnTypeURef>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ExpectAndReturnValues(const FirstReturnValue& firstReturnValue, const SubsequentReturnValues&... subsequentReturnValues)
      {
         SevenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>::Expect();
         ValueReturner<ReturnType>::ZenMockAddReturnValues(firstReturnValue, subsequentReturnValues...);
      }

      template<typename ContainerType>
      void ExpectAndReturnValues(ContainerType&& returnValues)
      {
         SevenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>::Expect();
         ValueReturner<ReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      ReturnType ZenMockItAndReturnValue(Arg1Type argument1, Arg2Type argument2, Arg3Type argument3, Arg4Type argument4, Arg5Type argument5, Arg6Type argument6, Arg7Type argument7)
      {
         SevenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>::ZenMockIt(argument1, argument2, argument3, argument4, argument5, argument6, argument7);
         return ValueReturner<ReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename ReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   class NonVoidSevenArgFunctionPointerMocker : public NonVoidSevenArgumentMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>
   {
   public:
      explicit NonVoidSevenArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidSevenArgumentMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>(zenMockedFunctionSignature)
      {
      }

      static ReturnType ZenMockItFunctionPointer(
         NonVoidSevenArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>* functionMocker,
         Arg1Type argument1, Arg2Type argument2, Arg3Type argument3, Arg4Type argument4, Arg5Type argument5, Arg6Type argument6, Arg7Type argument7)
      {
         return functionMocker->ZenMockItAndReturnValue(argument1, argument2, argument3, argument4, argument5, argument6, argument7);
      }
   };
}
