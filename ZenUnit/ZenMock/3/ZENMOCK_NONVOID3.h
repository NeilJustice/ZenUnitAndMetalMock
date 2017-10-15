#pragma once
#include "ZenUnit/ZenMock/3/ThreeArgumentMocker.h"
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/ValueReturner.h"

#define ZENMOCK_NONVOID3(returnType, functionName, arg1Type, arg2Type, arg3Type, ...) \
        ZENMOCK_NONVOID3_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, virtual,      ,        , final, __VA_ARGS__)

#define ZENMOCK_NONVOID3_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, ...) \
        ZENMOCK_NONVOID3_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, virtual, const, mutable, final, __VA_ARGS__)

#define ZENMOCK_NONVOID3_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, ...) \
        ZENMOCK_NONVOID3_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type,        ,      ,        ,         , __VA_ARGS__)

#define ZENMOCK_NONVOID3_CONST_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, ...) \
        ZENMOCK_NONVOID3_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type,        , const, mutable,         , __VA_ARGS__)

#define ZENMOCK_NONVOID3_FREE(returnType, functionName, arg1Type, arg2Type, arg3Type, ...) \
   ZenMock::NonVoidThreeArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidThreeArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type")"));

#define ZENMOCK_NONVOID3_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, ...) \
   ZenMock::NonVoidThreeArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidThreeArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type")"));

#define ZENMOCK_NONVOID3_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, virtualness, constness, mutableness, finalness, ...) \
returnType functionName(arg1Type argument1, arg2Type argument2, arg3Type argument3) constness finalness \
{ \
   return functionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(argument1, argument2, argument3); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidThreeArgumentMocker<returnType, arg1Type, arg2Type, arg3Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidThreeArgumentMocker<returnType, arg1Type, arg2Type, arg3Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename ReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class NonVoidThreeArgumentMocker : public ThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>, private ValueReturner<ReturnType>
   {
   public:
      explicit NonVoidThreeArgumentMocker(const std::string& zenMockedFunctionSignature)
         : ThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>(zenMockedFunctionSignature)
         , ValueReturner<ReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnTypeURef>
      void ExpectAndReturn(ReturnTypeURef&& returnValue)
      {
         ThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>::Expect();
         ValueReturner<ReturnType>::ZenMockAddReturnValue(std::forward<ReturnTypeURef>(returnValue));
      }

      template<typename ContainerType>
      void ExpectAndReturnValues(ContainerType&& returnValues)
      {
         ThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>::Expect();
         ValueReturner<ReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ExpectAndReturnValues(const FirstReturnValue& firstReturnValue, const SubsequentReturnValues&... subsequentReturnValues)
      {
         ThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>::Expect();
         ValueReturner<ReturnType>::ZenMockAddReturnValues(firstReturnValue, subsequentReturnValues...);
      }

      ReturnType ZenMockItAndReturnValue(Arg1Type argument1, Arg2Type argument2, Arg3Type argument3)
      {
         ThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>::ZenMockIt(argument1, argument2, argument3);
         return ValueReturner<ReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename ReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class NonVoidThreeArgFunctionPointerMocker : public NonVoidThreeArgumentMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type>
   {
   public:
      explicit NonVoidThreeArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidThreeArgumentMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type>(zenMockedFunctionSignature)
      {
      }

      static ReturnType ZenMockItFunctionPointer(
         NonVoidThreeArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type>* functionMocker,
         Arg1Type argument1, Arg2Type argument2, Arg3Type argument3)
      {
         return functionMocker->ZenMockItAndReturnValue(argument1, argument2, argument3);
      }
   };
}
