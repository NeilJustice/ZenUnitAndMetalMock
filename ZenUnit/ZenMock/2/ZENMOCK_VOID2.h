#pragma once
#include "ZenUnit/ZenMock/2/TwoArgMocker.h"
#include "ZenUnit/ZenMock/Mock.h"

// Virtual Functions
#define ZENMOCK_VOID2(functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_VOID2_DEFINED(functionName, arg1Type, arg2Type, virtual,      ,        , override final, __VA_ARGS__)

#define ZENMOCK_VOID2_CONST(functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_VOID2_DEFINED(functionName, arg1Type, arg2Type, virtual, const, mutable, override final, __VA_ARGS__)

// Non-Virtual Functions
#define ZENMOCK_VOID2_NONVIRTUAL(functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_VOID2_DEFINED(functionName, arg1Type, arg2Type,        ,      ,        ,         , __VA_ARGS__)

#define ZENMOCK_VOID2_CONST_NONVIRTUAL(functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_VOID2_DEFINED(functionName, arg1Type, arg2Type,        , const, mutable,         , __VA_ARGS__)

// Global Functions
#define ZENMOCK_VOID2_GLOBAL(globalFunctionName, arg1Type, arg2Type, ...) \
   ZenMock::VoidTwoArgFunctionPointerMocker<arg1Type, arg2Type> globalFunctionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidTwoArgFunctionPointerMocker<arg1Type, arg2Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#globalFunctionName"("#arg1Type", "#arg2Type")"));

// Static and Namespaced Functions
#define ZENMOCK_VOID2_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, ...) \
   ZenMock::VoidTwoArgFunctionPointerMocker<arg1Type, arg2Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidTwoArgFunctionPointerMocker<arg1Type, arg2Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type")"));

// Implementation
#define ZENMOCK_VOID2_DEFINED(functionName, arg1Type, arg2Type, virtualness, constness, mutableness, overridefinalness, ...) \
virtualness void functionName(arg1Type arg1, arg2Type arg2) constness overridefinalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(arg1, arg2); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::VoidTwoArgMocker<arg1Type, arg2Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidTwoArgMocker<arg1Type, arg2Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type", "#arg2Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type>
   class VoidTwoArgMocker : public TwoArgMocker<Arg1Type, Arg2Type>
   {
   public:
      explicit VoidTwoArgMocker(const std::string& zenMockedFunctionSignature)
         : TwoArgMocker<Arg1Type, Arg2Type>(zenMockedFunctionSignature)
      {
      }

      void Expect()
      {
         TwoArgMocker<Arg1Type, Arg2Type>::Expect();
      }
   };

   template<typename Arg1Type, typename Arg2Type>
   class VoidTwoArgFunctionPointerMocker : public VoidTwoArgMocker<Arg1Type, Arg2Type>
   {
   public:
      explicit VoidTwoArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : VoidTwoArgMocker<Arg1Type, Arg2Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidTwoArgFunctionPointerMocker<Arg1Type, Arg2Type>* functionMocker,
         Arg1Type arg1, Arg2Type arg2)
      {
         functionMocker->ZenMock(arg1, arg2);
      }
   };
}
