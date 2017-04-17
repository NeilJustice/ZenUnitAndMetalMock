#pragma once
#include "ZenUnit/ZenMock/6/SixArgMocker.h"
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/ValueReturner.h"

// Virtual Functions
#define ZENMOCK_NONVOID6(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
        ZENMOCK_NONVOID6_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, virtual,      ,        , override final, __VA_ARGS__)

#define ZENMOCK_NONVOID6_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
        ZENMOCK_NONVOID6_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, virtual, const, mutable, override final, __VA_ARGS__)

// Non-Virtual Functions
#define ZENMOCK_NONVOID6_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
        ZENMOCK_NONVOID6_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type,        ,      ,        ,         , __VA_ARGS__)

#define ZENMOCK_NONVOID6_CONST_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
        ZENMOCK_NONVOID6_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type,        , const, mutable,         , __VA_ARGS__)

// Global Functions
#define ZENMOCK_NONVOID6_GLOBAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
   ZenMock::NonVoidSixArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidSixArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type")"));

// Static and Namespaced Functions
#define ZENMOCK_NONVOID6_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
   ZenMock::NonVoidSixArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidSixArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type")"));

// Implementation
#define ZENMOCK_NONVOID6_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, virtualness, constness, mutableness, overridefinalness, ...) \
virtualness returnType functionName(arg1Type arg1, arg2Type arg2, arg3Type arg3, arg4Type arg4, arg5Type arg5, arg6Type arg6) constness overridefinalness \
{ \
   return functionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(arg1, arg2, arg3, arg4, arg5, arg6); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidSixArgMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidSixArgMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename ReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   class NonVoidSixArgMocker : public SixArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>, private ValueReturner<ReturnType>
   {
   public:
      explicit NonVoidSixArgMocker(const std::string& zenMockedFunctionSignature)
         : SixArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>(zenMockedFunctionSignature)
         , ValueReturner<ReturnType>(zenMockedFunctionSignature)
      {
      }

      void ExpectAndReturn(const ReturnType& returnValue)
      {
         SixArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>::Expect();
         ValueReturner<ReturnType>::ZenMockPushBackReturnValue(returnValue);
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ExpectAndReturnValues(
         const FirstReturnValue& firstReturnValue,
         const SubsequentReturnValues&... subsequentReturnValues)
      {
         SixArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>::Expect();
         ValueReturner<ReturnType>::ZenMockPushBackReturnValues(firstReturnValue, subsequentReturnValues...);
      }

      void ExpectAndReturnValues(
         const std::vector<typename std::decay<ReturnType>::type>& returnValues)
      {
         SixArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>::Expect();
         ValueReturner<ReturnType>::ZenMockPushBackReturnValues(returnValues);
      }

      ReturnType ZenMockItAndReturnValue(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4, Arg5Type arg5, Arg6Type arg6)
      {
         SixArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ExceptionThrower>::
            ZenMockIt(arg1, arg2, arg3, arg4, arg5, arg6);
         const ReturnType returnValue = ValueReturner<ReturnType>::ZenMockZenMockNextReturnValue();
         return returnValue;
      }
   };

   template<typename ReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   class NonVoidSixArgFunctionPointerMocker : public NonVoidSixArgMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>
   {
   public:
      explicit NonVoidSixArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidSixArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>(zenMockedFunctionSignature)
      {
      }

      static ReturnType ZenMockItFunctionPointer(
         NonVoidSixArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>* functionMocker,
         Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4, Arg5Type arg5, Arg6Type arg6)
      {
         return functionMocker->ZenMockItAndReturnValue(arg1, arg2, arg3, arg4, arg5, arg6);
      }
   };
}
