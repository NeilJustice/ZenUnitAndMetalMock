#pragma once
#include "ZenUnit/ZenMock/0/ZeroArgumentMocker.h"
#include "ZenUnit/ZenMock/Mock.h"

#define ZENMOCK_VOID0(functionName) \
        ZENMOCK_VOID0_DEFINED(functionName, virtual,      ,        , final)

#define ZENMOCK_VOID0_CONST(functionName) \
        ZENMOCK_VOID0_DEFINED(functionName, virtual, const, mutable, final)

#define ZENMOCK_VOID0_NONVIRTUAL(functionName) \
        ZENMOCK_VOID0_DEFINED(functionName,        ,        ,      ,         )

#define ZENMOCK_VOID0_CONST_NONVIRTUAL(functionName) \
        ZENMOCK_VOID0_DEFINED(functionName,        , const, mutable,         )

// Defines a freeFunctionName_ZenMock object for mocking a free function with signature "void freeFunctionName()".
#define ZENMOCK_VOID0_FREE(freeFunctionName) \
   static_assert(::freeFunctionName != nullptr); \
   ZenMock::VoidZeroArgFunctionPointerMocker freeFunctionName##_ZenMock = \
      ZenMock::VoidZeroArgFunctionPointerMocker(ZenMock::Signature::FunctionPointer("void", "::"#freeFunctionName"()"));

// Defines a functionName_ZenMock object for mocking a static or namespaced function with signature "void qualifiedClassNameOrNamespace::functionName()".
#define ZENMOCK_VOID0_STATIC(qualifiedClassNameOrNamespace, functionName, ...) \
   static_assert(qualifiedClassNameOrNamespace::functionName != nullptr); \
   ZenMock::VoidZeroArgFunctionPointerMocker functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidZeroArgFunctionPointerMocker( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"()"));

#define ZENMOCK_VOID0_DEFINED(functionName, virtualness, constness, mutableness, finalness) \
void functionName() constness finalness \
{ \
   functionName##Mock.ZenMockIt(); \
} \
struct ZenMock_##functionName : public ZenMock::VoidZeroArgumentMocker \
{ \
   explicit ZenMock_##functionName(const std::string* zenMockedClassName) \
      : ZenMock::VoidZeroArgumentMocker(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"()", #constness)) {} \
} mutableness functionName##Mock = ZenMock_##functionName(this->ZenMockedClassName());

namespace ZenMock
{
   class VoidZeroArgumentMocker : public ZeroArgumentMocker<ExceptionThrower>
   {
   public:
      explicit VoidZeroArgumentMocker(const std::string& zenMockedFunctionSignature)
         : ZeroArgumentMocker(zenMockedFunctionSignature)
      {
      }
   };

   class VoidZeroArgFunctionPointerMocker : public VoidZeroArgumentMocker
   {
   public:
      explicit VoidZeroArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : VoidZeroArgumentMocker(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(VoidZeroArgFunctionPointerMocker* functionPointerMocker)
      {
         functionPointerMocker->ZenMockIt();
      }
   };
}
