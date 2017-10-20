#pragma once
#include "ZenUnit/ZenMock/2/TwoArgumentMocker.h"
#include "ZenUnit/ZenMock/Mock.h"

// Defines a <functionName>Mock object for mocking a virtual function with signature "void functionName(arg1Type, arg2Type)".
#define ZENMOCK_VOID2(functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_VOID2_DEFINED(functionName, arg1Type, arg2Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a virtual function with signature "void functionName(arg1Type, arg2Type) const".
#define ZENMOCK_VOID2_CONST(functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_VOID2_DEFINED(functionName, arg1Type, arg2Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a non-virtual function with signature "void functionName(arg1Type, arg2Type)".
#define ZENMOCK_VOID2_NONVIRTUAL(functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_VOID2_DEFINED(functionName, arg1Type, arg2Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a non-virtual function with signature "void functionName(arg1Type, arg2Type) const".
#define ZENMOCK_VOID2_CONST_NONVIRTUAL(functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_VOID2_DEFINED(functionName, arg1Type, arg2Type,        , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "void functionName(arg1Type, arg2Type)".
#define ZENMOCK_VOID2_FREE(functionName, arg1Type, arg2Type, ...) \
   ZenMock::VoidTwoArgFunctionPointerMocker<arg1Type, arg2Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidTwoArgFunctionPointerMocker<arg1Type, arg2Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#functionName"("#arg1Type", "#arg2Type")"));

// Defines a <functionName>_ZenMock object for mocking a static or namespaced function with signature "void qualifiedClassNameOrNamespace::functionName(arg1Type, arg2Type)".
#define ZENMOCK_VOID2_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, ...) \
   ZenMock::VoidTwoArgFunctionPointerMocker<arg1Type, arg2Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidTwoArgFunctionPointerMocker<arg1Type, arg2Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type")"));

#define ZENMOCK_VOID2_DEFINED(functionName, arg1Type, arg2Type, virtualness, constness, mutableness, finalness, ...) \
void functionName(arg1Type firstArgument, arg2Type secondArgument) constness finalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(firstArgument, secondArgument); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::VoidTwoArgumentMocker<arg1Type, arg2Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidTwoArgumentMocker<arg1Type, arg2Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type", "#arg2Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type>
   class VoidTwoArgumentMocker : public TwoArgumentMocker<Arg1Type, Arg2Type>
   {
   public:
      explicit VoidTwoArgumentMocker(const std::string& zenMockedFunctionSignature)
         : TwoArgumentMocker<Arg1Type, Arg2Type>(zenMockedFunctionSignature)
      {
      }

      void Expect()
      {
         TwoArgumentMocker<Arg1Type, Arg2Type>::Expect();
      }
   };

   template<typename Arg1Type, typename Arg2Type>
   class VoidTwoArgFunctionPointerMocker : public VoidTwoArgumentMocker<Arg1Type, Arg2Type>
   {
   public:
      explicit VoidTwoArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : VoidTwoArgumentMocker<Arg1Type, Arg2Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidTwoArgFunctionPointerMocker<Arg1Type, Arg2Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument)
      {
         functionMocker->ZenMock(firstArgument, secondArgument);
      }
   };
}
