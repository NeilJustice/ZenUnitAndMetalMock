#pragma once
#include "ZenUnit/ZenMock/8/EightArgumentMocker.h"
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/ValueReturner.h"

// Virtual Functions
#define ZENMOCK_NONVOID8(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
        ZENMOCK_NONVOID8_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, virtual,      ,        , final, __VA_ARGS__)

#define ZENMOCK_NONVOID8_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
        ZENMOCK_NONVOID8_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, virtual, const, mutable, final, __VA_ARGS__)

// Non-Virtual Functions
#define ZENMOCK_NONVOID8_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
        ZENMOCK_NONVOID8_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type,        ,      ,        ,         , __VA_ARGS__)

#define ZENMOCK_NONVOID8_CONST_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
        ZENMOCK_NONVOID8_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type,        , const, mutable,         , __VA_ARGS__)

// Free Functions
#define ZENMOCK_NONVOID8_FREE(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
   ZenMock::NonVoidEightArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidEightArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type")"));

// Static and Namespaced Functions
#define ZENMOCK_NONVOID8_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
   ZenMock::NonVoidEightArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidEightArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type")"));

// Implementation
#define ZENMOCK_NONVOID8_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, virtualness, constness, mutableness, finalness, ...) \
returnType functionName(arg1Type argument1, arg2Type argument2, arg3Type argument3, arg4Type argument4, arg5Type argument5, arg6Type argument6, arg7Type argument7, arg8Type argument8) constness finalness \
{ \
   return functionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(argument1, argument2, argument3, argument4, argument5, argument6, argument7, argument8); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidEightArgumentMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidEightArgumentMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename ReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
   class NonVoidEightArgumentMocker : public EightArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ExceptionThrower>, private ValueReturner<ReturnType>
   {
   public:
      explicit NonVoidEightArgumentMocker(const std::string& zenMockedFunctionSignature)
         : EightArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>(zenMockedFunctionSignature)
         , ValueReturner<ReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnTypeURef>
      void ExpectAndReturn(ReturnTypeURef&& returnValue)
      {
         EightArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>::Expect();
         ValueReturner<ReturnType>::ZenMockAddReturnValue(std::forward<ReturnTypeURef>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ExpectAndReturnValues(const FirstReturnValue& firstReturnValue, const SubsequentReturnValues&... subsequentReturnValues)
      {
         EightArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>::Expect();
         ValueReturner<ReturnType>::ZenMockAddReturnValues(firstReturnValue, subsequentReturnValues...);
      }

      template<typename ContainerType>
      void ExpectAndReturnValues(ContainerType&& returnValues)
      {
         EightArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>::Expect();
         ValueReturner<ReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      ReturnType ZenMockItAndReturnValue(Arg1Type argument1, Arg2Type argument2, Arg3Type argument3, Arg4Type argument4, Arg5Type argument5, Arg6Type argument6, Arg7Type argument7, Arg8Type argument8)
      {
         EightArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>::ZenMockIt(argument1, argument2, argument3, argument4, argument5, argument6, argument7, argument8);
         return ValueReturner<ReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename ReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
   class NonVoidEightArgFunctionPointerMocker : public NonVoidEightArgumentMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>
   {
   public:
      explicit NonVoidEightArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidEightArgumentMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>(zenMockedFunctionSignature)
      {
      }

      static ReturnType ZenMockItFunctionPointer(
         NonVoidEightArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>* functionMocker,
         Arg1Type argument1, Arg2Type argument2, Arg3Type argument3, Arg4Type argument4, Arg5Type argument5, Arg6Type argument6, Arg7Type argument7, Arg8Type argument8)
      {
         return functionMocker->ZenMockItAndReturnValue(argument1, argument2, argument3, argument4, argument5, argument6, argument7, argument8);
      }
   };
}
