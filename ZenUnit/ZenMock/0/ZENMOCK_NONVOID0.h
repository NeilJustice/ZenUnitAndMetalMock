#pragma once
#include "ZenUnit/ZenMock/0/ZeroArgumentMocker.h"
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/ValueReturner.h"

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName()".
#define ZENMOCK_NONVOID0(returnType, functionName) \
        ZENMOCK_NONVOID0_DEFINED(returnType, functionName, virtual,      ,        , final)

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName() const".
#define ZENMOCK_NONVOID0_CONST(returnType, functionName) \
        ZENMOCK_NONVOID0_DEFINED(returnType, functionName, virtual, const, mutable, final)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName()".
#define ZENMOCK_NONVOID0_NONVIRTUAL(returnType, functionName) \
        ZENMOCK_NONVOID0_DEFINED(returnType, functionName,        ,      ,        ,         )

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName() const".
#define ZENMOCK_NONVOID0_CONST_NONVIRTUAL(returnType, functionName) \
        ZENMOCK_NONVOID0_DEFINED(returnType, functionName,        , const, mutable,         )

// Defines a <functionName>_ZenMock object for mocking a free function with signature "returnType functionName()".
#define ZENMOCK_NONVOID0_FREE(returnType, functionName) \
   ZenMock::NonVoidZeroArgFunctionPointerMocker<returnType> functionName##_ZenMock = \
      ZenMock::NonVoidZeroArgFunctionPointerMocker<returnType>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"()"));

// Defines a <functionName>_ZenMock object for mocking a static or namespaced function with signature "returnType qualifiedClassNameOrNamespace::functionName()".
#define ZENMOCK_NONVOID0_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, ...) \
   ZenMock::NonVoidZeroArgFunctionPointerMocker<returnType> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidZeroArgFunctionPointerMocker<returnType>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"()"));

#define ZENMOCK_NONVOID0_DEFINED(returnType, functionName, virtualness, constness, mutableness, finalness) \
returnType functionName() constness finalness \
{ \
   return functionName##Mock.ZenMockItAndReturnValue(); \
} \
struct ZenMock_##functionName : public ZenMock::NonVoidZeroArgumentMocker<returnType> \
{ \
   explicit ZenMock_##functionName(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidZeroArgumentMocker<returnType>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"()", #constness)) {} \
} mutableness functionName##Mock = ZenMock_##functionName(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename FunctionReturnType>
   class NonVoidZeroArgumentMocker : public ZeroArgumentMocker<ExceptionThrower>, protected ValueReturner<FunctionReturnType>
   {
   public:
      explicit NonVoidZeroArgumentMocker(const std::string& zenMockedFunctionSignature)
         : ZeroArgumentMocker<ExceptionThrower>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void ExpectAndReturn(ReturnType&& returnValue)
      {
         ZeroArgumentMocker<ExceptionThrower>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename ReturnType, typename... ReturnTypes>
      void ExpectAndReturnValues(ReturnType&& firstReturnValue, ReturnTypes&&... subsequentReturnValues)
      {
         ZeroArgumentMocker<ExceptionThrower>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(
            std::forward<ReturnType>(firstReturnValue),
            std::forward<ReturnTypes>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ExpectAndReturnValues(ContainerType&& returnValues)
      {
         ZeroArgumentMocker<ExceptionThrower>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      const FunctionReturnType& ZenMockItAndReturnValue()
      {
         ZeroArgumentMocker::ZenMockIt();
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType>
   class NonVoidZeroArgFunctionPointerMocker : public NonVoidZeroArgumentMocker<FunctionReturnType>
   {
   public:
      explicit NonVoidZeroArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidZeroArgumentMocker<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      static const FunctionReturnType& ZenMockItFunctionPointer(
         NonVoidZeroArgFunctionPointerMocker<FunctionReturnType>* functionPointerMocker)
      {
         return functionPointerMocker->ZenMockItAndReturnValue();
      }
   };
}
