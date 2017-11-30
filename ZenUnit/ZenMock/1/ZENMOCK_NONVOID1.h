#pragma once
#include "ZenUnit/ZenMock/1/OneArgumentMocker.h"
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/ValueReturner.h"

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type)".
#define ZENMOCK_NONVOID1(returnType, functionName, arg1Type, ...) \
        ZENMOCK_NONVOID1_DEFINED(returnType, functionName, arg1Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type) const".
#define ZENMOCK_NONVOID1_CONST(returnType, functionName, arg1Type, ...) \
        ZENMOCK_NONVOID1_DEFINED(returnType, functionName, arg1Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type)".
#define ZENMOCK_NONVOID1_NONVIRTUAL(returnType, functionName, arg1Type, ...) \
        ZENMOCK_NONVOID1_DEFINED(returnType, functionName, arg1Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type) const".
#define ZENMOCK_NONVOID1_CONST_NONVIRTUAL(returnType, functionName, arg1Type, ...) \
        ZENMOCK_NONVOID1_DEFINED(returnType, functionName, arg1Type,        , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "returnType functionName(arg1Type)".
#define ZENMOCK_NONVOID1_FREE(returnType, functionName, arg1Type, ...) \
   ZenMock::NonVoidOneArgFunctionPointerMocker<returnType, arg1Type> \
      functionName##_ZenMock##__VA_ARGS__ = ZenMock::NonVoidOneArgFunctionPointerMocker<returnType, arg1Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type")"));

// Defines a functionName_ZenMock object for mocking a static or namespaced function with signature "returnType qualifiedClassNameOrNamespace::functionName(arg1Type)".
#define ZENMOCK_NONVOID1_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, ...) \
   ZenMock::NonVoidOneArgFunctionPointerMocker<returnType, arg1Type> \
      functionName##_ZenMock##__VA_ARGS__ = ZenMock::NonVoidOneArgFunctionPointerMocker<returnType, arg1Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type")"));

#define ZENMOCK_NONVOID1_DEFINED(returnType, functionName, arg1Type, virtualness, constness, mutableness, finalness, ...) \
returnType functionName(arg1Type arg) constness finalness \
{ \
   return functionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(arg); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidOneArgumentMocker<returnType, arg1Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidOneArgumentMocker<returnType, arg1Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename FunctionReturnType, typename ArgType>
   class NonVoidOneArgumentMocker : public OneArgumentMocker<ArgType>, protected ValueReturner<FunctionReturnType>
   {
   public:
      explicit NonVoidOneArgumentMocker(const std::string& zenMockedFunctionSignature)
         : OneArgumentMocker<ArgType>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void ExpectAndReturn(ReturnType&& returnValue)
      {
         OneArgumentMocker<ArgType>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename ReturnValueURef, typename... ReturnValueURefs>
      void ExpectAndReturnValues(ReturnValueURef&& firstReturnValue, ReturnValueURefs&&... subsequentReturnValues)
      {
         OneArgumentMocker<ArgType>_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(
            std::forward<ReturnValueURef>(firstReturnValue),
            std::forward<ReturnValueURef>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ExpectAndReturnValues(ContainerType&& returnValues)
      {
         OneArgumentMocker<ArgType>_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      const FunctionReturnType& ZenMockItAndReturnValue(ArgType argument)
      {
         OneArgumentMocker<ArgType>::ZenMockIt(argument);
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type>
   class NonVoidOneArgFunctionPointerMocker : public NonVoidOneArgumentMocker<FunctionReturnType, Arg1Type>
   {
   public:
      explicit NonVoidOneArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidOneArgumentMocker<FunctionReturnType, Arg1Type>(zenMockedFunctionSignature)
      {
      }

      static const FunctionReturnType& ZenMockItFunctionPointer(
         NonVoidOneArgFunctionPointerMocker* functionMocker, Arg1Type argument)
      {
         return functionMocker->ZenMockItAndReturnValue(argument);
      }
   };
}
