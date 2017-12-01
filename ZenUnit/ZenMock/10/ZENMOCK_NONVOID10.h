#pragma once
#include "ZenUnit/ZenMock/10/TenArgumentMocker.h"
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/ValueReturner.h"

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type)".
#define ZENMOCK_NONVOID10(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
        ZENMOCK_NONVOID10_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type) const".
#define ZENMOCK_NONVOID10_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
        ZENMOCK_NONVOID10_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type)".
#define ZENMOCK_NONVOID10_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
        ZENMOCK_NONVOID10_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type,      ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type) const".
#define ZENMOCK_NONVOID10_CONST_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
        ZENMOCK_NONVOID10_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type,      , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type)".
#define ZENMOCK_NONVOID10_FREE(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
   ZenMock::NonVoidTenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidTenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type", "#arg10Type")"));

// Defines a functionName_ZenMock object for mocking a static or namespaced function with signature "returnType qualifiedClassNameOrNamespace::functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type)".
#define ZENMOCK_NONVOID10_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
   ZenMock::NonVoidTenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidTenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type", "#arg10Type")"));

#define ZENMOCK_NONVOID10_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, virtualness, constness, mutableness, finalness, ...) \
returnType functionName(arg1Type firstArgument, arg2Type secondArgument, arg3Type thirdArgument, arg4Type fourthArgument, arg5Type fifthArgument, arg6Type sixthArgument, arg7Type seventhArgument, arg8Type eigthArgument, arg9Type ninthArgument, arg10Type tenthArgument) constness finalness \
{ \
   return functionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument, tenthArgument); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidTenArgumentMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidTenArgumentMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type", "#arg10Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
   class NonVoidTenArgumentMocker : public TenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ExceptionThrower>, protected ValueReturner<FunctionReturnType>
   {
   public:
      explicit NonVoidTenArgumentMocker(const std::string& zenMockedFunctionSignature)
         : TenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void ExpectAndReturn(ReturnType&& returnValue)
      {
         TenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ExceptionThrower>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ExpectAndReturnValues(const FirstReturnValue& firstReturnValue, const SubsequentReturnValues&... subsequentReturnValues)
      {
         TenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ExceptionThrower>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(firstReturnValue, subsequentReturnValues...);
      }

      template<typename ContainerType>
      void ExpectAndReturnValues(ContainerType&& returnValues)
      {
         TenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ExceptionThrower>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      const FunctionReturnType& ZenMockItAndReturnValue(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument, Arg9Type ninthArgument, Arg10Type tenthArgument)
      {
         TenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>::ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument, tenthArgument);
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
   class NonVoidTenArgFunctionPointerMocker : public NonVoidTenArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>
   {
   public:
      explicit NonVoidTenArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidTenArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(zenMockedFunctionSignature)
      {
      }

      static const FunctionReturnType& ZenMockItFunctionPointer(
         NonVoidTenArgFunctionPointerMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument, Arg9Type ninthArgument, Arg10Type tenthArgument)
      {
         return functionMocker->ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument, tenthArgument);
      }
   };
}
