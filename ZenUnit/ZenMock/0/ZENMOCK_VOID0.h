#pragma once
#include "ZenUnit/ZenMock/0/ZeroArgumentMocker.h"
#include "ZenUnit/ZenMock/Mock.h"

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual void functionName()".
#define ZENMOCK_VOID0(functionName) \
        ZENMOCK_VOID0_DEFINED(functionName, virtual,      ,        , final)

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual void functionName() const".
#define ZENMOCK_VOID0_CONST(functionName) \
        ZENMOCK_VOID0_DEFINED(functionName, virtual, const, mutable, final)

// Defines a <functionName>Mock object for mocking a base class function with signature "void functionName()".
#define ZENMOCK_VOID0_NONVIRTUAL(functionName) \
        ZENMOCK_VOID0_DEFINED(functionName,        ,        ,      ,         )

// Defines a <functionName>Mock object for mocking a base class function with signature "void functionName() const".
#define ZENMOCK_VOID0_NONVIRTUAL_CONST(functionName) \
        ZENMOCK_VOID0_DEFINED(functionName,        , const, mutable,         )

// Defines a <functionName>_ZenMock object for mocking a free function with signature "void functionName()".
#define ZENMOCK_VOID0_FREE(functionName) \
   ZenMock::VoidZeroArgFunctionPointerMocker functionName##_ZenMock = \
      ZenMock::VoidZeroArgFunctionPointerMocker(ZenMock::Signature::FunctionPointer("void", "::"#functionName"()"));

// Defines a <functionName>_ZenMock object for mocking a static or namespaced function with signature "void qualifiedClassNameOrNamespace::functionName()".
#define ZENMOCK_VOID0_STATIC(qualifiedClassNameOrNamespace, functionName, ...) \
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
         : ZeroArgumentMocker<ExceptionThrower>(zenMockedFunctionSignature)
      {
      }

      void Expect()
      {
         ZeroArgumentMocker<ExceptionThrower>::_expected = true;
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
