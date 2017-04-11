#pragma once
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/2/TwoArgMocker.h"
#include "ZenUnit/ZenMock/ValueReturner.h"

// Virtual Functions
#define ZENMOCK_NONVOID2(returnType, functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_NONVOID2_DEFINED(returnType, functionName, arg1Type, arg2Type, virtual,      ,        , final, __VA_ARGS__)

#define ZENMOCK_NONVOID2_CONST(returnType, functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_NONVOID2_DEFINED(returnType, functionName, arg1Type, arg2Type, virtual, const, mutable, final, __VA_ARGS__)

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
#define ZENMOCK_NONVOID2_DEFINED(returnType, functionName, arg1Type, arg2Type, virtualness, constness, mutableness, overridefinalness, ...) \
virtualness returnType functionName(arg1Type arg1, arg2Type arg2) constness overridefinalness \
{ \
   return functionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(arg1, arg2); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidTwoArgMocker<returnType, arg1Type, arg2Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidTwoArgMocker<returnType, arg1Type, arg2Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type", "#arg2Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename ReturnType, typename Arg1Type, typename Arg2Type>
   class NonVoidTwoArgMocker : public TwoArgMocker<Arg1Type, Arg2Type>, private ValueReturner<ReturnType>
   {
   public:
      explicit NonVoidTwoArgMocker(const std::string& zenMockedFunctionSignature)
         : TwoArgMocker<Arg1Type, Arg2Type>(zenMockedFunctionSignature)
         , ValueReturner<ReturnType>(zenMockedFunctionSignature)
      {
      }

      void ExpectAndReturn(const ReturnType& returnValue)
      {
         TwoArgMocker<Arg1Type, Arg2Type>::Expect();
         ValueReturner<ReturnType>::ZenMockPushBackReturnValue(returnValue);
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ExpectAndReturnValues(
         const FirstReturnValue& firstReturnValue,
         const SubsequentReturnValues&... subsequentReturnValues)
      {
         TwoArgMocker<Arg1Type, Arg2Type>::Expect();
         ValueReturner<ReturnType>::ZenMockPushBackReturnValues(firstReturnValue, subsequentReturnValues...);
      }

      void ExpectAndReturnValues(
         const std::vector<typename std::decay<ReturnType>::type>& returnValues)
      {
         TwoArgMocker<Arg1Type, Arg2Type>::Expect();
         ValueReturner<ReturnType>::ZenMockPushBackReturnValues(returnValues);
      }

      ReturnType ZenMockItAndReturnValue(Arg1Type arg1, Arg2Type arg2)
      {
         TwoArgMocker<Arg1Type, Arg2Type>::ZenMockIt(arg1, arg2);
         const ReturnType returnValue = ValueReturner<ReturnType>::ZenMockZenMockNextReturnValue();
         return returnValue;
      }
   };

   template<typename ReturnType, typename Arg1Type, typename Arg2Type>
   class NonVoidTwoArgFunctionPointerMocker : public NonVoidTwoArgMocker<ReturnType, Arg1Type, Arg2Type>
   {
   public:
      explicit NonVoidTwoArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidTwoArgMocker<ReturnType, Arg1Type, Arg2Type>(zenMockedFunctionSignature)
      {
      }

      static ReturnType ZenMockItFunctionPointer(
         NonVoidTwoArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type>* functionMocker,
         Arg1Type arg1, Arg2Type arg2)
      {
         return functionMocker->ZenMockItAndReturnValue(arg1, arg2);
      }
   };
}
