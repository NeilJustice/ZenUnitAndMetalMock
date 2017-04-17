#pragma once
#include "ZenUnit/ZenMock/8/EightArgMocker.h"
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/ValueReturner.h"

// Virtual Functions
#define ZENMOCK_NONVOID8(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
        ZENMOCK_NONVOID8_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, virtual,      ,        , override final, __VA_ARGS__)

#define ZENMOCK_NONVOID8_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
        ZENMOCK_NONVOID8_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, virtual, const, mutable, override final, __VA_ARGS__)

// Non-Virtual Functions
#define ZENMOCK_NONVOID8_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
        ZENMOCK_NONVOID8_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type,        ,      ,        ,         , __VA_ARGS__)

#define ZENMOCK_NONVOID8_CONST_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
        ZENMOCK_NONVOID8_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type,        , const, mutable,         , __VA_ARGS__)

// Global Functions
#define ZENMOCK_NONVOID8_GLOBAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
   ZenMock::NonVoidEightArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidEightArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type")"));

// Static and Namespaced Functions
#define ZENMOCK_NONVOID8_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
   ZenMock::NonVoidEightArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidEightArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type")"));

// Implementation
#define ZENMOCK_NONVOID8_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, virtualness, constness, mutableness, overridefinalness, ...) \
virtualness returnType functionName(arg1Type arg1, arg2Type arg2, arg3Type arg3, arg4Type arg4, arg5Type arg5, arg6Type arg6, arg7Type arg7, arg8Type arg8) constness overridefinalness \
{ \
   return functionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidEightArgMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidEightArgMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<
      typename ReturnType,
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename Arg4Type,
      typename Arg5Type,
      typename Arg6Type,
      typename Arg7Type,
      typename Arg8Type>
   class NonVoidEightArgMocker : public EightArgMocker<
      Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ExceptionThrower>, private ValueReturner<ReturnType>
   {
   public:
      explicit NonVoidEightArgMocker(const std::string& zenMockedFunctionSignature)
         : EightArgMocker<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type>(zenMockedFunctionSignature)
      {
      }

      void ExpectAndReturn(const ReturnType& returnValue)
      {
         EightArgMocker<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type>::Expect();
         ValueReturner<ReturnType>::DoAddReturnValue(returnValue);
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ExpectAndReturnValues(
         const FirstReturnValue& firstReturnValue,
         const SubsequentReturnValues&... subsequentReturnValues)
      {
         EightArgMocker<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type>::Expect();
         ValueReturner<ReturnType>::ZenMockPushBackReturnValues(firstReturnValue, subsequentReturnValues...);
      }

      void ExpectAndReturnValues(
         const std::vector<typename std::decay<ReturnType>::type>& returnValues)
      {
         EightArgMocker<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type>::Expect();
         ValueReturner<ReturnType>::ZenMockPushBackReturnValues(returnValues);
      }

      ReturnType ZenMockItAndReturnValue(
         Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4,
         Arg5Type arg5, Arg6Type arg6, Arg7Type arg7, Arg8Type arg8)
      {
         EightArgMocker<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type>::
            ZenMock(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
         ReturnType returnValue = ValueReturner<ReturnType>::ZenMockZenMockNextReturnValue();
         return returnValue;
      }
   };

   template<
      typename ReturnType,
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename Arg4Type,
      typename Arg5Type,
      typename Arg6Type,
      typename Arg7Type,
      typename Arg8Type>
   class NonVoidEightArgFunctionPointerMocker : public NonVoidEightArgMocker<
      ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>
   {
   public:
      explicit NonVoidEightArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidEightArgFunctionPointerMocker<
            ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>(zenMockedFunctionSignature)
      {
      }

      static ReturnType ZenMockItFunctionPointer(NonVoidEightArgFunctionPointerMocker<
         ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>* functionMocker,
         Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4, Arg5Type arg5, Arg6Type arg6, Arg7Type arg7, Arg8Type arg8)
      {
         return functionMocker->ZenMockItAndReturnValue(
            arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
      }
   };
}
