#pragma once
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/3/ThreeArgMocker.h"

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

// Global Functions
#define ZENMOCK_VOID3_GLOBAL(globalFunctionName, arg1Type, arg2Type, arg3Type, ...) \
   ZenMock::VoidThreeArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type> globalFunctionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidThreeArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#globalFunctionName"("#arg1Type", "#arg2Type", "#arg3Type")"));

// Static and Namespaced Functions
#define ZENMOCK_VOID3_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, ...) \
   ZenMock::VoidThreeArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidThreeArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type")"));

// Implementation
#define ZENMOCK_VOID3_DEFINED(functionName, arg1Type, arg2Type, arg3Type, virtualness, constness, mutableness, overridefinalness, ...) \
virtualness void functionName(arg1Type arg1, arg2Type arg2, arg3Type arg3) constness overridefinalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(arg1, arg2, arg3); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::VoidThreeArgMocker<arg1Type, arg2Type, arg3Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidThreeArgMocker<arg1Type, arg2Type, arg3Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class VoidThreeArgMocker : public ThreeArgMocker<Arg1Type, Arg2Type, Arg3Type>
   {
   public:
      explicit VoidThreeArgMocker(const std::string& zenMockedFunctionSignature)
         : ThreeArgMocker<Arg1Type, Arg2Type, Arg3Type>(zenMockedFunctionSignature)
      {
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class VoidThreeArgFunctionPointerMocker : public VoidThreeArgMocker<Arg1Type, Arg2Type, Arg3Type>
   {
   public:
      explicit VoidThreeArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : VoidThreeArgMocker<Arg1Type, Arg2Type, Arg3Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidThreeArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type>* functionMocker,
         Arg1Type arg1, Arg2Type arg2, Arg3Type arg3)
      {
         functionMocker->ZenMock(arg1, arg2, arg3);
      }
   };
}
