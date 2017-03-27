#pragma once
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/4/FourArgMocker.h"
#include "ZenUnit/ZenMock/ValueReturner.h"

// Virtual Functions
#define ZENMOCK_NONVOID4(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
        ZENMOCK_NONVOID4_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, virtual,      ,        , override, __VA_ARGS__)

#define ZENMOCK_NONVOID4_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
        ZENMOCK_NONVOID4_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, virtual, const, mutable, override, __VA_ARGS__)

// Non-Virtual Functions
#define ZENMOCK_NONVOID4_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
        ZENMOCK_NONVOID4_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type,        ,      ,        ,         , __VA_ARGS__)

#define ZENMOCK_NONVOID4_CONST_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
        ZENMOCK_NONVOID4_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type,        , const, mutable,         , __VA_ARGS__)

// Global Functions
#define ZENMOCK_NONVOID4_GLOBAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
   ZenMock::NonVoidFourArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidFourArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type")"));

// Static and Namespaced Functions
#define ZENMOCK_NONVOID4_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
   ZenMock::NonVoidFourArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidFourArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type")"));

// Implementation
#define ZENMOCK_NONVOID4_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, virtualness, constness, mutableness, overrideness, ...) \
virtualness returnType functionName(arg1Type arg1, arg2Type arg2, arg3Type arg3, arg4Type arg4) constness overrideness \
{ \
   return functionName##Mock##__VA_ARGS__.PrivateZenMockAndReturnValue(arg1, arg2, arg3, arg4); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidFourArgMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type> \
{ \
   ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidFourArgMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename ReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class NonVoidFourArgMocker : public FourArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>, private ValueReturner<ReturnType>
   {
   public:
      NonVoidFourArgMocker(const std::string& zenMockedFunctionSignature)
         : FourArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>(zenMockedFunctionSignature)
         , ValueReturner<ReturnType>(zenMockedFunctionSignature)
      {
      }

      void ExpectAndReturn(const ReturnType& returnValue)
      {
         FourArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::Expect();
         ValueReturner<ReturnType>::PrivatePushBackReturnValue(returnValue);
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ExpectAndReturnValues(
         const FirstReturnValue& firstReturnValue,
         const SubsequentReturnValues&... subsequentReturnValues)
      {
         FourArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::Expect();
         ValueReturner<ReturnType>::PrivatePushBackReturnValues(firstReturnValue, subsequentReturnValues...);
      }

      void ExpectAndReturnValues(
         const std::vector<typename std::decay<ReturnType>::type>& returnValues)
      {
         FourArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::Expect();
         ValueReturner<ReturnType>::PrivatePushBackReturnValues(returnValues);
      }

      ReturnType PrivateZenMockAndReturnValue(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4)
      {
         FourArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::PrivateZenMock(arg1, arg2, arg3, arg4);
         const ReturnType nextReturnValue = ValueReturner<ReturnType>::PrivateNextReturnValue();
         return nextReturnValue;
      }
   };

   template<typename ReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class NonVoidFourArgFunctionPointerMocker : public NonVoidFourArgMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>
   {
   public:
      NonVoidFourArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidFourArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>(zenMockedFunctionSignature)
      {
      }

      static ReturnType PrivateZenMockFunctionPointer(
         NonVoidFourArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>* functionMocker,
         Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4)
      {
         return functionMocker->PrivateZenMockAndReturnValue(arg1, arg2, arg3, arg4);
      }
   };
}
