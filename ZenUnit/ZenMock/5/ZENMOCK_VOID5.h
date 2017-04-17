#pragma once
#include "ZenUnit/ZenMock/5/FiveArgMocker.h"
#include "ZenUnit/ZenMock/Mock.h"

// Virtual Functions
#define ZENMOCK_VOID5(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
        ZENMOCK_VOID5_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, virtual,      ,        , override final, __VA_ARGS__)

#define ZENMOCK_VOID5_CONST(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
        ZENMOCK_VOID5_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, virtual, const, mutable, override final, __VA_ARGS__)

// Non-Virtual Functions
#define ZENMOCK_VOID5_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
        ZENMOCK_VOID5_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type,       ,      ,        ,          , __VA_ARGS__)

#define ZENMOCK_VOID5_CONST_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
        ZENMOCK_VOID5_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type,       , const, mutable,          , __VA_ARGS__)

// Global Functions
#define ZENMOCK_VOID5_GLOBAL(globalFunctionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
   ZenMock::VoidFiveArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type> globalFunctionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidFiveArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#globalFunctionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type")"));

// Static and Namespaced Functions
#define ZENMOCK_VOID5_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
   ZenMock::VoidFiveArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidFiveArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type")"));

// Implementation
#define ZENMOCK_VOID5_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, virtualness, constness, mutableness, overridefinalness, ...) \
virtualness void functionName(arg1Type arg1, arg2Type arg2, arg3Type arg3, arg4Type arg4, arg5Type arg5) constness overridefinalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(arg1, arg2, arg3, arg4, arg5); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::VoidFiveArgMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidFiveArgMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   class VoidFiveArgMocker : public FiveArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>
   {
   public:
      explicit VoidFiveArgMocker(const std::string& zenMockedFunctionSignature)
         : FiveArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>(zenMockedFunctionSignature)
      {
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   class VoidFiveArgFunctionPointerMocker : public VoidFiveArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>
   {
   public:
      explicit VoidFiveArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : VoidFiveArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidFiveArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>* functionMocker,
         Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4, Arg5Type arg5)
      {
         functionMocker->ZenMock(arg1, arg2, arg3, arg4, arg5);
      }
   };
}
