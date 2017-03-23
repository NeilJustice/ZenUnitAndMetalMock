#pragma once
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/2/TwoArgMocker.h"
#include "ZenUnit/ZenMock/ValueReturner.h"

// Virtual Functions
#define ZENMOCK_NONVOID2(returnType, functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_NONVOID2_DEFINED(returnType, functionName, arg1Type, arg2Type, virtual,      ,        , override, __VA_ARGS__)

#define ZENMOCK_NONVOID2_CONST(returnType, functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_NONVOID2_DEFINED(returnType, functionName, arg1Type, arg2Type, virtual, const, mutable, override, __VA_ARGS__)

// Non-Virtual Functions
#define ZENMOCK_NONVOID2_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_NONVOID2_DEFINED(returnType, functionName, arg1Type, arg2Type,        ,      ,        ,         , __VA_ARGS__)

#define ZENMOCK_NONVOID2_CONST_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_NONVOID2_DEFINED(returnType, functionName, arg1Type, arg2Type,        , const, mutable,         , __VA_ARGS__)

// Global Functions
#define ZENMOCK_NONVOID2_GLOBAL(returnType, functionName, arg1Type, arg2Type, ...) \
   ZenMock::NonVoidTwoArgFunctionPointerMocker<returnType, arg1Type, arg2Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidTwoArgFunctionPointerMocker<returnType, arg1Type, arg2Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type", "#arg2Type")"));

// Static and Namespaced Functions
#define ZENMOCK_NONVOID2_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, ...) \
   ZenMock::NonVoidTwoArgFunctionPointerMocker<returnType, arg1Type, arg2Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidTwoArgFunctionPointerMocker<returnType, arg1Type, arg2Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type")"));

// Implementation
#define ZENMOCK_NONVOID2_DEFINED(returnType, functionName, arg1Type, arg2Type, virtualness, constness, mutableness, overrideness, ...) \
virtualness returnType functionName(arg1Type arg1, arg2Type arg2) constness overrideness \
{ \
   return functionName##Mock##__VA_ARGS__.PrivateZenMockAndReturnValue(arg1, arg2); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidTwoArgMocker<returnType, arg1Type, arg2Type> \
{ \
   ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidTwoArgMocker<returnType, arg1Type, arg2Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type", "#arg2Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename ReturnType, typename Arg1Type, typename Arg2Type>
   class NonVoidTwoArgMocker : public TwoArgMocker<Arg1Type, Arg2Type>, private ValueReturner<ReturnType>
   {
   public:
      NonVoidTwoArgMocker(const std::string& zenMockedFunctionSignature)
         : TwoArgMocker<Arg1Type, Arg2Type>(zenMockedFunctionSignature)
         , ValueReturner<ReturnType>(zenMockedFunctionSignature)
      {
      }

      void ExpectAndReturn(const ReturnType& value)
      {
         TwoArgMocker<Arg1Type, Arg2Type>::Expect();
         ValueReturner<ReturnType>::PrivatePushBackReturnValue(value);
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ExpectAndReturnValues(
         const FirstReturnValue& firstValue,
         const SubsequentReturnValues&... subsequentValues)
      {
         TwoArgMocker<Arg1Type, Arg2Type>::Expect();
         ValueReturner<ReturnType>::PrivatePushBackReturnValues(firstValue, subsequentValues...);
      }

      void ExpectAndReturnValues(const std::vector<typename std::decay<ReturnType>::type>& values)
      {
         TwoArgMocker<Arg1Type, Arg2Type>::Expect();
         ValueReturner<ReturnType>::PrivatePushBackReturnValues(values);
      }

      ReturnType PrivateZenMockAndReturnValue(Arg1Type arg1, Arg2Type arg2)
      {
         TwoArgMocker<Arg1Type, Arg2Type>::PrivateZenMock(arg1, arg2);
         ReturnType returnValue = ValueReturner<ReturnType>::PrivateNextReturnValue();
         return returnValue;
      }
   };

   template<typename ReturnType, typename Arg1Type, typename Arg2Type>
   class NonVoidTwoArgFunctionPointerMocker : public NonVoidTwoArgMocker<ReturnType, Arg1Type, Arg2Type>
   {
   public:
      NonVoidTwoArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidTwoArgMocker<ReturnType, Arg1Type, Arg2Type>(zenMockedFunctionSignature)
      {
      }

      static ReturnType PrivateZenMockFunctionPointer(
         NonVoidTwoArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type>* functionMocker,
         Arg1Type arg1, Arg2Type arg2)
      {
         return functionMocker->PrivateZenMockAndReturnValue(arg1, arg2);
      }
   };
}
