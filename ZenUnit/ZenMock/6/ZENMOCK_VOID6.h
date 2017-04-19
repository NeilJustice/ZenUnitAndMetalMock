#pragma once
#include "ZenUnit/ZenMock/6/SixArgMocker.h"
#include "ZenUnit/ZenMock/Mock.h"

// Virtual Functions
#define ZENMOCK_VOID6(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
        ZENMOCK_VOID6_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, virtual,      ,        , final, __VA_ARGS__)

#define ZENMOCK_VOID6_CONST(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
        ZENMOCK_VOID6_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, virtual, const, mutable, final, __VA_ARGS__)

// Non-Virtual Functions
#define ZENMOCK_VOID6_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
        ZENMOCK_VOID6_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type,        ,      ,        ,         , __VA_ARGS__)

#define ZENMOCK_VOID6_CONST_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
        ZENMOCK_VOID6_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type,        , const, mutable,         , __VA_ARGS__)

// Global Functions
#define ZENMOCK_VOID6_GLOBAL(globalFunctionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
   ZenMock::VoidSixArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type> globalFunctionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidSixArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#globalFunctionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type")"));

// Static and Namespaced Functions
#define ZENMOCK_VOID6_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
   ZenMock::VoidSixArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidSixArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type")"));

// Implementation
#define ZENMOCK_VOID6_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, virtualness, constness, mutableness, finalness, ...) \
void functionName(arg1Type arg1, arg2Type arg2, arg3Type arg3, arg4Type arg4, arg5Type arg5, arg6Type arg6) constness finalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(arg1, arg2, arg3, arg4, arg5, arg6); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::ZenMockVoidSixArgs<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::ZenMockVoidSixArgs<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   class VoidSixArgMocker : public SixArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>
   {
   public:
      explicit VoidSixArgMocker(const std::string& zenMockedFunctionSignature)
         : SixArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>(zenMockedFunctionSignature)
      {
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   class VoidSixArgFunctionPointerMocker : public VoidSixArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>
   {
   public:
      explicit VoidSixArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : VoidSixArgMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidSixArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>* functionMocker,
         Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4, Arg5Type arg5, Arg6Type arg6)
      {
         functionMocker->ZenMock(arg1, arg2, arg3, arg4, arg5, arg6);
      }
   };
}
