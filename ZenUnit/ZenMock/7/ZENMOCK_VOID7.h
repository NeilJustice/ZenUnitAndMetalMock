#pragma once
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/7/SevenArgMocker.h"

// Virtual Functions
#define ZENMOCK_VOID7(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
        ZENMOCK_VOID7_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, virtual,      ,        , override, __VA_ARGS__)

#define ZENMOCK_VOID7_CONST(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
        ZENMOCK_VOID7_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, virtual, const, mutable, override, __VA_ARGS__)

// Non-Virtual Functions
#define ZENMOCK_VOID7_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
        ZENMOCK_VOID7_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type,        ,      ,        ,         , __VA_ARGS__)

#define ZENMOCK_VOID7_CONST_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
        ZENMOCK_VOID7_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type,        , const, mutable,         , __VA_ARGS__)

// Global Functions
#define ZENMOCK_VOID7_GLOBAL(globalFunctionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
   ZenMock::VoidSevenArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type> globalFunctionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidSevenArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#globalFunctionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type")"));

// Static and Namespaced Functions
#define ZENMOCK_VOID7_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
   ZenMock::VoidSevenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidSevenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type")"));

// Implementation
#define ZENMOCK_VOID7_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, virtualness, constness, mutableness, overrideness, ...) \
virtualness void functionName(arg1Type arg1, arg2Type arg2, arg3Type arg3, arg4Type arg4, arg5Type arg5, arg6Type arg6, arg7Type arg7) constness overrideness \
{ \
   functionName##Mock##__VA_ARGS__.PrivateZenMock(arg1, arg2, arg3, arg4, arg5, arg6, arg7); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::ZenMockVoidSevenArgs<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type> \
{ \
   ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::ZenMockVoidSevenArgs<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename Arg4Type,
      typename Arg5Type,
      typename Arg6Type,
      typename Arg7Type>
   class VoidSevenArgMocker : public SevenArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ExceptionThrower>
   {
   public:
      VoidSevenArgMocker(const std::string& zenMockedFunctionSignature)
         : SevenArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>(zenMockedFunctionSignature)
      {
      }
   };

   template<
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename Arg4Type,
      typename Arg5Type,
      typename Arg6Type,
      typename Arg7Type>
   class VoidSevenArgFunctionPointerMocker : public VoidSevenArgMocker<
      Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>
   {
   public:
      VoidSevenArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : VoidSevenArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>(zenMockedFunctionSignature)
      {
      }

      static void PrivateZenMockFunctionPointer(
         VoidSevenArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>* functionMocker,
         Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4, Arg5Type arg5, Arg6Type arg6, Arg7Type arg7)
      {
         functionMocker->ZenMock(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
      }
   };
}
