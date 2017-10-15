#pragma once
#include "ZenUnit/ZenMock/0/ZeroArgumentMocker.h"
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/ValueReturner.h"

#define ZENMOCK_NONVOID0(returnType, functionName) \
        ZENMOCK_NONVOID0_DEFINED(returnType, functionName, virtual,      ,        , final)

#define ZENMOCK_NONVOID0_CONST(returnType, functionName) \
        ZENMOCK_NONVOID0_DEFINED(returnType, functionName, virtual, const, mutable, final)

#define ZENMOCK_NONVOID0_NONVIRTUAL(returnType, functionName) \
        ZENMOCK_NONVOID0_DEFINED(returnType, functionName,        ,      ,        ,         )

#define ZENMOCK_NONVOID0_CONST_NONVIRTUAL(returnType, functionName) \
        ZENMOCK_NONVOID0_DEFINED(returnType, functionName,        , const, mutable,         )

// Defines a freeFunctionName_ZenMock object for mocking a free function with signature "returnType freeFunctionName()".
#define ZENMOCK_NONVOID0_FREE(returnType, freeFunctionName) \
   static_assert(::freeFunctionName != nullptr); \
   ZenMock::NonVoidZeroArgFunctionPointerMocker<returnType> freeFunctionName##_ZenMock = \
      ZenMock::NonVoidZeroArgFunctionPointerMocker<returnType>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#freeFunctionName"()"));

// Defines a functionName_ZenMock object for mocking a static or namespaced function with signature "returnType qualifiedClassNameOrNamespace::functionName()".
#define ZENMOCK_NONVOID0_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, ...) \
   static_assert(qualifiedClassNameOrNamespace::functionName != nullptr); \
   ZenMock::NonVoidZeroArgFunctionPointerMocker<returnType> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidZeroArgFunctionPointerMocker<returnType>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"()"));

#define ZENMOCK_NONVOID0_DEFINED(returnType, functionName, virtualness, constness, mutableness, finalness) \
returnType functionName() constness finalness \
{ \
   return functionName##Mock.ZenMockItAndReturnValue(); \
} \
struct ZenMock_##functionName : public ZenMock::NonVoidZeroArgumentMocker<returnType> \
{ \
   explicit ZenMock_##functionName(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidZeroArgumentMocker<returnType>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"()", #constness)) {} \
} mutableness functionName##Mock = ZenMock_##functionName(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename ReturnType>
   class NonVoidZeroArgumentMocker : public ZeroArgumentMocker<ExceptionThrower>, private ValueReturner<ReturnType>
   {
   public:
      explicit NonVoidZeroArgumentMocker(const std::string& zenMockedFunctionSignature)
         : ZeroArgumentMocker(zenMockedFunctionSignature)
         , ValueReturner<ReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnTypeURef>
      void ExpectAndReturn(ReturnTypeURef&& returnValue)
      {
         ZeroArgumentMocker::Expect();
         ValueReturner<ReturnType>::ZenMockAddReturnValue(std::forward<ReturnTypeURef>(returnValue));
      }

      template<typename ContainerType>
      void ExpectAndReturnValues(ContainerType&& returnValues)
      {
         ZeroArgumentMocker::Expect();
         ValueReturner<ReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      template<typename ReturnTypeURef, typename... ReturnTypeURefs>
      void ExpectAndReturnValues(ReturnTypeURef&& firstReturnValue, ReturnTypeURefs&&... subsequentReturnValues)
      {
         ZeroArgumentMocker::Expect();
         ValueReturner<ReturnType>::ZenMockAddReturnValues(
            std::forward<ReturnTypeURef>(firstReturnValue),
            std::forward<ReturnTypeURefs>(subsequentReturnValues)...);
      }

      ReturnType ZenMockItAndReturnValue()
      {
         ZeroArgumentMocker::ZenMockIt();
         return ValueReturner<ReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename ReturnType>
   class NonVoidZeroArgFunctionPointerMocker : public NonVoidZeroArgumentMocker<ReturnType>
   {
   public:
      explicit NonVoidZeroArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidZeroArgumentMocker<ReturnType>(zenMockedFunctionSignature)
      {
      }

      static ReturnType ZenMockItFunctionPointer(
         NonVoidZeroArgFunctionPointerMocker<ReturnType>* functionPointerMocker)
      {
         return functionPointerMocker->ZenMockItAndReturnValue();
      }
   };
}
