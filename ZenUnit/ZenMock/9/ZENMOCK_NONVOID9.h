#pragma once
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/9/NineArgMocker.h"
#include "ZenUnit/ZenMock/ValueReturner.h"

// Virtual Functions
#define ZENMOCK_NONVOID9(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, ...) \
        ZENMOCK_NONVOID9_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, virtual,      ,        , override, __VA_ARGS__)

#define ZENMOCK_NONVOID9_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, ...) \
        ZENMOCK_NONVOID9_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, virtual, const, mutable, override, __VA_ARGS__)

// Non-Virtual Functions
#define ZENMOCK_NONVOID9_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, ...) \
        ZENMOCK_NONVOID9_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type,       ,      ,        ,         , __VA_ARGS__)

#define ZENMOCK_NONVOID9_CONST_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, ...) \
        ZENMOCK_NONVOID9_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type,       , const, mutable,         , __VA_ARGS__)

// Global Functions
#define ZENMOCK_NONVOID9_GLOBAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, ...) \
   ZenMock::NonVoidNineArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidNineArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type")"));

// Static and Namespaced Functions
#define ZENMOCK_NONVOID9_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, ...) \
   ZenMock::NonVoidNineArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidNineArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type")"));

// Implementation
#define ZENMOCK_NONVOID9_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, virtualness, constness, mutableness, overrideness, ...) \
virtualness returnType functionName(arg1Type arg1, arg2Type arg2, arg3Type arg3, arg4Type arg4, arg5Type arg5, arg6Type arg6, arg7Type arg7, arg8Type arg8, arg9Type arg9) constness overrideness \
{ \
   return functionName##Mock##__VA_ARGS__.PrivateZenMockAndReturnValue(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidNineArgMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type> \
{ \
   ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidNineArgMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type")", #constness)) {} \
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
      typename Arg9Type>
   class NonVoidNineArgMocker : public NineArgMocker<
      Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
      Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ExceptionThrower>, private ValueReturner<ReturnType>
   {
   public:
      NonVoidNineArgMocker(const std::string& zenMockedFunctionSignature)
         : NineArgMocker<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>(zenMockedFunctionSignature)
      {
      }

      void ExpectAndReturn(const ReturnType& returnValue)
      {
         NineArgMocker<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>::Expect();
         ValueReturner<ReturnType>::DoAddReturnValue(returnValue);
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ExpectAndReturnValues(
         const FirstReturnValue& firstReturnValue,
         const SubsequentReturnValues&... subsequentReturnValues)
      {
         NineArgMocker<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>::Expect();
         ValueReturner<ReturnType>::PrivatePushBackReturnValues(firstReturnValue, subsequentReturnValues...);
      }

      void ExpectAndReturnValues(
         const std::vector<typename std::decay<ReturnType>::type>& returnValues)
      {
         NineArgMocker<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>::Expect();
         ValueReturner<ReturnType>::PrivatePushBackReturnValues(returnValues);
      }

      ReturnType PrivateZenMockAndReturnValue(
         Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4, 
         Arg5Type arg5, Arg6Type arg6, Arg7Type arg7, Arg8Type arg8, Arg9Type arg9)
      {
         NineArgMocker<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>::
            ZenMock(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
         const ReturnType returnValue = ValueReturner<ReturnType>::PrivateNextReturnValue();
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
      typename Arg9Type>
   class NonVoidNineArgFunctionPointerMocker : public NonVoidNineArgMocker<
      ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>
   {
   public:
      NonVoidNineArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidNineArgFunctionPointerMocker<
            ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>(zenMockedFunctionSignature)
      {
      }

      static ReturnType PrivateZenMockFunctionPointer(NonVoidNineArgFunctionPointerMocker<
         ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>* functionMocker,
         Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4, 
         Arg5Type arg5, Arg6Type arg6, Arg7Type arg7, Arg8Type arg8, Arg9Type arg9)
      {
         return functionMocker->PrivateZenMockAndReturnValue(
            arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
      }
   };
}
