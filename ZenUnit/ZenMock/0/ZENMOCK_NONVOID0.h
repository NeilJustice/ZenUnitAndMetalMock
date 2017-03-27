#pragma once
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/0/ZeroArgMocker.h"
#include "ZenUnit/ZenMock/ValueReturner.h"

// Virtual Functions
#define ZENMOCK_NONVOID0(returnType, functionName) \
        ZENMOCK_NONVOID0_DEFINED(returnType, functionName, virtual,      ,        , override)

#define ZENMOCK_NONVOID0_CONST(returnType, functionName) \
        ZENMOCK_NONVOID0_DEFINED(returnType, functionName, virtual, const, mutable, override)

// Non-Virtual Functions
#define ZENMOCK_NONVOID0_NONVIRTUAL(returnType, functionName) \
        ZENMOCK_NONVOID0_DEFINED(returnType, functionName,        ,      ,        ,         )

#define ZENMOCK_NONVOID0_CONST_NONVIRTUAL(returnType, functionName) \
        ZENMOCK_NONVOID0_DEFINED(returnType, functionName,        , const, mutable,         )

// Global Functions
#define ZENMOCK_NONVOID0_GLOBAL(returnType, functionName) \
   ZenMock::NonVoidZeroArgFunctionPointerMocker<returnType> functionName##_ZenMock = \
      ZenMock::NonVoidZeroArgFunctionPointerMocker<returnType>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"()"));

// Static and Namespaced Functions
#define ZENMOCK_NONVOID0_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, ...) \
   ZenMock::NonVoidZeroArgFunctionPointerMocker<returnType> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidZeroArgFunctionPointerMocker<returnType>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"()"));

// Implementation
#define ZENMOCK_NONVOID0_DEFINED(returnType, functionName, virtualness, constness, mutableness, overrideness) \
virtualness returnType functionName() constness overrideness \
{ \
   return functionName##Mock.PrivateZenMockAndReturnValue(); \
} \
struct ZenMock_##functionName : public ZenMock::NonVoidZeroArgMocker<returnType> \
{ \
   ZenMock_##functionName(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidZeroArgMocker<returnType>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"()", #constness)) {} \
} mutableness functionName##Mock = ZenMock_##functionName(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename ReturnType>
   class NonVoidZeroArgMocker : public ZeroArgMocker<ExceptionThrower>, private ValueReturner<ReturnType>
   {
   public:
      NonVoidZeroArgMocker(const std::string& zenMockedFunctionSignature)
         : ZeroArgMocker(zenMockedFunctionSignature)
         , ValueReturner<ReturnType>(zenMockedFunctionSignature)
      {
      }

      void ExpectAndReturn(const ReturnType& returnValue)
      {
         ZeroArgMocker::Expect();
         ValueReturner<ReturnType>::PrivatePushBackReturnValue(returnValue);
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ExpectAndReturnValues(
         const FirstReturnValue& firstReturnValue,
         const SubsequentReturnValues&... subsequentReturnValues)
      {
         ZeroArgMocker::Expect();
         ValueReturner<ReturnType>::PrivatePushBackReturnValues(firstReturnValue, subsequentReturnValues...);
      }

      void ExpectAndReturnValues(
         const std::vector<typename std::decay<ReturnType>::type>& returnValues)
      {
         ZeroArgMocker::Expect();
         ValueReturner<ReturnType>::PrivatePushBackReturnValues(returnValues);
      }

      ReturnType PrivateZenMockAndReturnValue()
      {
         ZeroArgMocker::PrivateZenMock();
         const ReturnType returnValue = ValueReturner<ReturnType>::PrivateNextReturnValue();
         return returnValue;
      }
   };

   template<typename ReturnType>
   class NonVoidZeroArgFunctionPointerMocker : public NonVoidZeroArgMocker<ReturnType>
   {
   public:
      NonVoidZeroArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidZeroArgMocker<ReturnType>(zenMockedFunctionSignature)
      {
      }

      static ReturnType PrivateZenMockFunctionPointer(
         NonVoidZeroArgFunctionPointerMocker<ReturnType>* functionPointerMocker)
      {
         return functionPointerMocker->PrivateZenMockAndReturnValue();
      }
   };
}
