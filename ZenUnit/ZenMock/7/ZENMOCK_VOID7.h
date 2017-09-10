#pragma once
#include "ZenUnit/ZenMock/7/SevenArgumentMocker.h"
#include "ZenUnit/ZenMock/Mock.h"

// Virtual Functions
#define ZENMOCK_VOID7(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
        ZENMOCK_VOID7_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, virtual,      ,        , final, __VA_ARGS__)

#define ZENMOCK_VOID7_CONST(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
        ZENMOCK_VOID7_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, virtual, const, mutable, final, __VA_ARGS__)

// Non-Virtual Functions
#define ZENMOCK_VOID7_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
        ZENMOCK_VOID7_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type,        ,      ,        ,         , __VA_ARGS__)

#define ZENMOCK_VOID7_CONST_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
        ZENMOCK_VOID7_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type,        , const, mutable,         , __VA_ARGS__)

// Free Functions
#define ZENMOCK_VOID7_FREE(freeFunctionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
   ZenMock::VoidSevenArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type> freeFunctionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidSevenArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#freeFunctionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type")"));

// Static and Namespaced Functions
#define ZENMOCK_VOID7_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
   ZenMock::VoidSevenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidSevenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type")"));

// Implementation
#define ZENMOCK_VOID7_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, virtualness, constness, mutableness, finalness, ...) \
void functionName(arg1Type argument1, arg2Type argument2, arg3Type argument3, arg4Type argument4, arg5Type argument5, arg6Type argument6, arg7Type argument7) constness finalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(argument1, argument2, argument3, argument4, argument5, argument6, argument7); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::ZenMockVoidSevenArgs<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::ZenMockVoidSevenArgs<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   class VoidSevenArgumentMocker : public SevenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ExceptionThrower>
   {
   public:
      explicit VoidSevenArgumentMocker(const std::string& zenMockedFunctionSignature)
         : SevenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>(zenMockedFunctionSignature)
      {
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   class VoidSevenArgFunctionPointerMocker : public VoidSevenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>
   {
   public:
      explicit VoidSevenArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : VoidSevenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidSevenArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>* functionMocker,
         Arg1Type argument1, Arg2Type argument2, Arg3Type argument3, Arg4Type argument4, Arg5Type argument5, Arg6Type argument6, Arg7Type argument7)
      {
         functionMocker->ZenMock(argument1, argument2, argument3, argument4, argument5, argument6, argument7);
      }
   };
}
