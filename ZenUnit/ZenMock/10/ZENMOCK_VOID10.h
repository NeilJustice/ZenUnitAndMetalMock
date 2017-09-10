#pragma once
#include "ZenUnit/ZenMock/10/TenArgumentMocker.h"
#include "ZenUnit/ZenMock/Mock.h"

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

// Free Functions
#define ZENMOCK_VOID10_FREE(freeFunctionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
   ZenMock::VoidTenArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type> freeFunctionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidTenArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#freeFunctionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type", "#arg10Type")"));

// Static and Namespaced Functions
#define ZENMOCK_VOID10_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
   ZenMock::VoidTenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidTenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type", "#arg10Type")"));

// Implementation
#define ZENMOCK_VOID10_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, virtualness, constness, mutableness, finalness, ...) \
void functionName(arg1Type argument1, arg2Type argument2, arg3Type argument3, arg4Type argument4, arg5Type argument5, arg6Type argument6, arg7Type argument7, arg8Type argument8, arg9Type argument9, arg10Type argument10) constness finalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(argument1, argument2, argument3, argument4, argument5, argument6, argument7, argument8, argument9, argument10); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::ZenMockVoidTenArgs<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::ZenMockVoidTenArgs<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type", "#arg10Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
   class VoidTenArgumentMocker : public TenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ExceptionThrower>
   {
   public:
      explicit VoidTenArgumentMocker(const std::string& zenMockedFunctionSignature)
         : TenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(zenMockedFunctionSignature)
      {
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
   class VoidTenArgFunctionPointerMocker : public VoidTenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>
   {
   public:
      explicit VoidTenArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : VoidTenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidTenArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>* functionMocker,
         Arg1Type argument1, Arg2Type argument2, Arg3Type argument3, Arg4Type argument4, Arg5Type argument5, Arg6Type argument6, Arg7Type argument7, Arg8Type argument8, Arg9Type argument9, Arg10Type argument10)
      {
         functionMocker->ZenMock(argument1, argument2, argument3, argument4, argument5, argument6, argument7, argument8, argument9, argument10);
      }
   };
}
