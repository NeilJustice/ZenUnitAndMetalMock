#pragma once
#include "ZenUnit/ZenMock/8/EightArgMocker.h"
#include "ZenUnit/ZenMock/Mock.h"

// Virtual Functions
#define ZENMOCK_VOID8(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
        ZENMOCK_VOID8_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, virtual,      ,        , final, __VA_ARGS__)

#define ZENMOCK_VOID8_CONST(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
        ZENMOCK_VOID8_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, virtual, const, mutable, final, __VA_ARGS__)

// Non-Virtual Functions
#define ZENMOCK_VOID8_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
        ZENMOCK_VOID8_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type,        ,      ,        ,         , __VA_ARGS__)

#define ZENMOCK_VOID8_CONST_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
        ZENMOCK_VOID8_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type,        , const, mutable,         , __VA_ARGS__)

// Global Functions
#define ZENMOCK_VOID8_GLOBAL(globalFunctionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
   ZenMock::VoidEightArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type> globalFunctionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidEightArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#globalFunctionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type")"));

// Static and Namespaced Functions
#define ZENMOCK_VOID8_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
   ZenMock::VoidEightArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidEightArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type")"));

// Implementation
#define ZENMOCK_VOID8_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, virtualness, constness, mutableness, finalness, ...) \
void functionName(arg1Type arg1, arg2Type arg2, arg3Type arg3, arg4Type arg4, arg5Type arg5, arg6Type arg6, arg7Type arg7, arg8Type arg8) constness finalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::ZenMockVoidEightArgs<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::ZenMockVoidEightArgs<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type")", #constness)) {} \
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
      typename Arg7Type,
      typename Arg8Type>
   class VoidEightArgMocker : public EightArgMocker<
      Arg1Type, Arg2Type, Arg3Type, Arg4Type,
      Arg5Type, Arg6Type, Arg7Type, Arg8Type, ExceptionThrower>
   {
   public:
      explicit VoidEightArgMocker(const std::string& zenMockedFunctionSignature)
         : EightArgMocker<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type>(zenMockedFunctionSignature)
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
      typename Arg7Type,
      typename Arg8Type>
   class VoidEightArgFunctionPointerMocker : public VoidEightArgMocker<
      Arg1Type, Arg2Type, Arg3Type, Arg4Type,
      Arg5Type, Arg6Type, Arg7Type, Arg8Type>
   {
   public:
      explicit VoidEightArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : VoidEightArgMocker<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidEightArgFunctionPointerMocker<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type>* functionMocker,
         Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4,
         Arg5Type arg5, Arg6Type arg6, Arg7Type arg7, Arg8Type arg8)
      {
         functionMocker->ZenMock(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
      }
   };
}
