#pragma once
#include "ZenUnit/ZenMock/5/FiveArgumentMocker.h"
#include "ZenUnit/ZenMock/Mock.h"

// Defines a <functionName>Mock object for mocking a virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type)".
#define ZENMOCK_VOID5(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
        ZENMOCK_VOID5_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type) const".
#define ZENMOCK_VOID5_CONST(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
        ZENMOCK_VOID5_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a non-virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type)".
#define ZENMOCK_VOID5_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
        ZENMOCK_VOID5_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type,       ,      ,        ,          , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a non-virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type) const".
#define ZENMOCK_VOID5_CONST_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
        ZENMOCK_VOID5_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type,       , const, mutable,          , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type)".
#define ZENMOCK_VOID5_FREE(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
   ZenMock::VoidFiveArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidFiveArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type")"));

// Defines a <functionName>_ZenMock object for mocking a static or namespaced function with signature "void qualifiedClassNameOrNamespace::functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type)".
#define ZENMOCK_VOID5_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
   ZenMock::VoidFiveArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidFiveArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type")"));

#define ZENMOCK_VOID5_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, virtualness, constness, mutableness, finalness, ...) \
void functionName(arg1Type firstArgument, arg2Type secondArgument, arg3Type thirdArgument, arg4Type fourthArgument, arg5Type fifthArgument) constness finalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::VoidFiveArgumentMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidFiveArgumentMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   class VoidFiveArgumentMocker : public FiveArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>
   {
   public:
      explicit VoidFiveArgumentMocker(const std::string& zenMockedFunctionSignature)
         : FiveArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>(zenMockedFunctionSignature)
      {
      }

      void Expect()
      {
         _expected = true;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   class VoidFiveArgFunctionPointerMocker : public VoidFiveArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>
   {
   public:
      explicit VoidFiveArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : VoidFiveArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidFiveArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument)
      {
         functionMocker->ZenMock(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument);
      }
   };
}
