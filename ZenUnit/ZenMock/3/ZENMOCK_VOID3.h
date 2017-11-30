#pragma once
#include "ZenUnit/ZenMock/3/ThreeArgumentMocker.h"
#include "ZenUnit/ZenMock/Mock.h"

// Defines a <functionName>Mock object for mocking a virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type)".
#define ZENMOCK_VOID3(functionName, arg1Type, arg2Type, arg3Type, ...) \
        ZENMOCK_VOID3_DEFINED(functionName, arg1Type, arg2Type, arg3Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type) const".
#define ZENMOCK_VOID3_CONST(functionName, arg1Type, arg2Type, arg3Type, ...) \
        ZENMOCK_VOID3_DEFINED(functionName, arg1Type, arg2Type, arg3Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a non-virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type)".
#define ZENMOCK_VOID3_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, ...) \
        ZENMOCK_VOID3_DEFINED(functionName, arg1Type, arg2Type, arg3Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a non-virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type) const".
#define ZENMOCK_VOID3_CONST_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, ...) \
        ZENMOCK_VOID3_DEFINED(functionName, arg1Type, arg2Type, arg3Type,        , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "void functionName(arg1Type, arg2Type, arg3Type)".
#define ZENMOCK_VOID3_FREE(functionName, arg1Type, arg2Type, arg3Type, ...) \
   ZenMock::VoidThreeArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidThreeArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type")"));

// Defines a <functionName>_ZenMock object for mocking a static or namespaced function with signature "void qualifiedClassNameOrNamespace::functionName(arg1Type, arg2Type, arg3Type)".
#define ZENMOCK_VOID3_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, ...) \
   ZenMock::VoidThreeArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidThreeArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type")"));

#define ZENMOCK_VOID3_DEFINED(functionName, arg1Type, arg2Type, arg3Type, virtualness, constness, mutableness, finalness, ...) \
void functionName(arg1Type firstArgument, arg2Type secondArgument, arg3Type thirdArgument) constness finalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(firstArgument, secondArgument, thirdArgument); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::VoidThreeArgumentMocker<arg1Type, arg2Type, arg3Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidThreeArgumentMocker<arg1Type, arg2Type, arg3Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class VoidThreeArgumentMocker : public ThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>
   {
   public:
      explicit VoidThreeArgumentMocker(const std::string& zenMockedFunctionSignature)
         : ThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>(zenMockedFunctionSignature)
      {
      }

      void Expect()
      {
         _expected = true;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class VoidThreeArgFunctionPointerMocker : public VoidThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>
   {
   public:
      explicit VoidThreeArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : VoidThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidThreeArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument)
      {
         functionMocker->ZenMock(firstArgument, secondArgument, thirdArgument);
      }
   };
}
