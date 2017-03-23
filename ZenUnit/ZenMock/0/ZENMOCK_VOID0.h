#pragma once
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/0/ZeroArgMocker.h"

// Virtual Functions
#define ZENMOCK_VOID0(functionName) \
        ZENMOCK_VOID0_DEFINED(functionName, virtual,      ,        , override)

#define ZENMOCK_VOID0_CONST(functionName) \
        ZENMOCK_VOID0_DEFINED(functionName, virtual, const, mutable, override)

// Non-Virtual Functions
#define ZENMOCK_VOID0_NONVIRTUAL(functionName) \
        ZENMOCK_VOID0_DEFINED(functionName,        ,        ,      ,         )

#define ZENMOCK_VOID0_CONST_NONVIRTUAL(functionName) \
        ZENMOCK_VOID0_DEFINED(functionName,        , const, mutable,         )

// Global Functions
#define ZENMOCK_VOID0_GLOBAL(globalFunctionName) \
   ZenMock::VoidZeroArgFunctionPointerMocker globalFunctionName##_ZenMock = \
      ZenMock::VoidZeroArgFunctionPointerMocker(ZenMock::Signature::FunctionPointer("void", "::"#globalFunctionName"()"));

// Static and Namespaced Functions
#define ZENMOCK_VOID0_STATIC(qualifiedClassNameOrNamespace, functionName, ...) \
   ZenMock::VoidZeroArgFunctionPointerMocker functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidZeroArgFunctionPointerMocker( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"()"));

// Implementation
#define ZENMOCK_VOID0_DEFINED(functionName, virtualness, constness, mutableness, overrideness) \
virtualness void functionName() constness overrideness \
{ \
   functionName##Mock.PrivateZenMock(); \
} \
struct ZenMock_##functionName : public ZenMock::VoidZeroArgMocker \
{ \
   ZenMock_##functionName(const std::string* zenMockedClassName) \
      : ZenMock::VoidZeroArgMocker(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"()", #constness)) {} \
} mutableness functionName##Mock = ZenMock_##functionName(this->ZenMockedClassName());

namespace ZenMock
{
   class VoidZeroArgMocker : public ZeroArgMocker<ExceptionThrower>
   {
   public:
      VoidZeroArgMocker(const std::string& zenMockedFunctionSignature)
         : ZeroArgMocker(zenMockedFunctionSignature)
      {
      }
   };

   class VoidZeroArgFunctionPointerMocker : public VoidZeroArgMocker
   {
   public:
      VoidZeroArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : VoidZeroArgMocker(zenMockedFunctionSignature)
      {
      }

      static void PrivateZenMockFunctionPointer(VoidZeroArgFunctionPointerMocker* functionPointerMocker)
      {
         functionPointerMocker->PrivateZenMock();
      }
   };
}
