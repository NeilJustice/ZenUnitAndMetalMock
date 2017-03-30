#pragma once
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/3/ThreeArgMocker.h"
#include "ZenUnit/ZenMock/ValueReturner.h"

// Virtual Functions
#define ZENMOCK_NONVOID3(returnType, functionName, arg1Type, arg2Type, arg3Type, ...) \
        ZENMOCK_NONVOID3_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, virtual,      ,        , final, __VA_ARGS__)

#define ZENMOCK_NONVOID3_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, ...) \
        ZENMOCK_NONVOID3_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, virtual, const, mutable, final, __VA_ARGS__)

// Non-Virtual Functions
#define ZENMOCK_NONVOID3_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, ...) \
        ZENMOCK_NONVOID3_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type,        ,      ,        ,         , __VA_ARGS__)

#define ZENMOCK_NONVOID3_CONST_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, ...) \
        ZENMOCK_NONVOID3_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type,        , const, mutable,         , __VA_ARGS__)

// Global Functions
#define ZENMOCK_NONVOID3_GLOBAL(returnType, functionName, arg1Type, arg2Type, arg3Type, ...) \
   ZenMock::NonVoidThreeArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidThreeArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type")"));

// Static and Namespaced Functions
#define ZENMOCK_NONVOID3_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, ...) \
   ZenMock::NonVoidThreeArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidThreeArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type")"));

// Implementation
#define ZENMOCK_NONVOID3_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, virtualness, constness, mutableness, finalness, ...) \
virtualness returnType functionName(arg1Type arg1, arg2Type arg2, arg3Type arg3) constness finalness \
{ \
   return functionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(arg1, arg2, arg3); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidThreeArgMocker<returnType, arg1Type, arg2Type, arg3Type> \
{ \
   ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidThreeArgMocker<returnType, arg1Type, arg2Type, arg3Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename ReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class NonVoidThreeArgMocker : public ThreeArgMocker<Arg1Type, Arg2Type, Arg3Type>, private ValueReturner<ReturnType>
   {
   public:
      NonVoidThreeArgMocker(const std::string& zenMockedFunctionSignature)
         : ThreeArgMocker<Arg1Type, Arg2Type, Arg3Type>(zenMockedFunctionSignature)
         , ValueReturner<ReturnType>(zenMockedFunctionSignature)
      {
      }

      void ExpectAndReturn(const ReturnType& returnValue)
      {
         ThreeArgMocker<Arg1Type, Arg2Type, Arg3Type>::Expect();
         ValueReturner<ReturnType>::ZenMockPushBackReturnValue(returnValue);
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ExpectAndReturnValues(
         const FirstReturnValue& firstReturnValue,
         const SubsequentReturnValues&... subsequentReturnValues)
      {
         ThreeArgMocker<Arg1Type, Arg2Type, Arg3Type>::Expect();
         ValueReturner<ReturnType>::ZenMockPushBackReturnValues(firstReturnValue, subsequentReturnValues...);
      }

      void ExpectAndReturnValues(
         const std::vector<typename std::decay<ReturnType>::type>& returnValues)
      {
         ThreeArgMocker<Arg1Type, Arg2Type, Arg3Type>::Expect();
         ValueReturner<ReturnType>::ZenMockPushBackReturnValues(returnValues);
      }

      ReturnType ZenMockItAndReturnValue(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3)
      {
         ThreeArgMocker<Arg1Type, Arg2Type, Arg3Type>::ZenMockIt(arg1, arg2, arg3);
         const ReturnType returnValue = ValueReturner<ReturnType>::ZenMockZenMockNextReturnValue();
         return returnValue;
      }
   };

   template<typename ReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class NonVoidThreeArgFunctionPointerMocker : public NonVoidThreeArgMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type>
   {
   public:
      NonVoidThreeArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidThreeArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type>(zenMockedFunctionSignature)
      {
      }

      static ReturnType ZenMockItFunctionPointer(
         NonVoidThreeArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type>* functionMocker,
         Arg1Type arg1, Arg2Type arg2, Arg3Type arg3)
      {
         return functionMocker->ZenMockItAndReturnValue(arg1, arg2, arg3);
      }
   };
}
