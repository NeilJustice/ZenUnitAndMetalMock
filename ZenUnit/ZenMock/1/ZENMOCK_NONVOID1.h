#pragma once
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/1/OneArgMocker.h"
#include "ZenUnit/ZenMock/ValueReturner.h"

// Virtual Functions
#define ZENMOCK_NONVOID1(returnType, functionName, arg1Type, ...) \
        ZENMOCK_NONVOID1_DEFINED(returnType, functionName, arg1Type, virtual,      ,        , override, __VA_ARGS__)

#define ZENMOCK_NONVOID1_CONST(returnType, functionName, arg1Type, ...) \
        ZENMOCK_NONVOID1_DEFINED(returnType, functionName, arg1Type, virtual, const, mutable, override, __VA_ARGS__)

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
#define ZENMOCK_NONVOID1_DEFINED(returnType, functionName, arg1Type, virtualness, constness, mutableness, overrideness, ...) \
virtualness returnType functionName(arg1Type arg) constness overrideness \
{ \
   return functionName##Mock##__VA_ARGS__.PrivateZenMockAndReturnValue(arg); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidOneArgMocker<returnType, arg1Type> \
{ \
   ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidOneArgMocker<returnType, arg1Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename ReturnType, typename ArgType>
   class NonVoidOneArgMocker : public OneArgMocker<ArgType>, private ValueReturner<ReturnType>
   {
   public:
      NonVoidOneArgMocker(const std::string& zenMockedFunctionSignature)
         : OneArgMocker<ArgType>(zenMockedFunctionSignature)
         , ValueReturner<ReturnType>(zenMockedFunctionSignature)
      {
      }

      void ExpectAndReturn(const ReturnType& returnValue)
      {
         OneArgMocker<ArgType>::Expect();
         ValueReturner<ReturnType>::PrivatePushBackReturnValue(returnValue);
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ExpectAndReturnValues(
         const FirstReturnValue& firstReturnValue,
         const SubsequentReturnValues&... subsequentReturnValues)
      {
         OneArgMocker<ArgType>::Expect();
         ValueReturner<ReturnType>::PrivatePushBackReturnValues(firstReturnValue, subsequentReturnValues...);
      }

      void ExpectAndReturnValues(
         const std::vector<typename std::decay<ReturnType>::type>& returnValues)
      {
         OneArgMocker<ArgType>::Expect();
         ValueReturner<ReturnType>::PrivatePushBackReturnValues(returnValues);
      }

      ReturnType PrivateZenMockAndReturnValue(ArgType arg1)
      {
         OneArgMocker<ArgType>::PrivateZenMock(arg1);
         ReturnType returnValue = ValueReturner<ReturnType>::PrivateNextReturnValue();
         return returnValue;
      }
   };

   template<typename ReturnType, typename Arg1Type>
   class NonVoidOneArgFunctionPointerMocker : public NonVoidOneArgMocker<ReturnType, Arg1Type>
   {
   public:
      NonVoidOneArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidOneArgMocker<ReturnType, Arg1Type>(zenMockedFunctionSignature)
      {
      }

      static ReturnType PrivateZenMockFunctionPointer(
         NonVoidOneArgFunctionPointerMocker* functionMocker, Arg1Type arg1)
      {
         return functionMocker->PrivateZenMockAndReturnValue(arg1);
      }
   };
}
