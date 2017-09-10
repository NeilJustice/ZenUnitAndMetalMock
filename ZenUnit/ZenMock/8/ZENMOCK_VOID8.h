#pragma once
#include "ZenUnit/ZenMock/8/EightArgumentMocker.h"
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

// Free Functions
#define ZENMOCK_VOID8_FREE(freeFunctionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
   ZenMock::VoidEightArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type> freeFunctionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidEightArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#freeFunctionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type")"));

// Static and Namespaced Functions
#define ZENMOCK_VOID8_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
   ZenMock::VoidEightArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidEightArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type")"));

// Implementation
#define ZENMOCK_VOID8_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, virtualness, constness, mutableness, finalness, ...) \
void functionName(arg1Type argument1, arg2Type argument2, arg3Type argument3, arg4Type argument4, arg5Type argument5, arg6Type argument6, arg7Type argument7, arg8Type argument8) constness finalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(argument1, argument2, argument3, argument4, argument5, argument6, argument7, argument8); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::ZenMockVoidEightArgs<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::ZenMockVoidEightArgs<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
   class VoidEightArgumentMocker : public EightArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ExceptionThrower>
   {
   public:
      explicit VoidEightArgumentMocker(const std::string& zenMockedFunctionSignature)
         : EightArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>(zenMockedFunctionSignature)
      {
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
   class VoidEightArgFunctionPointerMocker : public VoidEightArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>
   {
   public:
      explicit VoidEightArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : VoidEightArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidEightArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>* functionMocker,
         Arg1Type argument1, Arg2Type argument2, Arg3Type argument3, Arg4Type argument4, Arg5Type argument5, Arg6Type argument6, Arg7Type argument7, Arg8Type argument8)
      {
         functionMocker->ZenMock(argument1, argument2, argument3, argument4, argument5, argument6, argument7, argument8);
      }
   };
}
