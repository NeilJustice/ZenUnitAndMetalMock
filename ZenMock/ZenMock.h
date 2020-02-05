// C++ Mocking Framework ZenMock 0.5.0
// https://github.com/NeilJustice/ZenUnitAndZenMock
// MIT License

#pragma once
#include "ZenUnit.h"
#include <atomic>
#include <deque>

namespace Zen
{
   template<typename ZenMockedClass>
   class Mock : public ZenMockedClass
   {
   public:
      template<typename... ArgTypes>
      explicit Mock(ArgTypes&&... args)
         : ZenMockedClass(std::forward<ArgTypes>(args)...)
      {
      }

      static const std::string* ZenMockedClassName()
      {
         const std::string* const zenMockedClassName = ZenUnit::Type::GetName<ZenMockedClass>();
         return zenMockedClassName;
      }
   };
}

#define ZENMOCK(ZenMockAssertStatement) \
try \
{ \
   (ZenMockAssertStatement); \
} \
catch (const ZenUnit::Anomaly& zenMockWrappedAnomaly) \
{ \
   throw ZenUnit::Anomaly::ZENMOCKWrapped("ZENMOCK("#ZenMockAssertStatement")", zenMockWrappedAnomaly, FILELINE); \
}

// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a base class function with signature "virtual void VirtualFunctionName()".
#define ZENMOCK_VOID0(VirtualFunctionName) \
        ZENMOCK_VOID0_DEFINED(VirtualFunctionName, virtual,      ,        , final)

// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a base class function with signature "virtual void VirtualFunctionName() const".
#define ZENMOCK_VOID0_CONST(VirtualFunctionName) \
        ZENMOCK_VOID0_DEFINED(VirtualFunctionName, virtual, const, mutable, final)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a base class function with signature "void NonVirtualFunctionName()".
#define ZENMOCK_VOID0_NONVIRTUAL(NonVirtualFunctionName) \
        ZENMOCK_VOID0_DEFINED(NonVirtualFunctionName,        ,        ,      ,         )

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a base class function with signature "void NonVirtualFunctionName() const".
#define ZENMOCK_VOID0_NONVIRTUAL_CONST(NonVirtualFunctionName) \
        ZENMOCK_VOID0_DEFINED(NonVirtualFunctionName,        , const, mutable,         )

// Defines a ZenMock object named <StaticFunctionName>Mock for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName()".
#define ZENMOCK_VOID0_STATIC(NamespaceQualifiedClassName, StaticFunctionName, ...) \
   ZenMock::VoidZeroArgFunctionPointerZenMocker StaticFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::VoidZeroArgFunctionPointerZenMocker( \
         ZenMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"()"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>Mock for mocking a namespaced free function with signature "void Namespace::NamespacedFreeFunctionName()".
#define ZENMOCK_VOID0_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, ...) \
   ZENMOCK_VOID0_STATIC(Namespace, FreeFunctionName, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "void ::FreeFunctionName()".
#define ZENMOCK_VOID0_FREE(GlobalFreeFunctionName) \
   ZenMock::VoidZeroArgFunctionPointerZenMocker GlobalFreeFunctionName##Mock = \
      ZenMock::VoidZeroArgFunctionPointerZenMocker(ZenMock::FunctionSignature::FunctionPointer("void", "::"#GlobalFreeFunctionName"()"));

#define ZENMOCK_VOID0_DEFINED(FunctionName, Virtualness, Constness, Mutableness, Finalness) \
struct ZenMock_##FunctionName : public ZenMock::VoidZeroArgumentZenMocker \
{ \
   explicit ZenMock_##FunctionName(const std::string* zenMockedClassName) \
      : ZenMock::VoidZeroArgumentZenMocker(ZenMock::FunctionSignature::Function( \
         #Virtualness, "void", zenMockedClassName, #FunctionName"()", #Constness)) {} \
} Mutableness FunctionName##Mock = ZenMock_##FunctionName(this->ZenMockedClassName()); \
void FunctionName() Constness Finalness \
{ \
   FunctionName##Mock.ZenMockIt(); \
}

// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName()".
#define ZENMOCK_NONVOID0(ReturnType, FunctionName) \
        ZENMOCK_NONVOID0_DEFINED(ReturnType, FunctionName, virtual,      ,        , final)

// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type)".
#define ZENMOCK_NONVOID1(ReturnType, FunctionName, Arg1Type, ...) \
        ZENMOCK_NONVOID1_DEFINED(ReturnType, FunctionName, Arg1Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName() const".
#define ZENMOCK_NONVOID0_CONST(ReturnType, FunctionName) \
        ZENMOCK_NONVOID0_DEFINED(ReturnType, FunctionName, virtual, const, mutable, final)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName()".
#define ZENMOCK_NONVOID0_NONVIRTUAL(ReturnType, FunctionName) \
        ZENMOCK_NONVOID0_DEFINED(ReturnType, FunctionName,        ,      ,        ,         )

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName() const".
#define ZENMOCK_NONVOID0_NONVIRTUAL_CONST(ReturnType, FunctionName) \
        ZENMOCK_NONVOID0_DEFINED(ReturnType, FunctionName,        , const, mutable,         )

// Defines a ZenMock object named <StaticFunctionName>Mock for mocking a static function with signature "ReturnType NamespaceQualifiedClassName::StaticFunctionName()".
#define ZENMOCK_NONVOID0_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, ...) \
   ZenMock::NonVoidZeroArgFunctionPointerZenMocker<ReturnType> StaticFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::NonVoidZeroArgFunctionPointerZenMocker<ReturnType>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"()"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>Mock for mocking a namespaced free function with signature "ReturnType Namespace::NamespacedFreeFunctionName()".
#define ZENMOCK_NONVOID0_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFreeFunctionName, ...) \
   ZENMOCK_NONVOID0_STATIC(ReturnType, Namespace, NamespacedFreeFunctionName, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName()".
#define ZENMOCK_NONVOID0_FREE(ReturnType, GlobalFreeFunctionName) \
   ZenMock::NonVoidZeroArgFunctionPointerZenMocker<ReturnType> GlobalFreeFunctionName##Mock = \
      ZenMock::NonVoidZeroArgFunctionPointerZenMocker<ReturnType>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, "::"#GlobalFreeFunctionName"()"));

#define ZENMOCK_NONVOID0_DEFINED(ReturnType, FunctionName, Virtualness, Constness, Mutableness, Finalness) \
struct ZenMock_##FunctionName : public ZenMock::NonVoidZeroArgumentZenMocker<ReturnType> \
{ \
   explicit ZenMock_##FunctionName(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidZeroArgumentZenMocker<ReturnType>(ZenMock::FunctionSignature::Function( \
         #Virtualness, #ReturnType, zenMockedClassName, #FunctionName"()", #Constness)) {} \
} Mutableness FunctionName##Mock = ZenMock_##FunctionName(this->ZenMockedClassName()); \
ReturnType FunctionName() Constness Finalness \
{ \
   return FunctionName##Mock.ZenMockItAndReturnValue(); \
}


// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type) const".
#define ZENMOCK_NONVOID1_CONST(ReturnType, FunctionName, Arg1Type, ...) \
        ZENMOCK_NONVOID1_DEFINED(ReturnType, FunctionName, Arg1Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type)".
#define ZENMOCK_NONVOID1_NONVIRTUAL(ReturnType, FunctionName, Arg1Type, ...) \
        ZENMOCK_NONVOID1_DEFINED(ReturnType, FunctionName, Arg1Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type) const".
#define ZENMOCK_NONVOID1_NONVIRTUAL_CONST(ReturnType, FunctionName, Arg1Type, ...) \
        ZENMOCK_NONVOID1_DEFINED(ReturnType, FunctionName, Arg1Type,        , const, mutable,         , __VA_ARGS__)

// Defines a ZenMock object named <StaticFunctionName>Mock for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type)".
#define ZENMOCK_NONVOID1_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, ...) \
   ZenMock::NonVoidOneArgFunctionPointerZenMocker<ReturnType, Arg1Type> \
      StaticFunctionName##Mock##__VA_ARGS__ = ZenMock::NonVoidOneArgFunctionPointerZenMocker<ReturnType, Arg1Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>Mock for mocking a namespaced free function with signature "ReturnType Namespace::NamespacedFreeFunctionName(Arg1Type)".
#define ZENMOCK_NONVOID1_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, ...) \
   ZENMOCK_NONVOID1_STATIC(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type)".
#define ZENMOCK_NONVOID1_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, ...) \
   ZenMock::NonVoidOneArgFunctionPointerZenMocker<ReturnType, Arg1Type> \
      GlobalFreeFunctionName##Mock##__VA_ARGS__ = ZenMock::NonVoidOneArgFunctionPointerZenMocker<ReturnType, Arg1Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, "::"#GlobalFreeFunctionName"("#Arg1Type")"));

#define ZENMOCK_NONVOID1_DEFINED(ReturnType, FunctionName, Arg1Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::NonVoidOneArgumentZenMocker<ReturnType, Arg1Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidOneArgumentZenMocker<ReturnType, Arg1Type>(ZenMock::FunctionSignature::Function( \
         #Virtualness, #ReturnType, zenMockedClassName, #FunctionName"("#Arg1Type")", #Constness)) {} \
} Mutableness FunctionName##Mock##__VA_ARGS__ = ZenMock_##FunctionName##__VA_ARGS__(this->ZenMockedClassName()); \
ReturnType FunctionName(Arg1Type arg) Constness Finalness \
{ \
   return FunctionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(arg); \
}


// Defines a ZenMock object named <FunctionName>Mock for mocking a base class function with signature "virtual void FunctionName(Arg1Type)".
#define ZENMOCK_VOID1(FunctionName, Arg1Type, ...) \
        ZENMOCK_VOID1_DEFINED(FunctionName, Arg1Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a ZenMock object named <FunctionName>Mock for mocking a base class function with signature "virtual void FunctionName(Arg1Type) const".
#define ZENMOCK_VOID1_CONST(FunctionName, Arg1Type, ...) \
        ZENMOCK_VOID1_DEFINED(FunctionName, Arg1Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a ZenMock object named <FunctionName>Mock for mocking a base class function with signature "void FunctionName(Arg1Type)".
#define ZENMOCK_VOID1_NONVIRTUAL(FunctionName, Arg1Type, ...) \
        ZENMOCK_VOID1_DEFINED(FunctionName, Arg1Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a ZenMock object named <FunctionName>Mock for mocking a base class function with signature "void FunctionName(Arg1Type) const".
#define ZENMOCK_VOID1_NONVIRTUAL_CONST(FunctionName, Arg1Type, ...) \
        ZENMOCK_VOID1_DEFINED(FunctionName, Arg1Type,        , const, mutable,         , __VA_ARGS__)

// Defines a ZenMock object named <StaticFunctionName>Mock for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName(Arg1Type)".
#define ZENMOCK_VOID1_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, ...) \
   ZenMock::VoidOneArgFunctionPointerZenMocker<Arg1Type> StaticFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::VoidOneArgFunctionPointerZenMocker<Arg1Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>Mock for mocking a namespaced free function with signature "void Namespace::NamespacedFreeFunctionName(Arg1Type)".
#define ZENMOCK_VOID1_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, ...) \
   ZENMOCK_VOID1_STATIC(NamespaceQualifiedClassName, NamespacedFreeFunctionName, Arg1Type, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type)".
#define ZENMOCK_VOID1_FREE(GlobalFreeFunctionName, Arg1Type, ...) \
   ZenMock::VoidOneArgFunctionPointerZenMocker<Arg1Type> GlobalFreeFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::VoidOneArgFunctionPointerZenMocker<Arg1Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", "::"#GlobalFreeFunctionName"("#Arg1Type")"));

#define ZENMOCK_VOID1_DEFINED(FunctionName, Arg1Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::VoidOneArgumentZenMocker<Arg1Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidOneArgumentZenMocker<Arg1Type>(ZenMock::FunctionSignature::Function( \
         #Virtualness, "void", zenMockedClassName, #FunctionName"("#Arg1Type")", #Constness)) {} \
} Mutableness FunctionName##Mock##__VA_ARGS__ = ZenMock_##FunctionName##__VA_ARGS__(this->ZenMockedClassName()); \
void FunctionName(Arg1Type arg) Constness Finalness \
{ \
   FunctionName##Mock##__VA_ARGS__.ZenMockIt(arg); \
}


// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type)".
#define ZENMOCK_NONVOID2(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, ...) \
        ZENMOCK_NONVOID2_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type) const".
#define ZENMOCK_NONVOID2_CONST(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, ...) \
        ZENMOCK_NONVOID2_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type)".
#define ZENMOCK_NONVOID2_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, ...) \
        ZENMOCK_NONVOID2_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type) const".
#define ZENMOCK_NONVOID2_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, ...) \
        ZENMOCK_NONVOID2_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type,        , const, mutable,         , __VA_ARGS__)

// Defines a ZenMock object named <StaticFunctionName>Mock for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type)".
#define ZENMOCK_NONVOID2_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, ...) \
   ZenMock::NonVoidTwoArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type> StaticFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::NonVoidTwoArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>Mock for mocking a namespaced free function with signature "ReturnType Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type)".
#define ZENMOCK_NONVOID2_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, ...) \
   ZENMOCK_NONVOID2_STATIC(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type, Arg2Type)".
#define ZENMOCK_NONVOID2_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, ...) \
   ZenMock::NonVoidTwoArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type> GlobalFreeFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::NonVoidTwoArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type")"));

#define ZENMOCK_NONVOID2_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::NonVoidTwoArgumentZenMocker<ReturnType, Arg1Type, Arg2Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidTwoArgumentZenMocker<ReturnType, Arg1Type, Arg2Type>(ZenMock::FunctionSignature::Function( \
         #Virtualness, #ReturnType, zenMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type")", #Constness)) {} \
} Mutableness FunctionName##Mock##__VA_ARGS__ = ZenMock_##FunctionName##__VA_ARGS__(this->ZenMockedClassName()); \
ReturnType FunctionName(Arg1Type firstArgument, Arg2Type secondArgument) Constness Finalness \
{ \
   return FunctionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(firstArgument, secondArgument); \
}


// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type)".
#define ZENMOCK_VOID2(VirtualFunctionName, Arg1Type, Arg2Type, ...) \
        ZENMOCK_VOID2_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type) const".
#define ZENMOCK_VOID2_CONST(VirtualFunctionName, Arg1Type, Arg2Type, ...) \
        ZENMOCK_VOID2_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type)".
#define ZENMOCK_VOID2_NONVIRTUAL(NonVirtualFunctionName, Arg1Type, Arg2Type, ...) \
        ZENMOCK_VOID2_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type) const".
#define ZENMOCK_VOID2_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type, Arg2Type, ...) \
        ZENMOCK_VOID2_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type,        , const, mutable,         , __VA_ARGS__)

// Defines a ZenMock object named <FunctionName>Mock for mocking a static function with signature "void QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type)".
#define ZENMOCK_VOID2_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, ...) \
   ZenMock::VoidTwoArgFunctionPointerZenMocker<Arg1Type, Arg2Type> StaticFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::VoidTwoArgFunctionPointerZenMocker<Arg1Type, Arg2Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>Mock for mocking a namespaced free function with signature "void Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type)".
#define ZENMOCK_VOID2_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, ...) \
   ZENMOCK_VOID2_STATIC(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type, Arg2Type)".
#define ZENMOCK_VOID2_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, ...) \
   ZenMock::VoidTwoArgFunctionPointerZenMocker<Arg1Type, Arg2Type> GlobalFreeFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::VoidTwoArgFunctionPointerZenMocker<Arg1Type, Arg2Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type")"));

#define ZENMOCK_VOID2_DEFINED(FunctionName, Arg1Type, Arg2Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::VoidTwoArgumentZenMocker<Arg1Type, Arg2Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidTwoArgumentZenMocker<Arg1Type, Arg2Type>(ZenMock::FunctionSignature::Function( \
         #Virtualness, "void", zenMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type")", #Constness)) {} \
} Mutableness FunctionName##Mock##__VA_ARGS__ = ZenMock_##FunctionName##__VA_ARGS__(this->ZenMockedClassName()); \
void FunctionName(Arg1Type firstArgument, Arg2Type secondArgument) Constness Finalness \
{ \
   FunctionName##Mock##__VA_ARGS__.ZenMockIt(firstArgument, secondArgument); \
}


// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type)".
#define ZENMOCK_NONVOID3(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, ...) \
        ZENMOCK_NONVOID3_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type) const".
#define ZENMOCK_NONVOID3_CONST(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, ...) \
        ZENMOCK_NONVOID3_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type)".
#define ZENMOCK_NONVOID3_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, ...) \
        ZENMOCK_NONVOID3_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type) const".
#define ZENMOCK_NONVOID3_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, ...) \
        ZENMOCK_NONVOID3_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type,        , const, mutable,         , __VA_ARGS__)

// Defines a ZenMock object named <StaticFunctionName>Mock for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type)".
#define ZENMOCK_NONVOID3_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, ...) \
   ZenMock::NonVoidThreeArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type> StaticFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::NonVoidThreeArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>Mock for mocking a static function with signature "ReturnType Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type, Arg3Type)".
#define ZENMOCK_NONVOID3_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, ...) \
   ZENMOCK_NONVOID3_STATIC(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type)

// Defines a ZenMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type)".
#define ZENMOCK_NONVOID3_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, ...) \
   ZenMock::NonVoidThreeArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type> GlobalFreeFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::NonVoidThreeArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type")"));

#define ZENMOCK_NONVOID3_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Arg3Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::NonVoidThreeArgumentZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidThreeArgumentZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type>(ZenMock::FunctionSignature::Function( \
         #Virtualness, #ReturnType, zenMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type")", #Constness)) {} \
} Mutableness FunctionName##Mock##__VA_ARGS__ = ZenMock_##FunctionName##__VA_ARGS__(this->ZenMockedClassName()); \
ReturnType FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument) Constness Finalness \
{ \
   return FunctionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument); \
}


// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type)".
#define ZENMOCK_VOID3(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, ...) \
        ZENMOCK_VOID3_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type) const".
#define ZENMOCK_VOID3_CONST(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, ...) \
        ZENMOCK_VOID3_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type)".
#define ZENMOCK_VOID3_NONVIRTUAL(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, ...) \
        ZENMOCK_VOID3_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type) const".
#define ZENMOCK_VOID3_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, ...) \
        ZENMOCK_VOID3_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type,        , const, mutable,         , __VA_ARGS__)

// Defines a ZenMock object named <StaticFunctionName>Mock for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type)".
#define ZENMOCK_VOID3_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, ...) \
   ZenMock::VoidThreeArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type> StaticFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::VoidThreeArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>Mock for mocking a static function with signature "void Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type, Arg3Type)".
#define ZENMOCK_VOID3_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, ...) \
   ZENMOCK_VOID3_STATIC(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type)".
#define ZENMOCK_VOID3_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, ...) \
   ZenMock::VoidThreeArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type> GlobalFreeFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::VoidThreeArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type")"));

#define ZENMOCK_VOID3_DEFINED(FunctionName, Arg1Type, Arg2Type, Arg3Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::VoidThreeArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidThreeArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type>(ZenMock::FunctionSignature::Function( \
         #Virtualness, "void", zenMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type")", #Constness)) {} \
} Mutableness FunctionName##Mock##__VA_ARGS__ = ZenMock_##FunctionName##__VA_ARGS__(this->ZenMockedClassName()); \
void FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument) Constness Finalness \
{ \
   FunctionName##Mock##__VA_ARGS__.ZenMockIt(firstArgument, secondArgument, thirdArgument); \
}


// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type)".
#define ZENMOCK_NONVOID4(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...) \
        ZENMOCK_NONVOID4_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type) const".
#define ZENMOCK_NONVOID4_CONST(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...) \
        ZENMOCK_NONVOID4_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type)".
#define ZENMOCK_NONVOID4_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...) \
        ZENMOCK_NONVOID4_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type) const".
#define ZENMOCK_NONVOID4_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...) \
        ZENMOCK_NONVOID4_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type,        , const, mutable,         , __VA_ARGS__)

// Defines a ZenMock object named <StaticFunctionName>Mock for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type)".
#define ZENMOCK_NONVOID4_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...) \
   ZenMock::NonVoidFourArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type> StaticFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::NonVoidFourArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type")"));

// Defines a ZenMock object named <NamespaceFreeFunctionName>Mock for mocking a static function with signature "ReturnType Namespace::NamespaceFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type)".
#define ZENMOCK_NONVOID4_NAMESPACED_FREE(ReturnType, Namespace, NamespaceFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...) \
   ZENMOCK_NONVOID4_STATIC(ReturnType, Namespace, NamespaceFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type)".
#define ZENMOCK_NONVOID4_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...) \
   ZenMock::NonVoidFourArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type> GlobalFreeFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::NonVoidFourArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type")"));

#define ZENMOCK_NONVOID4_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::NonVoidFourArgumentZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidFourArgumentZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>(ZenMock::FunctionSignature::Function( \
         #Virtualness, #ReturnType, zenMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type")", #Constness)) {} \
} Mutableness FunctionName##Mock##__VA_ARGS__ = ZenMock_##FunctionName##__VA_ARGS__(this->ZenMockedClassName()); \
ReturnType FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument) Constness Finalness \
{ \
   return FunctionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument); \
}


// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type)".
#define ZENMOCK_VOID4(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...) \
        ZENMOCK_VOID4_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type) const".
#define ZENMOCK_VOID4_CONST(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...) \
        ZENMOCK_VOID4_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type)".
#define ZENMOCK_VOID4_NONVIRTUAL(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...) \
        ZENMOCK_VOID4_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type) const".
#define ZENMOCK_VOID4_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...) \
        ZENMOCK_VOID4_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type,        , const, mutable,         , __VA_ARGS__)

// Defines a ZenMock object named <StaticFunctionName>Mock for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type)".
#define ZENMOCK_VOID4_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...) \
   ZenMock::VoidFourArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type> StaticFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::VoidFourArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>Mock for mocking a namespaced free function with signature "void Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type)".
#define ZENMOCK_VOID4_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...) \
   ZENMOCK_VOID4_STATIC(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type)".
#define ZENMOCK_VOID4_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...) \
   ZenMock::VoidFourArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type> GlobalFreeFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::VoidFourArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type")"));

#define ZENMOCK_VOID4_DEFINED(FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::VoidFourArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidFourArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>(ZenMock::FunctionSignature::Function( \
         #Virtualness, "void", zenMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type")", #Constness)) {} \
} Mutableness FunctionName##Mock##__VA_ARGS__ = ZenMock_##FunctionName##__VA_ARGS__(this->ZenMockedClassName()); \
void FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument) Constness Finalness \
{ \
   FunctionName##Mock##__VA_ARGS__.ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument); \
}


// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)".
#define ZENMOCK_NONVOID5(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...) \
        ZENMOCK_NONVOID5_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type) const".
#define ZENMOCK_NONVOID5_CONST(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...) \
        ZENMOCK_NONVOID5_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)".
#define ZENMOCK_NONVOID5_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...) \
        ZENMOCK_NONVOID5_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type) const".
#define ZENMOCK_NONVOID5_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...) \
        ZENMOCK_NONVOID5_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type,        , const, mutable,         , __VA_ARGS__)

// Defines a ZenMock object named <StaticFunctionName>Mock for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)".
#define ZENMOCK_NONVOID5_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...) \
   ZenMock::NonVoidFiveArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type> StaticFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::NonVoidFiveArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>Mock for mocking a namespaced free function with signature "ReturnType Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)".
#define ZENMOCK_NONVOID5_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...) \
   ZENMOCK_NONVOID5_STATIC(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)".
#define ZENMOCK_NONVOID5_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...) \
   ZenMock::NonVoidFiveArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type> GlobalFreeFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::NonVoidFiveArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type")"));

#define ZENMOCK_NONVOID5_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::NonVoidFiveArgumentZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidFiveArgumentZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>(ZenMock::FunctionSignature::Function( \
         #Virtualness, #ReturnType, zenMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type")", #Constness)) {} \
} Mutableness FunctionName##Mock##__VA_ARGS__ = ZenMock_##FunctionName##__VA_ARGS__(this->ZenMockedClassName()); \
ReturnType FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument) Constness Finalness \
{ \
   return FunctionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument); \
}


// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)".
#define ZENMOCK_VOID5(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...) \
        ZENMOCK_VOID5_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type) const".
#define ZENMOCK_VOID5_CONST(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...) \
        ZENMOCK_VOID5_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)".
#define ZENMOCK_VOID5_NONVIRTUAL(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...) \
        ZENMOCK_VOID5_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type,       ,      ,        ,          , __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type) const".
#define ZENMOCK_VOID5_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...) \
        ZENMOCK_VOID5_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type,       , const, mutable,          , __VA_ARGS__)

// Defines a ZenMock object named <StaticFunctionName>Mock for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)".
#define ZENMOCK_VOID5_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...) \
   ZenMock::VoidFiveArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type> StaticFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::VoidFiveArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>Mock for mocking a namespaced free function with signature "void Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)".
#define ZENMOCK_VOID5_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...) \
   ZENMOCK_VOID5_STATIC(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)".
#define ZENMOCK_VOID5_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...) \
   ZenMock::VoidFiveArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type> GlobalFreeFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::VoidFiveArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type")"));

#define ZENMOCK_VOID5_DEFINED(FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::VoidFiveArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidFiveArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>(ZenMock::FunctionSignature::Function( \
         #Virtualness, "void", zenMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type")", #Constness)) {} \
} Mutableness FunctionName##Mock##__VA_ARGS__ = ZenMock_##FunctionName##__VA_ARGS__(this->ZenMockedClassName()); \
void FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument) Constness Finalness \
{ \
   FunctionName##Mock##__VA_ARGS__.ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument); \
}


// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)".
#define ZENMOCK_NONVOID6(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...) \
        ZENMOCK_NONVOID6_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type) const".
#define ZENMOCK_NONVOID6_CONST(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...) \
        ZENMOCK_NONVOID6_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)".
#define ZENMOCK_NONVOID6_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...) \
        ZENMOCK_NONVOID6_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type) const".
#define ZENMOCK_NONVOID6_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...) \
        ZENMOCK_NONVOID6_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type,        , const, mutable,         , __VA_ARGS__)

// Defines a ZenMock object named <StaticFunctionName>Mock for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)".
#define ZENMOCK_NONVOID6_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...) \
   ZenMock::NonVoidSixArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type> StaticFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::NonVoidSixArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>Mock for mocking a namespaced free function with signature "ReturnType Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)".
#define ZENMOCK_NONVOID6_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...) \
   ZENMOCK_NONVOID6_STATIC(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)".
#define ZENMOCK_NONVOID6_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...) \
   ZenMock::NonVoidSixArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type> GlobalFreeFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::NonVoidSixArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type")"));

#define ZENMOCK_NONVOID6_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::NonVoidSixArgumentZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidSixArgumentZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>(ZenMock::FunctionSignature::Function( \
         #Virtualness, #ReturnType, zenMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type")", #Constness)) {} \
} Mutableness FunctionName##Mock##__VA_ARGS__ = ZenMock_##FunctionName##__VA_ARGS__(this->ZenMockedClassName()); \
ReturnType FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument) Constness Finalness \
{ \
   return FunctionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument); \
}


// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)".
#define ZENMOCK_VOID6(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...) \
        ZENMOCK_VOID6_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type) const".
#define ZENMOCK_VOID6_CONST(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...) \
        ZENMOCK_VOID6_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)".
#define ZENMOCK_VOID6_NONVIRTUAL(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...) \
        ZENMOCK_VOID6_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type) const".
#define ZENMOCK_VOID6_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...) \
        ZENMOCK_VOID6_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type,        , const, mutable,         , __VA_ARGS__)

// Defines a ZenMock object named <StaticFunctionName>Mock for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)".
#define ZENMOCK_VOID6_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...) \
   ZenMock::VoidSixArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type> StaticFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::VoidSixArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>Mock for mocking a static function with signature "void Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)".
#define ZENMOCK_VOID6_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...) \
   ZENMOCK_VOID6_STATIC(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, __VA_ARGS__) \

// Defines a ZenMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)".
#define ZENMOCK_VOID6_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...) \
   ZenMock::VoidSixArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type> GlobalFreeFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::VoidSixArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type")"));

#define ZENMOCK_VOID6_DEFINED(FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::VoidSixArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidSixArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>(ZenMock::FunctionSignature::Function( \
         #Virtualness, "void", zenMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type")", #Constness)) {} \
} Mutableness FunctionName##Mock##__VA_ARGS__ = ZenMock_##FunctionName##__VA_ARGS__(this->ZenMockedClassName()); \
void FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument) Constness Finalness \
{ \
   FunctionName##Mock##__VA_ARGS__.ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument); \
}


// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)".
#define ZENMOCK_NONVOID7(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...) \
        ZENMOCK_NONVOID7_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type) const".
#define ZENMOCK_NONVOID7_CONST(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...) \
        ZENMOCK_NONVOID7_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)".
#define ZENMOCK_NONVOID7_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...) \
        ZENMOCK_NONVOID7_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type) const".
#define ZENMOCK_NONVOID7_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...) \
        ZENMOCK_NONVOID7_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type,        , const, mutable,         , __VA_ARGS__)

// Defines a ZenMock object named <StaticFunctionName>Mock for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)".
#define ZENMOCK_NONVOID7_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...) \
   ZenMock::NonVoidSevenArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type> StaticFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::NonVoidSevenArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>Mock for mocking a namespaced free function with signature "ReturnType Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)".
#define ZENMOCK_NONVOID7_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...) \
   ZENMOCK_NONVOID7_STATIC(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)".
#define ZENMOCK_NONVOID7_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...) \
   ZenMock::NonVoidSevenArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type> GlobalFreeFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::NonVoidSevenArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type")"));

#define ZENMOCK_NONVOID7_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::NonVoidSevenArgumentZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidSevenArgumentZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>(ZenMock::FunctionSignature::Function( \
         #Virtualness, #ReturnType, zenMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type")", #Constness)) {} \
} Mutableness FunctionName##Mock##__VA_ARGS__ = ZenMock_##FunctionName##__VA_ARGS__(this->ZenMockedClassName()); \
ReturnType FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument) Constness Finalness \
{ \
   return FunctionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument); \
}


// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)".
#define ZENMOCK_VOID7(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...) \
        ZENMOCK_VOID7_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type) const".
#define ZENMOCK_VOID7_CONST(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...) \
        ZENMOCK_VOID7_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)".
#define ZENMOCK_VOID7_NONVIRTUAL(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...) \
        ZENMOCK_VOID7_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type) const".
#define ZENMOCK_VOID7_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...) \
        ZENMOCK_VOID7_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type,        , const, mutable,         , __VA_ARGS__)

// Defines a ZenMock object named <StaticFunctionName>Mock for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)".
#define ZENMOCK_VOID7_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...) \
   ZenMock::VoidSevenArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type> StaticFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::VoidSevenArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>Mock for mocking a namespaced free function with signature "void Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)".
#define ZENMOCK_VOID7_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...) \
   ZENMOCK_VOID7_STATIC(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, __VA_ARGS__) \

// Defines a ZenMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)".
#define ZENMOCK_VOID7_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...) \
   ZenMock::VoidSevenArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type> GlobalFreeFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::VoidSevenArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type")"));

#define ZENMOCK_VOID7_DEFINED(FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::VoidSevenArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidSevenArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>(ZenMock::FunctionSignature::Function( \
         #Virtualness, "void", zenMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type")", #Constness)) {} \
} Mutableness FunctionName##Mock##__VA_ARGS__ = ZenMock_##FunctionName##__VA_ARGS__(this->ZenMockedClassName()); \
void FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument) Constness Finalness \
{ \
   FunctionName##Mock##__VA_ARGS__.ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument); \
}


// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)".
#define ZENMOCK_NONVOID8(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...) \
        ZENMOCK_NONVOID8_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type) const".
#define ZENMOCK_NONVOID8_CONST(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...) \
        ZENMOCK_NONVOID8_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)".
#define ZENMOCK_NONVOID8_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...) \
        ZENMOCK_NONVOID8_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type) const".
#define ZENMOCK_NONVOID8_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...) \
        ZENMOCK_NONVOID8_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type,        , const, mutable,         , __VA_ARGS__)

// Defines a ZenMock object named <StaticFunctionName>Mock for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)".
#define ZENMOCK_NONVOID8_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...) \
   ZenMock::NonVoidEightArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type> StaticFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::NonVoidEightArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>Mock for mocking a namespaced free function with signature "ReturnType Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)".
#define ZENMOCK_NONVOID8_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...) \
   ZENMOCK_NONVOID8_STATIC(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)".
#define ZENMOCK_NONVOID8_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...) \
   ZenMock::NonVoidEightArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type> GlobalFreeFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::NonVoidEightArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type")"));

#define ZENMOCK_NONVOID8_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::NonVoidEightArgumentZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidEightArgumentZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>(ZenMock::FunctionSignature::Function( \
         #Virtualness, #ReturnType, zenMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type")", #Constness)) {} \
} Mutableness FunctionName##Mock##__VA_ARGS__ = ZenMock_##FunctionName##__VA_ARGS__(this->ZenMockedClassName()); \
ReturnType FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument) Constness Finalness \
{ \
   return FunctionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument); \
}


// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)".
#define ZENMOCK_VOID8(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...) \
        ZENMOCK_VOID8_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type) const".
#define ZENMOCK_VOID8_CONST(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...) \
        ZENMOCK_VOID8_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)".
#define ZENMOCK_VOID8_NONVIRTUAL(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...) \
        ZENMOCK_VOID8_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type) const".
#define ZENMOCK_VOID8_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...) \
        ZENMOCK_VOID8_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type,        , const, mutable,         , __VA_ARGS__)

// Defines a ZenMock object named <StaticFunctionName>Mock for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)".
#define ZENMOCK_VOID8_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...) \
   ZenMock::VoidEightArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type> StaticFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::VoidEightArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>Mock for mocking a namespaced free function with signature "void Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)".
#define ZENMOCK_VOID8_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...) \
   ZENMOCK_VOID8_STATIC(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, __VA_ARGS__) \

// Defines a ZenMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)".
#define ZENMOCK_VOID8_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...) \
   ZenMock::VoidEightArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type> GlobalFreeFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::VoidEightArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type")"));

#define ZENMOCK_VOID8_DEFINED(FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::VoidEightArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidEightArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>(ZenMock::FunctionSignature::Function( \
         #Virtualness, "void", zenMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type")", #Constness)) {} \
} Mutableness FunctionName##Mock##__VA_ARGS__ = ZenMock_##FunctionName##__VA_ARGS__(this->ZenMockedClassName()); \
void FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument) Constness Finalness \
{ \
   FunctionName##Mock##__VA_ARGS__.ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument); \
}


// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type)".
#define ZENMOCK_VOID9(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...) \
        ZENMOCK_VOID9_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type) const".
#define ZENMOCK_VOID9_CONST(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...) \
        ZENMOCK_VOID9_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type)".
#define ZENMOCK_VOID9_NONVIRTUAL(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...) \
        ZENMOCK_VOID9_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type) const".
#define ZENMOCK_VOID9_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...) \
        ZENMOCK_VOID9_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type,        , const, mutable,         , __VA_ARGS__)

// Defines a ZenMock object named <StaticFunctionName>Mock for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type)".
#define ZENMOCK_VOID9_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...) \
   ZenMock::VoidNineArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type> StaticFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::VoidNineArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>Mock for mocking a namespaced free function with signature "void Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type)".
#define ZENMOCK_VOID9_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...) \
   ZENMOCK_VOID9_STATIC(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, __VA_ARGS__) \

// Defines a ZenMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type)".
#define ZENMOCK_VOID9_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...) \
   ZenMock::VoidNineArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type> GlobalFreeFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::VoidNineArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type")"));

#define ZENMOCK_VOID9_DEFINED(FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::VoidNineArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidNineArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>(ZenMock::FunctionSignature::Function( \
         #Virtualness, "void", zenMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type")", #Constness)) {} \
} Mutableness FunctionName##Mock##__VA_ARGS__ = ZenMock_##FunctionName##__VA_ARGS__(this->ZenMockedClassName()); \
void FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument, Arg9Type ninthArgument) Constness Finalness \
{ \
   FunctionName##Mock##__VA_ARGS__.ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument); \
}


// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type)".
#define ZENMOCK_NONVOID9(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...) \
        ZENMOCK_NONVOID9_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type) const".
#define ZENMOCK_NONVOID9_CONST(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...) \
        ZENMOCK_NONVOID9_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type)".
#define ZENMOCK_NONVOID9_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...) \
        ZENMOCK_NONVOID9_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type,       ,      ,        ,         , __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type) const".
#define ZENMOCK_NONVOID9_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...) \
        ZENMOCK_NONVOID9_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type,       , const, mutable,         , __VA_ARGS__)

// Defines a ZenMock object named <StaticFunctionName>Mock for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type)".
#define ZENMOCK_NONVOID9_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...) \
   ZenMock::NonVoidNineArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type> StaticFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::NonVoidNineArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>Mock for mocking a namespaced free function with signature "ReturnType Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type)".
#define ZENMOCK_NONVOID9_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...) \
   ZENMOCK_NONVOID9_STATIC(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, __VA_ARGS__) \

// Defines a ZenMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type)".
#define ZENMOCK_NONVOID9_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...) \
   ZenMock::NonVoidNineArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type> GlobalFreeFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::NonVoidNineArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type")"));

#define ZENMOCK_NONVOID9_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::NonVoidNineArgumentZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidNineArgumentZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>(ZenMock::FunctionSignature::Function( \
         #Virtualness, #ReturnType, zenMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type")", #Constness)) {} \
} Mutableness FunctionName##Mock##__VA_ARGS__ = ZenMock_##FunctionName##__VA_ARGS__(this->ZenMockedClassName()); \
ReturnType FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument, Arg9Type ninthArgument) Constness Finalness \
{ \
   return FunctionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument); \
}


// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)".
#define ZENMOCK_VOID10(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...) \
        ZENMOCK_VOID10_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type) const".
#define ZENMOCK_VOID10_CONST(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...) \
        ZENMOCK_VOID10_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)".
#define ZENMOCK_VOID10_NONVIRTUAL(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...) \
        ZENMOCK_VOID10_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type) const".
#define ZENMOCK_VOID10_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...) \
        ZENMOCK_VOID10_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type,        , const, mutable,         , __VA_ARGS__)

// Defines a ZenMock object named <StaticFunctionName>Mock for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)".
#define ZENMOCK_VOID10_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...) \
   ZenMock::VoidTenArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type> StaticFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::VoidTenArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type", "#Arg10Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>Mock for mocking a static function with signature "void Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)".
#define ZENMOCK_VOID10_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...) \
   ZENMOCK_VOID10_STATIC(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, __VA_ARGS__) \

// Defines a ZenMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)".
#define ZENMOCK_VOID10_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...) \
   ZenMock::VoidTenArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type> GlobalFreeFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::VoidTenArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type", "#Arg10Type")"));

#define ZENMOCK_VOID10_DEFINED(FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::VoidTenArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidTenArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(ZenMock::FunctionSignature::Function( \
         #Virtualness, "void", zenMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type", "#Arg10Type")", #Constness)) {} \
} Mutableness FunctionName##Mock##__VA_ARGS__ = ZenMock_##FunctionName##__VA_ARGS__(this->ZenMockedClassName()); \
void FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument, Arg9Type ninthArgument, Arg10Type tenthArgument) Constness Finalness \
{ \
   FunctionName##Mock##__VA_ARGS__.ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument, tenthArgument); \
}


// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)".
#define ZENMOCK_NONVOID10(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...) \
        ZENMOCK_NONVOID10_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a ZenMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type) const".
#define ZENMOCK_NONVOID10_CONST(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...) \
        ZENMOCK_NONVOID10_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)".
#define ZENMOCK_NONVOID10_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...) \
        ZENMOCK_NONVOID10_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type,      ,      ,        ,         , __VA_ARGS__)

// Defines a ZenMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type) const".
#define ZENMOCK_NONVOID10_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...) \
        ZENMOCK_NONVOID10_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type,      , const, mutable,         , __VA_ARGS__)

// Defines a ZenMock object named <StaticFunctionName>Mock for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)".
#define ZENMOCK_NONVOID10_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...) \
   ZenMock::NonVoidTenArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type> StaticFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::NonVoidTenArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type", "#Arg10Type")"));

// Defines a ZenMock object named <NamespacedFunctionName>Mock for mocking a namespaced free function with signature "ReturnType Namespace::NamespacedFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)".
#define ZENMOCK_NONVOID10_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...) \
   ZENMOCK_NONVOID10_STATIC(ReturnType, Namespace, NamespacedFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)".
#define ZENMOCK_NONVOID10_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...) \
   ZenMock::NonVoidTenArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type> GlobalFreeFunctionName##Mock##__VA_ARGS__ = \
      ZenMock::NonVoidTenArgFunctionPointerZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type", "#Arg10Type")"));

#define ZENMOCK_NONVOID10_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::NonVoidTenArgumentZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidTenArgumentZenMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(ZenMock::FunctionSignature::Function( \
         #Virtualness, #ReturnType, zenMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type", "#Arg10Type")", #Constness)) {} \
} Mutableness FunctionName##Mock##__VA_ARGS__ = ZenMock_##FunctionName##__VA_ARGS__(this->ZenMockedClassName()); \
ReturnType FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument, Arg9Type ninthArgument, Arg10Type tenthArgument) Constness Finalness \
{ \
   return FunctionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument, tenthArgument); \
}


// std::binds a zero-argument ZenMock object for assignment to a std::function
#define BIND_0ARG_ZENMOCK_OBJECT(FunctionNameMock) \
   std::bind(&decltype(FunctionNameMock)::ZenMockItFunctionPointer, &(FunctionNameMock))

// std::binds a one-argument ZenMock object for assignment to a std::function
#define BIND_1ARG_ZENMOCK_OBJECT(FunctionNameMock) \
   std::bind(&decltype(FunctionNameMock)::ZenMockItFunctionPointer, &(FunctionNameMock), std::placeholders::_1)

// std::binds a two-argument ZenMock object for assignment to a std::function
#define BIND_2ARG_ZENMOCK_OBJECT(FunctionNameMock) \
   std::bind(&decltype(FunctionNameMock)::ZenMockItFunctionPointer, &(FunctionNameMock), std::placeholders::_1, std::placeholders::_2)

// std::binds a three-argument ZenMock object for assignment to a std::function
#define BIND_3ARG_ZENMOCK_OBJECT(FunctionNameMock) \
   std::bind(&decltype(FunctionNameMock)::ZenMockItFunctionPointer, &(FunctionNameMock), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)

// std::binds a four-argument ZenMock object for assignment to a std::function
#define BIND_4ARG_ZENMOCK_OBJECT(FunctionNameMock) \
   std::bind(&decltype(FunctionNameMock)::ZenMockItFunctionPointer, &(FunctionNameMock), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)

// std::binds a five-argument ZenMock object for assignment to a std::function
#define BIND_5ARG_ZENMOCK_OBJECT(FunctionNameMock) \
   std::bind(&decltype(FunctionNameMock)::ZenMockItFunctionPointer, &(FunctionNameMock), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5)

// std::binds a six-argument ZenMock object for assignment to a std::function
#define BIND_6ARG_ZENMOCK_OBJECT(FunctionNameMock) \
   std::bind(&decltype(FunctionNameMock)::ZenMockItFunctionPointer, &(FunctionNameMock), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6)

// std::binds a seven-argument ZenMock object for assignment to a std::function
#define BIND_7ARG_ZENMOCK_OBJECT(FunctionNameMock) \
   std::bind(&decltype(FunctionNameMock)::ZenMockItFunctionPointer, &(FunctionNameMock), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7)

// std::binds a eight-argument ZenMock object for assignment to a std::function
#define BIND_8ARG_ZENMOCK_OBJECT(FunctionNameMock) \
   std::bind(&decltype(FunctionNameMock)::ZenMockItFunctionPointer, &(FunctionNameMock), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8)

// std::binds a nine-argument ZenMock object for assignment to a std::function
#define BIND_9ARG_ZENMOCK_OBJECT(FunctionNameMock) \
   std::bind(&decltype(FunctionNameMock)::ZenMockItFunctionPointer, &(FunctionNameMock), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, std::placeholders::_9)

// std::binds a ten-argument ZenMock object for assignment to a std::function
#define BIND_10ARG_ZENMOCK_OBJECT(FunctionNameMock) \
   std::bind(&decltype(FunctionNameMock)::ZenMockItFunctionPointer, &(FunctionNameMock), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, std::placeholders::_9, std::placeholders::_10)

namespace ZenMock
{
   class UnexpectedCallException : public ZenUnit::ZenMockException
   {
   private:
      const std::string _what;
   public:
      template<typename... ArgTypes>
      explicit UnexpectedCallException(const std::string& zenMockedFunctionSignature, ArgTypes&&... args)
         : _what(MakeWhat(zenMockedFunctionSignature, std::forward<ArgTypes>(args)...))
      {
      }

      virtual ~UnexpectedCallException() = default;

      template<typename... ArgTypes>
      static std::string MakeWhat(const std::string& zenMockedFunctionSignature, ArgTypes&&... args)
      {
         std::ostringstream whatBuilder;
         whatBuilder << "Unexpected call to ZenMocked function:\n" << zenMockedFunctionSignature;
         AppendToStringedArgs(whatBuilder, 0, std::forward<ArgTypes>(args)...);
         const std::string what = whatBuilder.str();
         return what;
      }

      const char* what() const noexcept override
      {
         return _what.c_str();
      }
   private:
      template<typename ArgType, typename... SubsequentArgTypes>
      static void AppendToStringedArgs(std::ostringstream& outWhatBuilder, size_t argIndex, ArgType&& arg, SubsequentArgTypes&&... args)
      {
         const std::string toStringedArg = ZenUnit::ToStringer::ToString(std::forward<ArgType>(arg));
         outWhatBuilder << "\nArgument" << ++argIndex << ": " << toStringedArg;
         AppendToStringedArgs(outWhatBuilder, argIndex, std::forward<SubsequentArgTypes>(args)...);
      }

      static void AppendToStringedArgs(std::ostringstream&, size_t)
      {
      }
   };

   class ReturnValueMustBeSpecifiedException : public ZenUnit::ZenMockException
   {
   private:
      const std::string _what;
   public:
      explicit ReturnValueMustBeSpecifiedException(const std::string& zenMockedFunctionSignature)
         : _what(MakeWhat(zenMockedFunctionSignature))
      {
      }

      virtual ~ReturnValueMustBeSpecifiedException() = default;

      const char* what() const noexcept override
      {
         return _what.c_str();
      }

      static std::string MakeWhat(const std::string& zenMockedFunctionSignature)
      {
         const std::string what = "For ZenMocked function \"" + zenMockedFunctionSignature + R"(":
ZenMocked functions with non-void return types must have their return value or values set explicitly by calling:
[FunctionName]Mock.[Return|ReturnValues]())";
         return what;
      }
   };

   class UnsupportedCalledZeroTimesException : public ZenUnit::ZenMockException
   {
   private:
      const std::string _what;
   public:
      explicit UnsupportedCalledZeroTimesException(const std::string& zenMockedFunctionSignature)
         : _what(MakeWhat(zenMockedFunctionSignature))
      {
      }

      virtual ~UnsupportedCalledZeroTimesException() = default;

      static std::string MakeWhat(const std::string& zenMockedFunctionSignature)
      {
         const std::string what = ZenUnit::String::Concat(
            "For ZenMocked function \"", zenMockedFunctionSignature, R"(":

Due to ZenMock being a strict mocking library,
ZenMock objects by design do not support asserting that
their corresponding ZenMocked functions were called zero times.
To state the intention that a ZenMocked function
is expected to be called zero times, simply do not call Expect(),
Return(), ReturnValues(), ReturnRandom(), or ThrowException<T>() on a ZenMock object.)");
         return what;
      }

      const char* what() const noexcept override
      {
         return _what.c_str();
      }
   };

   class Throwable
   {
   public:
      virtual void ThrowException() const = 0;
      virtual ~Throwable() = default;
   };

   template<typename ExceptionType>
   class TemplateThrowable : public Throwable
   {
      template<typename T>
      friend class TemplateThrowableTests;
   private:
      std::unique_ptr<const ExceptionType> _exceptionToBeThrown;
   public:
      template<typename... ExceptionArgTypes>
      static const Throwable* New(ExceptionArgTypes&&... exceptionArgs)
      {
         auto* newInstanceOfTemplateThrowable = new TemplateThrowable<ExceptionType>;
         newInstanceOfTemplateThrowable->_exceptionToBeThrown = std::make_unique<ExceptionType>(std::forward<ExceptionArgTypes>(exceptionArgs)...);
         return newInstanceOfTemplateThrowable;
      }

      void ThrowException() const override
      {
         if (_exceptionToBeThrown != nullptr)
         {
            throw * _exceptionToBeThrown;
         }
      }
   };

   class ExceptionThrower
   {
   private:
      std::shared_ptr<const Throwable> _throwable;
   public:
      template<typename ExceptionType, typename... ExceptionArgTypes>
      void ThrowException(ExceptionArgTypes&&... exceptionArgs)
      {
         if (_throwable != nullptr)
         {
            throw std::logic_error("ExceptionThrower::ThrowException<T>() called twice");
         }
         _throwable.reset(TemplateThrowable<ExceptionType>::New(std::forward<ExceptionArgTypes>(exceptionArgs)...));
      }

      void ZenMockThrowExceptionIfExceptionSet() const
      {
         if (_throwable != nullptr)
         {
            _throwable->ThrowException();
         }
      }

      // virtual for ExceptionThrowerMock
      virtual ~ExceptionThrower() = default;
   };

   template<typename FunctionReturnType>
   class ValueReturner
   {
      friend class ValueReturnerTests;
   public:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   private:
      const std::string _zenMockedFunctionSignature;
      // std::deque here instead of std::vector due to the implementation of std::vector<bool>
      std::deque<DecayedFunctionReturnType> _returnValues;
      size_t _returnValueIndex;
   public:
      ValueReturner()
      {
      }

      explicit ValueReturner(std::string zenMockedFunctionSignature)
         : _zenMockedFunctionSignature(std::move(zenMockedFunctionSignature))
         , _returnValueIndex(0)
      {
      }

      template<typename ReturnType>
      void ZenMockAddReturnValue(ReturnType&& returnValue)
      {
         _returnValues.emplace_back(std::forward<ReturnType>(returnValue));
      }

      template<typename ReturnType, typename... ReturnTypes>
      void ZenMockAddReturnValues(ReturnType&& firstReturnValue, ReturnTypes&&... subsequentReturnValues)
      {
         ZenMockAddReturnValue(std::forward<ReturnType>(firstReturnValue));
         ZenMockAddReturnValues(std::forward<ReturnTypes>(subsequentReturnValues)...);
      }

      void ZenMockAddReturnValues()
      {
      }

      template<typename ContainerType>
      void ZenMockAddContainerReturnValues(ContainerType&& returnValues)
      {
         if (returnValues.empty())
         {
            throw std::invalid_argument("ZenMock::ValueReturner::ZenMockAddContainerReturnValues(): Return values container cannot be empty.");
         }
         _returnValues.insert(_returnValues.end(), returnValues.cbegin(), returnValues.cend());
      }

      DecayedFunctionReturnType ZenMockAddRandomReturnValue()
      {
         const DecayedFunctionReturnType randomReturnValue = ZenUnit::Random<DecayedFunctionReturnType>();
         _returnValues.emplace_back(randomReturnValue);
         return randomReturnValue;
      }

      DecayedFunctionReturnType& ZenMockNextReturnValue()
      {
         if (_returnValues.empty())
         {
            throw ZenMock::ReturnValueMustBeSpecifiedException(_zenMockedFunctionSignature);
         }
         DecayedFunctionReturnType& nextReturnValue =
            _returnValueIndex < _returnValues.size() ? _returnValues[_returnValueIndex++] : _returnValues.back();
         return nextReturnValue;
      }
   };

   using ZenMockAtomicFunctionSequencingIndex = ZenUnit::SingleHeaderVariable<std::atomic<unsigned long long>>;

   struct FunctionSequencingToken
   {
      unsigned long long sequencingIndex;

      FunctionSequencingToken() : sequencingIndex(ZenMockAtomicFunctionSequencingIndex::value++) {}

      FunctionSequencingToken Then(FunctionSequencingToken functionSequencingToken)
      {
         IS_TRUE(sequencingIndex < functionSequencingToken.sequencingIndex);
         return functionSequencingToken;
      }
   };

   template<typename MockableExceptionThrowerType>
   class ZenMocker
   {
      friend class ZenMockerTests;
   private:
      std::function<void(int)> _call_exit;
      std::function<const ZenUnit::ZenUnitArgs&()> _call_ZenUnitTestRunner_GetZenUnitArgs;
      bool _zenMockExceptionIsInFlight;
   protected:
      MockableExceptionThrowerType _exceptionThrower;
      FunctionSequencingToken _functionSequencingToken;
   public:
      const std::string ZenMockedFunctionSignature;
      bool _wasExpected;
      bool _wasAsserted;

      ZenMocker()
      {
      }

      explicit ZenMocker(std::string zenMockedFunctionSignature)
         : _call_exit(::exit)
         , _call_ZenUnitTestRunner_GetZenUnitArgs(ZenUnit::ZenUnitTestRunner::GetZenUnitArgs)
         , _zenMockExceptionIsInFlight(false)
         , ZenMockedFunctionSignature(std::move(zenMockedFunctionSignature))
         , _wasExpected(false)
         , _wasAsserted(false)
      {
      }

      ZenMocker& operator=(const ZenMocker&) = delete;

      template<typename ExceptionType, typename... ExceptionArgTypes>
      void ThrowException(ExceptionArgTypes&&... exceptionArgs)
      {
         _exceptionThrower.template ThrowException<ExceptionType>(std::forward<ExceptionArgTypes>(exceptionArgs)...);
         _wasExpected = true;
      }

      ~ZenMocker()
      {
         ZenMockExitIfExpectedButNotAsserted();
      }
   protected:
      void AssignAndIncrementFunctionSequenceIndex()
      {
         _functionSequencingToken.sequencingIndex = ZenMockAtomicFunctionSequencingIndex::value++;
      }

      void ZenMockThrowExceptionIfExceptionSet()
      {
         _exceptionThrower.ZenMockThrowExceptionIfExceptionSet();
      }

      template<typename... ArgTypes>
      void ZenMockThrowIfNotExpected(ArgTypes&&... args)
      {
         if (!_wasExpected)
         {
            _zenMockExceptionIsInFlight = true;
            throw UnexpectedCallException(ZenMockedFunctionSignature, std::forward<ArgTypes>(args)...);
         }
      }

      void ZenMockSetAsserted()
      {
         _wasAsserted = true;
      }

      void ZenMockThrowIfExpectedNumberOfCalls0(size_t expectedNumberOfCalls)
      {
         if (expectedNumberOfCalls == 0)
         {
            _zenMockExceptionIsInFlight = true;
            throw UnsupportedCalledZeroTimesException(ZenMockedFunctionSignature);
         }
      }

      void ZenMockThrowIfExpectedCallsSizeIsZero(size_t expectedCallsSize)
      {
         if (expectedCallsSize == 0)
         {
            _zenMockExceptionIsInFlight = true;
            throw UnsupportedCalledZeroTimesException(ZenMockedFunctionSignature);
         }
      }
   private:
      void ZenMockExitIfExpectedButNotAsserted() const
      {
         if (_wasExpected && !_wasAsserted && !_zenMockExceptionIsInFlight)
         {
            const ZenUnit::Console console;
            console.WriteLineColor(R"(
========================================================
Fatal EBNA: ZenMocked Function Expected But Not Asserted
========================================================)", ZenUnit::Color::Red);
            console.Write("ZenMocked function expected but not later asserted as having been called:\n");
            console.WriteLine(ZenMockedFunctionSignature);
            const ZenUnit::ZenUnitArgs& zenUnitArgs = _call_ZenUnitTestRunner_GetZenUnitArgs();
            console.WriteColor("\n>>------>", ZenUnit::Color::Red);
            console.WriteLine("     Completed: " + zenUnitArgs.commandLine);
            console.WriteColor(">>------>", ZenUnit::Color::Red);
            console.WriteLine("    RandomSeed: " + std::to_string(zenUnitArgs.randomSeed));
            console.WriteColor(">>------>", ZenUnit::Color::Red);
            console.WriteLine("     StartTime: " + zenUnitArgs.startDateTime);
            console.WriteColor(">>------>", ZenUnit::Color::Red);
            ZenUnit::Watch watch;
            const std::string endDateTime = watch.DateTimeNow();
            console.WriteLine("       EndTime: " + endDateTime);
            console.WriteColor(">>------> ", ZenUnit::Color::Red);
            const std::string testRunDurationInSeconds = ZenUnit::ZenUnitTestRunner::Instance()->StopTestRunStopwatchAndGetElapsedSeconds();
            console.WriteLine("     Duration: " + testRunDurationInSeconds + " seconds");
            console.WriteColor(">>------>", ZenUnit::Color::Red);
            console.WriteLine(" Result: Fatal EBNA");
            console.WriteColor(">>-FAIL->", ZenUnit::Color::Red);
            const int exitCode = zenUnitArgs.exitZero ? 0 : 1;
            console.WriteLine("      ExitCode: " + std::to_string(exitCode));
            _call_exit(exitCode);
         }
      }
   };

   class ZeroArgumentZenMockerTests;

   template<typename MockableExceptionThrowerType = ExceptionThrower>
   class ZeroArgumentZenMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class ZeroArgumentZenMockerTests;
   private:
      size_t actualNumberOfCalls;
   protected:
      std::function<void()> _callInstead_voidZeroArgFunction;
   public:
      explicit ZeroArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
         , actualNumberOfCalls(0)
      {
      }

      ~ZeroArgumentZenMocker()
      {
         if (_callInstead_voidZeroArgFunction)
         {
            this->_wasAsserted = true;
         }
      }

      void ZenMockIt()
      {
         this->ZenMockThrowIfNotExpected();
         ++this->actualNumberOfCalls;
         if (this->_callInstead_voidZeroArgFunction)
         {
            this->_callInstead_voidZeroArgFunction();
         }
         this->AssignAndIncrementFunctionSequenceIndex();
         this->ZenMockThrowExceptionIfExceptionSet();
      }

      void CallInstead(const std::function<void()>& voidZeroArgFunction)
      {
         ZeroArgumentZenMocker::_wasExpected = true;
         this->_callInstead_voidZeroArgFunction = voidZeroArgFunction;
      }

      FunctionSequencingToken CalledOnce()
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->ZenMockedFunctionSignature);
         return this->_functionSequencingToken;
      }

      FunctionSequencingToken CalledNTimes(size_t expectedNumberOfCalls)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->ZenMockedFunctionSignature);
         return this->_functionSequencingToken;
      }
   };

   template<typename FunctionReturnType>
   class NonVoidZeroArgumentZenMocker : public ZeroArgumentZenMocker<ExceptionThrower>, protected ValueReturner<FunctionReturnType>
   {
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   public:
      explicit NonVoidZeroArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : ZeroArgumentZenMocker<ExceptionThrower>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         ZeroArgumentZenMocker<ExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         ZeroArgumentZenMocker<ExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         ZeroArgumentZenMocker<ExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         ZeroArgumentZenMocker<ExceptionThrower>::_wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::ZenMockAddRandomReturnValue();
         return randomReturnValue;
      }

      const FunctionReturnType& ZenMockItAndReturnValue()
      {
         ZeroArgumentZenMocker::ZenMockIt();
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType>
   class NonVoidZeroArgFunctionPointerZenMocker : public NonVoidZeroArgumentZenMocker<FunctionReturnType>
   {
   public:
      explicit NonVoidZeroArgFunctionPointerZenMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidZeroArgumentZenMocker<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      static const FunctionReturnType& ZenMockItFunctionPointer(
         NonVoidZeroArgFunctionPointerZenMocker<FunctionReturnType>* functionPointerZenMocker)
      {
         return functionPointerZenMocker->ZenMockItAndReturnValue();
      }
   };

   class VoidZeroArgumentZenMocker : public ZeroArgumentZenMocker<ExceptionThrower>
   {
   public:
      explicit VoidZeroArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : ZeroArgumentZenMocker<ExceptionThrower>(zenMockedFunctionSignature)
      {
      }

      void Expect()
      {
         ZeroArgumentZenMocker<ExceptionThrower>::_wasExpected = true;
      }
   };

   class VoidZeroArgFunctionPointerZenMocker : public VoidZeroArgumentZenMocker
   {
   public:
      explicit VoidZeroArgFunctionPointerZenMocker(const std::string& zenMockedFunctionSignature)
         : VoidZeroArgumentZenMocker(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(VoidZeroArgFunctionPointerZenMocker* functionPointerZenMocker)
      {
         functionPointerZenMocker->ZenMockIt();
      }
   };

   template<typename T>
   struct ArgumentStorage
   {
      typename std::decay<T>::type value;

      ArgumentStorage()
         : value() {}

      ArgumentStorage(const T& value)
         : value(value) {}
   };

   template<>
   struct ArgumentStorage<std::string_view>
   {
      std::string value;

      ArgumentStorage() = default;

      ArgumentStorage(std::string_view stringView)
         : value(stringView) {}
   };

   template<>
   struct ArgumentStorage<std::wstring_view>
   {
      std::wstring value;

      ArgumentStorage() = default;

      ArgumentStorage(std::wstring_view wideStringView)
         : value(wideStringView) {}
   };

   template<typename T>
   struct ArgumentStorage<std::unique_ptr<T>>
   {
      const T* const value;

      ArgumentStorage() = delete;

      ArgumentStorage(const std::unique_ptr<T>& uniquePtr)
         : value(uniquePtr.get()) {}
   };

   template<typename T>
   struct ReferenceStorage
   {
      const T& value;

      ReferenceStorage()
         : value() {}

      ReferenceStorage(const T& argument)
         : value(argument) {}
   };

   template<>
   struct ReferenceStorage<std::string_view>
   {
      std::string value;

      ReferenceStorage() = default;

      ReferenceStorage(std::string_view argument)
         : value(argument) {}
   };

   template<typename T>
   struct ReferenceStorage<std::unique_ptr<T>>
   {
      const T* const value;

      ReferenceStorage() = delete;

      ReferenceStorage(const std::unique_ptr<T>& uniquePtr)
         : value(uniquePtr.get()) {}
   };

   template<typename Arg1Type>
   struct OneArgumentFunctionCall
   {
      ArgumentStorage<Arg1Type> argument;

      OneArgumentFunctionCall() noexcept
         : argument() {}

      OneArgumentFunctionCall(const Arg1Type& argument)
         : argument(argument) {}
   };

   template<typename ArgType>
   struct OneArgumentFunctionCallReference
   {
      const ReferenceStorage<ArgType> argumentReference;

      OneArgumentFunctionCallReference(const ArgType& argument)
         : argumentReference(argument) {}

      explicit OneArgumentFunctionCallReference(const OneArgumentFunctionCall<ArgType>& oneArgumentFunctionCall)
         : argumentReference(oneArgumentFunctionCall.argument.value) {}
   };

   template<typename Arg1Type, typename Arg2Type>
   struct TwoArgumentFunctionCall
   {
      ArgumentStorage<Arg1Type> firstArgument;
      ArgumentStorage<Arg2Type> secondArgument;

      TwoArgumentFunctionCall() noexcept
         : firstArgument()
         , secondArgument() {}

      TwoArgumentFunctionCall(const Arg1Type& firstArgument, const Arg2Type& secondArgument)
         : firstArgument(firstArgument)
         , secondArgument(secondArgument) {}
   };

   template<typename Arg1Type, typename Arg2Type>
   struct TwoArgumentFunctionCallReferences
   {
      const ReferenceStorage<Arg1Type> firstArgumentReference;
      const ReferenceStorage<Arg2Type> secondArgumentReference;

      TwoArgumentFunctionCallReferences(const Arg1Type& firstArgument, const Arg2Type& secondArgument)
         : firstArgumentReference(firstArgument)
         , secondArgumentReference(secondArgument) {}

      explicit TwoArgumentFunctionCallReferences(const TwoArgumentFunctionCall<Arg1Type, Arg2Type>& twoArgumentFunctionCall)
         : firstArgumentReference(twoArgumentFunctionCall.firstArgument.value)
         , secondArgumentReference(twoArgumentFunctionCall.secondArgument.value) {}
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   struct ThreeArgumentFunctionCall
   {
      ArgumentStorage<Arg1Type> firstArgument;
      ArgumentStorage<Arg2Type> secondArgument;
      ArgumentStorage<Arg3Type> thirdArgument;

      ThreeArgumentFunctionCall() noexcept
         : firstArgument()
         , secondArgument()
         , thirdArgument() {}

      ThreeArgumentFunctionCall(const Arg1Type& firstArgument, const Arg2Type& secondArgument, const Arg3Type& thirdArgument)
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
         , thirdArgument(thirdArgument) {}
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   struct ThreeArgumentFunctionCallReferences
   {
      const ReferenceStorage<Arg1Type> firstArgumentReference;
      const ReferenceStorage<Arg2Type> secondArgumentReference;
      const ReferenceStorage<Arg3Type> thirdArgumentReference;

      ThreeArgumentFunctionCallReferences(const Arg1Type& firstArgument, const Arg2Type& secondArgument, const Arg3Type& thirdArgument)
         : firstArgumentReference(firstArgument)
         , secondArgumentReference(secondArgument)
         , thirdArgumentReference(thirdArgument) {}

      explicit ThreeArgumentFunctionCallReferences(const ThreeArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type>& threeArgumentFunctionCall)
         : firstArgumentReference(threeArgumentFunctionCall.firstArgument.value)
         , secondArgumentReference(threeArgumentFunctionCall.secondArgument.value)
         , thirdArgumentReference(threeArgumentFunctionCall.thirdArgument.value) {}
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   struct FourArgumentFunctionCall
   {
      ArgumentStorage<Arg1Type> firstArgument;
      ArgumentStorage<Arg2Type> secondArgument;
      ArgumentStorage<Arg3Type> thirdArgument;
      ArgumentStorage<Arg4Type> fourthArgument;

      FourArgumentFunctionCall() noexcept
         : firstArgument()
         , secondArgument()
         , thirdArgument()
         , fourthArgument() {}

      FourArgumentFunctionCall(const Arg1Type& firstArgument, const Arg2Type& secondArgument, const Arg3Type& thirdArgument, const Arg4Type& fourthArgument)
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
         , thirdArgument(thirdArgument)
         , fourthArgument(fourthArgument) {}
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   struct FourArgumentFunctionCallReference
   {
      const ReferenceStorage<Arg1Type> firstArgumentReference;
      const ReferenceStorage<Arg2Type> secondArgumentReference;
      const ReferenceStorage<Arg3Type> thirdArgumentReference;
      const ReferenceStorage<Arg4Type> fourthArgumentReference;

      FourArgumentFunctionCallReference(const Arg1Type& firstArgument, const Arg2Type& secondArgument, const Arg3Type& thirdArgument, const Arg4Type& fourthArgument)
         : firstArgumentReference(firstArgument)
         , secondArgumentReference(secondArgument)
         , thirdArgumentReference(thirdArgument)
         , fourthArgumentReference(fourthArgument) {}

      explicit FourArgumentFunctionCallReference(const FourArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& fourArgumentFunctionCall)
         : firstArgumentReference(fourArgumentFunctionCall.firstArgument.value)
         , secondArgumentReference(fourArgumentFunctionCall.secondArgument.value)
         , thirdArgumentReference(fourArgumentFunctionCall.thirdArgument.value)
         , fourthArgumentReference(fourArgumentFunctionCall.fourthArgument.value) {}
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   struct FiveArgumentFunctionCall // LCOV_EXCL_LINE
   {
      ArgumentStorage<Arg1Type> firstArgument;
      ArgumentStorage<Arg2Type> secondArgument;
      ArgumentStorage<Arg3Type> thirdArgument;
      ArgumentStorage<Arg4Type> fourthArgument;
      ArgumentStorage<Arg5Type> fifthArgument;

      FiveArgumentFunctionCall() noexcept
         : firstArgument()
         , secondArgument()
         , thirdArgument()
         , fourthArgument()
         , fifthArgument() {}

      FiveArgumentFunctionCall(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument)
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
         , thirdArgument(thirdArgument)
         , fourthArgument(fourthArgument)
         , fifthArgument(fifthArgument) {}
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   struct FiveArgumentFunctionCallReferences
   {
      const ReferenceStorage<Arg1Type> firstArgumentReference;
      const ReferenceStorage<Arg2Type> secondArgumentReference;
      const ReferenceStorage<Arg3Type> thirdArgumentReference;
      const ReferenceStorage<Arg4Type> fourthArgumentReference;
      const ReferenceStorage<Arg5Type> fifthArgumentReference;

      FiveArgumentFunctionCallReferences(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument)
         : firstArgumentReference(firstArgument)
         , secondArgumentReference(secondArgument)
         , thirdArgumentReference(thirdArgument)
         , fourthArgumentReference(fourthArgument)
         , fifthArgumentReference(fifthArgument) {}

      explicit FiveArgumentFunctionCallReferences(const FiveArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& fiveArgumentFunctionCall)
         : firstArgumentReference(fiveArgumentFunctionCall.firstArgument.value)
         , secondArgumentReference(fiveArgumentFunctionCall.secondArgument.value)
         , thirdArgumentReference(fiveArgumentFunctionCall.thirdArgument.value)
         , fourthArgumentReference(fiveArgumentFunctionCall.fourthArgument.value)
         , fifthArgumentReference(fiveArgumentFunctionCall.fifthArgument.value) {}
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   struct SixArgumentFunctionCall
   {
      ArgumentStorage<Arg1Type> firstArgument;
      ArgumentStorage<Arg2Type> secondArgument;
      ArgumentStorage<Arg3Type> thirdArgument;
      ArgumentStorage<Arg4Type> fourthArgument;
      ArgumentStorage<Arg5Type> fifthArgument;
      ArgumentStorage<Arg6Type> sixthArgument;

      SixArgumentFunctionCall() noexcept
         : firstArgument()
         , secondArgument()
         , thirdArgument()
         , fourthArgument()
         , fifthArgument()
         , sixthArgument() {}

      SixArgumentFunctionCall(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument,
         const Arg6Type& sixthArgument)
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
         , thirdArgument(thirdArgument)
         , fourthArgument(fourthArgument)
         , fifthArgument(fifthArgument)
         , sixthArgument(sixthArgument) {}
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   struct SixArgumentFunctionCallReferences
   {
      const ReferenceStorage<Arg1Type> firstArgumentReference;
      const ReferenceStorage<Arg2Type> secondArgumentReference;
      const ReferenceStorage<Arg3Type> thirdArgumentReference;
      const ReferenceStorage<Arg4Type> fourthArgumentReference;
      const ReferenceStorage<Arg5Type> fifthArgumentReference;
      const ReferenceStorage<Arg6Type> sixthArgumentReference;

      SixArgumentFunctionCallReferences(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument,
         const Arg6Type& sixthArgument)
         : firstArgumentReference(firstArgument)
         , secondArgumentReference(secondArgument)
         , thirdArgumentReference(thirdArgument)
         , fourthArgumentReference(fourthArgument)
         , fifthArgumentReference(fifthArgument)
         , sixthArgumentReference(sixthArgument) {}

      explicit SixArgumentFunctionCallReferences(const SixArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& sixArgumentFunctionCall)
         : firstArgumentReference(sixArgumentFunctionCall.firstArgument.value)
         , secondArgumentReference(sixArgumentFunctionCall.secondArgument.value)
         , thirdArgumentReference(sixArgumentFunctionCall.thirdArgument.value)
         , fourthArgumentReference(sixArgumentFunctionCall.fourthArgument.value)
         , fifthArgumentReference(sixArgumentFunctionCall.fifthArgument.value)
         , sixthArgumentReference(sixArgumentFunctionCall.sixthArgument.value) {}
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   struct SevenArgumentFunctionCall
   {
      ArgumentStorage<Arg1Type> firstArgument;
      ArgumentStorage<Arg2Type> secondArgument;
      ArgumentStorage<Arg3Type> thirdArgument;
      ArgumentStorage<Arg4Type> fourthArgument;
      ArgumentStorage<Arg5Type> fifthArgument;
      ArgumentStorage<Arg6Type> sixthArgument;
      ArgumentStorage<Arg7Type> seventhArgument;

      SevenArgumentFunctionCall() noexcept
         : firstArgument()
         , secondArgument()
         , thirdArgument()
         , fourthArgument()
         , fifthArgument()
         , sixthArgument()
         , seventhArgument() {}

      SevenArgumentFunctionCall(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument,
         const Arg6Type& sixthArgument,
         const Arg7Type& seventhArgument)
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
         , thirdArgument(thirdArgument)
         , fourthArgument(fourthArgument)
         , fifthArgument(fifthArgument)
         , sixthArgument(sixthArgument)
         , seventhArgument(seventhArgument) {}
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   struct SevenArgumentFunctionCallReferences
   {
      const ReferenceStorage<Arg1Type> firstArgumentReference;
      const ReferenceStorage<Arg2Type> secondArgumentReference;
      const ReferenceStorage<Arg3Type> thirdArgumentReference;
      const ReferenceStorage<Arg4Type> fourthArgumentReference;
      const ReferenceStorage<Arg5Type> fifthArgumentReference;
      const ReferenceStorage<Arg6Type> sixthArgumentReference;
      const ReferenceStorage<Arg7Type> seventhArgumentReference;

      SevenArgumentFunctionCallReferences(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument,
         const Arg6Type& sixthArgument,
         const Arg7Type& seventhArgument)
         : firstArgumentReference(firstArgument)
         , secondArgumentReference(secondArgument)
         , thirdArgumentReference(thirdArgument)
         , fourthArgumentReference(fourthArgument)
         , fifthArgumentReference(fifthArgument)
         , sixthArgumentReference(sixthArgument)
         , seventhArgumentReference(seventhArgument) {}

      explicit SevenArgumentFunctionCallReferences(const SevenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& sevenArgumentFunctionCall)
         : firstArgumentReference(sevenArgumentFunctionCall.firstArgument.value)
         , secondArgumentReference(sevenArgumentFunctionCall.secondArgument.value)
         , thirdArgumentReference(sevenArgumentFunctionCall.thirdArgument.value)
         , fourthArgumentReference(sevenArgumentFunctionCall.fourthArgument.value)
         , fifthArgumentReference(sevenArgumentFunctionCall.fifthArgument.value)
         , sixthArgumentReference(sevenArgumentFunctionCall.sixthArgument.value)
         , seventhArgumentReference(sevenArgumentFunctionCall.seventhArgument.value) {}
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
   struct EightArgumentFunctionCall
   {
      ArgumentStorage<Arg1Type> firstArgument;
      ArgumentStorage<Arg2Type> secondArgument;
      ArgumentStorage<Arg3Type> thirdArgument;
      ArgumentStorage<Arg4Type> fourthArgument;
      ArgumentStorage<Arg5Type> fifthArgument;
      ArgumentStorage<Arg6Type> sixthArgument;
      ArgumentStorage<Arg7Type> seventhArgument;
      ArgumentStorage<Arg8Type> eigthArgument;

      EightArgumentFunctionCall() noexcept
         : firstArgument()
         , secondArgument()
         , thirdArgument()
         , fourthArgument()
         , fifthArgument()
         , sixthArgument()
         , seventhArgument()
         , eigthArgument() {}

      EightArgumentFunctionCall(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument,
         const Arg6Type& sixthArgument,
         const Arg7Type& seventhArgument,
         const Arg8Type& eigthArgument)
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
         , thirdArgument(thirdArgument)
         , fourthArgument(fourthArgument)
         , fifthArgument(fifthArgument)
         , sixthArgument(sixthArgument)
         , seventhArgument(seventhArgument)
         , eigthArgument(eigthArgument) {}
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
   struct EightArgumentFunctionCallReferences
   {
      const ReferenceStorage<Arg1Type> firstArgumentReference;
      const ReferenceStorage<Arg2Type> secondArgumentReference;
      const ReferenceStorage<Arg3Type> thirdArgumentReference;
      const ReferenceStorage<Arg4Type> fourthArgumentReference;
      const ReferenceStorage<Arg5Type> fifthArgumentReference;
      const ReferenceStorage<Arg6Type> sixthArgumentReference;
      const ReferenceStorage<Arg7Type> seventhArgumentReference;
      const ReferenceStorage<Arg8Type> eigthArgumentReference;

      EightArgumentFunctionCallReferences(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument,
         const Arg6Type& sixthArgument,
         const Arg7Type& seventhArgument,
         const Arg8Type& eigthArgument)
         : firstArgumentReference(firstArgument)
         , secondArgumentReference(secondArgument)
         , thirdArgumentReference(thirdArgument)
         , fourthArgumentReference(fourthArgument)
         , fifthArgumentReference(fifthArgument)
         , sixthArgumentReference(sixthArgument)
         , seventhArgumentReference(seventhArgument)
         , eigthArgumentReference(eigthArgument) {}

      explicit EightArgumentFunctionCallReferences(const EightArgumentFunctionCall<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& eightArgumentFunctionCall)
         : firstArgumentReference(eightArgumentFunctionCall.firstArgument.value)
         , secondArgumentReference(eightArgumentFunctionCall.secondArgument.value)
         , thirdArgumentReference(eightArgumentFunctionCall.thirdArgument.value)
         , fourthArgumentReference(eightArgumentFunctionCall.fourthArgument.value)
         , fifthArgumentReference(eightArgumentFunctionCall.fifthArgument.value)
         , sixthArgumentReference(eightArgumentFunctionCall.sixthArgument.value)
         , seventhArgumentReference(eightArgumentFunctionCall.seventhArgument.value)
         , eigthArgumentReference(eightArgumentFunctionCall.eigthArgument.value) {}
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
   struct NineArgumentFunctionCall
   {
      ArgumentStorage<Arg1Type> firstArgument;
      ArgumentStorage<Arg2Type> secondArgument;
      ArgumentStorage<Arg3Type> thirdArgument;
      ArgumentStorage<Arg4Type> fourthArgument;
      ArgumentStorage<Arg5Type> fifthArgument;
      ArgumentStorage<Arg6Type> sixthArgument;
      ArgumentStorage<Arg7Type> seventhArgument;
      ArgumentStorage<Arg8Type> eigthArgument;
      ArgumentStorage<Arg9Type> ninthArgument;

      NineArgumentFunctionCall() noexcept
         : firstArgument()
         , secondArgument()
         , thirdArgument()
         , fourthArgument()
         , fifthArgument()
         , sixthArgument()
         , seventhArgument()
         , eigthArgument()
         , ninthArgument() {}

      NineArgumentFunctionCall(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument,
         const Arg6Type& sixthArgument,
         const Arg7Type& seventhArgument,
         const Arg8Type& eigthArgument,
         const Arg9Type& ninthArgument)
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
         , thirdArgument(thirdArgument)
         , fourthArgument(fourthArgument)
         , fifthArgument(fifthArgument)
         , sixthArgument(sixthArgument)
         , seventhArgument(seventhArgument)
         , eigthArgument(eigthArgument)
         , ninthArgument(ninthArgument) {}
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
   struct NineArgumentFunctionCallReferences
   {
      const ReferenceStorage<Arg1Type> firstArgumentReference;
      const ReferenceStorage<Arg2Type> secondArgumentReference;
      const ReferenceStorage<Arg3Type> thirdArgumentReference;
      const ReferenceStorage<Arg4Type> fourthArgumentReference;
      const ReferenceStorage<Arg5Type> fifthArgumentReference;
      const ReferenceStorage<Arg6Type> sixthArgumentReference;
      const ReferenceStorage<Arg7Type> seventhArgumentReference;
      const ReferenceStorage<Arg8Type> eigthArgumentReference;
      const ReferenceStorage<Arg9Type> ninthArgumentReference;

      NineArgumentFunctionCallReferences(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument,
         const Arg6Type& sixthArgument,
         const Arg7Type& seventhArgument,
         const Arg8Type& eigthArgument,
         const Arg9Type& ninthArgument)
         : firstArgumentReference(firstArgument)
         , secondArgumentReference(secondArgument)
         , thirdArgumentReference(thirdArgument)
         , fourthArgumentReference(fourthArgument)
         , fifthArgumentReference(fifthArgument)
         , sixthArgumentReference(sixthArgument)
         , seventhArgumentReference(seventhArgument)
         , eigthArgumentReference(eigthArgument)
         , ninthArgumentReference(ninthArgument) {}

      explicit NineArgumentFunctionCallReferences(const NineArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& nineArgumentFunctionCall)
         : firstArgumentReference(nineArgumentFunctionCall.firstArgument.value)
         , secondArgumentReference(nineArgumentFunctionCall.secondArgument.value)
         , thirdArgumentReference(nineArgumentFunctionCall.thirdArgument.value)
         , fourthArgumentReference(nineArgumentFunctionCall.fourthArgument.value)
         , fifthArgumentReference(nineArgumentFunctionCall.fifthArgument.value)
         , sixthArgumentReference(nineArgumentFunctionCall.sixthArgument.value)
         , seventhArgumentReference(nineArgumentFunctionCall.seventhArgument.value)
         , eigthArgumentReference(nineArgumentFunctionCall.eigthArgument.value)
         , ninthArgumentReference(nineArgumentFunctionCall.ninthArgument.value) {}
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
   struct TenArgumentFunctionCall
   {
      ArgumentStorage<Arg1Type> firstArgument;
      ArgumentStorage<Arg2Type> secondArgument;
      ArgumentStorage<Arg3Type> thirdArgument;
      ArgumentStorage<Arg4Type> fourthArgument;
      ArgumentStorage<Arg5Type> fifthArgument;
      ArgumentStorage<Arg6Type> sixthArgument;
      ArgumentStorage<Arg7Type> seventhArgument;
      ArgumentStorage<Arg8Type> eigthArgument;
      ArgumentStorage<Arg9Type> ninthArgument;
      ArgumentStorage<Arg10Type> tenthArgument;

      TenArgumentFunctionCall() noexcept
         : firstArgument()
         , secondArgument()
         , thirdArgument()
         , fourthArgument()
         , fifthArgument()
         , sixthArgument()
         , seventhArgument()
         , eigthArgument()
         , ninthArgument()
         , tenthArgument() {}

      TenArgumentFunctionCall(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument,
         const Arg6Type& sixthArgument,
         const Arg7Type& seventhArgument,
         const Arg8Type& eigthArgument,
         const Arg9Type& ninthArgument,
         const Arg10Type& tenthArgument)
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
         , thirdArgument(thirdArgument)
         , fourthArgument(fourthArgument)
         , fifthArgument(fifthArgument)
         , sixthArgument(sixthArgument)
         , seventhArgument(seventhArgument)
         , eigthArgument(eigthArgument)
         , ninthArgument(ninthArgument)
         , tenthArgument(tenthArgument) {}
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
   struct TenArgumentFunctionCallReferences
   {
      const ReferenceStorage<Arg1Type> firstArgumentReference;
      const ReferenceStorage<Arg2Type> secondArgumentReference;
      const ReferenceStorage<Arg3Type> thirdArgumentReference;
      const ReferenceStorage<Arg4Type> fourthArgumentReference;
      const ReferenceStorage<Arg5Type> fifthArgumentReference;
      const ReferenceStorage<Arg6Type> sixthArgumentReference;
      const ReferenceStorage<Arg7Type> seventhArgumentReference;
      const ReferenceStorage<Arg8Type> eigthArgumentReference;
      const ReferenceStorage<Arg9Type> ninthArgumentReference;
      const ReferenceStorage<Arg10Type> tenthArgumentReference;

      TenArgumentFunctionCallReferences(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument,
         const Arg6Type& sixthArgument,
         const Arg7Type& seventhArgument,
         const Arg8Type& eigthArgument,
         const Arg9Type& ninthArgument,
         const Arg10Type& tenthArgument)
         : firstArgumentReference(firstArgument)
         , secondArgumentReference(secondArgument)
         , thirdArgumentReference(thirdArgument)
         , fourthArgumentReference(fourthArgument)
         , fifthArgumentReference(fifthArgument)
         , sixthArgumentReference(sixthArgument)
         , seventhArgumentReference(seventhArgument)
         , eigthArgumentReference(eigthArgument)
         , ninthArgumentReference(ninthArgument)
         , tenthArgumentReference(tenthArgument) {}

      explicit TenArgumentFunctionCallReferences(const TenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& tenArgumentFunctionCall)
         : firstArgumentReference(tenArgumentFunctionCall.firstArgument.value)
         , secondArgumentReference(tenArgumentFunctionCall.secondArgument.value)
         , thirdArgumentReference(tenArgumentFunctionCall.thirdArgument.value)
         , fourthArgumentReference(tenArgumentFunctionCall.fourthArgument.value)
         , fifthArgumentReference(tenArgumentFunctionCall.fifthArgument.value)
         , sixthArgumentReference(tenArgumentFunctionCall.sixthArgument.value)
         , seventhArgumentReference(tenArgumentFunctionCall.seventhArgument.value)
         , eigthArgumentReference(tenArgumentFunctionCall.eigthArgument.value)
         , ninthArgumentReference(tenArgumentFunctionCall.ninthArgument.value)
         , tenthArgumentReference(tenArgumentFunctionCall.tenthArgument.value) {}
   };

   template<
      typename ArgType,
      typename MockableExceptionThrowerType = ExceptionThrower>
   class OneArgumentZenMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class OneArgumentZenMockerTests;
      template<
         typename ZenMockObjectType,
         typename FreeMockType,
         typename NamespaceMockType,
         typename StaticMockType,
         typename StaticNameClashMockType>
      friend class ZenMock1Tester;
   public:
      std::vector<OneArgumentFunctionCall<ArgType>> zenMockedFunctionCallHistory;

      explicit OneArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(const ArgType& argument)
      {
         this->ZenMockThrowIfNotExpected(argument);
         this->zenMockedFunctionCallHistory.emplace_back(argument);
         this->ZenMockThrowExceptionIfExceptionSet();
      }

      FunctionSequencingToken CalledOnceWith(const ArgType& expectedArgument)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, zenMockedFunctionCallHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument, zenMockedFunctionCallHistory[0].argument.value, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledOnceWithAny()
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, zenMockedFunctionCallHistory.size(), this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledNTimesWith(size_t expectedNumberOfCalls, const ArgType& expectedArgument)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, zenMockedFunctionCallHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex =
               ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArgument, zenMockedFunctionCallHistory[i].argument.value, zenMockedFunctionSignatureAndCallIndex);
         }
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(const std::vector<OneArgumentFunctionCallReference<ArgType>>& expectedOneArgumentFunctionCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedOneArgumentFunctionCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<OneArgumentFunctionCallReference<ArgType>> actualOneArgumentFunctionCalls = PrivateCallsToCallRefs(zenMockedFunctionCallHistory);
         VECTORS_EQUAL(expectedOneArgumentFunctionCalls, actualOneArgumentFunctionCalls, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }
   private:
      static std::vector<OneArgumentFunctionCallReference<ArgType>>
         PrivateCallsToCallRefs(const std::vector<OneArgumentFunctionCall<ArgType>>& zenMockedFunctionCallHistory)
      {
         std::vector<OneArgumentFunctionCallReference<ArgType>> oneArgumentFunctionCallRefs;
         oneArgumentFunctionCallRefs.reserve(zenMockedFunctionCallHistory.size());
         std::for_each(zenMockedFunctionCallHistory.cbegin(), zenMockedFunctionCallHistory.cend(),
            [&](const OneArgumentFunctionCall<ArgType>& oneArgumentFunctionCall)
         {
            oneArgumentFunctionCallRefs.emplace_back(oneArgumentFunctionCall);
         });
         return oneArgumentFunctionCallRefs;
      }
   };

   template<typename ArgType>
   class VoidOneArgumentZenMocker : public OneArgumentZenMocker<ArgType>
   {
   public:
      explicit VoidOneArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : OneArgumentZenMocker<ArgType>(zenMockedFunctionSignature)
      {
      }

      void Expect()
      {
         OneArgumentZenMocker<ArgType>::_wasExpected = true;
      }
   };

   template<typename FunctionReturnType, typename ArgType>
   class NonVoidOneArgumentZenMocker : public OneArgumentZenMocker<ArgType>, protected ValueReturner<FunctionReturnType>
   {
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   public:
      explicit NonVoidOneArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : OneArgumentZenMocker<ArgType>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         OneArgumentZenMocker<ArgType>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         OneArgumentZenMocker<ArgType>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         OneArgumentZenMocker<ArgType>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         OneArgumentZenMocker<ArgType>::_wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::ZenMockAddRandomReturnValue();
         return randomReturnValue;
      }

      const FunctionReturnType& ZenMockItAndReturnValue(ArgType argument)
      {
         OneArgumentZenMocker<ArgType>::ZenMockIt(argument);
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type>
   class NonVoidOneArgFunctionPointerZenMocker : public NonVoidOneArgumentZenMocker<FunctionReturnType, Arg1Type>
   {
   public:
      explicit NonVoidOneArgFunctionPointerZenMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidOneArgumentZenMocker<FunctionReturnType, Arg1Type>(zenMockedFunctionSignature)
      {
      }

      static const FunctionReturnType& ZenMockItFunctionPointer(
         NonVoidOneArgFunctionPointerZenMocker* functionMocker, Arg1Type argument)
      {
         return functionMocker->ZenMockItAndReturnValue(argument);
      }
   };

   template<typename Arg1Type>
   class VoidOneArgFunctionPointerZenMocker : public VoidOneArgumentZenMocker<Arg1Type>
   {
   public:
      explicit VoidOneArgFunctionPointerZenMocker(const std::string& zenMockedFunctionSignature)
         : VoidOneArgumentZenMocker<Arg1Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidOneArgFunctionPointerZenMocker<Arg1Type>* functionMocker, Arg1Type argument)
      {
         functionMocker->ZenMockIt(argument);
      }
   };

   template<
      typename Arg1Type,
      typename Arg2Type,
      typename MockableExceptionThrowerType = ExceptionThrower>
   class TwoArgumentZenMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class TwoArgumentZenMockerTests;
   protected:
      std::function<void(Arg1Type, Arg2Type)> _callInstead_voidTwoArgFunction;
   public:
      std::vector<TwoArgumentFunctionCall<Arg1Type, Arg2Type>> zenMockedFunctionCallHistory;

      explicit TwoArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      ~TwoArgumentZenMocker()
      {
         if (_callInstead_voidTwoArgFunction)
         {
            this->_wasAsserted = true;
         }
      }

      void ZenMockIt(const Arg1Type& firstArgument, const Arg2Type& secondArgument)
      {
         this->ZenMockThrowIfNotExpected(firstArgument, secondArgument);
         zenMockedFunctionCallHistory.emplace_back(firstArgument, secondArgument);
         if (this->_callInstead_voidTwoArgFunction)
         {
            this->_callInstead_voidTwoArgFunction(firstArgument, secondArgument);
         }
         this->ZenMockThrowExceptionIfExceptionSet();
      }

      FunctionSequencingToken CalledOnceWith(
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, zenMockedFunctionCallHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, zenMockedFunctionCallHistory[0].firstArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, zenMockedFunctionCallHistory[0].secondArgument.value, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, zenMockedFunctionCallHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex =
               ZenUnit::String::Concat(this->ZenMockedFunctionSignature, ", at i=", i);
            ARE_EQUAL(expectedFirstArgument, zenMockedFunctionCallHistory[i].firstArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, zenMockedFunctionCallHistory[i].secondArgument.value, zenMockedFunctionSignatureAndCallIndex);
         }
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(const std::vector<TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>>& expectedTwoArgumentFunctionCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedTwoArgumentFunctionCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>>
            actualTwoArgumentFunctionCalls = PrivateCallsToCallRefs(zenMockedFunctionCallHistory);
         VECTORS_EQUAL(expectedTwoArgumentFunctionCalls, actualTwoArgumentFunctionCalls, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }
   private:
      static std::vector<TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>>
         PrivateCallsToCallRefs(const std::vector<TwoArgumentFunctionCall<Arg1Type, Arg2Type>>& zenMockedFunctionCallHistory)
      {
         std::vector<TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>> twoArgumentFunctionCallRefs;
         twoArgumentFunctionCallRefs.reserve(zenMockedFunctionCallHistory.size());
         std::for_each(zenMockedFunctionCallHistory.cbegin(), zenMockedFunctionCallHistory.cend(),
            [&](const TwoArgumentFunctionCall<Arg1Type, Arg2Type>& twoArgumentFunctionCall)
         {
            twoArgumentFunctionCallRefs.emplace_back(twoArgumentFunctionCall);
         });
         return twoArgumentFunctionCallRefs;
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type>
   class NonVoidTwoArgumentZenMocker : public TwoArgumentZenMocker<Arg1Type, Arg2Type>, protected ValueReturner<FunctionReturnType>
   {
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   public:
      explicit NonVoidTwoArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : TwoArgumentZenMocker<Arg1Type, Arg2Type>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         TwoArgumentZenMocker<Arg1Type, Arg2Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         TwoArgumentZenMocker<Arg1Type, Arg2Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         TwoArgumentZenMocker<Arg1Type, Arg2Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         TwoArgumentZenMocker<Arg1Type, Arg2Type>::_wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::ZenMockAddRandomReturnValue();
         return randomReturnValue;
      }

      const FunctionReturnType& ZenMockItAndReturnValue(Arg1Type firstArgument, Arg2Type secondArgument)
      {
         TwoArgumentZenMocker<Arg1Type, Arg2Type>::ZenMockIt(firstArgument, secondArgument);
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type>
   class NonVoidTwoArgFunctionPointerZenMocker : public NonVoidTwoArgumentZenMocker<FunctionReturnType, Arg1Type, Arg2Type>
   {
   public:
      explicit NonVoidTwoArgFunctionPointerZenMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidTwoArgumentZenMocker<FunctionReturnType, Arg1Type, Arg2Type>(zenMockedFunctionSignature)
      {
      }

      static const FunctionReturnType& ZenMockItFunctionPointer(
         NonVoidTwoArgFunctionPointerZenMocker<FunctionReturnType, Arg1Type, Arg2Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument)
      {
         return functionMocker->ZenMockItAndReturnValue(firstArgument, secondArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type>
   class VoidTwoArgumentZenMocker : public TwoArgumentZenMocker<Arg1Type, Arg2Type>
   {
   public:
      explicit VoidTwoArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : TwoArgumentZenMocker<Arg1Type, Arg2Type>(zenMockedFunctionSignature)
      {
      }

      void Expect()
      {
         TwoArgumentZenMocker<Arg1Type, Arg2Type>::_wasExpected = true;
      }

      void CallInstead(const std::function<void(Arg1Type, Arg2Type)>& voidTwoArgFunction)
      {
         TwoArgumentZenMocker<Arg1Type, Arg2Type>::_wasExpected = true;
         this->_callInstead_voidTwoArgFunction = voidTwoArgFunction;
      }
   };

   template<typename Arg1Type, typename Arg2Type>
   class VoidTwoArgFunctionPointerZenMocker : public VoidTwoArgumentZenMocker<Arg1Type, Arg2Type>
   {
   public:
      explicit VoidTwoArgFunctionPointerZenMocker(const std::string& zenMockedFunctionSignature)
         : VoidTwoArgumentZenMocker<Arg1Type, Arg2Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidTwoArgFunctionPointerZenMocker<Arg1Type, Arg2Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument)
      {
         functionMocker->ZenMockIt(firstArgument, secondArgument);
      }
   };

   template<
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename MockableExceptionThrowerType = ExceptionThrower>
   class ThreeArgumentZenMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class ThreeArgumentZenMockerTests;
   public:
      std::vector<ThreeArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type>> zenMockedFunctionCallHistory;

      explicit ThreeArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      virtual ~ThreeArgumentZenMocker() = default;

      virtual void ZenMockIt(const Arg1Type& firstArgument, const Arg2Type& secondArgument, const Arg3Type& thirdArgument)
      {
         this->ZenMockThrowIfNotExpected(firstArgument, secondArgument, thirdArgument);
         this->zenMockedFunctionCallHistory.emplace_back(firstArgument, secondArgument, thirdArgument);
         this->ZenMockThrowExceptionIfExceptionSet();
      }

      FunctionSequencingToken CalledOnceWith(
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, this->zenMockedFunctionCallHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, this->zenMockedFunctionCallHistory[0].firstArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, this->zenMockedFunctionCallHistory[0].secondArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, this->zenMockedFunctionCallHistory[0].thirdArgument.value, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, this->zenMockedFunctionCallHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, this->zenMockedFunctionCallHistory[i].firstArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, this->zenMockedFunctionCallHistory[i].secondArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, this->zenMockedFunctionCallHistory[i].thirdArgument.value, zenMockedFunctionSignatureAndCallIndex);
         }
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(const std::vector<ThreeArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type>>& expectedThreeArgumentFunctionCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedThreeArgumentFunctionCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<ThreeArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type>> actualThreeArgumentFunctionCalls = PrivateCallsToCallRefs(zenMockedFunctionCallHistory);
         VECTORS_EQUAL(expectedThreeArgumentFunctionCalls, actualThreeArgumentFunctionCalls, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

   private:
      static std::vector<ThreeArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type>>
         PrivateCallsToCallRefs(const std::vector<ThreeArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type>>& zenMockedFunctionCallHistory)
      {
         std::vector<ThreeArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type>> threeArgumentFunctionCallRefs;
         threeArgumentFunctionCallRefs.reserve(zenMockedFunctionCallHistory.size());
         std::for_each(zenMockedFunctionCallHistory.cbegin(), zenMockedFunctionCallHistory.cend(),
            [&](const ThreeArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type>& threeArgumentFunctionCall)
         {
            threeArgumentFunctionCallRefs.emplace_back(threeArgumentFunctionCall);
         });
         return threeArgumentFunctionCallRefs;
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class NonVoidThreeArgumentZenMocker : public ThreeArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type>, protected ValueReturner<FunctionReturnType>
   {
      friend class NonVoidThreeArgumentZenMockerTests;
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
      std::function<FunctionReturnType(Arg1Type, Arg2Type, Arg3Type)> _callInstead_nonVoidThreeArgFunction;
   public:
      explicit NonVoidThreeArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : ThreeArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      ~NonVoidThreeArgumentZenMocker()
      {
         if (_callInstead_nonVoidThreeArgFunction)
         {
            this->_wasAsserted = true;
         }
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         ThreeArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         ThreeArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         ThreeArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         ThreeArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type>::_wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::ZenMockAddRandomReturnValue();
         return randomReturnValue;
      }

      void CallInstead(const std::function<FunctionReturnType(Arg1Type, Arg2Type, Arg3Type)>& nonVoidThreeArgFunction)
      {
         ThreeArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type>::_wasExpected = true;
         this->_callInstead_nonVoidThreeArgFunction = nonVoidThreeArgFunction;
      }

      FunctionReturnType ZenMockItAndReturnValue(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument)
      {
         ThreeArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type>::ZenMockIt(firstArgument, secondArgument, thirdArgument);
         if (this->_callInstead_nonVoidThreeArgFunction)
         {
            const FunctionReturnType returnValue = this->_callInstead_nonVoidThreeArgFunction(firstArgument, secondArgument, thirdArgument);
            return returnValue;
         }
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class NonVoidThreeArgFunctionPointerZenMocker : public NonVoidThreeArgumentZenMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type>
   {
   public:
      explicit NonVoidThreeArgFunctionPointerZenMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidThreeArgumentZenMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type>(zenMockedFunctionSignature)
      {
      }

      static FunctionReturnType ZenMockItFunctionPointer(
         NonVoidThreeArgFunctionPointerZenMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument)
      {
         return functionMocker->ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class VoidThreeArgumentZenMocker : public ThreeArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type>
   {
   protected:
      std::function<void(Arg1Type, Arg2Type, Arg3Type)> _callInstead_voidThreeArgFunction;
   public:
      explicit VoidThreeArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : ThreeArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type>(zenMockedFunctionSignature)
      {
      }

      ~VoidThreeArgumentZenMocker()
      {
         if (_callInstead_voidThreeArgFunction)
         {
            this->_wasAsserted = true;
         }
      }

      void Expect()
      {
         ThreeArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type>::_wasExpected = true;
      }

      void CallInstead(const std::function<void(Arg1Type, Arg2Type, Arg3Type)>& voidThreeArgFunction)
      {
         ThreeArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type>::_wasExpected = true;
         this->_callInstead_voidThreeArgFunction = voidThreeArgFunction;
      }

      void ZenMockIt(const Arg1Type& firstArgument, const Arg2Type& secondArgument, const Arg3Type& thirdArgument) override
      {
         this->ZenMockThrowIfNotExpected(firstArgument, secondArgument, thirdArgument);
         this->zenMockedFunctionCallHistory.emplace_back(firstArgument, secondArgument, thirdArgument);
         if (this->_callInstead_voidThreeArgFunction)
         {
            this->_callInstead_voidThreeArgFunction(firstArgument, secondArgument, thirdArgument);
         }
         this->ZenMockThrowExceptionIfExceptionSet();
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class VoidThreeArgFunctionPointerZenMocker : public VoidThreeArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type>
   {
   public:
      explicit VoidThreeArgFunctionPointerZenMocker(const std::string& zenMockedFunctionSignature)
         : VoidThreeArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidThreeArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument)
      {
         functionMocker->ZenMockIt(firstArgument, secondArgument, thirdArgument);
      }
   };

   template<
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename Arg4Type,
      typename MockableExceptionThrowerType = ExceptionThrower>
   class FourArgumentZenMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class FourArgumentZenMockerTests;
   public:
      std::vector<FourArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>> zenMockedFunctionCallHistory;

      explicit FourArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument)
      {
         this->ZenMockThrowIfNotExpected(firstArgument, secondArgument, thirdArgument, fourthArgument);
         zenMockedFunctionCallHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument);
         this->ZenMockThrowExceptionIfExceptionSet();
      }

      FunctionSequencingToken CalledOnceWith(
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, zenMockedFunctionCallHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, zenMockedFunctionCallHistory[0].firstArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, zenMockedFunctionCallHistory[0].secondArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, zenMockedFunctionCallHistory[0].thirdArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, zenMockedFunctionCallHistory[0].fourthArgument.value, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, zenMockedFunctionCallHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex =
               ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, zenMockedFunctionCallHistory[i].firstArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, zenMockedFunctionCallHistory[i].secondArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, zenMockedFunctionCallHistory[i].thirdArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, zenMockedFunctionCallHistory[i].fourthArgument.value, zenMockedFunctionSignatureAndCallIndex);
         }
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(const std::vector<FourArgumentFunctionCallReference<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>& expectedFourArgumentFunctionCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedFourArgumentFunctionCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<FourArgumentFunctionCallReference<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
            actualFourArgumentFunctionCalls = PrivateCallsToCallRefs(zenMockedFunctionCallHistory);
         VECTORS_EQUAL(expectedFourArgumentFunctionCalls, actualFourArgumentFunctionCalls, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

   private:
      static std::vector<FourArgumentFunctionCallReference<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
         PrivateCallsToCallRefs(const std::vector<FourArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>& zenMockedFunctionCallHistory)
      {
         std::vector<FourArgumentFunctionCallReference<Arg1Type, Arg2Type, Arg3Type, Arg4Type>> fourArgumentFunctionCallRefs;
         fourArgumentFunctionCallRefs.reserve(zenMockedFunctionCallHistory.size());
         std::for_each(zenMockedFunctionCallHistory.cbegin(), zenMockedFunctionCallHistory.cend(),
            [&](const FourArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& fourArgumentFunctionCall)
         {
            fourArgumentFunctionCallRefs.emplace_back(fourArgumentFunctionCall);
         });
         return fourArgumentFunctionCallRefs;
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class NonVoidFourArgumentZenMocker : public FourArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>, protected ValueReturner<FunctionReturnType>
   {
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   public:
      explicit NonVoidFourArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : FourArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      virtual ~NonVoidFourArgumentZenMocker() = default;

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         FourArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         FourArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         FourArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         FourArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::_wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::ZenMockAddRandomReturnValue();
         return randomReturnValue;
      }

      virtual const FunctionReturnType& ZenMockItAndReturnValue(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument)
      {
         FourArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument);
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class NonVoidFourArgFunctionPointerZenMocker : public NonVoidFourArgumentZenMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>
   {
   public:
      explicit NonVoidFourArgFunctionPointerZenMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidFourArgumentZenMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>(zenMockedFunctionSignature)
      {
      }

      static const FunctionReturnType& ZenMockItFunctionPointer(
         NonVoidFourArgFunctionPointerZenMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument)
      {
         return functionMocker->ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class VoidFourArgumentZenMocker : public FourArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>
   {
   public:
      explicit VoidFourArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : FourArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>(zenMockedFunctionSignature)
      {
      }

      void Expect()
      {
         FourArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::_wasExpected = true;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class VoidFourArgFunctionPointerZenMocker : public VoidFourArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>
   {
   public:
      explicit VoidFourArgFunctionPointerZenMocker(const std::string& zenMockedFunctionSignature)
         : VoidFourArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidFourArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument)
      {
         functionMocker->ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument);
      }
   };

   template<
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename Arg4Type,
      typename Arg5Type,
      typename MockableExceptionThrowerType = ExceptionThrower>
   class FiveArgumentZenMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class FiveArgumentZenMockerTests;
   public:
      std::vector<FiveArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>> zenMockedFunctionCallHistory;

      explicit FiveArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument)
      {
         this->ZenMockThrowIfNotExpected(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument);
         zenMockedFunctionCallHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument);
         this->ZenMockThrowExceptionIfExceptionSet();
      }

      FunctionSequencingToken CalledOnceWith(
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument,
         const Arg5Type& expectedFifthArgument)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, zenMockedFunctionCallHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, zenMockedFunctionCallHistory[0].firstArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, zenMockedFunctionCallHistory[0].secondArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, zenMockedFunctionCallHistory[0].thirdArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, zenMockedFunctionCallHistory[0].fourthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFifthArgument, zenMockedFunctionCallHistory[0].fifthArgument.value, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument,
         const Arg5Type& expectedFifthArgument)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, zenMockedFunctionCallHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            std::string zenMockedFunctionSignatureAndCallIndex = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, zenMockedFunctionCallHistory[i].firstArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, zenMockedFunctionCallHistory[i].secondArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, zenMockedFunctionCallHistory[i].thirdArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, zenMockedFunctionCallHistory[i].fourthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFifthArgument, zenMockedFunctionCallHistory[i].fifthArgument.value, zenMockedFunctionSignatureAndCallIndex);
         }
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(const std::vector<FiveArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>& expectedFiveArgumentFunctionCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedFiveArgumentFunctionCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<FiveArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
            actualFiveArgumentFunctionCalls = PrivateCallsToCallRefs(zenMockedFunctionCallHistory);
         VECTORS_EQUAL(expectedFiveArgumentFunctionCalls, actualFiveArgumentFunctionCalls, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

   private:
      static std::vector<FiveArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
         PrivateCallsToCallRefs(const std::vector<FiveArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>& zenMockedFunctionCallHistory)
      {
         std::vector<FiveArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>> fiveArgumentFunctionCallRefs;
         fiveArgumentFunctionCallRefs.reserve(zenMockedFunctionCallHistory.size());
         std::for_each(zenMockedFunctionCallHistory.cbegin(), zenMockedFunctionCallHistory.cend(),
            [&](const FiveArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& fiveArgumentFunctionCall)
         {
            fiveArgumentFunctionCallRefs.emplace_back(fiveArgumentFunctionCall);
         });
         return fiveArgumentFunctionCallRefs;
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   class NonVoidFiveArgumentZenMocker : public FiveArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>, protected ValueReturner<FunctionReturnType>
   {
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   public:
      explicit NonVoidFiveArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : FiveArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         FiveArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         FiveArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         FiveArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         FiveArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::_wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::ZenMockAddRandomReturnValue();
         return randomReturnValue;
      }

      const FunctionReturnType& ZenMockItAndReturnValue(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument)
      {
         FiveArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument);
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   class NonVoidFiveArgFunctionPointerZenMocker : public NonVoidFiveArgumentZenMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>
   {
   public:
      explicit NonVoidFiveArgFunctionPointerZenMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidFiveArgumentZenMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>(zenMockedFunctionSignature)
      {
      }

      static const FunctionReturnType& ZenMockItFunctionPointer(
         NonVoidFiveArgFunctionPointerZenMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument)
      {
         return functionMocker->ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   class VoidFiveArgumentZenMocker : public FiveArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>
   {
   public:
      explicit VoidFiveArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : FiveArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>(zenMockedFunctionSignature)
      {
      }

      void Expect()
      {
         FiveArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::_wasExpected = true;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   class VoidFiveArgFunctionPointerZenMocker : public VoidFiveArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>
   {
   public:
      explicit VoidFiveArgFunctionPointerZenMocker(const std::string& zenMockedFunctionSignature)
         : VoidFiveArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidFiveArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument)
      {
         functionMocker->ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument);
      }
   };

   template<
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename Arg4Type,
      typename Arg5Type,
      typename Arg6Type,
      typename MockableExceptionThrowerType = ExceptionThrower>
   class SixArgumentZenMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class SixArgumentZenMockerTests;
   public:
      std::vector<SixArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>> zenMockedFunctionCallHistory;

      explicit SixArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument,
         const Arg6Type& sixthArgument)
      {
         this->ZenMockThrowIfNotExpected(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument);
         zenMockedFunctionCallHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument);
         this->ZenMockThrowExceptionIfExceptionSet();
      }

      FunctionSequencingToken CalledOnceWith(
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument,
         const Arg5Type& expectedFifthArgument,
         const Arg6Type& expectedSixthArgument)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, zenMockedFunctionCallHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, zenMockedFunctionCallHistory[0].firstArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, zenMockedFunctionCallHistory[0].secondArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, zenMockedFunctionCallHistory[0].thirdArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, zenMockedFunctionCallHistory[0].fourthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFifthArgument, zenMockedFunctionCallHistory[0].fifthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSixthArgument, zenMockedFunctionCallHistory[0].sixthArgument.value, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument,
         const Arg5Type& expectedFifthArgument,
         const Arg6Type& expectedSixthArgument)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, zenMockedFunctionCallHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex =
               ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, zenMockedFunctionCallHistory[i].firstArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, zenMockedFunctionCallHistory[i].secondArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, zenMockedFunctionCallHistory[i].thirdArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, zenMockedFunctionCallHistory[i].fourthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFifthArgument, zenMockedFunctionCallHistory[i].fifthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSixthArgument, zenMockedFunctionCallHistory[i].sixthArgument.value, zenMockedFunctionSignatureAndCallIndex);
         }
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(const std::vector<SixArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>& expectedSixArgumentFunctionCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedSixArgumentFunctionCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<SixArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
            actualSixArgumentFunctionCalls = PrivateCallsToCallRefs(zenMockedFunctionCallHistory);
         VECTORS_EQUAL(expectedSixArgumentFunctionCalls, actualSixArgumentFunctionCalls, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

   private:
      static std::vector<SixArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
         PrivateCallsToCallRefs(const std::vector<SixArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>& zenMockedFunctionCallHistory)
      {
         std::vector<SixArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>> sixArgumentFunctionCallRefs;
         sixArgumentFunctionCallRefs.reserve(zenMockedFunctionCallHistory.size());
         std::for_each(zenMockedFunctionCallHistory.cbegin(), zenMockedFunctionCallHistory.cend(),
            [&](const SixArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& sixArgumentFunctionCall)
         {
            sixArgumentFunctionCallRefs.emplace_back(sixArgumentFunctionCall);
         });
         return sixArgumentFunctionCallRefs;
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   class NonVoidSixArgumentZenMocker : public SixArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>, protected ValueReturner<FunctionReturnType>
   {
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   public:
      explicit NonVoidSixArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : SixArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         SixArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         SixArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         SixArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         SixArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>::_wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::ZenMockAddRandomReturnValue();
         return randomReturnValue;
      }

      const FunctionReturnType& ZenMockItAndReturnValue(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument)
      {
         SixArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ExceptionThrower>::ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument);
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   class NonVoidSixArgFunctionPointerZenMocker : public NonVoidSixArgumentZenMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>
   {
   public:
      explicit NonVoidSixArgFunctionPointerZenMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidSixArgumentZenMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>(zenMockedFunctionSignature)
      {
      }

      static const FunctionReturnType& ZenMockItFunctionPointer(
         NonVoidSixArgFunctionPointerZenMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument)
      {
         return functionMocker->ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   class VoidSixArgumentZenMocker : public SixArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>
   {
   public:
      explicit VoidSixArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : SixArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>(zenMockedFunctionSignature)
      {
      }

      void Expect()
      {
         SixArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>::_wasExpected = true;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   class VoidSixArgFunctionPointerZenMocker : public VoidSixArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>
   {
   public:
      explicit VoidSixArgFunctionPointerZenMocker(const std::string& zenMockedFunctionSignature)
         : VoidSixArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidSixArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument)
      {
         functionMocker->ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument);
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
      typename MockableExceptionThrowerType = ExceptionThrower>
   class SevenArgumentZenMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class SevenArgumentZenMockerTests;
   public:
      std::vector<SevenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>> zenMockedFunctionCallHistory;

      explicit SevenArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument,
         const Arg6Type& sixthArgument,
         const Arg7Type& seventhArgument)
      {
         this->ZenMockThrowIfNotExpected(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument);
         zenMockedFunctionCallHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument);
         this->ZenMockThrowExceptionIfExceptionSet();
      }

      FunctionSequencingToken CalledOnceWith(
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument,
         const Arg5Type& expectedFifthArgument,
         const Arg6Type& expectedSixthArgument,
         const Arg7Type& expectedSeventhArgument)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, zenMockedFunctionCallHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, zenMockedFunctionCallHistory[0].firstArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, zenMockedFunctionCallHistory[0].secondArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, zenMockedFunctionCallHistory[0].thirdArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, zenMockedFunctionCallHistory[0].fourthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFifthArgument, zenMockedFunctionCallHistory[0].fifthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSixthArgument, zenMockedFunctionCallHistory[0].sixthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSeventhArgument, zenMockedFunctionCallHistory[0].seventhArgument.value, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument,
         const Arg5Type& expectedFifthArgument,
         const Arg6Type& expectedSixthArgument,
         const Arg7Type& expectedSeventhArgument)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, zenMockedFunctionCallHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex =
               ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, zenMockedFunctionCallHistory[i].firstArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, zenMockedFunctionCallHistory[i].secondArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, zenMockedFunctionCallHistory[i].thirdArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, zenMockedFunctionCallHistory[i].fourthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFifthArgument, zenMockedFunctionCallHistory[i].fifthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSixthArgument, zenMockedFunctionCallHistory[i].sixthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSeventhArgument, zenMockedFunctionCallHistory[i].seventhArgument.value, zenMockedFunctionSignatureAndCallIndex);
         }
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(const std::vector<SevenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>& expectedSevenArgumentFunctionCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedSevenArgumentFunctionCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<SevenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
            actualSevenArgumentFunctionCalls = PrivateCallsToCallRefs(zenMockedFunctionCallHistory);
         VECTORS_EQUAL(expectedSevenArgumentFunctionCalls, actualSevenArgumentFunctionCalls, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

   private:
      static std::vector<SevenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
         PrivateCallsToCallRefs(const std::vector<SevenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>& zenMockedFunctionCallHistory)
      {
         std::vector<SevenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>> sevenArgumentFunctionCallRefs;
         sevenArgumentFunctionCallRefs.reserve(zenMockedFunctionCallHistory.size());
         std::for_each(zenMockedFunctionCallHistory.cbegin(), zenMockedFunctionCallHistory.cend(),
            [&](const SevenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& sevenArgumentFunctionCall)
         {
            sevenArgumentFunctionCallRefs.emplace_back(sevenArgumentFunctionCall);
         });
         return sevenArgumentFunctionCallRefs;
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   class NonVoidSevenArgumentZenMocker : public SevenArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ExceptionThrower>, protected ValueReturner<FunctionReturnType>
   {
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   public:
      explicit NonVoidSevenArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : SevenArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         SevenArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         SevenArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         SevenArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         SevenArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ExceptionThrower>::_wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::ZenMockAddRandomReturnValue();
         return randomReturnValue;
      }

      const FunctionReturnType& ZenMockItAndReturnValue(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument)
      {
         SevenArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>::ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument);
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   class NonVoidSevenArgFunctionPointerZenMocker : public NonVoidSevenArgumentZenMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>
   {
   public:
      explicit NonVoidSevenArgFunctionPointerZenMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidSevenArgumentZenMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>(zenMockedFunctionSignature)
      {
      }

      static const FunctionReturnType& ZenMockItFunctionPointer(
         NonVoidSevenArgFunctionPointerZenMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument)
      {
         return functionMocker->ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   class VoidSevenArgumentZenMocker : public SevenArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ExceptionThrower>
   {
   public:
      explicit VoidSevenArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : SevenArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>(zenMockedFunctionSignature)
      {
      }

      void Expect()
      {
         SevenArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ExceptionThrower>::_wasExpected = true;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   class VoidSevenArgFunctionPointerZenMocker : public VoidSevenArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>
   {
   public:
      explicit VoidSevenArgFunctionPointerZenMocker(const std::string& zenMockedFunctionSignature)
         : VoidSevenArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidSevenArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument)
      {
         functionMocker->ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument);
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
      typename MockableExceptionThrowerType = ExceptionThrower>
   class EightArgumentZenMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class EightArgumentZenMockerTests;
   public:
      std::vector<EightArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>> zenMockedFunctionCallHistory;

      explicit EightArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument,
         const Arg6Type& sixthArgument,
         const Arg7Type& seventhArgument,
         const Arg8Type& eigthArgument)
      {
         this->ZenMockThrowIfNotExpected(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument);
         zenMockedFunctionCallHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument);
         this->ZenMockThrowExceptionIfExceptionSet();
      }

      FunctionSequencingToken CalledOnceWith(
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument,
         const Arg5Type& expectedFifthArgument,
         const Arg6Type& expectedSixthArgument,
         const Arg7Type& expectedSeventhArgument,
         const Arg8Type& expectedEigthArgument)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, zenMockedFunctionCallHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, zenMockedFunctionCallHistory[0].firstArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, zenMockedFunctionCallHistory[0].secondArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, zenMockedFunctionCallHistory[0].thirdArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, zenMockedFunctionCallHistory[0].fourthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFifthArgument, zenMockedFunctionCallHistory[0].fifthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSixthArgument, zenMockedFunctionCallHistory[0].sixthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSeventhArgument, zenMockedFunctionCallHistory[0].seventhArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedEigthArgument, zenMockedFunctionCallHistory[0].eigthArgument.value, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument,
         const Arg5Type& expectedFifthArgument,
         const Arg6Type& expectedSixthArgument,
         const Arg7Type& expectedSeventhArgument,
         const Arg8Type& expectedEigthArgument)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, zenMockedFunctionCallHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex =
               ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, zenMockedFunctionCallHistory[i].firstArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, zenMockedFunctionCallHistory[i].secondArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, zenMockedFunctionCallHistory[i].thirdArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, zenMockedFunctionCallHistory[i].fourthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFifthArgument, zenMockedFunctionCallHistory[i].fifthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSixthArgument, zenMockedFunctionCallHistory[i].sixthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSeventhArgument, zenMockedFunctionCallHistory[i].seventhArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedEigthArgument, zenMockedFunctionCallHistory[i].eigthArgument.value, zenMockedFunctionSignatureAndCallIndex);
         }
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(const std::vector<EightArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>>& expectedEightArgumentFunctionCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedEightArgumentFunctionCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<EightArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
            actualEightArgumentFunctionCalls = PrivateCallsToCallRefs(zenMockedFunctionCallHistory);
         VECTORS_EQUAL(expectedEightArgumentFunctionCalls, actualEightArgumentFunctionCalls, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

   private:
      static std::vector<EightArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
         PrivateCallsToCallRefs(const std::vector<EightArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>>& zenMockedFunctionCallHistory)
      {
         std::vector<EightArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>> eightArgumentFunctionCallRefs;
         eightArgumentFunctionCallRefs.reserve(zenMockedFunctionCallHistory.size());
         std::for_each(zenMockedFunctionCallHistory.cbegin(), zenMockedFunctionCallHistory.cend(),
            [&](const EightArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& eightArgumentFunctionCall)
         {
            eightArgumentFunctionCallRefs.emplace_back(eightArgumentFunctionCall);
         });
         return eightArgumentFunctionCallRefs;
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
   class NonVoidEightArgumentZenMocker : public EightArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ExceptionThrower>, protected ValueReturner<FunctionReturnType>
   {
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   public:
      explicit NonVoidEightArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : EightArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         EightArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         EightArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         EightArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         EightArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ExceptionThrower>::_wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::ZenMockAddRandomReturnValue();
         return randomReturnValue;
      }

      const FunctionReturnType& ZenMockItAndReturnValue(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument)
      {
         EightArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>::ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument);
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
   class NonVoidEightArgFunctionPointerZenMocker : public NonVoidEightArgumentZenMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>
   {
   public:
      explicit NonVoidEightArgFunctionPointerZenMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidEightArgumentZenMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>(zenMockedFunctionSignature)
      {
      }

      static const FunctionReturnType& ZenMockItFunctionPointer(
         NonVoidEightArgFunctionPointerZenMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument)
      {
         return functionMocker->ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
   class VoidEightArgumentZenMocker : public EightArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ExceptionThrower>
   {
   public:
      explicit VoidEightArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : EightArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>(zenMockedFunctionSignature)
      {
      }

      void Expect()
      {
         EightArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ExceptionThrower>::_wasExpected = true;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
   class VoidEightArgFunctionPointerZenMocker : public VoidEightArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>
   {
   public:
      explicit VoidEightArgFunctionPointerZenMocker(const std::string& zenMockedFunctionSignature)
         : VoidEightArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidEightArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument)
      {
         functionMocker->ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument);
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
      typename MockableExceptionThrowerType = ExceptionThrower>
   class NineArgumentZenMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class NineArgumentZenMockerTests;
   public:
      std::vector<NineArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>> zenMockedFunctionCallHistory;

      explicit NineArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument,
         const Arg6Type& sixthArgument,
         const Arg7Type& seventhArgument,
         const Arg8Type& eigthArgument,
         const Arg9Type& ninthArgument)
      {
         this->ZenMockThrowIfNotExpected(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument);
         zenMockedFunctionCallHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument);
         this->ZenMockThrowExceptionIfExceptionSet();
      }

      FunctionSequencingToken CalledOnceWith(
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument,
         const Arg5Type& expectedFifthArgument,
         const Arg6Type& expectedSixthArgument,
         const Arg7Type& expectedSeventhArgument,
         const Arg8Type& expectedEigthArgument,
         const Arg9Type& expectedNinthArgument)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, zenMockedFunctionCallHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, zenMockedFunctionCallHistory[0].firstArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, zenMockedFunctionCallHistory[0].secondArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, zenMockedFunctionCallHistory[0].thirdArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, zenMockedFunctionCallHistory[0].fourthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFifthArgument, zenMockedFunctionCallHistory[0].fifthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSixthArgument, zenMockedFunctionCallHistory[0].sixthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSeventhArgument, zenMockedFunctionCallHistory[0].seventhArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedEigthArgument, zenMockedFunctionCallHistory[0].eigthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedNinthArgument, zenMockedFunctionCallHistory[0].ninthArgument.value, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument,
         const Arg5Type& expectedFifthArgument,
         const Arg6Type& expectedSixthArgument,
         const Arg7Type& expectedSeventhArgument,
         const Arg8Type& expectedEigthArgument,
         const Arg9Type& expectedNinthArgument)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, zenMockedFunctionCallHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex =
               ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, zenMockedFunctionCallHistory[i].firstArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, zenMockedFunctionCallHistory[i].secondArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, zenMockedFunctionCallHistory[i].thirdArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, zenMockedFunctionCallHistory[i].fourthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFifthArgument, zenMockedFunctionCallHistory[i].fifthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSixthArgument, zenMockedFunctionCallHistory[i].sixthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSeventhArgument, zenMockedFunctionCallHistory[i].seventhArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedEigthArgument, zenMockedFunctionCallHistory[i].eigthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedNinthArgument, zenMockedFunctionCallHistory[i].ninthArgument.value, zenMockedFunctionSignatureAndCallIndex);
         }
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(const std::vector<NineArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>& expectedNineArgumentFunctionCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedNineArgumentFunctionCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<NineArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
            actualNineArgumentFunctionCalls = PrivateCallsToCallRefs(zenMockedFunctionCallHistory);
         VECTORS_EQUAL(expectedNineArgumentFunctionCalls, actualNineArgumentFunctionCalls, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

   private:
      static std::vector<NineArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
         PrivateCallsToCallRefs(const std::vector<NineArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>& zenMockedFunctionCallHistory)
      {
         std::vector<NineArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>> nineArgumentFunctionCallRefs;
         nineArgumentFunctionCallRefs.reserve(zenMockedFunctionCallHistory.size());
         std::for_each(zenMockedFunctionCallHistory.cbegin(), zenMockedFunctionCallHistory.cend(),
            [&](const NineArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& nineArgumentFunctionCall)
         {
            nineArgumentFunctionCallRefs.emplace_back(nineArgumentFunctionCall);
         });
         return nineArgumentFunctionCallRefs;
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
   class NonVoidNineArgumentZenMocker : public NineArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ExceptionThrower>, protected ValueReturner<FunctionReturnType>
   {
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   public:
      explicit NonVoidNineArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : NineArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         NineArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         NineArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         NineArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         NineArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ExceptionThrower>::_wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::ZenMockAddRandomReturnValue();
         return randomReturnValue;
      }

      const FunctionReturnType& ZenMockItAndReturnValue(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument, Arg9Type ninthArgument)
      {
         NineArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>::ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument);
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
   class NonVoidNineArgFunctionPointerZenMocker : public NonVoidNineArgumentZenMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>
   {
   public:
      explicit NonVoidNineArgFunctionPointerZenMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidNineArgumentZenMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>(zenMockedFunctionSignature)
      {
      }

      static const FunctionReturnType& ZenMockItFunctionPointer(
         NonVoidNineArgFunctionPointerZenMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument, Arg9Type ninthArgument)
      {
         return functionMocker->ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
   class VoidNineArgumentZenMocker : public NineArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ExceptionThrower>
   {
   public:
      explicit VoidNineArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : NineArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>(zenMockedFunctionSignature)
      {
      }

      void Expect()
      {
         NineArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ExceptionThrower>::_wasExpected = true;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
   class VoidNineArgFunctionPointerZenMocker : public VoidNineArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>
   {
   public:
      explicit VoidNineArgFunctionPointerZenMocker(const std::string& zenMockedFunctionSignature)
         : VoidNineArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidNineArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument, Arg9Type ninthArgument)
      {
         functionMocker->ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument);
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
      typename Arg10Type,
      typename MockableExceptionThrowerType = ExceptionThrower>
   class TenArgumentZenMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class TenArgumentZenMockerTests;
   public:
      std::vector<TenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>> zenMockedFunctionCallHistory;

      explicit TenArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument,
         const Arg6Type& sixthArgument,
         const Arg7Type& seventhArgument,
         const Arg8Type& eigthArgument,
         const Arg9Type& ninthArgument,
         const Arg10Type& tenthArgument)
      {
         this->ZenMockThrowIfNotExpected(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument, tenthArgument);
         zenMockedFunctionCallHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument, tenthArgument);
         this->ZenMockThrowExceptionIfExceptionSet();
      }

      FunctionSequencingToken CalledOnceWith(
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument,
         const Arg5Type& expectedFifthArgument,
         const Arg6Type& expectedSixthArgument,
         const Arg7Type& expectedSeventhArgument,
         const Arg8Type& expectedEigthArgument,
         const Arg9Type& expectedNinthArgument,
         const Arg10Type& expectedTenthArgument)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, zenMockedFunctionCallHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, zenMockedFunctionCallHistory[0].firstArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, zenMockedFunctionCallHistory[0].secondArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, zenMockedFunctionCallHistory[0].thirdArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, zenMockedFunctionCallHistory[0].fourthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFifthArgument, zenMockedFunctionCallHistory[0].fifthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSixthArgument, zenMockedFunctionCallHistory[0].sixthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSeventhArgument, zenMockedFunctionCallHistory[0].seventhArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedEigthArgument, zenMockedFunctionCallHistory[0].eigthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedNinthArgument, zenMockedFunctionCallHistory[0].ninthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedTenthArgument, zenMockedFunctionCallHistory[0].tenthArgument.value, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument,
         const Arg5Type& expectedFifthArgument,
         const Arg6Type& expectedSixthArgument,
         const Arg7Type& expectedSeventhArgument,
         const Arg8Type& expectedEigthArgument,
         const Arg9Type& expectedNinthArgument,
         const Arg10Type& expectedTenthArgument)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, zenMockedFunctionCallHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex =
               ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, zenMockedFunctionCallHistory[i].firstArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, zenMockedFunctionCallHistory[i].secondArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, zenMockedFunctionCallHistory[i].thirdArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, zenMockedFunctionCallHistory[i].fourthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFifthArgument, zenMockedFunctionCallHistory[i].fifthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSixthArgument, zenMockedFunctionCallHistory[i].sixthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSeventhArgument, zenMockedFunctionCallHistory[i].seventhArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedEigthArgument, zenMockedFunctionCallHistory[i].eigthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedNinthArgument, zenMockedFunctionCallHistory[i].ninthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedTenthArgument, zenMockedFunctionCallHistory[i].tenthArgument.value, zenMockedFunctionSignatureAndCallIndex);
         }
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(const std::vector<TenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>& expectedTenArgumentFunctionCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedTenArgumentFunctionCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<TenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>
            actualTenArgumentFunctionCalls = PrivateCallsToCallRefs(zenMockedFunctionCallHistory);
         VECTORS_EQUAL(expectedTenArgumentFunctionCalls, actualTenArgumentFunctionCalls, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

   private:
      static std::vector<TenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>
         PrivateCallsToCallRefs(const std::vector<TenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>& zenMockedFunctionCallHistory)
      {
         std::vector<TenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>> tenArgumentFunctionCallRefs;
         tenArgumentFunctionCallRefs.reserve(zenMockedFunctionCallHistory.size());
         std::for_each(zenMockedFunctionCallHistory.cbegin(), zenMockedFunctionCallHistory.cend(),
            [&](const TenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& tenArgumentFunctionCall)
         {
            tenArgumentFunctionCallRefs.emplace_back(tenArgumentFunctionCall);
         });
         return tenArgumentFunctionCallRefs;
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
   class NonVoidTenArgumentZenMocker : public TenArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ExceptionThrower>, protected ValueReturner<FunctionReturnType>
   {
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   public:
      explicit NonVoidTenArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : TenArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         TenArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         TenArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         TenArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         TenArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ExceptionThrower>::_wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::ZenMockAddRandomReturnValue();
         return randomReturnValue;
      }

      const FunctionReturnType& ZenMockItAndReturnValue(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument, Arg9Type ninthArgument, Arg10Type tenthArgument)
      {
         TenArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>::ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument, tenthArgument);
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
   class NonVoidTenArgFunctionPointerZenMocker : public NonVoidTenArgumentZenMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>
   {
   public:
      explicit NonVoidTenArgFunctionPointerZenMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidTenArgumentZenMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(zenMockedFunctionSignature) {}

      static const FunctionReturnType& ZenMockItFunctionPointer(
         NonVoidTenArgFunctionPointerZenMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument, Arg9Type ninthArgument, Arg10Type tenthArgument)
      {
         return functionMocker->ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument, tenthArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
   class VoidTenArgumentZenMocker : public TenArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ExceptionThrower>
   {
   public:
      explicit VoidTenArgumentZenMocker(const std::string& zenMockedFunctionSignature)
         : TenArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(zenMockedFunctionSignature) {}

      void Expect()
      {
         TenArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ExceptionThrower>::_wasExpected = true;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
   class VoidTenArgFunctionPointerZenMocker : public VoidTenArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>
   {
   public:
      explicit VoidTenArgFunctionPointerZenMocker(const std::string& zenMockedFunctionSignature)
         : VoidTenArgumentZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(zenMockedFunctionSignature) {}

      static void ZenMockItFunctionPointer(
         VoidTenArgFunctionPointerZenMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument, Arg9Type ninthArgument, Arg10Type tenthArgument)
      {
         functionMocker->ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument, tenthArgument);
      }
   };

   class FunctionSignature
   {
   public:
      static std::string Function(
         const char* virtualOrEmptyString,
         const char* returnType,
         const std::string* zenMockedClassName,
         //   Adorned function signature: "virtual int FunctionName(int) const"
         // Unadorned function signature: "FunctionName(int)"
         const char* unadornedFunctionSignature,
         const char* constOrEmptyString)
      {
         std::ostringstream builder;
         if (strlen(virtualOrEmptyString) > 0)
         {
            builder << virtualOrEmptyString << " ";
         }
         builder << returnType << ' ' << *zenMockedClassName << "::" << unadornedFunctionSignature;
         if (strlen(constOrEmptyString) > 0)
         {
            builder << ' ' << constOrEmptyString;
         }
         const std::string zenMockedFunctionSignature = builder.str();
         return zenMockedFunctionSignature;
      }

      static std::string FunctionPointer(const char* returnType, const char* unadornedFunctionSignature)
      {
         const std::string zenMockedFunctionPointerSignature = ZenUnit::String::Concat(returnType, " ", unadornedFunctionSignature);
         return zenMockedFunctionPointerSignature;
      }
   };
}

namespace ZenUnit
{
   template<typename ArgType>
   class Equalizer<ZenMock::OneArgumentFunctionCall<ArgType>>
   {
   public:
      static void AssertEqual(
         const ZenMock::OneArgumentFunctionCall<ArgType>& expectedOneArgumentFunctionCall,
         const ZenMock::OneArgumentFunctionCall<ArgType>& actualOneArgumentFunctionCall)
      {
         ARE_EQUAL(expectedOneArgumentFunctionCall.argument.value, actualOneArgumentFunctionCall.argument.value);
      }
   };

   template<typename ArgType>
   class Equalizer<ZenMock::OneArgumentFunctionCallReference<ArgType>>
   {
   public:
      static void AssertEqual(
         const ZenMock::OneArgumentFunctionCallReference<ArgType>& expectedOneArgumentFunctionCall,
         const ZenMock::OneArgumentFunctionCallReference<ArgType>& actualOneArgumentFunctionCall)
      {
         ARE_EQUAL(expectedOneArgumentFunctionCall.argumentReference.value, actualOneArgumentFunctionCall.argumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type>
   class Equalizer<ZenMock::TwoArgumentFunctionCall<Arg1Type, Arg2Type>>
   {
   public:
      static void AssertEqual(
         const ZenMock::TwoArgumentFunctionCall<Arg1Type, Arg2Type>& expectedTwoArgumentFunctionCall,
         const ZenMock::TwoArgumentFunctionCall<Arg1Type, Arg2Type>& actualTwoArgumentFunctionCall)
      {
         ARE_EQUAL(expectedTwoArgumentFunctionCall.firstArgument.value, actualTwoArgumentFunctionCall.firstArgument.value);
         ARE_EQUAL(expectedTwoArgumentFunctionCall.secondArgument.value, actualTwoArgumentFunctionCall.secondArgument.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type>
   class Equalizer<ZenMock::TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>>
   {
   public:
      static void AssertEqual(
         const ZenMock::TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>& expectedTwoArgumentFunctionCall,
         const ZenMock::TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>& actualTwoArgumentFunctionCall)
      {
         ARE_EQUAL(expectedTwoArgumentFunctionCall.firstArgumentReference.value, actualTwoArgumentFunctionCall.firstArgumentReference.value);
         ARE_EQUAL(expectedTwoArgumentFunctionCall.secondArgumentReference.value, actualTwoArgumentFunctionCall.secondArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class Equalizer<ZenMock::ThreeArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type>>
   {
   public:
      static void AssertEqual(
         const ZenMock::ThreeArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type>& expectedThreeArgumentFunctionCall,
         const ZenMock::ThreeArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type>& actualThreeArgumentFunctionCall)
      {
         ARE_EQUAL(expectedThreeArgumentFunctionCall.firstArgument.value, actualThreeArgumentFunctionCall.firstArgument.value);
         ARE_EQUAL(expectedThreeArgumentFunctionCall.secondArgument.value, actualThreeArgumentFunctionCall.secondArgument.value);
         ARE_EQUAL(expectedThreeArgumentFunctionCall.thirdArgument.value, actualThreeArgumentFunctionCall.thirdArgument.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class Equalizer<ZenMock::ThreeArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type>>
   {
   public:
      static void AssertEqual(
         const ZenMock::ThreeArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type>& expectedThreeArgumentFunctionCall,
         const ZenMock::ThreeArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type>& actualThreeArgumentFunctionCall)
      {
         ARE_EQUAL(expectedThreeArgumentFunctionCall.firstArgumentReference.value, actualThreeArgumentFunctionCall.firstArgumentReference.value);
         ARE_EQUAL(expectedThreeArgumentFunctionCall.secondArgumentReference.value, actualThreeArgumentFunctionCall.secondArgumentReference.value);
         ARE_EQUAL(expectedThreeArgumentFunctionCall.thirdArgumentReference.value, actualThreeArgumentFunctionCall.thirdArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class Equalizer<ZenMock::FourArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
   {
   public:
      static void AssertEqual(
         const ZenMock::FourArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& expectedFourArgumentFunctionCall,
         const ZenMock::FourArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& actualFourArgumentFunctionCall)
      {
         ARE_EQUAL(expectedFourArgumentFunctionCall.firstArgument.value, actualFourArgumentFunctionCall.firstArgument.value);
         ARE_EQUAL(expectedFourArgumentFunctionCall.secondArgument.value, actualFourArgumentFunctionCall.secondArgument.value);
         ARE_EQUAL(expectedFourArgumentFunctionCall.thirdArgument.value, actualFourArgumentFunctionCall.thirdArgument.value);
         ARE_EQUAL(expectedFourArgumentFunctionCall.fourthArgument.value, actualFourArgumentFunctionCall.fourthArgument.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class Equalizer<ZenMock::FourArgumentFunctionCallReference<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
   {
   public:
      static void AssertEqual(
         const ZenMock::FourArgumentFunctionCallReference<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& expectedFourArgumentFunctionCall,
         const ZenMock::FourArgumentFunctionCallReference<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& actualFourArgumentFunctionCall)
      {
         ARE_EQUAL(expectedFourArgumentFunctionCall.firstArgumentReference.value, actualFourArgumentFunctionCall.firstArgumentReference.value);
         ARE_EQUAL(expectedFourArgumentFunctionCall.secondArgumentReference.value, actualFourArgumentFunctionCall.secondArgumentReference.value);
         ARE_EQUAL(expectedFourArgumentFunctionCall.thirdArgumentReference.value, actualFourArgumentFunctionCall.thirdArgumentReference.value);
         ARE_EQUAL(expectedFourArgumentFunctionCall.fourthArgumentReference.value, actualFourArgumentFunctionCall.fourthArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   class Equalizer<ZenMock::FiveArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
   {
   public:
      static void AssertEqual(
         const ZenMock::FiveArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& expectedFiveArgumentFunctionCall,
         const ZenMock::FiveArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& actualFiveArgumentFunctionCall)
      {
         ARE_EQUAL(expectedFiveArgumentFunctionCall.firstArgument.value, actualFiveArgumentFunctionCall.firstArgument.value);
         ARE_EQUAL(expectedFiveArgumentFunctionCall.secondArgument.value, actualFiveArgumentFunctionCall.secondArgument.value);
         ARE_EQUAL(expectedFiveArgumentFunctionCall.thirdArgument.value, actualFiveArgumentFunctionCall.thirdArgument.value);
         ARE_EQUAL(expectedFiveArgumentFunctionCall.fourthArgument.value, actualFiveArgumentFunctionCall.fourthArgument.value);
         ARE_EQUAL(expectedFiveArgumentFunctionCall.fifthArgument.value, actualFiveArgumentFunctionCall.fifthArgument.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   class Equalizer<ZenMock::FiveArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
   {
   public:
      static void AssertEqual(
         const ZenMock::FiveArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& expectedFiveArgumentFunctionCall,
         const ZenMock::FiveArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& actualFiveArgumentFunctionCall)
      {
         ARE_EQUAL(expectedFiveArgumentFunctionCall.firstArgumentReference.value, actualFiveArgumentFunctionCall.firstArgumentReference.value);
         ARE_EQUAL(expectedFiveArgumentFunctionCall.secondArgumentReference.value, actualFiveArgumentFunctionCall.secondArgumentReference.value);
         ARE_EQUAL(expectedFiveArgumentFunctionCall.thirdArgumentReference.value, actualFiveArgumentFunctionCall.thirdArgumentReference.value);
         ARE_EQUAL(expectedFiveArgumentFunctionCall.fourthArgumentReference.value, actualFiveArgumentFunctionCall.fourthArgumentReference.value);
         ARE_EQUAL(expectedFiveArgumentFunctionCall.fifthArgumentReference.value, actualFiveArgumentFunctionCall.fifthArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   class Equalizer<ZenMock::SixArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
   {
   public:
      static void AssertEqual(
         const ZenMock::SixArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& expectedSixArgumentFunctionCall,
         const ZenMock::SixArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& actualSixArgumentFunctionCall)
      {
         ARE_EQUAL(expectedSixArgumentFunctionCall.firstArgument.value, actualSixArgumentFunctionCall.firstArgument.value);
         ARE_EQUAL(expectedSixArgumentFunctionCall.secondArgument.value, actualSixArgumentFunctionCall.secondArgument.value);
         ARE_EQUAL(expectedSixArgumentFunctionCall.thirdArgument.value, actualSixArgumentFunctionCall.thirdArgument.value);
         ARE_EQUAL(expectedSixArgumentFunctionCall.fourthArgument.value, actualSixArgumentFunctionCall.fourthArgument.value);
         ARE_EQUAL(expectedSixArgumentFunctionCall.fifthArgument.value, actualSixArgumentFunctionCall.fifthArgument.value);
         ARE_EQUAL(expectedSixArgumentFunctionCall.sixthArgument.value, actualSixArgumentFunctionCall.sixthArgument.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   class Equalizer<ZenMock::SixArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
   {
   public:
      static void AssertEqual(
         const ZenMock::SixArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& expectedSixArgumentFunctionCall,
         const ZenMock::SixArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& actualSixArgumentFunctionCall)
      {
         ARE_EQUAL(expectedSixArgumentFunctionCall.firstArgumentReference.value, actualSixArgumentFunctionCall.firstArgumentReference.value);
         ARE_EQUAL(expectedSixArgumentFunctionCall.secondArgumentReference.value, actualSixArgumentFunctionCall.secondArgumentReference.value);
         ARE_EQUAL(expectedSixArgumentFunctionCall.thirdArgumentReference.value, actualSixArgumentFunctionCall.thirdArgumentReference.value);
         ARE_EQUAL(expectedSixArgumentFunctionCall.fourthArgumentReference.value, actualSixArgumentFunctionCall.fourthArgumentReference.value);
         ARE_EQUAL(expectedSixArgumentFunctionCall.fifthArgumentReference.value, actualSixArgumentFunctionCall.fifthArgumentReference.value);
         ARE_EQUAL(expectedSixArgumentFunctionCall.sixthArgumentReference.value, actualSixArgumentFunctionCall.sixthArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   class Equalizer<ZenMock::SevenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
   {
   public:
      static void AssertEqual(
         const ZenMock::SevenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& expectedSevenArgumentFunctionCall,
         const ZenMock::SevenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& actualSevenArgumentFunctionCall)
      {
         ARE_EQUAL(expectedSevenArgumentFunctionCall.firstArgument.value, actualSevenArgumentFunctionCall.firstArgument.value);
         ARE_EQUAL(expectedSevenArgumentFunctionCall.secondArgument.value, actualSevenArgumentFunctionCall.secondArgument.value);
         ARE_EQUAL(expectedSevenArgumentFunctionCall.thirdArgument.value, actualSevenArgumentFunctionCall.thirdArgument.value);
         ARE_EQUAL(expectedSevenArgumentFunctionCall.fourthArgument.value, actualSevenArgumentFunctionCall.fourthArgument.value);
         ARE_EQUAL(expectedSevenArgumentFunctionCall.fifthArgument.value, actualSevenArgumentFunctionCall.fifthArgument.value);
         ARE_EQUAL(expectedSevenArgumentFunctionCall.sixthArgument.value, actualSevenArgumentFunctionCall.sixthArgument.value);
         ARE_EQUAL(expectedSevenArgumentFunctionCall.seventhArgument.value, actualSevenArgumentFunctionCall.seventhArgument.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   class Equalizer<ZenMock::SevenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
   {
   public:
      static void AssertEqual(
         const ZenMock::SevenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& expectedSevenArgumentFunctionCall,
         const ZenMock::SevenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& actualSevenArgumentFunctionCall)
      {
         ARE_EQUAL(expectedSevenArgumentFunctionCall.firstArgumentReference.value, actualSevenArgumentFunctionCall.firstArgumentReference.value);
         ARE_EQUAL(expectedSevenArgumentFunctionCall.secondArgumentReference.value, actualSevenArgumentFunctionCall.secondArgumentReference.value);
         ARE_EQUAL(expectedSevenArgumentFunctionCall.thirdArgumentReference.value, actualSevenArgumentFunctionCall.thirdArgumentReference.value);
         ARE_EQUAL(expectedSevenArgumentFunctionCall.fourthArgumentReference.value, actualSevenArgumentFunctionCall.fourthArgumentReference.value);
         ARE_EQUAL(expectedSevenArgumentFunctionCall.fifthArgumentReference.value, actualSevenArgumentFunctionCall.fifthArgumentReference.value);
         ARE_EQUAL(expectedSevenArgumentFunctionCall.sixthArgumentReference.value, actualSevenArgumentFunctionCall.sixthArgumentReference.value);
         ARE_EQUAL(expectedSevenArgumentFunctionCall.seventhArgumentReference.value, actualSevenArgumentFunctionCall.seventhArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
   class Equalizer<ZenMock::EightArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
   {
   public:
      static void AssertEqual(
         const ZenMock::EightArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& expectedEightArgumentFunctionCall,
         const ZenMock::EightArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& actualEightArgumentFunctionCall)
      {
         ARE_EQUAL(expectedEightArgumentFunctionCall.firstArgument.value, actualEightArgumentFunctionCall.firstArgument.value);
         ARE_EQUAL(expectedEightArgumentFunctionCall.secondArgument.value, actualEightArgumentFunctionCall.secondArgument.value);
         ARE_EQUAL(expectedEightArgumentFunctionCall.thirdArgument.value, actualEightArgumentFunctionCall.thirdArgument.value);
         ARE_EQUAL(expectedEightArgumentFunctionCall.fourthArgument.value, actualEightArgumentFunctionCall.fourthArgument.value);
         ARE_EQUAL(expectedEightArgumentFunctionCall.fifthArgument.value, actualEightArgumentFunctionCall.fifthArgument.value);
         ARE_EQUAL(expectedEightArgumentFunctionCall.sixthArgument.value, actualEightArgumentFunctionCall.sixthArgument.value);
         ARE_EQUAL(expectedEightArgumentFunctionCall.seventhArgument.value, actualEightArgumentFunctionCall.seventhArgument.value);
         ARE_EQUAL(expectedEightArgumentFunctionCall.eigthArgument.value, actualEightArgumentFunctionCall.eigthArgument.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
   class Equalizer<ZenMock::EightArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
   {
   public:
      static void AssertEqual(
         const ZenMock::EightArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& expectedEightArgumentFunctionCall,
         const ZenMock::EightArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& actualEightArgumentFunctionCall)
      {
         ARE_EQUAL(expectedEightArgumentFunctionCall.firstArgumentReference.value, actualEightArgumentFunctionCall.firstArgumentReference.value);
         ARE_EQUAL(expectedEightArgumentFunctionCall.secondArgumentReference.value, actualEightArgumentFunctionCall.secondArgumentReference.value);
         ARE_EQUAL(expectedEightArgumentFunctionCall.thirdArgumentReference.value, actualEightArgumentFunctionCall.thirdArgumentReference.value);
         ARE_EQUAL(expectedEightArgumentFunctionCall.fourthArgumentReference.value, actualEightArgumentFunctionCall.fourthArgumentReference.value);
         ARE_EQUAL(expectedEightArgumentFunctionCall.fifthArgumentReference.value, actualEightArgumentFunctionCall.fifthArgumentReference.value);
         ARE_EQUAL(expectedEightArgumentFunctionCall.sixthArgumentReference.value, actualEightArgumentFunctionCall.sixthArgumentReference.value);
         ARE_EQUAL(expectedEightArgumentFunctionCall.seventhArgumentReference.value, actualEightArgumentFunctionCall.seventhArgumentReference.value);
         ARE_EQUAL(expectedEightArgumentFunctionCall.eigthArgumentReference.value, actualEightArgumentFunctionCall.eigthArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
   class Equalizer<ZenMock::NineArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
   {
   public:
      static void AssertEqual(
         const ZenMock::NineArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& expectedNineArgumentFunctionCall,
         const ZenMock::NineArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& actualNineArgumentFunctionCall)
      {
         ARE_EQUAL(expectedNineArgumentFunctionCall.firstArgument.value, actualNineArgumentFunctionCall.firstArgument.value);
         ARE_EQUAL(expectedNineArgumentFunctionCall.secondArgument.value, actualNineArgumentFunctionCall.secondArgument.value);
         ARE_EQUAL(expectedNineArgumentFunctionCall.thirdArgument.value, actualNineArgumentFunctionCall.thirdArgument.value);
         ARE_EQUAL(expectedNineArgumentFunctionCall.fourthArgument.value, actualNineArgumentFunctionCall.fourthArgument.value);
         ARE_EQUAL(expectedNineArgumentFunctionCall.fifthArgument.value, actualNineArgumentFunctionCall.fifthArgument.value);
         ARE_EQUAL(expectedNineArgumentFunctionCall.sixthArgument.value, actualNineArgumentFunctionCall.sixthArgument.value);
         ARE_EQUAL(expectedNineArgumentFunctionCall.seventhArgument.value, actualNineArgumentFunctionCall.seventhArgument.value);
         ARE_EQUAL(expectedNineArgumentFunctionCall.eigthArgument.value, actualNineArgumentFunctionCall.eigthArgument.value);
         ARE_EQUAL(expectedNineArgumentFunctionCall.ninthArgument.value, actualNineArgumentFunctionCall.ninthArgument.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
   class Equalizer<ZenMock::NineArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
   {
   public:
      static void AssertEqual(
         const ZenMock::NineArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& expectedNineArgumentFunctionCall,
         const ZenMock::NineArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& actualNineArgumentFunctionCall)
      {
         ARE_EQUAL(expectedNineArgumentFunctionCall.firstArgumentReference.value, actualNineArgumentFunctionCall.firstArgumentReference.value);
         ARE_EQUAL(expectedNineArgumentFunctionCall.secondArgumentReference.value, actualNineArgumentFunctionCall.secondArgumentReference.value);
         ARE_EQUAL(expectedNineArgumentFunctionCall.thirdArgumentReference.value, actualNineArgumentFunctionCall.thirdArgumentReference.value);
         ARE_EQUAL(expectedNineArgumentFunctionCall.fourthArgumentReference.value, actualNineArgumentFunctionCall.fourthArgumentReference.value);
         ARE_EQUAL(expectedNineArgumentFunctionCall.fifthArgumentReference.value, actualNineArgumentFunctionCall.fifthArgumentReference.value);
         ARE_EQUAL(expectedNineArgumentFunctionCall.sixthArgumentReference.value, actualNineArgumentFunctionCall.sixthArgumentReference.value);
         ARE_EQUAL(expectedNineArgumentFunctionCall.seventhArgumentReference.value, actualNineArgumentFunctionCall.seventhArgumentReference.value);
         ARE_EQUAL(expectedNineArgumentFunctionCall.eigthArgumentReference.value, actualNineArgumentFunctionCall.eigthArgumentReference.value);
         ARE_EQUAL(expectedNineArgumentFunctionCall.ninthArgumentReference.value, actualNineArgumentFunctionCall.ninthArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
   class Equalizer<ZenMock::TenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>
   {
   public:
      static void AssertEqual(
         const ZenMock::TenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& expectedTenArgumentFunctionCall,
         const ZenMock::TenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& actualTenArgumentFunctionCall)
      {
         ARE_EQUAL(expectedTenArgumentFunctionCall.firstArgument.value, actualTenArgumentFunctionCall.firstArgument.value);
         ARE_EQUAL(expectedTenArgumentFunctionCall.secondArgument.value, actualTenArgumentFunctionCall.secondArgument.value);
         ARE_EQUAL(expectedTenArgumentFunctionCall.thirdArgument.value, actualTenArgumentFunctionCall.thirdArgument.value);
         ARE_EQUAL(expectedTenArgumentFunctionCall.fourthArgument.value, actualTenArgumentFunctionCall.fourthArgument.value);
         ARE_EQUAL(expectedTenArgumentFunctionCall.fifthArgument.value, actualTenArgumentFunctionCall.fifthArgument.value);
         ARE_EQUAL(expectedTenArgumentFunctionCall.sixthArgument.value, actualTenArgumentFunctionCall.sixthArgument.value);
         ARE_EQUAL(expectedTenArgumentFunctionCall.seventhArgument.value, actualTenArgumentFunctionCall.seventhArgument.value);
         ARE_EQUAL(expectedTenArgumentFunctionCall.eigthArgument.value, actualTenArgumentFunctionCall.eigthArgument.value);
         ARE_EQUAL(expectedTenArgumentFunctionCall.ninthArgument.value, actualTenArgumentFunctionCall.ninthArgument.value);
         ARE_EQUAL(expectedTenArgumentFunctionCall.tenthArgument.value, actualTenArgumentFunctionCall.tenthArgument.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
   class Equalizer<ZenMock::TenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>
   {
   public:
      static void AssertEqual(
         const ZenMock::TenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& expectedTenArgumentFunctionCall,
         const ZenMock::TenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& actualTenArgumentFunctionCall)
      {
         ARE_EQUAL(expectedTenArgumentFunctionCall.firstArgumentReference.value, actualTenArgumentFunctionCall.firstArgumentReference.value);
         ARE_EQUAL(expectedTenArgumentFunctionCall.secondArgumentReference.value, actualTenArgumentFunctionCall.secondArgumentReference.value);
         ARE_EQUAL(expectedTenArgumentFunctionCall.thirdArgumentReference.value, actualTenArgumentFunctionCall.thirdArgumentReference.value);
         ARE_EQUAL(expectedTenArgumentFunctionCall.fourthArgumentReference.value, actualTenArgumentFunctionCall.fourthArgumentReference.value);
         ARE_EQUAL(expectedTenArgumentFunctionCall.fifthArgumentReference.value, actualTenArgumentFunctionCall.fifthArgumentReference.value);
         ARE_EQUAL(expectedTenArgumentFunctionCall.sixthArgumentReference.value, actualTenArgumentFunctionCall.sixthArgumentReference.value);
         ARE_EQUAL(expectedTenArgumentFunctionCall.seventhArgumentReference.value, actualTenArgumentFunctionCall.seventhArgumentReference.value);
         ARE_EQUAL(expectedTenArgumentFunctionCall.eigthArgumentReference.value, actualTenArgumentFunctionCall.eigthArgumentReference.value);
         ARE_EQUAL(expectedTenArgumentFunctionCall.ninthArgumentReference.value, actualTenArgumentFunctionCall.ninthArgumentReference.value);
         ARE_EQUAL(expectedTenArgumentFunctionCall.tenthArgumentReference.value, actualTenArgumentFunctionCall.tenthArgumentReference.value);
      }
   };

   template<typename ArgType>
   class Printer<ZenMock::OneArgumentFunctionCallReference<ArgType>>
   {
   public:
      static void Print(std::ostream& os, const ZenMock::OneArgumentFunctionCallReference<ArgType>& oneArgumentFunctionCall)
      {
         os << "ZenMock::OneArgumentFunctionCall:\n" <<
               "Argument: " << ZenUnit::ToStringer::ToString(oneArgumentFunctionCall.argumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type>
   class Printer<ZenMock::TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>>
   {
   public:
      static void Print(std::ostream& os, const ZenMock::TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>& twoArgumentFunctionCallRef)
      {
         os << "ZenMock::TwoArgumentFunctionCall:\n"
               "Argument1: " << ZenUnit::ToStringer::ToString(twoArgumentFunctionCallRef.firstArgumentReference.value) << '\n' <<
               "Argument2: " << ZenUnit::ToStringer::ToString(twoArgumentFunctionCallRef.secondArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class Printer<ZenMock::ThreeArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type>>
   {
   public:
      static void Print(std::ostream& os, const ZenMock::ThreeArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type>& threeArgumentFunctionCallRef)
      {
         os << "ZenMock::ThreeArgumentFunctionCall:\n"
               "Argument1: " << ZenUnit::ToStringer::ToString(threeArgumentFunctionCallRef.firstArgumentReference.value) << '\n' <<
               "Argument2: " << ZenUnit::ToStringer::ToString(threeArgumentFunctionCallRef.secondArgumentReference.value) << '\n' <<
               "Argument3: " << ZenUnit::ToStringer::ToString(threeArgumentFunctionCallRef.thirdArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class Printer<ZenMock::FourArgumentFunctionCallReference<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
   {
   public:
      static void Print(std::ostream& os, const ZenMock::FourArgumentFunctionCallReference<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& fourArgumentFunctionCallRef)
      {
         os << "ZenMock::FourArgumentFunctionCall:\n"
               "Argument1: " << ZenUnit::ToStringer::ToString(fourArgumentFunctionCallRef.firstArgumentReference.value) << '\n' <<
               "Argument2: " << ZenUnit::ToStringer::ToString(fourArgumentFunctionCallRef.secondArgumentReference.value) << '\n' <<
               "Argument3: " << ZenUnit::ToStringer::ToString(fourArgumentFunctionCallRef.thirdArgumentReference.value) << '\n' <<
               "Argument4: " << ZenUnit::ToStringer::ToString(fourArgumentFunctionCallRef.fourthArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   class Printer<ZenMock::FiveArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
   {
   public:
      static void Print(std::ostream& os, const ZenMock::FiveArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& fiveArgumentFunctionCallRef)
      {
         os << "ZenMock::FiveArgumentFunctionCall:\n"
               "Argument1: " << ZenUnit::ToStringer::ToString(fiveArgumentFunctionCallRef.firstArgumentReference.value) << '\n' <<
               "Argument2: " << ZenUnit::ToStringer::ToString(fiveArgumentFunctionCallRef.secondArgumentReference.value) << '\n' <<
               "Argument3: " << ZenUnit::ToStringer::ToString(fiveArgumentFunctionCallRef.thirdArgumentReference.value) << '\n' <<
               "Argument4: " << ZenUnit::ToStringer::ToString(fiveArgumentFunctionCallRef.fourthArgumentReference.value) << '\n' <<
               "Argument5: " << ZenUnit::ToStringer::ToString(fiveArgumentFunctionCallRef.fifthArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   class Printer<ZenMock::SixArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
   {
   public:
      static void Print(std::ostream& os, const ZenMock::SixArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& sixArgumentFunctionCallRef)
      {
         os << "ZenMock::SixArgumentFunctionCall:\n"
               "Argument1: " << ZenUnit::ToStringer::ToString(sixArgumentFunctionCallRef.firstArgumentReference.value) << '\n' <<
               "Argument2: " << ZenUnit::ToStringer::ToString(sixArgumentFunctionCallRef.secondArgumentReference.value) << '\n' <<
               "Argument3: " << ZenUnit::ToStringer::ToString(sixArgumentFunctionCallRef.thirdArgumentReference.value) << '\n' <<
               "Argument4: " << ZenUnit::ToStringer::ToString(sixArgumentFunctionCallRef.fourthArgumentReference.value) << '\n' <<
               "Argument5: " << ZenUnit::ToStringer::ToString(sixArgumentFunctionCallRef.fifthArgumentReference.value) << '\n' <<
               "Argument6: " << ZenUnit::ToStringer::ToString(sixArgumentFunctionCallRef.sixthArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   class Printer<ZenMock::SevenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
   {
   public:
      static void Print(std::ostream& os, const ZenMock::SevenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& sevenArgumentFunctionCallRef)
      {
         os << "ZenMock::SevenArgumentFunctionCall:\n"
               "Argument1: " << ZenUnit::ToStringer::ToString(sevenArgumentFunctionCallRef.firstArgumentReference.value) << '\n' <<
               "Argument2: " << ZenUnit::ToStringer::ToString(sevenArgumentFunctionCallRef.secondArgumentReference.value) << '\n' <<
               "Argument3: " << ZenUnit::ToStringer::ToString(sevenArgumentFunctionCallRef.thirdArgumentReference.value) << '\n' <<
               "Argument4: " << ZenUnit::ToStringer::ToString(sevenArgumentFunctionCallRef.fourthArgumentReference.value) << '\n' <<
               "Argument5: " << ZenUnit::ToStringer::ToString(sevenArgumentFunctionCallRef.fifthArgumentReference.value) << '\n' <<
               "Argument6: " << ZenUnit::ToStringer::ToString(sevenArgumentFunctionCallRef.sixthArgumentReference.value) << '\n' <<
               "Argument7: " << ZenUnit::ToStringer::ToString(sevenArgumentFunctionCallRef.seventhArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
   class Printer<ZenMock::EightArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
   {
   public:
      static void Print(std::ostream& os, const ZenMock::EightArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& eightArgumentFunctionCallRef)
      {
         os << "ZenMock::EightArgumentFunctionCall:\n"
               "Argument1: " << ZenUnit::ToStringer::ToString(eightArgumentFunctionCallRef.firstArgumentReference.value) << '\n' <<
               "Argument2: " << ZenUnit::ToStringer::ToString(eightArgumentFunctionCallRef.secondArgumentReference.value) << '\n' <<
               "Argument3: " << ZenUnit::ToStringer::ToString(eightArgumentFunctionCallRef.thirdArgumentReference.value) << '\n' <<
               "Argument4: " << ZenUnit::ToStringer::ToString(eightArgumentFunctionCallRef.fourthArgumentReference.value) << '\n' <<
               "Argument5: " << ZenUnit::ToStringer::ToString(eightArgumentFunctionCallRef.fifthArgumentReference.value) << '\n' <<
               "Argument6: " << ZenUnit::ToStringer::ToString(eightArgumentFunctionCallRef.sixthArgumentReference.value) << '\n' <<
               "Argument7: " << ZenUnit::ToStringer::ToString(eightArgumentFunctionCallRef.seventhArgumentReference.value) << '\n' <<
               "Argument8: " << ZenUnit::ToStringer::ToString(eightArgumentFunctionCallRef.eigthArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
   class Printer<ZenMock::NineArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
   {
   public:
      static void Print(std::ostream& os, const ZenMock::NineArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& nineArgumentFunctionCallRef)
      {
         os << "ZenMock::NineArgumentFunctionCall:\n"
               "Argument1: " << ZenUnit::ToStringer::ToString(nineArgumentFunctionCallRef.firstArgumentReference.value) << '\n' <<
               "Argument2: " << ZenUnit::ToStringer::ToString(nineArgumentFunctionCallRef.secondArgumentReference.value) << '\n' <<
               "Argument3: " << ZenUnit::ToStringer::ToString(nineArgumentFunctionCallRef.thirdArgumentReference.value) << '\n' <<
               "Argument4: " << ZenUnit::ToStringer::ToString(nineArgumentFunctionCallRef.fourthArgumentReference.value) << '\n' <<
               "Argument5: " << ZenUnit::ToStringer::ToString(nineArgumentFunctionCallRef.fifthArgumentReference.value) << '\n' <<
               "Argument6: " << ZenUnit::ToStringer::ToString(nineArgumentFunctionCallRef.sixthArgumentReference.value) << '\n' <<
               "Argument7: " << ZenUnit::ToStringer::ToString(nineArgumentFunctionCallRef.seventhArgumentReference.value) << '\n' <<
               "Argument8: " << ZenUnit::ToStringer::ToString(nineArgumentFunctionCallRef.eigthArgumentReference.value) << '\n' <<
               "Argument9: " << ZenUnit::ToStringer::ToString(nineArgumentFunctionCallRef.ninthArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
   class Printer<ZenMock::TenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>
   {
   public:
      static void Print(std::ostream& os, const ZenMock::TenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& tenArgumentFunctionCallRef)
      {
         os << "ZenMock::TenArgumentFunctionCall:\n"
               " Argument1: " << ZenUnit::ToStringer::ToString(tenArgumentFunctionCallRef.firstArgumentReference.value) << '\n' <<
               " Argument2: " << ZenUnit::ToStringer::ToString(tenArgumentFunctionCallRef.secondArgumentReference.value) << '\n' <<
               " Argument3: " << ZenUnit::ToStringer::ToString(tenArgumentFunctionCallRef.thirdArgumentReference.value) << '\n' <<
               " Argument4: " << ZenUnit::ToStringer::ToString(tenArgumentFunctionCallRef.fourthArgumentReference.value) << '\n' <<
               " Argument5: " << ZenUnit::ToStringer::ToString(tenArgumentFunctionCallRef.fifthArgumentReference.value) << '\n' <<
               " Argument6: " << ZenUnit::ToStringer::ToString(tenArgumentFunctionCallRef.sixthArgumentReference.value) << '\n' <<
               " Argument7: " << ZenUnit::ToStringer::ToString(tenArgumentFunctionCallRef.seventhArgumentReference.value) << '\n' <<
               " Argument8: " << ZenUnit::ToStringer::ToString(tenArgumentFunctionCallRef.eigthArgumentReference.value) << '\n' <<
               " Argument9: " << ZenUnit::ToStringer::ToString(tenArgumentFunctionCallRef.ninthArgumentReference.value) << '\n' <<
               "Argument10: " << ZenUnit::ToStringer::ToString(tenArgumentFunctionCallRef.tenthArgumentReference.value);
      }
   };
}

namespace ZenMock
{
   // ZenMock::RandomGeneratorMock can be used to confirm the correctness of ZenUnit::Random<T>() functions
   class RandomGeneratorMock : public Zen::Mock<ZenUnit::RandomGenerator>
   {
   public:
      ZENMOCK_NONVOID0_CONST(bool, Bool)

      ZENMOCK_NONVOID0_CONST(char, Char)
      ZENMOCK_NONVOID0_CONST(unsigned char, UnsignedChar)

      ZENMOCK_NONVOID0_CONST(short, Short)
      ZENMOCK_NONVOID0_CONST(unsigned short, UnsignedShort)

      ZENMOCK_NONVOID0_CONST(int, Int)
      ZENMOCK_NONVOID0_CONST(unsigned int, UnsignedInt)

      ZENMOCK_NONVOID1_CONST(int, Enum, int)

      ZENMOCK_NONVOID0_CONST(long long, LongLong)
      ZENMOCK_NONVOID0_CONST(unsigned long long, UnsignedLongLong)
      ZENMOCK_NONVOID0_CONST(size_t, SizeT)

      ZENMOCK_NONVOID0_CONST(float, Float)
      ZENMOCK_NONVOID0_CONST(double, Double)

      ZENMOCK_NONVOID0_CONST(const char*, ConstCharPointer)

      ZENMOCK_NONVOID0_CONST(std::string, String)

      ZENMOCK_NONVOID0_CONST(std::vector<std::string>, StringVector)

      ZENMOCK_NONVOID0_CONST(fs::path, Path)
   };
}
