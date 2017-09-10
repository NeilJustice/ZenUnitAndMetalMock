#pragma once
#include "ZenUnit/ZenMock/9/NineArgumentMocker.h"
#include "ZenUnit/ZenMock/Mock.h"

// Virtual Functions
#define ZENMOCK_VOID9(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, ...) \
        ZENMOCK_VOID9_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, virtual,      ,        , final, __VA_ARGS__)

#define ZENMOCK_VOID9_CONST(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, ...) \
        ZENMOCK_VOID9_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, virtual, const, mutable, final, __VA_ARGS__)

// Non-Virtual Functions
#define ZENMOCK_VOID9_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, ...) \
        ZENMOCK_VOID9_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type,        ,      ,        ,         , __VA_ARGS__)

#define ZENMOCK_VOID9_CONST_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, ...) \
        ZENMOCK_VOID9_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type,        , const, mutable,         , __VA_ARGS__)

// Free Functions
#define ZENMOCK_VOID9_FREE(freeFunctionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, ...) \
   ZenMock::VoidNineArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type> freeFunctionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidNineArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#freeFunctionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type")"));

// Static and Namespaced Functions
#define ZENMOCK_VOID9_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, ...) \
   ZenMock::VoidNineArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidNineArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type")"));

// Implementation
#define ZENMOCK_VOID9_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, virtualness, constness, mutableness, finalness, ...) \
void functionName(arg1Type argument1, arg2Type argument2, arg3Type argument3, arg4Type argument4, arg5Type argument5, arg6Type argument6, arg7Type argument7, arg8Type argument8, arg9Type argument9) constness finalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(argument1, argument2, argument3, argument4, argument5, argument6, argument7, argument8, argument9); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::ZenMockVoidNineArgs<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::ZenMockVoidNineArgs<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
   class VoidNineArgumentMocker : public NineArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ExceptionThrower>
   {
   public:
      explicit VoidNineArgumentMocker(const std::string& zenMockedFunctionSignature)
         : NineArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>(zenMockedFunctionSignature)
      {
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
   class VoidNineArgFunctionPointerMocker : public VoidNineArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>
   {
   public:
      explicit VoidNineArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : VoidNineArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidNineArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>* functionMocker,
         Arg1Type argument1, Arg2Type argument2, Arg3Type argument3, Arg4Type argument4, Arg5Type argument5, Arg6Type argument6, Arg7Type argument7, Arg8Type argument8, Arg9Type argument9)
      {
         functionMocker->ZenMock(argument1, argument2, argument3, argument4, argument5, argument6, argument7, argument8, argument9);
      }
   };
}
