#pragma once
#include "ZenUnit/ZenMock/0/ZeroArgMocker.h"
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/ValueReturner.h"

// Virtual Functions
#define ZENMOCK_NONVOID0(returnType, functionName) \
        ZENMOCK_NONVOID0_DEFINED(returnType, functionName, virtual,      ,        , final)

#define ZENMOCK_NONVOID0_CONST(returnType, functionName) \
        ZENMOCK_NONVOID0_DEFINED(returnType, functionName, virtual, const, mutable, final)

// Non-Virtual Functions
#define ZENMOCK_NONVOID0_NONVIRTUAL(returnType, functionName) \
        ZENMOCK_NONVOID0_DEFINED(returnType, functionName,        ,      ,        ,         )

#define ZENMOCK_NONVOID0_CONST_NONVIRTUAL(returnType, functionName) \
        ZENMOCK_NONVOID0_DEFINED(returnType, functionName,        , const, mutable,         )

// Free Functions
#define ZENMOCK_NONVOID0_FREE(returnType, functionName) \
   ZenMock::NonVoidZeroArgFunctionPointerMocker<returnType> functionName##_ZenMock = \
      ZenMock::NonVoidZeroArgFunctionPointerMocker<returnType>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"()"));

// Static and Namespaced Functions
#define ZENMOCK_NONVOID0_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, ...) \
   ZenMock::NonVoidZeroArgFunctionPointerMocker<returnType> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidZeroArgFunctionPointerMocker<returnType>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"()"));

// Implementation
#define ZENMOCK_NONVOID0_DEFINED(returnType, functionName, virtualness, constness, mutableness, finalness) \
returnType functionName() constness finalness \
{ \
   return functionName##Mock.ZenMockItAndReturnValue(); \
} \
struct ZenMock_##functionName : public ZenMock::NonVoidZeroArgMocker<returnType> \
{ \
   explicit ZenMock_##functionName(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidZeroArgMocker<returnType>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"()", #constness)) {} \
} mutableness functionName##Mock = ZenMock_##functionName(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename ReturnType>
   class NonVoidZeroArgMocker : public ZeroArgMocker<ExceptionThrower>, private ValueReturner<ReturnType>
   {
   public:
      explicit NonVoidZeroArgMocker(const std::string& zenMockedFunctionSignature)
         : ZeroArgMocker(zenMockedFunctionSignature)
         , ValueReturner<ReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnTypeURef>
      void ExpectAndReturn(ReturnTypeURef&& returnValue)
      {
         ZeroArgMocker::Expect();
         ValueReturner<ReturnType>::ZenMockAddReturnValue(std::forward<ReturnTypeURef>(returnValue));
      }

      template<typename ContainerType>
      void ExpectAndReturnValues(ContainerType&& returnValues)
      {
         ZeroArgMocker::Expect();
         ValueReturner<ReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      template<typename ReturnTypeURef, typename... ReturnTypeURefs>
      void ExpectAndReturnValues(ReturnTypeURef&& firstReturnValue, ReturnTypeURefs&&... subsequentReturnValues)
      {
         ZeroArgMocker::Expect();
         ValueReturner<ReturnType>::ZenMockAddReturnValues(
            std::forward<ReturnTypeURef>(firstReturnValue),
            std::forward<ReturnTypeURefs>(subsequentReturnValues)...);
      }

      ReturnType ZenMockItAndReturnValue()
      {
         ZeroArgMocker::ZenMockIt();
         return ValueReturner<ReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename ReturnType>
   class NonVoidZeroArgFunctionPointerMocker : public NonVoidZeroArgMocker<ReturnType>
   {
   public:
      explicit NonVoidZeroArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidZeroArgMocker<ReturnType>(zenMockedFunctionSignature)
      {
      }

      static ReturnType ZenMockItFunctionPointer(
         NonVoidZeroArgFunctionPointerMocker<ReturnType>* functionPointerMocker)
      {
         return functionPointerMocker->ZenMockItAndReturnValue();
      }
   };
}
