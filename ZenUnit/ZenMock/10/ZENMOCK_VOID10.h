#pragma once
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/10/TenArgMocker.h"

// Virtual Functions
#define ZENMOCK_VOID10(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
        ZENMOCK_VOID10_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, virtual,      ,        , final, __VA_ARGS__)

#define ZENMOCK_VOID10_CONST(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
        ZENMOCK_VOID10_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, virtual, const, mutable, final, __VA_ARGS__)

// Non-Virtual Functions
#define ZENMOCK_VOID10_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
        ZENMOCK_VOID10_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type,        ,      ,        ,         , __VA_ARGS__)

#define ZENMOCK_VOID10_CONST_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
        ZENMOCK_VOID10_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type,        , const, mutable,         , __VA_ARGS__)

// Global Functions
#define ZENMOCK_VOID10_GLOBAL(globalFunctionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
   ZenMock::VoidTenArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type> globalFunctionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidTenArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#globalFunctionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type", "#arg10Type")"));

// Static and Namespaced Functions
#define ZENMOCK_VOID10_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
   ZenMock::VoidTenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidTenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type", "#arg10Type")"));

// Implementation
#define ZENMOCK_VOID10_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, virtualness, constness, mutableness, finalness, ...) \
virtualness void functionName(arg1Type arg1, arg2Type arg2, arg3Type arg3, arg4Type arg4, arg5Type arg5, arg6Type arg6, arg7Type arg7, arg8Type arg8, arg9Type arg9, arg10Type arg10) constness finalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::ZenMockVoidTenArgs<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type> \
{ \
   ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::ZenMockVoidTenArgs<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type", "#arg10Type")", #constness)) {} \
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
      typename Arg8Type,
      typename Arg9Type,
      typename Arg10Type>
   class VoidTenArgMocker : public TenArgMocker<
      Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
      Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ExceptionThrower>
   {
   public:
      VoidTenArgMocker(const std::string& zenMockedFunctionSignature)
         : TenArgMocker<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(zenMockedFunctionSignature)
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
      typename Arg8Type,
      typename Arg9Type,
      typename Arg10Type>
   class VoidTenArgFunctionPointerMocker : public VoidTenArgMocker<
      Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
      Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>
   {
   public:
      VoidTenArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : VoidTenArgMocker<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidTenArgFunctionPointerMocker<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>* functionMocker,
         Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4, 
         Arg5Type arg5, Arg6Type arg6, Arg7Type arg7, Arg8Type arg8, Arg9Type arg9, Arg10Type arg10)
      {
         functionMocker->ZenMock(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
      }
   };
}
