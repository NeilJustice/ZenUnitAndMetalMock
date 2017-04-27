#pragma once
#include "ZenUnit/ZenMock/1/OneArgMocker.h"
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/ValueReturner.h"

// Virtual Functions
#define ZENMOCK_NONVOID1(returnType, functionName, arg1Type, ...) \
        ZENMOCK_NONVOID1_DEFINED(returnType, functionName, arg1Type, virtual,      ,        , final, __VA_ARGS__)

#define ZENMOCK_NONVOID1_CONST(returnType, functionName, arg1Type, ...) \
        ZENMOCK_NONVOID1_DEFINED(returnType, functionName, arg1Type, virtual, const, mutable, final, __VA_ARGS__)

// Non-Virtual Functions
#define ZENMOCK_NONVOID1_NONVIRTUAL(returnType, functionName, arg1Type, ...) \
        ZENMOCK_NONVOID1_DEFINED(returnType, functionName, arg1Type,        ,      ,        ,         , __VA_ARGS__)

#define ZENMOCK_NONVOID1_CONST_NONVIRTUAL(returnType, functionName, arg1Type, ...) \
        ZENMOCK_NONVOID1_DEFINED(returnType, functionName, arg1Type,        , const, mutable,         , __VA_ARGS__)

// Global Functions
#define ZENMOCK_NONVOID1_GLOBAL(returnType, functionName, arg1Type, ...) \
   ZenMock::NonVoidOneArgFunctionPointerMocker<returnType, arg1Type> \
      functionName##_ZenMock##__VA_ARGS__ = ZenMock::NonVoidOneArgFunctionPointerMocker<returnType, arg1Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type")"));

// Static and Namespaced Functions
#define ZENMOCK_NONVOID1_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, ...) \
   ZenMock::NonVoidOneArgFunctionPointerMocker<returnType, arg1Type> \
      functionName##_ZenMock##__VA_ARGS__ = ZenMock::NonVoidOneArgFunctionPointerMocker<returnType, arg1Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type")"));

// Implementation
#define ZENMOCK_NONVOID1_DEFINED(returnType, functionName, arg1Type, virtualness, constness, mutableness, finalness, ...) \
returnType functionName(arg1Type arg) constness finalness \
{ \
   return functionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(arg); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidOneArgMocker<returnType, arg1Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidOneArgMocker<returnType, arg1Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename ReturnType, typename ArgType>
   class NonVoidOneArgMocker : public OneArgMocker<ArgType>, private ValueReturner<ReturnType>
   {
   public:
      explicit NonVoidOneArgMocker(const std::string& zenMockedFunctionSignature)
         : OneArgMocker<ArgType>(zenMockedFunctionSignature)
         , ValueReturner<ReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnTypeURef>
      void ExpectAndReturn(ReturnTypeURef&& returnValue)
      {
         OneArgMocker<ArgType>::Expect();
         ValueReturner<ReturnType>::ZenMockAddReturnValue(std::forward<ReturnTypeURef>(returnValue));
      }

      template<typename ContainerType>
      void ExpectAndReturnValues(ContainerType&& returnValues)
      {
         OneArgMocker<ArgType>::Expect();
         ValueReturner<ReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      template<typename ReturnValueURef, typename... ReturnValueURefs>
      void ExpectAndReturnValues(ReturnValueURef&& firstReturnValue, ReturnValueURefs&&... subsequentReturnValues)
      {
         OneArgMocker<ArgType>::Expect();
         ValueReturner<ReturnType>::ZenMockAddReturnValues(
            std::forward<ReturnValueURef>(firstReturnValue),
            std::forward<ReturnValueURef>(subsequentReturnValues)...);
      }

      ReturnType ZenMockItAndReturnValue(ArgType arg1)
      {
         OneArgMocker<ArgType>::ZenMockIt(arg1);
         return ValueReturner<ReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename ReturnType, typename Arg1Type>
   class NonVoidOneArgFunctionPointerMocker : public NonVoidOneArgMocker<ReturnType, Arg1Type>
   {
   public:
      explicit NonVoidOneArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidOneArgMocker<ReturnType, Arg1Type>(zenMockedFunctionSignature)
      {
      }

      static ReturnType ZenMockItFunctionPointer(
         NonVoidOneArgFunctionPointerMocker* functionMocker, Arg1Type arg1)
      {
         return functionMocker->ZenMockItAndReturnValue(arg1);
      }
   };
}
