#pragma once
#include "ZenUnit/ZenMock/4/FourArgumentMocker.h"
#include "ZenUnit/ZenMock/Mock.h"

// Defines a <functionName>Mock object for mocking a virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type)".
#define ZENMOCK_VOID4(functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
        ZENMOCK_VOID4_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type) const".
#define ZENMOCK_VOID4_CONST(functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
        ZENMOCK_VOID4_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a non-virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type)".
#define ZENMOCK_VOID4_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
        ZENMOCK_VOID4_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a non-virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type) const".
#define ZENMOCK_VOID4_NONVIRTUAL_CONST(functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
        ZENMOCK_VOID4_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type,        , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type)".
#define ZENMOCK_VOID4_FREE(functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
   ZenMock::VoidFourArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidFourArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type")"));

// Defines a <functionName>_ZenMock object for mocking a static or namespaced function with signature "void qualifiedClassNameOrNamespace::functionName(arg1Type, arg2Type, arg3Type, arg4Type)".
#define ZENMOCK_VOID4_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
   ZenMock::VoidFourArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidFourArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type")"));

#define ZENMOCK_VOID4_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, virtualness, constness, mutableness, finalness, ...) \
void functionName(arg1Type firstArgument, arg2Type secondArgument, arg3Type thirdArgument, arg4Type fourthArgument) constness finalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::VoidFourArgumentMocker<arg1Type, arg2Type, arg3Type, arg4Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidFourArgumentMocker<arg1Type, arg2Type, arg3Type, arg4Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class VoidFourArgumentMocker : public FourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>
   {
   public:
      explicit VoidFourArgumentMocker(const std::string& zenMockedFunctionSignature)
         : FourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>(zenMockedFunctionSignature)
      {
      }

      void Expect()
      {
         FourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::_expected = true;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class VoidFourArgFunctionPointerMocker : public VoidFourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>
   {
   public:
      explicit VoidFourArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : VoidFourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidFourArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument)
      {
         functionMocker->ZenMock(firstArgument, secondArgument, thirdArgument, fourthArgument);
      }
   };
}
