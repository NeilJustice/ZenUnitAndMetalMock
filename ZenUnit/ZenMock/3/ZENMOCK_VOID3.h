#pragma once
#include "ZenUnit/ZenMock/3/ThreeArgumentMocker.h"
#include "ZenUnit/ZenMock/Mock.h"

// Virtual Functions
#define ZENMOCK_VOID3(functionName, arg1Type, arg2Type, arg3Type, ...) \
        ZENMOCK_VOID3_DEFINED(functionName, arg1Type, arg2Type, arg3Type, virtual,      ,        , final, __VA_ARGS__)

#define ZENMOCK_VOID3_CONST(functionName, arg1Type, arg2Type, arg3Type, ...) \
        ZENMOCK_VOID3_DEFINED(functionName, arg1Type, arg2Type, arg3Type, virtual, const, mutable, final, __VA_ARGS__)

// Non-Virtual Functions
#define ZENMOCK_VOID3_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, ...) \
        ZENMOCK_VOID3_DEFINED(functionName, arg1Type, arg2Type, arg3Type,        ,      ,        ,         , __VA_ARGS__)

#define ZENMOCK_VOID3_CONST_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, ...) \
        ZENMOCK_VOID3_DEFINED(functionName, arg1Type, arg2Type, arg3Type,        , const, mutable,         , __VA_ARGS__)

// Free Functions
#define ZENMOCK_VOID3_FREE(freeFunctionName, arg1Type, arg2Type, arg3Type, ...) \
   ZenMock::VoidThreeArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type> freeFunctionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidThreeArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#freeFunctionName"("#arg1Type", "#arg2Type", "#arg3Type")"));

// Static and Namespaced Functions
#define ZENMOCK_VOID3_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, ...) \
   ZenMock::VoidThreeArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidThreeArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type")"));

// Implementation
#define ZENMOCK_VOID3_DEFINED(functionName, arg1Type, arg2Type, arg3Type, virtualness, constness, mutableness, finalness, ...) \
void functionName(arg1Type argument1, arg2Type argument2, arg3Type argument3) constness finalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(argument1, argument2, argument3); \
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
         Arg1Type argument1, Arg2Type argument2, Arg3Type argument3)
      {
         functionMocker->ZenMock(argument1, argument2, argument3);
      }
   };
}
