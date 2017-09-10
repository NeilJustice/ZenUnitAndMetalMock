#pragma once
#include "ZenUnit/ZenMock/5/FiveArgumentMocker.h"
#include "ZenUnit/ZenMock/Mock.h"

// Virtual Functions
#define ZENMOCK_VOID5(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
        ZENMOCK_VOID5_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, virtual,      ,        , final, __VA_ARGS__)

#define ZENMOCK_VOID5_CONST(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
        ZENMOCK_VOID5_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, virtual, const, mutable, final, __VA_ARGS__)

// Non-Virtual Functions
#define ZENMOCK_VOID5_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
        ZENMOCK_VOID5_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type,       ,      ,        ,          , __VA_ARGS__)

#define ZENMOCK_VOID5_CONST_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
        ZENMOCK_VOID5_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type,       , const, mutable,          , __VA_ARGS__)

// Free Functions
#define ZENMOCK_VOID5_FREE(freeFunctionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
   ZenMock::VoidFiveArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type> freeFunctionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidFiveArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#freeFunctionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type")"));

// Static and Namespaced Functions
#define ZENMOCK_VOID5_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
   ZenMock::VoidFiveArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidFiveArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type")"));

// Implementation
#define ZENMOCK_VOID5_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, virtualness, constness, mutableness, finalness, ...) \
void functionName(arg1Type argument1, arg2Type argument2, arg3Type argument3, arg4Type argument4, arg5Type argument5) constness finalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(argument1, argument2, argument3, argument4, argument5); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::VoidFiveArgumentMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidFiveArgumentMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   class VoidFiveArgumentMocker : public FiveArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>
   {
   public:
      explicit VoidFiveArgumentMocker(const std::string& zenMockedFunctionSignature)
         : FiveArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>(zenMockedFunctionSignature)
      {
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   class VoidFiveArgFunctionPointerMocker : public VoidFiveArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>
   {
   public:
      explicit VoidFiveArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : VoidFiveArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidFiveArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>* functionMocker,
         Arg1Type argument1, Arg2Type argument2, Arg3Type argument3, Arg4Type argument4, Arg5Type argument5)
      {
         functionMocker->ZenMock(argument1, argument2, argument3, argument4, argument5);
      }
   };
}
