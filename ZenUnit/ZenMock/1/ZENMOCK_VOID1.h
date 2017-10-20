#pragma once
#include "ZenUnit/ZenMock/1/OneArgumentMocker.h"
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/Signature.h"

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual void functionName(arg1Type)".
#define ZENMOCK_VOID1(functionName, arg1Type, ...) \
        ZENMOCK_VOID1_DEFINED(functionName, arg1Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual void functionName(arg1Type) const".
#define ZENMOCK_VOID1_CONST(functionName, arg1Type, ...) \
        ZENMOCK_VOID1_DEFINED(functionName, arg1Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "void functionName(arg1Type)".
#define ZENMOCK_VOID1_NONVIRTUAL(functionName, arg1Type, ...) \
        ZENMOCK_VOID1_DEFINED(functionName, arg1Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "void functionName(arg1Type) const".
#define ZENMOCK_VOID1_CONST_NONVIRTUAL(functionName, arg1Type, ...) \
        ZENMOCK_VOID1_DEFINED(functionName, arg1Type,        , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "void functionName(arg1Type)".
#define ZENMOCK_VOID1_FREE(functionName, arg1Type, ...) \
   ZenMock::VoidOneArgFunctionPointerMocker<arg1Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidOneArgFunctionPointerMocker<arg1Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#functionName"("#arg1Type")"));

// Defines a <functionName>_ZenMock object for mocking a static or namespaced function with signature "void qualifiedClassNameOrNamespace::functionName(arg1Type)".
#define ZENMOCK_VOID1_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, ...) \
   ZenMock::VoidOneArgFunctionPointerMocker<arg1Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidOneArgFunctionPointerMocker<arg1Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type")"));

#define ZENMOCK_VOID1_DEFINED(functionName, arg1Type, virtualness, constness, mutableness, finalness, ...) \
void functionName(arg1Type arg) constness finalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(arg); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::VoidOneArgumentMocker<arg1Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidOneArgumentMocker<arg1Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename ArgType>
   class VoidOneArgumentMocker : public OneArgumentMocker<ArgType>
   {
   public:
      explicit VoidOneArgumentMocker(const std::string& zenMockedFunctionSignature)
         : OneArgumentMocker<ArgType>(zenMockedFunctionSignature)
      {
      }
   };

   template<typename Arg1Type>
   class VoidOneArgFunctionPointerMocker : public VoidOneArgumentMocker<Arg1Type>
   {
   public:
      explicit VoidOneArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : VoidOneArgumentMocker<Arg1Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidOneArgFunctionPointerMocker<Arg1Type>* functionMocker, Arg1Type argument)
      {
         functionMocker->ZenMockIt(argument);
      }
   };
}
