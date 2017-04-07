#pragma once
#include "ZenUnit/ZenMock/Mock.h"
#include "ZenUnit/ZenMock/1/OneArgMocker.h"
#include "ZenUnit/ZenMock/Signature.h"

// Virtual Functions
#define ZENMOCK_VOID1(functionName, arg1Type, ...) \
        ZENMOCK_VOID1_DEFINED(functionName, arg1Type, virtual,      ,        , override final, __VA_ARGS__)

#define ZENMOCK_VOID1_CONST(functionName, arg1Type, ...) \
        ZENMOCK_VOID1_DEFINED(functionName, arg1Type, virtual, const, mutable, override final, __VA_ARGS__)

// Non-Virtual Functions
#define ZENMOCK_VOID1_NONVIRTUAL(functionName, arg1Type, ...) \
        ZENMOCK_VOID1_DEFINED(functionName, arg1Type,        ,      ,        ,         , __VA_ARGS__)

#define ZENMOCK_VOID1_CONST_NONVIRTUAL(functionName, arg1Type, ...) \
        ZENMOCK_VOID1_DEFINED(functionName, arg1Type,        , const, mutable,         , __VA_ARGS__)

// Global Functions
#define ZENMOCK_VOID1_GLOBAL(globalFunctionName, arg1Type, ...) \
   ZenMock::VoidOneArgFunctionPointerMocker<arg1Type> globalFunctionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidOneArgFunctionPointerMocker<arg1Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#globalFunctionName"("#arg1Type")"));

// Static and Namespaced Functions
#define ZENMOCK_VOID1_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, ...) \
   ZenMock::VoidOneArgFunctionPointerMocker<arg1Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidOneArgFunctionPointerMocker<arg1Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type")"));

// Implementation
#define ZENMOCK_VOID1_DEFINED(functionName, arg1Type, virtualness, constness, mutableness, overridefinalness, ...) \
virtualness void functionName(arg1Type arg) constness overridefinalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(arg); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::VoidOneArgMocker<arg1Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidOneArgMocker<arg1Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

namespace ZenMock
{
   template<typename ArgType>
   class VoidOneArgMocker : public OneArgMocker<ArgType>
   {
   public:
      explicit VoidOneArgMocker(const std::string& zenMockedFunctionSignature)
         : OneArgMocker<ArgType>(zenMockedFunctionSignature)
      {
      }
   };

   template<typename Arg1Type>
   class VoidOneArgFunctionPointerMocker : public VoidOneArgMocker<Arg1Type>
   {
   public:
      explicit VoidOneArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : VoidOneArgMocker<Arg1Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidOneArgFunctionPointerMocker<Arg1Type>* functionMocker, Arg1Type arg1)
      {
         functionMocker->ZenMockIt(arg1);
      }
   };
}
