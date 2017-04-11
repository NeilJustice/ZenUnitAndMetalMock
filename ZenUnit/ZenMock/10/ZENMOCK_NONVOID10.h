#pragma once
#include "ZenUnit/ZenMock/10/TenArgMocker.h"
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/ValueReturner.h"

// Virtual Functions
#define ZENMOCK_NONVOID10(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
        ZENMOCK_NONVOID10_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, virtual,      ,        , final, __VA_ARGS__)

#define ZENMOCK_NONVOID10_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
        ZENMOCK_NONVOID10_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, virtual, const, mutable, final, __VA_ARGS__)

// Non-Virtual Functions
#define ZENMOCK_NONVOID10_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
        ZENMOCK_NONVOID10_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type,      ,      ,        ,         , __VA_ARGS__)

#define ZENMOCK_NONVOID10_CONST_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
        ZENMOCK_NONVOID10_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type,      , const, mutable,         , __VA_ARGS__)

// Global Functions
#define ZENMOCK_NONVOID10_GLOBAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
   ZenMock::NonVoidTenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidTenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type", "#arg10Type")"));

// Static and Namespaced Functions
#define ZENMOCK_NONVOID10_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
   ZenMock::NonVoidTenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidTenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type", "#arg10Type")"));

// Implementation
#define ZENMOCK_NONVOID10_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, virtualness, constness, mutableness, overridefinalness, ...) \
virtualness returnType functionName(arg1Type arg1, arg2Type arg2, arg3Type arg3, arg4Type arg4, arg5Type arg5, arg6Type arg6, arg7Type arg7, arg8Type arg8, arg9Type arg9, arg10Type arg10) constness overridefinalness \
{ \
   return functionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidTenArgMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidTenArgMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type", "#arg10Type")", #constness)) {} \
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
      typename Arg8Type,
      typename Arg9Type,
      typename Arg10Type>
   class NonVoidTenArgMocker : public TenArgMocker<
      Arg1Type, Arg2Type, Arg3Type, Arg4Type,
      Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ExceptionThrower>, private ValueReturner<ReturnType>
   {
   public:
      explicit NonVoidTenArgMocker(const std::string& zenMockedFunctionSignature)
         : TenArgMocker<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(zenMockedFunctionSignature)
      {
      }

      void ExpectAndReturn(const ReturnType& returnValue)
      {
         TenArgMocker<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>::Expect();
         ValueReturner<ReturnType>::DoAddReturnValue(returnValue);
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ExpectAndReturnValues(
         const FirstReturnValue& firstReturnValue,
         const SubsequentReturnValues&... subsequentReturnValues)
      {
         TenArgMocker<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>::Expect();
         ValueReturner<ReturnType>::ZenMockPushBackReturnValues(firstReturnValue, subsequentReturnValues...);
      }

      void ExpectAndReturnValues(
         const std::vector<typename std::decay<ReturnType>::type>& returnValues)
      {
         TenArgMocker<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>::Expect();
         ValueReturner<ReturnType>::ZenMockPushBackReturnValues(returnValues);
      }

      ReturnType ZenMockItAndReturnValue(
         Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4,
         Arg5Type arg5, Arg6Type arg6, Arg7Type arg7, Arg8Type arg8, Arg9Type arg9, Arg10Type arg10)
      {
         TenArgMocker<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>::
            ZenMock(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
         const ReturnType returnValue = ValueReturner<ReturnType>::ZenMockZenMockNextReturnValue();
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
      typename Arg8Type,
      typename Arg9Type,
      typename Arg10Type>
   class NonVoidTenArgFunctionPointerMocker : public NonVoidTenArgMocker<
      ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>
   {
   public:
      explicit NonVoidTenArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidTenArgFunctionPointerMocker<
            ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(zenMockedFunctionSignature)
      {
      }

      static ReturnType ZenMockItFunctionPointer(NonVoidTenArgFunctionPointerMocker<
         ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>* functionMocker,
         Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4,
         Arg5Type arg5, Arg6Type arg6, Arg7Type arg7, Arg8Type arg8, Arg9Type arg9, Arg10Type arg10)
      {
         return functionMocker->ZenMockItAndReturnValue(
            arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
      }
   };
}
