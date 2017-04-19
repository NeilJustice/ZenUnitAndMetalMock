#pragma once
#include "ZenUnit/ZenMock/4/FourArgMocker.h"
#include "ZenUnit/ZenMock/Mock.h"

// Virtual Functions
#define ZENMOCK_VOID4(functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
        ZENMOCK_VOID4_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, virtual,      ,        , final, __VA_ARGS__)

#define ZENMOCK_VOID4_CONST(functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
        ZENMOCK_VOID4_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, virtual, const, mutable, final, __VA_ARGS__)

// Non-Virtual Functions
#define ZENMOCK_VOID4_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
        ZENMOCK_VOID4_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type,        ,      ,        ,         , __VA_ARGS__)

#define ZENMOCK_VOID4_CONST_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
        ZENMOCK_VOID4_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type,        , const, mutable,         , __VA_ARGS__)

// Global Functions
#define ZENMOCK_VOID4_GLOBAL(globalFunctionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
   ZenMock::VoidFourArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type> globalFunctionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidFourArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#globalFunctionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type")"));

// Static and Namespaced Functions
#define ZENMOCK_VOID4_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
   ZenMock::VoidFourArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidFourArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type")"));

// Implementation
#define ZENMOCK_VOID4_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, virtualness, constness, mutableness, finalness, ...) \
void functionName(arg1Type arg1, arg2Type arg2, arg3Type arg3, arg4Type arg4) constness finalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(arg1, arg2, arg3, arg4); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::VoidFourArgMocker<arg1Type, arg2Type, arg3Type, arg4Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidFourArgMocker<arg1Type, arg2Type, arg3Type, arg4Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class VoidFourArgMocker : public FourArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>
   {
   public:
      explicit VoidFourArgMocker(const std::string& zenMockedFunctionSignature)
         : FourArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>(zenMockedFunctionSignature)
      {
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class VoidFourArgFunctionPointerMocker : public VoidFourArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>
   {
   public:
      explicit VoidFourArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : VoidFourArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidFourArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>* functionMocker,
         Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4)
      {
         functionMocker->ZenMock(arg1, arg2, arg3, arg4);
      }
   };
}
