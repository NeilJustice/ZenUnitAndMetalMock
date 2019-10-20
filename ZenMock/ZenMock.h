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

// Defines a ZenMock object named <StaticFunctionName>_ZenMockObject for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName()".
#define ZENMOCK_VOID0_STATIC(NamespaceQualifiedClassName, StaticFunctionName, ...) \
   ZenMock::VoidZeroArgFunctionPointerMocker StaticFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::VoidZeroArgFunctionPointerMocker( \
         ZenMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"()"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>_ZenMockObject for mocking a namespaced free function with signature "void Namespace::NamespacedFreeFunctionName()".
#define ZENMOCK_VOID0_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, ...) \
   ZENMOCK_VOID0_STATIC(Namespace, FreeFunctionName, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>_ZenMockObject for mocking a global free function with signature "void ::FreeFunctionName()".
#define ZENMOCK_VOID0_FREE(GlobalFreeFunctionName) \
   ZenMock::VoidZeroArgFunctionPointerMocker GlobalFreeFunctionName##_ZenMockObject = \
      ZenMock::VoidZeroArgFunctionPointerMocker(ZenMock::FunctionSignature::FunctionPointer("void", "::"#GlobalFreeFunctionName"()"));

#define ZENMOCK_VOID0_DEFINED(FunctionName, Virtualness, Constness, Mutableness, Finalness) \
struct ZenMock_##FunctionName : public ZenMock::VoidZeroArgumentMocker \
{ \
   explicit ZenMock_##FunctionName(const std::string* zenMockedClassName) \
      : ZenMock::VoidZeroArgumentMocker(ZenMock::FunctionSignature::Function( \
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

// Defines a ZenMock object named <StaticFunctionName>_ZenMockObject for mocking a static function with signature "ReturnType NamespaceQualifiedClassName::StaticFunctionName()".
#define ZENMOCK_NONVOID0_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, ...) \
   ZenMock::NonVoidZeroArgFunctionPointerMocker<ReturnType> StaticFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::NonVoidZeroArgFunctionPointerMocker<ReturnType>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"()"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>_ZenMockObject for mocking a namespaced free function with signature "ReturnType Namespace::NamespacedFreeFunctionName()".
#define ZENMOCK_NONVOID0_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFreeFunctionName, ...) \
   ZENMOCK_NONVOID0_STATIC(ReturnType, Namespace, NamespacedFreeFunctionName, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>_ZenMockObject for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName()".
#define ZENMOCK_NONVOID0_FREE(ReturnType, GlobalFreeFunctionName) \
   ZenMock::NonVoidZeroArgFunctionPointerMocker<ReturnType> GlobalFreeFunctionName##_ZenMockObject = \
      ZenMock::NonVoidZeroArgFunctionPointerMocker<ReturnType>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, "::"#GlobalFreeFunctionName"()"));

#define ZENMOCK_NONVOID0_DEFINED(ReturnType, FunctionName, Virtualness, Constness, Mutableness, Finalness) \
struct ZenMock_##FunctionName : public ZenMock::NonVoidZeroArgumentMocker<ReturnType> \
{ \
   explicit ZenMock_##FunctionName(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidZeroArgumentMocker<ReturnType>(ZenMock::FunctionSignature::Function( \
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

// Defines a ZenMock object named <StaticFunctionName>_ZenMockObject for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type)".
#define ZENMOCK_NONVOID1_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, ...) \
   ZenMock::NonVoidOneArgFunctionPointerMocker<ReturnType, Arg1Type> \
      StaticFunctionName##_ZenMockObject##__VA_ARGS__ = ZenMock::NonVoidOneArgFunctionPointerMocker<ReturnType, Arg1Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>_ZenMockObject for mocking a namespaced free function with signature "ReturnType Namespace::NamespacedFreeFunctionName(Arg1Type)".
#define ZENMOCK_NONVOID1_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, ...) \
   ZENMOCK_NONVOID1_STATIC(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>_ZenMockObject for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type)".
#define ZENMOCK_NONVOID1_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, ...) \
   ZenMock::NonVoidOneArgFunctionPointerMocker<ReturnType, Arg1Type> \
      GlobalFreeFunctionName##_ZenMockObject##__VA_ARGS__ = ZenMock::NonVoidOneArgFunctionPointerMocker<ReturnType, Arg1Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, "::"#GlobalFreeFunctionName"("#Arg1Type")"));

#define ZENMOCK_NONVOID1_DEFINED(ReturnType, FunctionName, Arg1Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::NonVoidOneArgumentMocker<ReturnType, Arg1Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidOneArgumentMocker<ReturnType, Arg1Type>(ZenMock::FunctionSignature::Function( \
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

// Defines a ZenMock object named <StaticFunctionName>_ZenMockObject for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName(Arg1Type)".
#define ZENMOCK_VOID1_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, ...) \
   ZenMock::VoidOneArgFunctionPointerMocker<Arg1Type> StaticFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::VoidOneArgFunctionPointerMocker<Arg1Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>_ZenMockObject for mocking a namespaced free function with signature "void Namespace::NamespacedFreeFunctionName(Arg1Type)".
#define ZENMOCK_VOID1_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, ...) \
   ZENMOCK_VOID1_STATIC(NamespaceQualifiedClassName, NamespacedFreeFunctionName, Arg1Type, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>_ZenMockObject for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type)".
#define ZENMOCK_VOID1_FREE(GlobalFreeFunctionName, Arg1Type, ...) \
   ZenMock::VoidOneArgFunctionPointerMocker<Arg1Type> GlobalFreeFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::VoidOneArgFunctionPointerMocker<Arg1Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", "::"#GlobalFreeFunctionName"("#Arg1Type")"));

#define ZENMOCK_VOID1_DEFINED(FunctionName, Arg1Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::VoidOneArgumentMocker<Arg1Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidOneArgumentMocker<Arg1Type>(ZenMock::FunctionSignature::Function( \
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

// Defines a ZenMock object named <StaticFunctionName>_ZenMockObject for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type)".
#define ZENMOCK_NONVOID2_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, ...) \
   ZenMock::NonVoidTwoArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type> StaticFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::NonVoidTwoArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>_ZenMockObject for mocking a namespaced free function with signature "ReturnType Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type)".
#define ZENMOCK_NONVOID2_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, ...) \
   ZENMOCK_NONVOID2_STATIC(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>_ZenMockObject for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type, Arg2Type)".
#define ZENMOCK_NONVOID2_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, ...) \
   ZenMock::NonVoidTwoArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type> GlobalFreeFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::NonVoidTwoArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type")"));

#define ZENMOCK_NONVOID2_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::NonVoidTwoArgumentMocker<ReturnType, Arg1Type, Arg2Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidTwoArgumentMocker<ReturnType, Arg1Type, Arg2Type>(ZenMock::FunctionSignature::Function( \
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

// Defines a ZenMock object named <FunctionName>_ZenMockObject for mocking a static function with signature "void QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type)".
#define ZENMOCK_VOID2_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, ...) \
   ZenMock::VoidTwoArgFunctionPointerMocker<Arg1Type, Arg2Type> StaticFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::VoidTwoArgFunctionPointerMocker<Arg1Type, Arg2Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>_ZenMockObject for mocking a namespaced free function with signature "void Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type)".
#define ZENMOCK_VOID2_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, ...) \
   ZENMOCK_VOID2_STATIC(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>_ZenMockObject for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type, Arg2Type)".
#define ZENMOCK_VOID2_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, ...) \
   ZenMock::VoidTwoArgFunctionPointerMocker<Arg1Type, Arg2Type> GlobalFreeFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::VoidTwoArgFunctionPointerMocker<Arg1Type, Arg2Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type")"));

#define ZENMOCK_VOID2_DEFINED(FunctionName, Arg1Type, Arg2Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::VoidTwoArgumentMocker<Arg1Type, Arg2Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidTwoArgumentMocker<Arg1Type, Arg2Type>(ZenMock::FunctionSignature::Function( \
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

// Defines a ZenMock object named <StaticFunctionName>_ZenMockObject for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type)".
#define ZENMOCK_NONVOID3_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, ...) \
   ZenMock::NonVoidThreeArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type> StaticFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::NonVoidThreeArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>_ZenMockObject for mocking a static function with signature "ReturnType Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type, Arg3Type)".
#define ZENMOCK_NONVOID3_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, ...) \
   ZENMOCK_NONVOID3_STATIC(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type)

// Defines a ZenMock object named <GlobalFreeFunctionName>_ZenMockObject for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type)".
#define ZENMOCK_NONVOID3_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, ...) \
   ZenMock::NonVoidThreeArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type> GlobalFreeFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::NonVoidThreeArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type")"));

#define ZENMOCK_NONVOID3_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Arg3Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::NonVoidThreeArgumentMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidThreeArgumentMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type>(ZenMock::FunctionSignature::Function( \
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

// Defines a ZenMock object named <StaticFunctionName>_ZenMockObject for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type)".
#define ZENMOCK_VOID3_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, ...) \
   ZenMock::VoidThreeArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type> StaticFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::VoidThreeArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>_ZenMockObject for mocking a static function with signature "void Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type, Arg3Type)".
#define ZENMOCK_VOID3_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, ...) \
   ZENMOCK_VOID3_STATIC(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>_ZenMockObject for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type)".
#define ZENMOCK_VOID3_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, ...) \
   ZenMock::VoidThreeArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type> GlobalFreeFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::VoidThreeArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type")"));

#define ZENMOCK_VOID3_DEFINED(FunctionName, Arg1Type, Arg2Type, Arg3Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::VoidThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>(ZenMock::FunctionSignature::Function( \
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

// Defines a ZenMock object named <StaticFunctionName>_ZenMockObject for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type)".
#define ZENMOCK_NONVOID4_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...) \
   ZenMock::NonVoidFourArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type> StaticFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::NonVoidFourArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type")"));

// Defines a ZenMock object named <NamespaceFreeFunctionName>_ZenMockObject for mocking a static function with signature "ReturnType Namespace::NamespaceFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type)".
#define ZENMOCK_NONVOID4_NAMESPACED_FREE(ReturnType, Namespace, NamespaceFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...) \
   ZENMOCK_NONVOID4_STATIC(ReturnType, Namespace, NamespaceFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>_ZenMockObject for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type)".
#define ZENMOCK_NONVOID4_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...) \
   ZenMock::NonVoidFourArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type> GlobalFreeFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::NonVoidFourArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type")"));

#define ZENMOCK_NONVOID4_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::NonVoidFourArgumentMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidFourArgumentMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>(ZenMock::FunctionSignature::Function( \
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

// Defines a ZenMock object named <StaticFunctionName>_ZenMockObject for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type)".
#define ZENMOCK_VOID4_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...) \
   ZenMock::VoidFourArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type> StaticFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::VoidFourArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>_ZenMockObject for mocking a namespaced free function with signature "void Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type)".
#define ZENMOCK_VOID4_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...) \
   ZENMOCK_VOID4_STATIC(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>_ZenMockObject for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type)".
#define ZENMOCK_VOID4_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...) \
   ZenMock::VoidFourArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type> GlobalFreeFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::VoidFourArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type")"));

#define ZENMOCK_VOID4_DEFINED(FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::VoidFourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidFourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>(ZenMock::FunctionSignature::Function( \
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

// Defines a ZenMock object named <StaticFunctionName>_ZenMockObject for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)".
#define ZENMOCK_NONVOID5_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...) \
   ZenMock::NonVoidFiveArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type> StaticFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::NonVoidFiveArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>_ZenMockObject for mocking a namespaced free function with signature "ReturnType Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)".
#define ZENMOCK_NONVOID5_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...) \
   ZENMOCK_NONVOID5_STATIC(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>_ZenMockObject for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)".
#define ZENMOCK_NONVOID5_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...) \
   ZenMock::NonVoidFiveArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type> GlobalFreeFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::NonVoidFiveArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type")"));

#define ZENMOCK_NONVOID5_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::NonVoidFiveArgumentMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidFiveArgumentMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>(ZenMock::FunctionSignature::Function( \
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

// Defines a ZenMock object named <StaticFunctionName>_ZenMockObject for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)".
#define ZENMOCK_VOID5_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...) \
   ZenMock::VoidFiveArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type> StaticFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::VoidFiveArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>_ZenMockObject for mocking a namespaced free function with signature "void Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)".
#define ZENMOCK_VOID5_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...) \
   ZENMOCK_VOID5_STATIC(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>_ZenMockObject for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)".
#define ZENMOCK_VOID5_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...) \
   ZenMock::VoidFiveArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type> GlobalFreeFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::VoidFiveArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type")"));

#define ZENMOCK_VOID5_DEFINED(FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::VoidFiveArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidFiveArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>(ZenMock::FunctionSignature::Function( \
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

// Defines a ZenMock object named <StaticFunctionName>_ZenMockObject for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)".
#define ZENMOCK_NONVOID6_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...) \
   ZenMock::NonVoidSixArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type> StaticFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::NonVoidSixArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>_ZenMockObject for mocking a namespaced free function with signature "ReturnType Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)".
#define ZENMOCK_NONVOID6_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...) \
   ZENMOCK_NONVOID6_STATIC(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>_ZenMockObject for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)".
#define ZENMOCK_NONVOID6_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...) \
   ZenMock::NonVoidSixArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type> GlobalFreeFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::NonVoidSixArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type")"));

#define ZENMOCK_NONVOID6_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::NonVoidSixArgumentMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidSixArgumentMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>(ZenMock::FunctionSignature::Function( \
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

// Defines a ZenMock object named <StaticFunctionName>_ZenMockObject for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)".
#define ZENMOCK_VOID6_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...) \
   ZenMock::VoidSixArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type> StaticFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::VoidSixArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>_ZenMockObject for mocking a static function with signature "void Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)".
#define ZENMOCK_VOID6_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...) \
   ZENMOCK_VOID6_STATIC(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, __VA_ARGS__) \

// Defines a ZenMock object named <GlobalFreeFunctionName>_ZenMockObject for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)".
#define ZENMOCK_VOID6_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...) \
   ZenMock::VoidSixArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type> GlobalFreeFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::VoidSixArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type")"));

#define ZENMOCK_VOID6_DEFINED(FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::VoidSixArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidSixArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>(ZenMock::FunctionSignature::Function( \
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

// Defines a ZenMock object named <StaticFunctionName>_ZenMockObject for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)".
#define ZENMOCK_NONVOID7_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...) \
   ZenMock::NonVoidSevenArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type> StaticFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::NonVoidSevenArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>_ZenMockObject for mocking a namespaced free function with signature "ReturnType Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)".
#define ZENMOCK_NONVOID7_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...) \
   ZENMOCK_NONVOID7_STATIC(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>_ZenMockObject for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)".
#define ZENMOCK_NONVOID7_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...) \
   ZenMock::NonVoidSevenArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type> GlobalFreeFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::NonVoidSevenArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type")"));

#define ZENMOCK_NONVOID7_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::NonVoidSevenArgumentMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidSevenArgumentMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>(ZenMock::FunctionSignature::Function( \
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

// Defines a ZenMock object named <StaticFunctionName>_ZenMockObject for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)".
#define ZENMOCK_VOID7_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...) \
   ZenMock::VoidSevenArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type> StaticFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::VoidSevenArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>_ZenMockObject for mocking a namespaced free function with signature "void Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)".
#define ZENMOCK_VOID7_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...) \
   ZENMOCK_VOID7_STATIC(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, __VA_ARGS__) \

// Defines a ZenMock object named <GlobalFreeFunctionName>_ZenMockObject for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)".
#define ZENMOCK_VOID7_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...) \
   ZenMock::VoidSevenArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type> GlobalFreeFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::VoidSevenArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type")"));

#define ZENMOCK_VOID7_DEFINED(FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::VoidSevenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidSevenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>(ZenMock::FunctionSignature::Function( \
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

// Defines a ZenMock object named <StaticFunctionName>_ZenMockObject for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)".
#define ZENMOCK_NONVOID8_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...) \
   ZenMock::NonVoidEightArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type> StaticFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::NonVoidEightArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>_ZenMockObject for mocking a namespaced free function with signature "ReturnType Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)".
#define ZENMOCK_NONVOID8_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...) \
   ZENMOCK_NONVOID8_STATIC(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>_ZenMockObject for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)".
#define ZENMOCK_NONVOID8_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...) \
   ZenMock::NonVoidEightArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type> GlobalFreeFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::NonVoidEightArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type")"));

#define ZENMOCK_NONVOID8_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::NonVoidEightArgumentMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidEightArgumentMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>(ZenMock::FunctionSignature::Function( \
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

// Defines a ZenMock object named <StaticFunctionName>_ZenMockObject for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)".
#define ZENMOCK_VOID8_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...) \
   ZenMock::VoidEightArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type> StaticFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::VoidEightArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>_ZenMockObject for mocking a namespaced free function with signature "void Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)".
#define ZENMOCK_VOID8_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...) \
   ZENMOCK_VOID8_STATIC(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, __VA_ARGS__) \

// Defines a ZenMock object named <GlobalFreeFunctionName>_ZenMockObject for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)".
#define ZENMOCK_VOID8_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...) \
   ZenMock::VoidEightArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type> GlobalFreeFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::VoidEightArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type")"));

#define ZENMOCK_VOID8_DEFINED(FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::VoidEightArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidEightArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>(ZenMock::FunctionSignature::Function( \
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

// Defines a ZenMock object named <StaticFunctionName>_ZenMockObject for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type)".
#define ZENMOCK_VOID9_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...) \
   ZenMock::VoidNineArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type> StaticFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::VoidNineArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>_ZenMockObject for mocking a namespaced free function with signature "void Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type)".
#define ZENMOCK_VOID9_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...) \
   ZENMOCK_VOID9_STATIC(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, __VA_ARGS__) \

// Defines a ZenMock object named <GlobalFreeFunctionName>_ZenMockObject for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type)".
#define ZENMOCK_VOID9_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...) \
   ZenMock::VoidNineArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type> GlobalFreeFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::VoidNineArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type")"));

#define ZENMOCK_VOID9_DEFINED(FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::VoidNineArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidNineArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>(ZenMock::FunctionSignature::Function( \
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

// Defines a ZenMock object named <StaticFunctionName>_ZenMockObject for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type)".
#define ZENMOCK_NONVOID9_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...) \
   ZenMock::NonVoidNineArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type> StaticFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::NonVoidNineArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>_ZenMockObject for mocking a namespaced free function with signature "ReturnType Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type)".
#define ZENMOCK_NONVOID9_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...) \
   ZENMOCK_NONVOID9_STATIC(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, __VA_ARGS__) \

// Defines a ZenMock object named <GlobalFreeFunctionName>_ZenMockObject for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type)".
#define ZENMOCK_NONVOID9_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...) \
   ZenMock::NonVoidNineArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type> GlobalFreeFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::NonVoidNineArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type")"));

#define ZENMOCK_NONVOID9_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::NonVoidNineArgumentMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidNineArgumentMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>(ZenMock::FunctionSignature::Function( \
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

// Defines a ZenMock object named <StaticFunctionName>_ZenMockObject for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)".
#define ZENMOCK_VOID10_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...) \
   ZenMock::VoidTenArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type> StaticFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::VoidTenArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type", "#Arg10Type")"));

// Defines a ZenMock object named <NamespacedFreeFunctionName>_ZenMockObject for mocking a static function with signature "void Namespace::NamespacedFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)".
#define ZENMOCK_VOID10_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...) \
   ZENMOCK_VOID10_STATIC(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, __VA_ARGS__) \

// Defines a ZenMock object named <GlobalFreeFunctionName>_ZenMockObject for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)".
#define ZENMOCK_VOID10_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...) \
   ZenMock::VoidTenArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type> GlobalFreeFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::VoidTenArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>( \
         ZenMock::FunctionSignature::FunctionPointer("void", "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type", "#Arg10Type")"));

#define ZENMOCK_VOID10_DEFINED(FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::VoidTenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidTenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(ZenMock::FunctionSignature::Function( \
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

// Defines a ZenMock object named <StaticFunctionName>_ZenMockObject for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)".
#define ZENMOCK_NONVOID10_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...) \
   ZenMock::NonVoidTenArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type> StaticFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::NonVoidTenArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type", "#Arg10Type")"));

// Defines a ZenMock object named <NamespacedFunctionName>_ZenMockObject for mocking a namespaced free function with signature "ReturnType Namespace::NamespacedFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)".
#define ZENMOCK_NONVOID10_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...) \
   ZENMOCK_NONVOID10_STATIC(ReturnType, Namespace, NamespacedFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, __VA_ARGS__)

// Defines a ZenMock object named <GlobalFreeFunctionName>_ZenMockObject for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)".
#define ZENMOCK_NONVOID10_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...) \
   ZenMock::NonVoidTenArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type> GlobalFreeFunctionName##_ZenMockObject##__VA_ARGS__ = \
      ZenMock::NonVoidTenArgFunctionPointerMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>( \
         ZenMock::FunctionSignature::FunctionPointer(#ReturnType, "::"#GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type", "#Arg10Type")"));

#define ZENMOCK_NONVOID10_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, Virtualness, Constness, Mutableness, Finalness, ...) \
struct ZenMock_##FunctionName##__VA_ARGS__ : public ZenMock::NonVoidTenArgumentMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type> \
{ \
   explicit ZenMock_##FunctionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidTenArgumentMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(ZenMock::FunctionSignature::Function( \
         #Virtualness, #ReturnType, zenMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type", "#Arg10Type")", #Constness)) {} \
} Mutableness FunctionName##Mock##__VA_ARGS__ = ZenMock_##FunctionName##__VA_ARGS__(this->ZenMockedClassName()); \
ReturnType FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument, Arg9Type ninthArgument, Arg10Type tenthArgument) Constness Finalness \
{ \
   return FunctionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument, tenthArgument); \
}


// std::binds a zero-argument ZenMock object for assignment to a std::function
#define BIND_0ARG_ZENMOCK_OBJECT(FunctionName_ZenMockObject) \
   std::bind(&decltype(FunctionName_ZenMockObject)::ZenMockItFunctionPointer, &(FunctionName_ZenMockObject))

// std::binds a one-argument ZenMock object for assignment to a std::function
#define BIND_1ARG_ZENMOCK_OBJECT(FunctionName_ZenMockObject) \
   std::bind(&decltype(FunctionName_ZenMockObject)::ZenMockItFunctionPointer, &(FunctionName_ZenMockObject), std::placeholders::_1)

// std::binds a two-argument ZenMock object for assignment to a std::function
#define BIND_2ARG_ZENMOCK_OBJECT(FunctionName_ZenMockObject) \
   std::bind(&decltype(FunctionName_ZenMockObject)::ZenMockItFunctionPointer, &(FunctionName_ZenMockObject), std::placeholders::_1, std::placeholders::_2)

// std::binds a three-argument ZenMock object for assignment to a std::function
#define BIND_3ARG_ZENMOCK_OBJECT(FunctionName_ZenMockObject) \
   std::bind(&decltype(FunctionName_ZenMockObject)::ZenMockItFunctionPointer, &(FunctionName_ZenMockObject), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)

// std::binds a four-argument ZenMock object for assignment to a std::function
#define BIND_4ARG_ZENMOCK_OBJECT(FunctionName_ZenMockObject) \
   std::bind(&decltype(FunctionName_ZenMockObject)::ZenMockItFunctionPointer, &(FunctionName_ZenMockObject), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)

// std::binds a five-argument ZenMock object for assignment to a std::function
#define BIND_5ARG_ZENMOCK_OBJECT(FunctionName_ZenMockObject) \
   std::bind(&decltype(FunctionName_ZenMockObject)::ZenMockItFunctionPointer, &(FunctionName_ZenMockObject), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5)

// std::binds a six-argument ZenMock object for assignment to a std::function
#define BIND_6ARG_ZENMOCK_OBJECT(FunctionName_ZenMockObject) \
   std::bind(&decltype(FunctionName_ZenMockObject)::ZenMockItFunctionPointer, &(FunctionName_ZenMockObject), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6)

// std::binds a seven-argument ZenMock object for assignment to a std::function
#define BIND_7ARG_ZENMOCK_OBJECT(FunctionName_ZenMockObject) \
   std::bind(&decltype(FunctionName_ZenMockObject)::ZenMockItFunctionPointer, &(FunctionName_ZenMockObject), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7)

// std::binds a eight-argument ZenMock object for assignment to a std::function
#define BIND_8ARG_ZENMOCK_OBJECT(FunctionName_ZenMockObject) \
   std::bind(&decltype(FunctionName_ZenMockObject)::ZenMockItFunctionPointer, &(FunctionName_ZenMockObject), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8)

// std::binds a nine-argument ZenMock object for assignment to a std::function
#define BIND_9ARG_ZENMOCK_OBJECT(FunctionName_ZenMockObject) \
   std::bind(&decltype(FunctionName_ZenMockObject)::ZenMockItFunctionPointer, &(FunctionName_ZenMockObject), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, std::placeholders::_9)

// std::binds a ten-argument ZenMock object for assignment to a std::function
#define BIND_10ARG_ZENMOCK_OBJECT(FunctionName_ZenMockObject) \
   std::bind(&decltype(FunctionName_ZenMockObject)::ZenMockItFunctionPointer, &(FunctionName_ZenMockObject), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, std::placeholders::_9, std::placeholders::_10)

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
ZenMocked functions with non-void return types
must have their return value or values set explicitly by calling
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
Return(), ReturnValues(), ReturnRandom(), or Throw<T>() on a ZenMock object.)");
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
      virtual void Throw() const = 0;
      virtual ~Throwable() = default;
   };

   template<typename ExpectedExceptionType>
   class TemplateThrowable : public Throwable
   {
      template<typename T>
      friend class TemplateThrowableTests;
   private:
      std::unique_ptr<const ExpectedExceptionType> _exception;
   public:
      template<typename... ExceptionArgTypes>
      static const Throwable* New(ExceptionArgTypes&&... exceptionArgs)
      {
         auto* templateThrowable = new TemplateThrowable<ExpectedExceptionType>;
         templateThrowable->_exception = std::make_unique<ExpectedExceptionType>(
            std::forward<ExceptionArgTypes>(exceptionArgs)...);
         return templateThrowable;
      }

      void Throw() const override
      {
         if (_exception != nullptr)
         {
            throw *_exception;
         }
      }
   };

   class ExceptionThrower
   {
   private:
      std::shared_ptr<const Throwable> _throwable;
   public:
      template<typename ExceptionType, typename... ExceptionArgTypes>
      void Throw(ExceptionArgTypes&&... exceptionArgs)
      {
         if (_throwable != nullptr)
         {
            throw std::logic_error("ExceptionThrower::Throw<T>() called twice");
         }
         _throwable.reset(TemplateThrowable<ExceptionType>::New(
            std::forward<ExceptionArgTypes>(exceptionArgs)...));
      }

      void ZenMockThrowIfExceptionSet() const
      {
         if (_throwable != nullptr)
         {
            _throwable->Throw();
         }
      }

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
      std::function<const ZenUnit::ZenUnitArgs&()> _call_ZenUnitTestRunner_GetArgs;
      bool _zenMockExceptionIsInFlight;
   protected:
      bool _expected;
      bool _asserted;
      FunctionSequencingToken _functionSequencingToken;
      const std::string ZenMockedFunctionSignature;
      MockableExceptionThrowerType _exceptionThrower;
   public:
      explicit ZenMocker(std::string zenMockedFunctionSignature)
         : _call_exit(::exit)
         , _call_ZenUnitTestRunner_GetArgs(ZenUnit::ZenUnitTestRunner::GetArgs)
         , _zenMockExceptionIsInFlight(false)
         , _expected(false)
         , _asserted(false)
         , ZenMockedFunctionSignature(std::move(zenMockedFunctionSignature))
      {
      }

      ZenMocker& operator=(const ZenMocker&) = delete;

      template<typename ExceptionType, typename... ExceptionArgTypes>
      void Throw(ExceptionArgTypes&&... exceptionArgs)
      {
         _exceptionThrower.template Throw<ExceptionType>(std::forward<ExceptionArgTypes>(exceptionArgs)...);
         _expected = true;
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

      void ZenMockThrowIfExceptionSet()
      {
         _exceptionThrower.ZenMockThrowIfExceptionSet();
      }

      template<typename... ArgTypes>
      void ZenMockThrowIfNotExpected(ArgTypes&&... args)
      {
         if (!_expected)
         {
            _zenMockExceptionIsInFlight = true;
            throw UnexpectedCallException(ZenMockedFunctionSignature, std::forward<ArgTypes>(args)...);
         }
      }

      void ZenMockSetAsserted()
      {
         _asserted = true;
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
         if (_expected && !_asserted && !_zenMockExceptionIsInFlight)
         {
            const ZenUnit::Console console;
            console.WriteLineColor(R"(
==================================================
Fatal Expected-But-Not-Asserted ZenMocked Function
==================================================)", ZenUnit::Color::Red);
            console.Write("ZenMocked function that was expected but not later asserted as having been called:\n");
				console.WriteLine(ZenMockedFunctionSignature);
            const ZenUnit::ZenUnitArgs& args = _call_ZenUnitTestRunner_GetArgs();
				console.WriteColor("\n>>------>", ZenUnit::Color::Red);
				console.WriteLine("     Completed: " + args.commandLine);
            console.WriteColor(">>------>", ZenUnit::Color::Red);
            console.WriteLine("    RandomSeed: " + std::to_string(args.randomSeed));
				console.WriteColor(">>------>", ZenUnit::Color::Red);
				console.WriteLine("     StartTime: " + args.startDateTime);
				console.WriteColor(">>------>", ZenUnit::Color::Red);
				ZenUnit::Watch watch;
				const std::string endDateTime = watch.DateTimeNow();
				console.WriteLine("       EndTime: " + endDateTime);
            console.WriteColor(">>------> ", ZenUnit::Color::Red);
            const std::string testRunDurationInSeconds = ZenUnit::ZenUnitTestRunner::Instance().StopTestRunStopwatchAndGetElapsedSeconds();
            console.WriteLine("     Duration: " + testRunDurationInSeconds + " seconds");
            console.WriteColor(">>------>", ZenUnit::Color::Red);
				console.WriteLine(" TestRunResult: Fatal EBNA");
            console.WriteColor(">>-FAIL->", ZenUnit::Color::Red);
            const int exitCode = args.exitZero ? 0 : 1;
            console.WriteLine("      ExitCode: " + std::to_string(exitCode));
            _call_exit(exitCode);
         }
      }
   };

   class ZeroArgumentMockerTests;

   template<typename MockableExceptionThrowerType = ExceptionThrower>
   class ZeroArgumentMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class ZeroArgumentMockerTests;
   private:
      size_t actualNumberOfCalls;
   protected:
      std::function<void()> voidZeroArgFunctionToCallInstead;
   public:
      explicit ZeroArgumentMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
         , actualNumberOfCalls(0)
      {
      }

      void ZenMockIt()
      {
         this->ZenMockThrowIfNotExpected();
         ++this->actualNumberOfCalls;
         if (this->voidZeroArgFunctionToCallInstead)
         {
            this->voidZeroArgFunctionToCallInstead();
         }
         this->AssignAndIncrementFunctionSequenceIndex();
         this->ZenMockThrowIfExceptionSet();
      }

      void CallInstead(const std::function<void()>& voidZeroArgFunction)
      {
         ZeroArgumentMocker::_expected = true;
         this->voidZeroArgFunctionToCallInstead = voidZeroArgFunction;
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
   class NonVoidZeroArgumentMocker : public ZeroArgumentMocker<ExceptionThrower>, protected ValueReturner<FunctionReturnType>
   {
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   public:
      explicit NonVoidZeroArgumentMocker(const std::string& zenMockedFunctionSignature)
         : ZeroArgumentMocker<ExceptionThrower>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         ZeroArgumentMocker<ExceptionThrower>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         ZeroArgumentMocker<ExceptionThrower>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         ZeroArgumentMocker<ExceptionThrower>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         ZeroArgumentMocker<ExceptionThrower>::_expected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::ZenMockAddRandomReturnValue();
         return randomReturnValue;
      }

      const FunctionReturnType& ZenMockItAndReturnValue()
      {
         ZeroArgumentMocker::ZenMockIt();
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType>
   class NonVoidZeroArgFunctionPointerMocker : public NonVoidZeroArgumentMocker<FunctionReturnType>
   {
   public:
      explicit NonVoidZeroArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidZeroArgumentMocker<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      static const FunctionReturnType& ZenMockItFunctionPointer(
         NonVoidZeroArgFunctionPointerMocker<FunctionReturnType>* functionPointerMocker)
      {
         return functionPointerMocker->ZenMockItAndReturnValue();
      }
   };

   class VoidZeroArgumentMocker : public ZeroArgumentMocker<ExceptionThrower>
   {
   public:
      explicit VoidZeroArgumentMocker(const std::string& zenMockedFunctionSignature)
         : ZeroArgumentMocker<ExceptionThrower>(zenMockedFunctionSignature)
      {
      }

      void Expect()
      {
         ZeroArgumentMocker<ExceptionThrower>::_expected = true;
      }
   };

   class VoidZeroArgFunctionPointerMocker : public VoidZeroArgumentMocker
   {
   public:
      explicit VoidZeroArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : VoidZeroArgumentMocker(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(VoidZeroArgFunctionPointerMocker* functionPointerMocker)
      {
         functionPointerMocker->ZenMockIt();
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

      ArgumentStorage(std::string_view value)
         : value(value) {}
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
   struct ReferenceArgumentStorage
   {
      const T& value;

      ReferenceArgumentStorage()
         : value() {}

      ReferenceArgumentStorage(const T& argument)
         : value(argument) {}
   };

   template<>
   struct ReferenceArgumentStorage<std::string_view>
   {
      std::string value;

      ReferenceArgumentStorage() = default;

      ReferenceArgumentStorage(std::string_view argument)
         : value(argument) {}
   };

   template<typename T>
   struct ReferenceArgumentStorage<std::unique_ptr<T>>
   {
      const T* const value;

      ReferenceArgumentStorage() = delete;

      ReferenceArgumentStorage(const std::unique_ptr<T>& uniquePtr)
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
   struct OneArgumentFunctionCallRef
   {
      const ReferenceArgumentStorage<ArgType> argumentReference;

      OneArgumentFunctionCallRef(const ArgType& argument)
         : argumentReference(argument) {}

      explicit OneArgumentFunctionCallRef(const OneArgumentFunctionCall<ArgType>& oneArgumentCall)
         : argumentReference(oneArgumentCall.argument.value) {}
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
   struct TwoArgumentFunctionCallRef
   {
      const ReferenceArgumentStorage<Arg1Type> firstArgumentReference;
      const ReferenceArgumentStorage<Arg2Type> secondArgumentReference;

      TwoArgumentFunctionCallRef(const Arg1Type& firstArgument, const Arg2Type& secondArgument)
         : firstArgumentReference(firstArgument)
         , secondArgumentReference(secondArgument) {}

      explicit TwoArgumentFunctionCallRef(const TwoArgumentFunctionCall<Arg1Type, Arg2Type>& twoArgumentCall)
         : firstArgumentReference(twoArgumentCall.firstArgument.value)
         , secondArgumentReference(twoArgumentCall.secondArgument.value) {}
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
   struct ThreeArgumentFunctionCallRef
   {
      const ReferenceArgumentStorage<Arg1Type> firstArgumentReference;
      const ReferenceArgumentStorage<Arg2Type> secondArgumentReference;
      const ReferenceArgumentStorage<Arg3Type> thirdArgumentReference;

      ThreeArgumentFunctionCallRef(const Arg1Type& firstArgument, const Arg2Type& secondArgument, const Arg3Type& thirdArgument)
         : firstArgumentReference(firstArgument)
         , secondArgumentReference(secondArgument)
         , thirdArgumentReference(thirdArgument) {}

      explicit ThreeArgumentFunctionCallRef(const ThreeArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type>& threeArgumentCall)
         : firstArgumentReference(threeArgumentCall.firstArgument.value)
         , secondArgumentReference(threeArgumentCall.secondArgument.value)
         , thirdArgumentReference(threeArgumentCall.thirdArgument.value) {}
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
   struct FourArgumentFunctionCallRef
   {
      const ReferenceArgumentStorage<Arg1Type> firstArgumentReference;
      const ReferenceArgumentStorage<Arg2Type> secondArgumentReference;
      const ReferenceArgumentStorage<Arg3Type> thirdArgumentReference;
      const ReferenceArgumentStorage<Arg4Type> fourthArgumentReference;

      FourArgumentFunctionCallRef(const Arg1Type& firstArgument, const Arg2Type& secondArgument, const Arg3Type& thirdArgument, const Arg4Type& fourthArgument)
         : firstArgumentReference(firstArgument)
         , secondArgumentReference(secondArgument)
         , thirdArgumentReference(thirdArgument)
         , fourthArgumentReference(fourthArgument) {}

      explicit FourArgumentFunctionCallRef(const FourArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& fourArgumentCall)
         : firstArgumentReference(fourArgumentCall.firstArgument.value)
         , secondArgumentReference(fourArgumentCall.secondArgument.value)
         , thirdArgumentReference(fourArgumentCall.thirdArgument.value)
         , fourthArgumentReference(fourArgumentCall.fourthArgument.value) {}
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   struct FiveArgumentFunctionCall
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
   struct FiveArgumentFunctionCallRef
   {
      const ReferenceArgumentStorage<Arg1Type> firstArgumentReference;
      const ReferenceArgumentStorage<Arg2Type> secondArgumentReference;
      const ReferenceArgumentStorage<Arg3Type> thirdArgumentReference;
      const ReferenceArgumentStorage<Arg4Type> fourthArgumentReference;
      const ReferenceArgumentStorage<Arg5Type> fifthArgumentReference;

      FiveArgumentFunctionCallRef(
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

      explicit FiveArgumentFunctionCallRef(const FiveArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& fiveArgumentCall)
         : firstArgumentReference(fiveArgumentCall.firstArgument.value)
         , secondArgumentReference(fiveArgumentCall.secondArgument.value)
         , thirdArgumentReference(fiveArgumentCall.thirdArgument.value)
         , fourthArgumentReference(fiveArgumentCall.fourthArgument.value)
         , fifthArgumentReference(fiveArgumentCall.fifthArgument.value) {}
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
   struct SixArgumentFunctionCallRef
   {
      const ReferenceArgumentStorage<Arg1Type> firstArgumentReference;
      const ReferenceArgumentStorage<Arg2Type> secondArgumentReference;
      const ReferenceArgumentStorage<Arg3Type> thirdArgumentReference;
      const ReferenceArgumentStorage<Arg4Type> fourthArgumentReference;
      const ReferenceArgumentStorage<Arg5Type> fifthArgumentReference;
      const ReferenceArgumentStorage<Arg6Type> sixthArgumentReference;

      SixArgumentFunctionCallRef(
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

      explicit SixArgumentFunctionCallRef(const SixArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& sixArgumentCall)
         : firstArgumentReference(sixArgumentCall.firstArgument.value)
         , secondArgumentReference(sixArgumentCall.secondArgument.value)
         , thirdArgumentReference(sixArgumentCall.thirdArgument.value)
         , fourthArgumentReference(sixArgumentCall.fourthArgument.value)
         , fifthArgumentReference(sixArgumentCall.fifthArgument.value)
         , sixthArgumentReference(sixArgumentCall.sixthArgument.value) {}
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
   struct SevenArgumentFunctionCallRef
   {
      const ReferenceArgumentStorage<Arg1Type> firstArgumentReference;
      const ReferenceArgumentStorage<Arg2Type> secondArgumentReference;
      const ReferenceArgumentStorage<Arg3Type> thirdArgumentReference;
      const ReferenceArgumentStorage<Arg4Type> fourthArgumentReference;
      const ReferenceArgumentStorage<Arg5Type> fifthArgumentReference;
      const ReferenceArgumentStorage<Arg6Type> sixthArgumentReference;
      const ReferenceArgumentStorage<Arg7Type> seventhArgumentReference;

      SevenArgumentFunctionCallRef(
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

      explicit SevenArgumentFunctionCallRef(const SevenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& sevenArgumentCall)
         : firstArgumentReference(sevenArgumentCall.firstArgument.value)
         , secondArgumentReference(sevenArgumentCall.secondArgument.value)
         , thirdArgumentReference(sevenArgumentCall.thirdArgument.value)
         , fourthArgumentReference(sevenArgumentCall.fourthArgument.value)
         , fifthArgumentReference(sevenArgumentCall.fifthArgument.value)
         , sixthArgumentReference(sevenArgumentCall.sixthArgument.value)
         , seventhArgumentReference(sevenArgumentCall.seventhArgument.value) {}
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
   struct EightArgumentFunctionCallRef
   {
      const ReferenceArgumentStorage<Arg1Type> firstArgumentReference;
      const ReferenceArgumentStorage<Arg2Type> secondArgumentReference;
      const ReferenceArgumentStorage<Arg3Type> thirdArgumentReference;
      const ReferenceArgumentStorage<Arg4Type> fourthArgumentReference;
      const ReferenceArgumentStorage<Arg5Type> fifthArgumentReference;
      const ReferenceArgumentStorage<Arg6Type> sixthArgumentReference;
      const ReferenceArgumentStorage<Arg7Type> seventhArgumentReference;
      const ReferenceArgumentStorage<Arg8Type> eigthArgumentReference;

      EightArgumentFunctionCallRef(
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

      explicit EightArgumentFunctionCallRef(const EightArgumentFunctionCall<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& eightArgumentCall)
         : firstArgumentReference(eightArgumentCall.firstArgument.value)
         , secondArgumentReference(eightArgumentCall.secondArgument.value)
         , thirdArgumentReference(eightArgumentCall.thirdArgument.value)
         , fourthArgumentReference(eightArgumentCall.fourthArgument.value)
         , fifthArgumentReference(eightArgumentCall.fifthArgument.value)
         , sixthArgumentReference(eightArgumentCall.sixthArgument.value)
         , seventhArgumentReference(eightArgumentCall.seventhArgument.value)
         , eigthArgumentReference(eightArgumentCall.eigthArgument.value) {}
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
   struct NineArgumentFunctionCallRef
   {
      const ReferenceArgumentStorage<Arg1Type> firstArgumentReference;
      const ReferenceArgumentStorage<Arg2Type> secondArgumentReference;
      const ReferenceArgumentStorage<Arg3Type> thirdArgumentReference;
      const ReferenceArgumentStorage<Arg4Type> fourthArgumentReference;
      const ReferenceArgumentStorage<Arg5Type> fifthArgumentReference;
      const ReferenceArgumentStorage<Arg6Type> sixthArgumentReference;
      const ReferenceArgumentStorage<Arg7Type> seventhArgumentReference;
      const ReferenceArgumentStorage<Arg8Type> eigthArgumentReference;
      const ReferenceArgumentStorage<Arg9Type> ninthArgumentReference;

      NineArgumentFunctionCallRef(
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

      explicit NineArgumentFunctionCallRef(const NineArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& nineArgumentCall)
         : firstArgumentReference(nineArgumentCall.firstArgument.value)
         , secondArgumentReference(nineArgumentCall.secondArgument.value)
         , thirdArgumentReference(nineArgumentCall.thirdArgument.value)
         , fourthArgumentReference(nineArgumentCall.fourthArgument.value)
         , fifthArgumentReference(nineArgumentCall.fifthArgument.value)
         , sixthArgumentReference(nineArgumentCall.sixthArgument.value)
         , seventhArgumentReference(nineArgumentCall.seventhArgument.value)
         , eigthArgumentReference(nineArgumentCall.eigthArgument.value)
         , ninthArgumentReference(nineArgumentCall.ninthArgument.value) {}
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
   struct TenArgumentFunctionCallRef
   {
      const ReferenceArgumentStorage<Arg1Type> firstArgumentReference;
      const ReferenceArgumentStorage<Arg2Type> secondArgumentReference;
      const ReferenceArgumentStorage<Arg3Type> thirdArgumentReference;
      const ReferenceArgumentStorage<Arg4Type> fourthArgumentReference;
      const ReferenceArgumentStorage<Arg5Type> fifthArgumentReference;
      const ReferenceArgumentStorage<Arg6Type> sixthArgumentReference;
      const ReferenceArgumentStorage<Arg7Type> seventhArgumentReference;
      const ReferenceArgumentStorage<Arg8Type> eigthArgumentReference;
      const ReferenceArgumentStorage<Arg9Type> ninthArgumentReference;
      const ReferenceArgumentStorage<Arg10Type> tenthArgumentReference;

      TenArgumentFunctionCallRef(
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

      explicit TenArgumentFunctionCallRef(const TenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& tenArgumentCall)
         : firstArgumentReference(tenArgumentCall.firstArgument.value)
         , secondArgumentReference(tenArgumentCall.secondArgument.value)
         , thirdArgumentReference(tenArgumentCall.thirdArgument.value)
         , fourthArgumentReference(tenArgumentCall.fourthArgument.value)
         , fifthArgumentReference(tenArgumentCall.fifthArgument.value)
         , sixthArgumentReference(tenArgumentCall.sixthArgument.value)
         , seventhArgumentReference(tenArgumentCall.seventhArgument.value)
         , eigthArgumentReference(tenArgumentCall.eigthArgument.value)
         , ninthArgumentReference(tenArgumentCall.ninthArgument.value)
         , tenthArgumentReference(tenArgumentCall.tenthArgument.value) {}
   };

   template<
      typename ArgType,
      typename MockableExceptionThrowerType = ExceptionThrower>
   class OneArgumentMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class OneArgumentMockerTests;
      template<
         typename ZenMockObjectType,
         typename FreeMockType,
         typename NamespaceMockType,
         typename StaticMockType,
         typename StaticNameClashMockType>
      friend class ZenMock1Tester;
   private:
      std::vector<OneArgumentFunctionCall<ArgType>> zenMockObjectCallHistory;
   public:
      explicit OneArgumentMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(const ArgType& argument)
      {
         this->ZenMockThrowIfNotExpected(argument);
         this->zenMockObjectCallHistory.emplace_back(argument);
         this->ZenMockThrowIfExceptionSet();
      }

      FunctionSequencingToken CalledOnceWith(const ArgType& expectedArgument)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, zenMockObjectCallHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument, zenMockObjectCallHistory[0].argument.value, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledOnceWithAny()
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, zenMockObjectCallHistory.size(), this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledNTimesWith(size_t expectedNumberOfCalls, const ArgType& expectedArgument)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, zenMockObjectCallHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex =
               ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArgument, zenMockObjectCallHistory[i].argument.value, zenMockedFunctionSignatureAndCallIndex);
         }
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(const std::vector<OneArgumentFunctionCallRef<ArgType>>& expectedOneArgumentCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedOneArgumentCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<OneArgumentFunctionCallRef<ArgType>> actualOneArgumentCalls = PrivateCallsToCallRefs(zenMockObjectCallHistory);
         VECTORS_EQUAL(expectedOneArgumentCalls, actualOneArgumentCalls, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }
   private:
      static std::vector<OneArgumentFunctionCallRef<ArgType>>
         PrivateCallsToCallRefs(const std::vector<OneArgumentFunctionCall<ArgType>>& zenMockObjectCallHistory)
      {
         std::vector<OneArgumentFunctionCallRef<ArgType>> oneArgumentCallRefs;
         oneArgumentCallRefs.reserve(zenMockObjectCallHistory.size());
         std::for_each(zenMockObjectCallHistory.cbegin(), zenMockObjectCallHistory.cend(),
            [&](const OneArgumentFunctionCall<ArgType>& oneArgumentCall)
         {
            oneArgumentCallRefs.emplace_back(oneArgumentCall);
         });
         return oneArgumentCallRefs;
      }
   };

   template<typename ArgType>
   class VoidOneArgumentMocker : public OneArgumentMocker<ArgType>
   {
   public:
      explicit VoidOneArgumentMocker(const std::string& zenMockedFunctionSignature)
         : OneArgumentMocker<ArgType>(zenMockedFunctionSignature)
      {
      }

      void Expect()
      {
         OneArgumentMocker<ArgType>::_expected = true;
      }
   };

   template<typename FunctionReturnType, typename ArgType>
   class NonVoidOneArgumentMocker : public OneArgumentMocker<ArgType>, protected ValueReturner<FunctionReturnType>
   {
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   public:
      explicit NonVoidOneArgumentMocker(const std::string& zenMockedFunctionSignature)
         : OneArgumentMocker<ArgType>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         OneArgumentMocker<ArgType>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         OneArgumentMocker<ArgType>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         OneArgumentMocker<ArgType>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         OneArgumentMocker<ArgType>::_expected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::ZenMockAddRandomReturnValue();
         return randomReturnValue;
      }

      const FunctionReturnType& ZenMockItAndReturnValue(ArgType argument)
      {
         OneArgumentMocker<ArgType>::ZenMockIt(argument);
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type>
   class NonVoidOneArgFunctionPointerMocker : public NonVoidOneArgumentMocker<FunctionReturnType, Arg1Type>
   {
   public:
      explicit NonVoidOneArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidOneArgumentMocker<FunctionReturnType, Arg1Type>(zenMockedFunctionSignature)
      {
      }

      static const FunctionReturnType& ZenMockItFunctionPointer(
         NonVoidOneArgFunctionPointerMocker* functionMocker, Arg1Type argument)
      {
         return functionMocker->ZenMockItAndReturnValue(argument);
      }
   };

   template<typename Arg1Type>
   class VoidOneArgFunctionPointerMocker : public VoidOneArgumentMocker<Arg1Type>
   {
   public:
      explicit VoidOneArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : VoidOneArgumentMocker<Arg1Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidOneArgFunctionPointerMocker<Arg1Type>* functionMocker, Arg1Type argument)
      {
         functionMocker->ZenMockIt(argument);
      }
   };

   template<
      typename Arg1Type,
      typename Arg2Type,
      typename MockableExceptionThrowerType = ExceptionThrower>
   class TwoArgumentMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class TwoArgumentMockerTests;
   private:
      std::vector<TwoArgumentFunctionCall<Arg1Type, Arg2Type>> zenMockObjectCallHistory;
   public:
      explicit TwoArgumentMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(const Arg1Type& firstArgument, const Arg2Type& secondArgument)
      {
         this->ZenMockThrowIfNotExpected(firstArgument, secondArgument);
         zenMockObjectCallHistory.emplace_back(firstArgument, secondArgument);
         this->ZenMockThrowIfExceptionSet();
      }

      FunctionSequencingToken CalledOnceWith(
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, zenMockObjectCallHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, zenMockObjectCallHistory[0].firstArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, zenMockObjectCallHistory[0].secondArgument.value, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, zenMockObjectCallHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex =
               ZenUnit::String::Concat(this->ZenMockedFunctionSignature, ", at i=", i);
            ARE_EQUAL(expectedFirstArgument, zenMockObjectCallHistory[i].firstArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, zenMockObjectCallHistory[i].secondArgument.value, zenMockedFunctionSignatureAndCallIndex);
         }
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(const std::vector<TwoArgumentFunctionCallRef<Arg1Type, Arg2Type>>& expectedTwoArgumentFunctionCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedTwoArgumentFunctionCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<TwoArgumentFunctionCallRef<Arg1Type, Arg2Type>>
            actualTwoArgumentFunctionCalls = PrivateCallsToCallRefs(zenMockObjectCallHistory);
         VECTORS_EQUAL(expectedTwoArgumentFunctionCalls, actualTwoArgumentFunctionCalls, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }
   private:
      static std::vector<TwoArgumentFunctionCallRef<Arg1Type, Arg2Type>>
         PrivateCallsToCallRefs(const std::vector<TwoArgumentFunctionCall<Arg1Type, Arg2Type>>& zenMockObjectCallHistory)
      {
         std::vector<TwoArgumentFunctionCallRef<Arg1Type, Arg2Type>> twoArgumentCallRefs;
         twoArgumentCallRefs.reserve(zenMockObjectCallHistory.size());
         std::for_each(zenMockObjectCallHistory.cbegin(), zenMockObjectCallHistory.cend(),
            [&](const TwoArgumentFunctionCall<Arg1Type, Arg2Type>& twoArgumentCall)
         {
            twoArgumentCallRefs.emplace_back(twoArgumentCall);
         });
         return twoArgumentCallRefs;
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type>
   class NonVoidTwoArgumentMocker : public TwoArgumentMocker<Arg1Type, Arg2Type>, protected ValueReturner<FunctionReturnType>
   {
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   public:
      explicit NonVoidTwoArgumentMocker(const std::string& zenMockedFunctionSignature)
         : TwoArgumentMocker<Arg1Type, Arg2Type>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         TwoArgumentMocker<Arg1Type, Arg2Type>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         TwoArgumentMocker<Arg1Type, Arg2Type>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(
				std::forward<FirstReturnValue>(firstReturnValue),
				std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         TwoArgumentMocker<Arg1Type, Arg2Type>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         TwoArgumentMocker<Arg1Type, Arg2Type>::_expected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::ZenMockAddRandomReturnValue();
         return randomReturnValue;
      }

      const FunctionReturnType& ZenMockItAndReturnValue(Arg1Type firstArgument, Arg2Type secondArgument)
      {
         TwoArgumentMocker<Arg1Type, Arg2Type>::ZenMockIt(firstArgument, secondArgument);
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type>
   class NonVoidTwoArgFunctionPointerMocker : public NonVoidTwoArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type>
   {
   public:
      explicit NonVoidTwoArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidTwoArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type>(zenMockedFunctionSignature)
      {
      }

      static const FunctionReturnType& ZenMockItFunctionPointer(
         NonVoidTwoArgFunctionPointerMocker<FunctionReturnType, Arg1Type, Arg2Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument)
      {
         return functionMocker->ZenMockItAndReturnValue(firstArgument, secondArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type>
   class VoidTwoArgumentMocker : public TwoArgumentMocker<Arg1Type, Arg2Type>
   {
   public:
      explicit VoidTwoArgumentMocker(const std::string& zenMockedFunctionSignature)
         : TwoArgumentMocker<Arg1Type, Arg2Type>(zenMockedFunctionSignature)
      {
      }

      void Expect()
      {
         TwoArgumentMocker<Arg1Type, Arg2Type>::_expected = true;
      }
   };

   template<typename Arg1Type, typename Arg2Type>
   class VoidTwoArgFunctionPointerMocker : public VoidTwoArgumentMocker<Arg1Type, Arg2Type>
   {
   public:
      explicit VoidTwoArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : VoidTwoArgumentMocker<Arg1Type, Arg2Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidTwoArgFunctionPointerMocker<Arg1Type, Arg2Type>* functionMocker,
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
   class ThreeArgumentMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class ThreeArgumentMockerTests;
   private:
      std::vector<ThreeArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type>> zenMockObjectCallHistory;
   protected:
      std::function<void(Arg1Type, Arg2Type, Arg3Type)> voidThreeArgFunctionToCallInstead;
   public:
      explicit ThreeArgumentMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(const Arg1Type& firstArgument, const Arg2Type& secondArgument, const Arg3Type& thirdArgument)
      {
         this->ZenMockThrowIfNotExpected(firstArgument, secondArgument, thirdArgument);
         this->zenMockObjectCallHistory.emplace_back(firstArgument, secondArgument, thirdArgument);
         if (this->voidThreeArgFunctionToCallInstead)
         {
            this->voidThreeArgFunctionToCallInstead(firstArgument, secondArgument, thirdArgument);
         }
         this->ZenMockThrowIfExceptionSet();
      }

      FunctionSequencingToken CalledOnceWith(
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, this->zenMockObjectCallHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, this->zenMockObjectCallHistory[0].firstArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, this->zenMockObjectCallHistory[0].secondArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, this->zenMockObjectCallHistory[0].thirdArgument.value, this->ZenMockedFunctionSignature);
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
         ARE_EQUAL(expectedNumberOfCalls, this->zenMockObjectCallHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, this->zenMockObjectCallHistory[i].firstArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, this->zenMockObjectCallHistory[i].secondArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, this->zenMockObjectCallHistory[i].thirdArgument.value, zenMockedFunctionSignatureAndCallIndex);
         }
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(const std::vector<ThreeArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type>>& expectedThreeArgumentFunctionCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedThreeArgumentFunctionCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<ThreeArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type>> actualThreeArgumentFunctionCalls = PrivateCallsToCallRefs(zenMockObjectCallHistory);
         VECTORS_EQUAL(expectedThreeArgumentFunctionCalls, actualThreeArgumentFunctionCalls, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

   private:
      static std::vector<ThreeArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type>>
         PrivateCallsToCallRefs(const std::vector<ThreeArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type>>& zenMockObjectCallHistory)
      {
         std::vector<ThreeArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type>> threeArgumentCallRefs;
         threeArgumentCallRefs.reserve(zenMockObjectCallHistory.size());
         std::for_each(zenMockObjectCallHistory.cbegin(), zenMockObjectCallHistory.cend(),
            [&](const ThreeArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type>& threeArgumentCall)
         {
            threeArgumentCallRefs.emplace_back(threeArgumentCall);
         });
         return threeArgumentCallRefs;
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class NonVoidThreeArgumentMocker : public ThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>, protected ValueReturner<FunctionReturnType>
   {
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   public:
      explicit NonVoidThreeArgumentMocker(const std::string& zenMockedFunctionSignature)
         : ThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         ThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         ThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(
				std::forward<FirstReturnValue>(firstReturnValue),
				std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         ThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         ThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>::_expected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::ZenMockAddRandomReturnValue();
         return randomReturnValue;
      }

      const FunctionReturnType& ZenMockItAndReturnValue(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument)
      {
         ThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>::ZenMockIt(firstArgument, secondArgument, thirdArgument);
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class NonVoidThreeArgFunctionPointerMocker : public NonVoidThreeArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type>
   {
   public:
      explicit NonVoidThreeArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidThreeArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type>(zenMockedFunctionSignature)
      {
      }

      static const FunctionReturnType& ZenMockItFunctionPointer(
         NonVoidThreeArgFunctionPointerMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument)
      {
         return functionMocker->ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class VoidThreeArgumentMocker : public ThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>
   {
   public:
      explicit VoidThreeArgumentMocker(const std::string& zenMockedFunctionSignature)
         : ThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>(zenMockedFunctionSignature)
      {
      }

      void Expect()
      {
         ThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>::_expected = true;
      }

      void CallInstead(const std::function<void(Arg1Type, Arg2Type, Arg3Type)>& voidThreeArgFunction)
      {
         ThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>::_expected = true;
         this->voidThreeArgFunctionToCallInstead = voidThreeArgFunction;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class VoidThreeArgFunctionPointerMocker : public VoidThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>
   {
   public:
      explicit VoidThreeArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : VoidThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidThreeArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type>* functionMocker,
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
   class FourArgumentMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class FourArgumentMockerTests;
   private:
      std::vector<FourArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>> zenMockObjectCallHistory;
   public:
      explicit FourArgumentMocker(const std::string& zenMockedFunctionSignature)
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
         zenMockObjectCallHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument);
         this->ZenMockThrowIfExceptionSet();
      }

      FunctionSequencingToken CalledOnceWith(
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, zenMockObjectCallHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, zenMockObjectCallHistory[0].firstArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, zenMockObjectCallHistory[0].secondArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, zenMockObjectCallHistory[0].thirdArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, zenMockObjectCallHistory[0].fourthArgument.value, this->ZenMockedFunctionSignature);
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
         ARE_EQUAL(expectedNumberOfCalls, zenMockObjectCallHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex =
               ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, zenMockObjectCallHistory[i].firstArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, zenMockObjectCallHistory[i].secondArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, zenMockObjectCallHistory[i].thirdArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, zenMockObjectCallHistory[i].fourthArgument.value, zenMockedFunctionSignatureAndCallIndex);
         }
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(const std::vector<FourArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>& expectedFourArgumentFunctionCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedFourArgumentFunctionCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<FourArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
            actualFourArgumentFunctionCalls = PrivateCallsToCallRefs(zenMockObjectCallHistory);
         VECTORS_EQUAL(expectedFourArgumentFunctionCalls, actualFourArgumentFunctionCalls, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

   private:
      static std::vector<FourArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
         PrivateCallsToCallRefs(const std::vector<FourArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>& zenMockObjectCallHistory)
      {
         std::vector<FourArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>> fourArgumentCallRefs;
         fourArgumentCallRefs.reserve(zenMockObjectCallHistory.size());
         std::for_each(zenMockObjectCallHistory.cbegin(), zenMockObjectCallHistory.cend(),
            [&](const FourArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& fourArgumentCall)
         {
            fourArgumentCallRefs.emplace_back(fourArgumentCall);
         });
         return fourArgumentCallRefs;
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class NonVoidFourArgumentMocker : public FourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>, protected ValueReturner<FunctionReturnType>
   {
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   public:
      explicit NonVoidFourArgumentMocker(const std::string& zenMockedFunctionSignature)
         : FourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         FourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         FourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(
				std::forward<FirstReturnValue>(firstReturnValue),
				std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         FourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         FourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::_expected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::ZenMockAddRandomReturnValue();
         return randomReturnValue;
      }

      const FunctionReturnType& ZenMockItAndReturnValue(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument)
      {
         FourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument);
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class NonVoidFourArgFunctionPointerMocker : public NonVoidFourArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>
   {
   public:
      explicit NonVoidFourArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidFourArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>(zenMockedFunctionSignature)
      {
      }

      static const FunctionReturnType& ZenMockItFunctionPointer(
         NonVoidFourArgFunctionPointerMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument)
      {
         return functionMocker->ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class VoidFourArgumentMocker : public FourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>
   {
   public:
      explicit VoidFourArgumentMocker(const std::string& zenMockedFunctionSignature)
         : FourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>(zenMockedFunctionSignature)
      {
      }

      void Expect()
      {
         FourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::_expected = true;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class VoidFourArgFunctionPointerMocker : public VoidFourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>
   {
   public:
      explicit VoidFourArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : VoidFourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidFourArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>* functionMocker,
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
   class FiveArgumentMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class FiveArgumentMockerTests;
   private:
      std::vector<FiveArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>> zenMockObjectCallHistory;
   public:
      explicit FiveArgumentMocker(const std::string& zenMockedFunctionSignature)
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
         zenMockObjectCallHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument);
         this->ZenMockThrowIfExceptionSet();
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
         ARE_EQUAL(expectedNumberOfCalls, zenMockObjectCallHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, zenMockObjectCallHistory[0].firstArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, zenMockObjectCallHistory[0].secondArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, zenMockObjectCallHistory[0].thirdArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, zenMockObjectCallHistory[0].fourthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFifthArgument, zenMockObjectCallHistory[0].fifthArgument.value, this->ZenMockedFunctionSignature);
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
         ARE_EQUAL(expectedNumberOfCalls, zenMockObjectCallHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            std::string zenMockedFunctionSignatureAndCallIndex =
               ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, zenMockObjectCallHistory[i].firstArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, zenMockObjectCallHistory[i].secondArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, zenMockObjectCallHistory[i].thirdArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, zenMockObjectCallHistory[i].fourthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFifthArgument, zenMockObjectCallHistory[i].fifthArgument.value, zenMockedFunctionSignatureAndCallIndex);
         }
			return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(const std::vector<FiveArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>& expectedFiveArgumentFunctionCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedFiveArgumentFunctionCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<FiveArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
            actualFiveArgumentFunctionCalls = PrivateCallsToCallRefs(zenMockObjectCallHistory);
         VECTORS_EQUAL(expectedFiveArgumentFunctionCalls, actualFiveArgumentFunctionCalls, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

   private:
      static std::vector<FiveArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
         PrivateCallsToCallRefs(const std::vector<FiveArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>& zenMockObjectCallHistory)
      {
         std::vector<FiveArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>> fiveArgumentCallRefs;
         fiveArgumentCallRefs.reserve(zenMockObjectCallHistory.size());
         std::for_each(zenMockObjectCallHistory.cbegin(), zenMockObjectCallHistory.cend(),
            [&](const FiveArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& fiveArgumentCall)
         {
            fiveArgumentCallRefs.emplace_back(fiveArgumentCall);
         });
         return fiveArgumentCallRefs;
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   class NonVoidFiveArgumentMocker : public FiveArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>, protected ValueReturner<FunctionReturnType>
   {
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   public:
      explicit NonVoidFiveArgumentMocker(const std::string& zenMockedFunctionSignature)
         : FiveArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         FiveArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         FiveArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(
				std::forward<FirstReturnValue>(firstReturnValue),
				std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         FiveArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         FiveArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::_expected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::ZenMockAddRandomReturnValue();
         return randomReturnValue;
      }

      const FunctionReturnType& ZenMockItAndReturnValue(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument)
      {
         FiveArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument);
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   class NonVoidFiveArgFunctionPointerMocker : public NonVoidFiveArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>
   {
   public:
      explicit NonVoidFiveArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidFiveArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>(zenMockedFunctionSignature)
      {
      }

      static const FunctionReturnType& ZenMockItFunctionPointer(
         NonVoidFiveArgFunctionPointerMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument)
      {
         return functionMocker->ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   class VoidFiveArgumentMocker : public FiveArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>
   {
   public:
      explicit VoidFiveArgumentMocker(const std::string& zenMockedFunctionSignature)
         : FiveArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>(zenMockedFunctionSignature)
      {
      }

      void Expect()
      {
         FiveArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::_expected = true;
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
   class SixArgumentMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class SixArgumentMockerTests;
   private:
      std::vector<SixArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>> zenMockObjectCallHistory;
   public:
      explicit SixArgumentMocker(const std::string& zenMockedFunctionSignature)
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
         zenMockObjectCallHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument);
         this->ZenMockThrowIfExceptionSet();
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
         ARE_EQUAL(expectedNumberOfCalls, zenMockObjectCallHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, zenMockObjectCallHistory[0].firstArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, zenMockObjectCallHistory[0].secondArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, zenMockObjectCallHistory[0].thirdArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, zenMockObjectCallHistory[0].fourthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFifthArgument, zenMockObjectCallHistory[0].fifthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSixthArgument, zenMockObjectCallHistory[0].sixthArgument.value, this->ZenMockedFunctionSignature);
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
         ARE_EQUAL(expectedNumberOfCalls, zenMockObjectCallHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex =
               ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, zenMockObjectCallHistory[i].firstArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, zenMockObjectCallHistory[i].secondArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, zenMockObjectCallHistory[i].thirdArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, zenMockObjectCallHistory[i].fourthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFifthArgument, zenMockObjectCallHistory[i].fifthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSixthArgument, zenMockObjectCallHistory[i].sixthArgument.value, zenMockedFunctionSignatureAndCallIndex);
         }
			return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(const std::vector<SixArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>& expectedSixArgumentFunctionCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedSixArgumentFunctionCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<SixArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
            actualSixArgumentFunctionCalls = PrivateCallsToCallRefs(zenMockObjectCallHistory);
         VECTORS_EQUAL(expectedSixArgumentFunctionCalls, actualSixArgumentFunctionCalls, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

   private:
      static std::vector<SixArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
         PrivateCallsToCallRefs(const std::vector<SixArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>& zenMockObjectCallHistory)
      {
         std::vector<SixArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>> sixArgumentCallRefs;
         sixArgumentCallRefs.reserve(zenMockObjectCallHistory.size());
         std::for_each(zenMockObjectCallHistory.cbegin(), zenMockObjectCallHistory.cend(),
            [&](const SixArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& sixArgumentCall)
         {
            sixArgumentCallRefs.emplace_back(sixArgumentCall);
         });
         return sixArgumentCallRefs;
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   class NonVoidSixArgumentMocker : public SixArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>, protected ValueReturner<FunctionReturnType>
   {
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   public:
      explicit NonVoidSixArgumentMocker(const std::string& zenMockedFunctionSignature)
         : SixArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         SixArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         SixArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(
				std::forward<FirstReturnValue>(firstReturnValue),
				std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         SixArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         SixArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>::_expected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::ZenMockAddRandomReturnValue();
         return randomReturnValue;
      }

      const FunctionReturnType& ZenMockItAndReturnValue(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument)
      {
         SixArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ExceptionThrower>::ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument);
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   class NonVoidSixArgFunctionPointerMocker : public NonVoidSixArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>
   {
   public:
      explicit NonVoidSixArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidSixArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>(zenMockedFunctionSignature)
      {
      }

      static const FunctionReturnType& ZenMockItFunctionPointer(
         NonVoidSixArgFunctionPointerMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument)
      {
         return functionMocker->ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   class VoidSixArgumentMocker : public SixArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>
   {
   public:
      explicit VoidSixArgumentMocker(const std::string& zenMockedFunctionSignature)
         : SixArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>(zenMockedFunctionSignature)
      {
      }

      void Expect()
      {
         SixArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>::_expected = true;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   class VoidSixArgFunctionPointerMocker : public VoidSixArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>
   {
   public:
      explicit VoidSixArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : VoidSixArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidSixArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>* functionMocker,
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
   class SevenArgumentMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class SevenArgumentMockerTests;
   private:
      std::vector<SevenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>> zenMockObjectCallHistory;
   public:
      explicit SevenArgumentMocker(const std::string& zenMockedFunctionSignature)
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
         zenMockObjectCallHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument);
         this->ZenMockThrowIfExceptionSet();
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
         ARE_EQUAL(expectedNumberOfCalls, zenMockObjectCallHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, zenMockObjectCallHistory[0].firstArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, zenMockObjectCallHistory[0].secondArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, zenMockObjectCallHistory[0].thirdArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, zenMockObjectCallHistory[0].fourthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFifthArgument, zenMockObjectCallHistory[0].fifthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSixthArgument, zenMockObjectCallHistory[0].sixthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSeventhArgument, zenMockObjectCallHistory[0].seventhArgument.value, this->ZenMockedFunctionSignature);
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
         ARE_EQUAL(expectedNumberOfCalls, zenMockObjectCallHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex =
               ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, zenMockObjectCallHistory[i].firstArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, zenMockObjectCallHistory[i].secondArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, zenMockObjectCallHistory[i].thirdArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, zenMockObjectCallHistory[i].fourthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFifthArgument, zenMockObjectCallHistory[i].fifthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSixthArgument, zenMockObjectCallHistory[i].sixthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSeventhArgument, zenMockObjectCallHistory[i].seventhArgument.value, zenMockedFunctionSignatureAndCallIndex);
         }
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(const std::vector<SevenArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>& expectedSevenArgumentFunctionCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedSevenArgumentFunctionCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<SevenArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
            actualSevenArgumentFunctionCalls = PrivateCallsToCallRefs(zenMockObjectCallHistory);
         VECTORS_EQUAL(expectedSevenArgumentFunctionCalls, actualSevenArgumentFunctionCalls, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

   private:
      static std::vector<SevenArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
         PrivateCallsToCallRefs(const std::vector<SevenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>& zenMockObjectCallHistory)
      {
         std::vector<SevenArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>> sevenArgumentCallRefs;
         sevenArgumentCallRefs.reserve(zenMockObjectCallHistory.size());
         std::for_each(zenMockObjectCallHistory.cbegin(), zenMockObjectCallHistory.cend(),
            [&](const SevenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& sevenArgumentCall)
         {
            sevenArgumentCallRefs.emplace_back(sevenArgumentCall);
         });
         return sevenArgumentCallRefs;
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   class NonVoidSevenArgumentMocker : public SevenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ExceptionThrower>, protected ValueReturner<FunctionReturnType>
   {
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   public:
      explicit NonVoidSevenArgumentMocker(const std::string& zenMockedFunctionSignature)
         : SevenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         SevenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ExceptionThrower>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         SevenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ExceptionThrower>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(
				std::forward<FirstReturnValue>(firstReturnValue),
				std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         SevenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ExceptionThrower>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         SevenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ExceptionThrower>::_expected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::ZenMockAddRandomReturnValue();
         return randomReturnValue;
      }

      const FunctionReturnType& ZenMockItAndReturnValue(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument)
      {
         SevenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>::ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument);
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   class NonVoidSevenArgFunctionPointerMocker : public NonVoidSevenArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>
   {
   public:
      explicit NonVoidSevenArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidSevenArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>(zenMockedFunctionSignature)
      {
      }

      static const FunctionReturnType& ZenMockItFunctionPointer(
         NonVoidSevenArgFunctionPointerMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument)
      {
         return functionMocker->ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   class VoidSevenArgumentMocker : public SevenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ExceptionThrower>
   {
   public:
      explicit VoidSevenArgumentMocker(const std::string& zenMockedFunctionSignature)
         : SevenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>(zenMockedFunctionSignature)
      {
      }

      void Expect()
      {
         SevenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ExceptionThrower>::_expected = true;
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
   class EightArgumentMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class EightArgumentMockerTests;
   private:
      std::vector<EightArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>> zenMockObjectCallHistory;
   public:
      explicit EightArgumentMocker(const std::string& zenMockedFunctionSignature)
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
         zenMockObjectCallHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument);
         this->ZenMockThrowIfExceptionSet();
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
         ARE_EQUAL(expectedNumberOfCalls, zenMockObjectCallHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, zenMockObjectCallHistory[0].firstArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, zenMockObjectCallHistory[0].secondArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, zenMockObjectCallHistory[0].thirdArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, zenMockObjectCallHistory[0].fourthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFifthArgument, zenMockObjectCallHistory[0].fifthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSixthArgument, zenMockObjectCallHistory[0].sixthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSeventhArgument, zenMockObjectCallHistory[0].seventhArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedEigthArgument, zenMockObjectCallHistory[0].eigthArgument.value, this->ZenMockedFunctionSignature);
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
         ARE_EQUAL(expectedNumberOfCalls, zenMockObjectCallHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex =
               ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, zenMockObjectCallHistory[i].firstArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, zenMockObjectCallHistory[i].secondArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, zenMockObjectCallHistory[i].thirdArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, zenMockObjectCallHistory[i].fourthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFifthArgument, zenMockObjectCallHistory[i].fifthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSixthArgument, zenMockObjectCallHistory[i].sixthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSeventhArgument, zenMockObjectCallHistory[i].seventhArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedEigthArgument, zenMockObjectCallHistory[i].eigthArgument.value, zenMockedFunctionSignatureAndCallIndex);
         }
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(const std::vector<EightArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>>& expectedEightArgumentFunctionCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedEightArgumentFunctionCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<EightArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
            actualEightArgumentFunctionCalls = PrivateCallsToCallRefs(zenMockObjectCallHistory);
         VECTORS_EQUAL(expectedEightArgumentFunctionCalls, actualEightArgumentFunctionCalls, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

   private:
      static std::vector<EightArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
         PrivateCallsToCallRefs(const std::vector<EightArgumentFunctionCall<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>>& zenMockObjectCallHistory)
      {
         std::vector<EightArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>> eightArgumentCallRefs;
         eightArgumentCallRefs.reserve(zenMockObjectCallHistory.size());
         std::for_each(zenMockObjectCallHistory.cbegin(), zenMockObjectCallHistory.cend(),
            [&](const EightArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& eightArgumentCall)
         {
            eightArgumentCallRefs.emplace_back(eightArgumentCall);
         });
         return eightArgumentCallRefs;
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
   class NonVoidEightArgumentMocker : public EightArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ExceptionThrower>, protected ValueReturner<FunctionReturnType>
   {
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   public:
      explicit NonVoidEightArgumentMocker(const std::string& zenMockedFunctionSignature)
         : EightArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         EightArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ExceptionThrower>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         EightArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ExceptionThrower>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(
				std::forward<FirstReturnValue>(firstReturnValue),
				std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         EightArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ExceptionThrower>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         EightArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ExceptionThrower>::_expected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::ZenMockAddRandomReturnValue();
         return randomReturnValue;
      }

      const FunctionReturnType& ZenMockItAndReturnValue(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument)
      {
         EightArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>::ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument);
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
   class NonVoidEightArgFunctionPointerMocker : public NonVoidEightArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>
   {
   public:
      explicit NonVoidEightArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidEightArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>(zenMockedFunctionSignature)
      {
      }

      static const FunctionReturnType& ZenMockItFunctionPointer(
         NonVoidEightArgFunctionPointerMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument)
      {
         return functionMocker->ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
   class VoidEightArgumentMocker : public EightArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ExceptionThrower>
   {
   public:
      explicit VoidEightArgumentMocker(const std::string& zenMockedFunctionSignature)
         : EightArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>(zenMockedFunctionSignature)
      {
      }

      void Expect()
      {
         EightArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ExceptionThrower>::_expected = true;
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
   class NineArgumentMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class NineArgumentMockerTests;
   private:
      std::vector<NineArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>> zenMockObjectCallHistory;
   public:
      explicit NineArgumentMocker(const std::string& zenMockedFunctionSignature)
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
         zenMockObjectCallHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument);
         this->ZenMockThrowIfExceptionSet();
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
         ARE_EQUAL(expectedNumberOfCalls, zenMockObjectCallHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, zenMockObjectCallHistory[0].firstArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, zenMockObjectCallHistory[0].secondArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, zenMockObjectCallHistory[0].thirdArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, zenMockObjectCallHistory[0].fourthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFifthArgument, zenMockObjectCallHistory[0].fifthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSixthArgument, zenMockObjectCallHistory[0].sixthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSeventhArgument, zenMockObjectCallHistory[0].seventhArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedEigthArgument, zenMockObjectCallHistory[0].eigthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedNinthArgument, zenMockObjectCallHistory[0].ninthArgument.value, this->ZenMockedFunctionSignature);
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
         ARE_EQUAL(expectedNumberOfCalls, zenMockObjectCallHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex =
               ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, zenMockObjectCallHistory[i].firstArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, zenMockObjectCallHistory[i].secondArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, zenMockObjectCallHistory[i].thirdArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, zenMockObjectCallHistory[i].fourthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFifthArgument, zenMockObjectCallHistory[i].fifthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSixthArgument, zenMockObjectCallHistory[i].sixthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSeventhArgument, zenMockObjectCallHistory[i].seventhArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedEigthArgument, zenMockObjectCallHistory[i].eigthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedNinthArgument, zenMockObjectCallHistory[i].ninthArgument.value, zenMockedFunctionSignatureAndCallIndex);
         }
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(const std::vector<NineArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>& expectedNineArgumentFunctionCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedNineArgumentFunctionCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<NineArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
            actualNineArgumentFunctionCalls = PrivateCallsToCallRefs(zenMockObjectCallHistory);
         VECTORS_EQUAL(expectedNineArgumentFunctionCalls, actualNineArgumentFunctionCalls, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

   private:
      static std::vector<NineArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
         PrivateCallsToCallRefs(const std::vector<NineArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>& zenMockObjectCallHistory)
      {
         std::vector<NineArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>> nineArgumentCallRefs;
         nineArgumentCallRefs.reserve(zenMockObjectCallHistory.size());
         std::for_each(zenMockObjectCallHistory.cbegin(), zenMockObjectCallHistory.cend(),
            [&](const NineArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& nineArgumentCall)
         {
            nineArgumentCallRefs.emplace_back(nineArgumentCall);
         });
         return nineArgumentCallRefs;
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
   class NonVoidNineArgumentMocker : public NineArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ExceptionThrower>, protected ValueReturner<FunctionReturnType>
   {
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   public:
      explicit NonVoidNineArgumentMocker(const std::string& zenMockedFunctionSignature)
         : NineArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         NineArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ExceptionThrower>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         NineArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ExceptionThrower>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(
				std::forward<FirstReturnValue>(firstReturnValue),
				std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         NineArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ExceptionThrower>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         NineArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ExceptionThrower>::_expected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::ZenMockAddRandomReturnValue();
         return randomReturnValue;
      }

      const FunctionReturnType& ZenMockItAndReturnValue(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument, Arg9Type ninthArgument)
      {
         NineArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>::ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument);
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
   class NonVoidNineArgFunctionPointerMocker : public NonVoidNineArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>
   {
   public:
      explicit NonVoidNineArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidNineArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>(zenMockedFunctionSignature)
      {
      }

      static const FunctionReturnType& ZenMockItFunctionPointer(
         NonVoidNineArgFunctionPointerMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument, Arg9Type ninthArgument)
      {
         return functionMocker->ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
   class VoidNineArgumentMocker : public NineArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ExceptionThrower>
   {
   public:
      explicit VoidNineArgumentMocker(const std::string& zenMockedFunctionSignature)
         : NineArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>(zenMockedFunctionSignature)
      {
      }

      void Expect()
      {
         NineArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ExceptionThrower>::_expected = true;
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
   class TenArgumentMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class TenArgumentMockerTests;
   private:
      std::vector<TenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>> zenMockObjectCallHistory;
   public:
      explicit TenArgumentMocker(const std::string& zenMockedFunctionSignature)
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
         zenMockObjectCallHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument, tenthArgument);
         this->ZenMockThrowIfExceptionSet();
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
         ARE_EQUAL(expectedNumberOfCalls, zenMockObjectCallHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, zenMockObjectCallHistory[0].firstArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, zenMockObjectCallHistory[0].secondArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, zenMockObjectCallHistory[0].thirdArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, zenMockObjectCallHistory[0].fourthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFifthArgument, zenMockObjectCallHistory[0].fifthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSixthArgument, zenMockObjectCallHistory[0].sixthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSeventhArgument, zenMockObjectCallHistory[0].seventhArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedEigthArgument, zenMockObjectCallHistory[0].eigthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedNinthArgument, zenMockObjectCallHistory[0].ninthArgument.value, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedTenthArgument, zenMockObjectCallHistory[0].tenthArgument.value, this->ZenMockedFunctionSignature);
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
         ARE_EQUAL(expectedNumberOfCalls, zenMockObjectCallHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex =
               ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, zenMockObjectCallHistory[i].firstArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, zenMockObjectCallHistory[i].secondArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, zenMockObjectCallHistory[i].thirdArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, zenMockObjectCallHistory[i].fourthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFifthArgument, zenMockObjectCallHistory[i].fifthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSixthArgument, zenMockObjectCallHistory[i].sixthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSeventhArgument, zenMockObjectCallHistory[i].seventhArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedEigthArgument, zenMockObjectCallHistory[i].eigthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedNinthArgument, zenMockObjectCallHistory[i].ninthArgument.value, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedTenthArgument, zenMockObjectCallHistory[i].tenthArgument.value, zenMockedFunctionSignatureAndCallIndex);
         }
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(const std::vector<TenArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>& expectedTenArgumentFunctionCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedTenArgumentFunctionCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<TenArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>
            actualTenArgumentFunctionCalls = PrivateCallsToCallRefs(zenMockObjectCallHistory);
         VECTORS_EQUAL(expectedTenArgumentFunctionCalls, actualTenArgumentFunctionCalls, this->ZenMockedFunctionSignature);
         return FunctionSequencingToken();
      }

   private:
      static std::vector<TenArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>
         PrivateCallsToCallRefs(const std::vector<TenArgumentFunctionCall<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>& zenMockObjectCallHistory)
      {
         std::vector<TenArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>> tenArgumentCallRefs;
         tenArgumentCallRefs.reserve(zenMockObjectCallHistory.size());
         std::for_each(zenMockObjectCallHistory.cbegin(), zenMockObjectCallHistory.cend(),
            [&](const TenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& tenArgumentCall)
         {
            tenArgumentCallRefs.emplace_back(tenArgumentCall);
         });
         return tenArgumentCallRefs;
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
   class NonVoidTenArgumentMocker : public TenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ExceptionThrower>, protected ValueReturner<FunctionReturnType>
   {
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   public:
      explicit NonVoidTenArgumentMocker(const std::string& zenMockedFunctionSignature)
         : TenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(zenMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(zenMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         TenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ExceptionThrower>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         TenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ExceptionThrower>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(
				std::forward<FirstReturnValue>(firstReturnValue),
				std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         TenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ExceptionThrower>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         TenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ExceptionThrower>::_expected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::ZenMockAddRandomReturnValue();
         return randomReturnValue;
      }

      const FunctionReturnType& ZenMockItAndReturnValue(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument, Arg9Type ninthArgument, Arg10Type tenthArgument)
      {
         TenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>::ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument, tenthArgument);
         return ValueReturner<FunctionReturnType>::ZenMockNextReturnValue();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
   class NonVoidTenArgFunctionPointerMocker : public NonVoidTenArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>
   {
   public:
      explicit NonVoidTenArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : NonVoidTenArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(zenMockedFunctionSignature) {}

      static const FunctionReturnType& ZenMockItFunctionPointer(
         NonVoidTenArgFunctionPointerMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument, Arg9Type ninthArgument, Arg10Type tenthArgument)
      {
         return functionMocker->ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument, tenthArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
   class VoidTenArgumentMocker : public TenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ExceptionThrower>
   {
   public:
      explicit VoidTenArgumentMocker(const std::string& zenMockedFunctionSignature)
         : TenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(zenMockedFunctionSignature) {}

      void Expect()
      {
         TenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ExceptionThrower>::_expected = true;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
   class VoidTenArgFunctionPointerMocker : public VoidTenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>
   {
   public:
      explicit VoidTenArgFunctionPointerMocker(const std::string& zenMockedFunctionSignature)
         : VoidTenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(zenMockedFunctionSignature) {}

      static void ZenMockItFunctionPointer(
         VoidTenArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>* functionMocker,
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
   struct Equalizer<ZenMock::OneArgumentFunctionCall<ArgType>>
   {
      static void AssertEqual(
         const ZenMock::OneArgumentFunctionCall<ArgType>& expectedOneArgumentCall,
         const ZenMock::OneArgumentFunctionCall<ArgType>& actualOneArgumentCall)
      {
         ARE_EQUAL(expectedOneArgumentCall.argument.value, actualOneArgumentCall.argument.value);
      }
   };

   template<typename ArgType>
   struct Equalizer<ZenMock::OneArgumentFunctionCallRef<ArgType>>
   {
      static void AssertEqual(
         const ZenMock::OneArgumentFunctionCallRef<ArgType>& expectedOneArgumentCall,
         const ZenMock::OneArgumentFunctionCallRef<ArgType>& actualOneArgumentCall)
      {
         ARE_EQUAL(expectedOneArgumentCall.argumentReference.value, actualOneArgumentCall.argumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type>
   struct Equalizer<ZenMock::TwoArgumentFunctionCall<Arg1Type, Arg2Type>>
   {
      static void AssertEqual(
         const ZenMock::TwoArgumentFunctionCall<Arg1Type, Arg2Type>& expectedTwoArgumentFunctionCall,
         const ZenMock::TwoArgumentFunctionCall<Arg1Type, Arg2Type>& actualTwoArgumentFunctionCall)
      {
         ARE_EQUAL(expectedTwoArgumentFunctionCall.firstArgument.value, actualTwoArgumentFunctionCall.firstArgument.value);
         ARE_EQUAL(expectedTwoArgumentFunctionCall.secondArgument.value, actualTwoArgumentFunctionCall.secondArgument.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type>
   struct Equalizer<ZenMock::TwoArgumentFunctionCallRef<Arg1Type, Arg2Type>>
   {
      static void AssertEqual(
         const ZenMock::TwoArgumentFunctionCallRef<Arg1Type, Arg2Type>& expectedTwoArgumentFunctionCall,
         const ZenMock::TwoArgumentFunctionCallRef<Arg1Type, Arg2Type>& actualTwoArgumentFunctionCall)
      {
         ARE_EQUAL(expectedTwoArgumentFunctionCall.firstArgumentReference.value, actualTwoArgumentFunctionCall.firstArgumentReference.value);
         ARE_EQUAL(expectedTwoArgumentFunctionCall.secondArgumentReference.value, actualTwoArgumentFunctionCall.secondArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   struct Equalizer<ZenMock::ThreeArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type>>
   {
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
   struct Equalizer<ZenMock::ThreeArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type>>
   {
      static void AssertEqual(
         const ZenMock::ThreeArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type>& expectedThreeArgumentFunctionCall,
         const ZenMock::ThreeArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type>& actualThreeArgumentFunctionCall)
      {
         ARE_EQUAL(expectedThreeArgumentFunctionCall.firstArgumentReference.value, actualThreeArgumentFunctionCall.firstArgumentReference.value);
         ARE_EQUAL(expectedThreeArgumentFunctionCall.secondArgumentReference.value, actualThreeArgumentFunctionCall.secondArgumentReference.value);
         ARE_EQUAL(expectedThreeArgumentFunctionCall.thirdArgumentReference.value, actualThreeArgumentFunctionCall.thirdArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   struct Equalizer<ZenMock::FourArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
   {
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
   struct Equalizer<ZenMock::FourArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
   {
      static void AssertEqual(
         const ZenMock::FourArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& expectedFourArgumentFunctionCall,
         const ZenMock::FourArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& actualFourArgumentFunctionCall)
      {
         ARE_EQUAL(expectedFourArgumentFunctionCall.firstArgumentReference.value, actualFourArgumentFunctionCall.firstArgumentReference.value);
         ARE_EQUAL(expectedFourArgumentFunctionCall.secondArgumentReference.value, actualFourArgumentFunctionCall.secondArgumentReference.value);
         ARE_EQUAL(expectedFourArgumentFunctionCall.thirdArgumentReference.value, actualFourArgumentFunctionCall.thirdArgumentReference.value);
         ARE_EQUAL(expectedFourArgumentFunctionCall.fourthArgumentReference.value, actualFourArgumentFunctionCall.fourthArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   struct Equalizer<ZenMock::FiveArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
   {
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
   struct Equalizer<ZenMock::FiveArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
   {
      static void AssertEqual(
         const ZenMock::FiveArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& expectedFiveArgumentFunctionCall,
         const ZenMock::FiveArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& actualFiveArgumentFunctionCall)
      {
         ARE_EQUAL(expectedFiveArgumentFunctionCall.firstArgumentReference.value, actualFiveArgumentFunctionCall.firstArgumentReference.value);
         ARE_EQUAL(expectedFiveArgumentFunctionCall.secondArgumentReference.value, actualFiveArgumentFunctionCall.secondArgumentReference.value);
         ARE_EQUAL(expectedFiveArgumentFunctionCall.thirdArgumentReference.value, actualFiveArgumentFunctionCall.thirdArgumentReference.value);
         ARE_EQUAL(expectedFiveArgumentFunctionCall.fourthArgumentReference.value, actualFiveArgumentFunctionCall.fourthArgumentReference.value);
         ARE_EQUAL(expectedFiveArgumentFunctionCall.fifthArgumentReference.value, actualFiveArgumentFunctionCall.fifthArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   struct Equalizer<ZenMock::SixArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
   {
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
   struct Equalizer<ZenMock::SixArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
   {
      static void AssertEqual(
         const ZenMock::SixArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& expectedSixArgumentFunctionCall,
         const ZenMock::SixArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& actualSixArgumentFunctionCall)
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
   struct Equalizer<ZenMock::SevenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
   {
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
   struct Equalizer<ZenMock::SevenArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
   {
      static void AssertEqual(
         const ZenMock::SevenArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& expectedSevenArgumentFunctionCall,
         const ZenMock::SevenArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& actualSevenArgumentFunctionCall)
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
   struct Equalizer<ZenMock::EightArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
   {
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
   struct Equalizer<ZenMock::EightArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
   {
      static void AssertEqual(
         const ZenMock::EightArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& expectedEightArgumentFunctionCall,
         const ZenMock::EightArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& actualEightArgumentFunctionCall)
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
   struct Equalizer<ZenMock::NineArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
   {
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
   struct Equalizer<ZenMock::NineArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
   {
      static void AssertEqual(
         const ZenMock::NineArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& expectedNineArgumentFunctionCall,
         const ZenMock::NineArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& actualNineArgumentFunctionCall)
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
   struct Equalizer<ZenMock::TenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>
   {
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
   struct Equalizer<ZenMock::TenArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>
   {
      static void AssertEqual(
         const ZenMock::TenArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& expectedTenArgumentFunctionCall,
         const ZenMock::TenArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& actualTenArgumentFunctionCall)
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
   struct Printer<ZenMock::OneArgumentFunctionCallRef<ArgType>>
   {
      static void Print(std::ostream& os, const ZenMock::OneArgumentFunctionCallRef<ArgType>& oneArgumentCall)
      {
         os << "ZenMock::OneArgumentCall:\n" <<
               "Argument: " << ZenUnit::ToStringer::ToString(oneArgumentCall.argumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type>
   struct Printer<ZenMock::TwoArgumentFunctionCallRef<Arg1Type, Arg2Type>>
   {
      static void Print(std::ostream& os, const ZenMock::TwoArgumentFunctionCallRef<Arg1Type, Arg2Type>& twoArgumentCallRef)
      {
         os << "ZenMock::TwoArgumentFunctionCall:\n"
               "Argument1: " << ZenUnit::ToStringer::ToString(twoArgumentCallRef.firstArgumentReference.value) << '\n' <<
               "Argument2: " << ZenUnit::ToStringer::ToString(twoArgumentCallRef.secondArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   struct Printer<ZenMock::ThreeArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type>>
   {
      static void Print(std::ostream& os, const ZenMock::ThreeArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type>& threeArgumentCallRef)
      {
         os << "ZenMock::ThreeArgumentFunctionCall:\n"
               "Argument1: " << ZenUnit::ToStringer::ToString(threeArgumentCallRef.firstArgumentReference.value) << '\n' <<
               "Argument2: " << ZenUnit::ToStringer::ToString(threeArgumentCallRef.secondArgumentReference.value) << '\n' <<
               "Argument3: " << ZenUnit::ToStringer::ToString(threeArgumentCallRef.thirdArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   struct Printer<ZenMock::FourArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
   {
      static void Print(std::ostream& os, const ZenMock::FourArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& fourArgumentCallRef)
      {
         os << "ZenMock::FourArgumentFunctionCall:\n"
               "Argument1: " << ZenUnit::ToStringer::ToString(fourArgumentCallRef.firstArgumentReference.value) << '\n' <<
               "Argument2: " << ZenUnit::ToStringer::ToString(fourArgumentCallRef.secondArgumentReference.value) << '\n' <<
               "Argument3: " << ZenUnit::ToStringer::ToString(fourArgumentCallRef.thirdArgumentReference.value) << '\n' <<
               "Argument4: " << ZenUnit::ToStringer::ToString(fourArgumentCallRef.fourthArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   struct Printer<ZenMock::FiveArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
   {
      static void Print(std::ostream& os, const ZenMock::FiveArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& fiveArgumentCallRef)
      {
         os << "ZenMock::FiveArgumentFunctionCall:\n"
               "Argument1: " << ZenUnit::ToStringer::ToString(fiveArgumentCallRef.firstArgumentReference.value) << '\n' <<
               "Argument2: " << ZenUnit::ToStringer::ToString(fiveArgumentCallRef.secondArgumentReference.value) << '\n' <<
               "Argument3: " << ZenUnit::ToStringer::ToString(fiveArgumentCallRef.thirdArgumentReference.value) << '\n' <<
               "Argument4: " << ZenUnit::ToStringer::ToString(fiveArgumentCallRef.fourthArgumentReference.value) << '\n' <<
               "Argument5: " << ZenUnit::ToStringer::ToString(fiveArgumentCallRef.fifthArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   struct Printer<ZenMock::SixArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
   {
      static void Print(std::ostream& os, const ZenMock::SixArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& sixArgumentCallRef)
      {
         os << "ZenMock::SixArgumentFunctionCall:\n"
               "Argument1: " << ZenUnit::ToStringer::ToString(sixArgumentCallRef.firstArgumentReference.value) << '\n' <<
               "Argument2: " << ZenUnit::ToStringer::ToString(sixArgumentCallRef.secondArgumentReference.value) << '\n' <<
               "Argument3: " << ZenUnit::ToStringer::ToString(sixArgumentCallRef.thirdArgumentReference.value) << '\n' <<
               "Argument4: " << ZenUnit::ToStringer::ToString(sixArgumentCallRef.fourthArgumentReference.value) << '\n' <<
               "Argument5: " << ZenUnit::ToStringer::ToString(sixArgumentCallRef.fifthArgumentReference.value) << '\n' <<
               "Argument6: " << ZenUnit::ToStringer::ToString(sixArgumentCallRef.sixthArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   struct Printer<ZenMock::SevenArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
   {
      static void Print(std::ostream& os, const ZenMock::SevenArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& sevenArgumentCallRef)
      {
         os << "ZenMock::SevenArgumentFunctionCall:\n"
               "Argument1: " << ZenUnit::ToStringer::ToString(sevenArgumentCallRef.firstArgumentReference.value) << '\n' <<
               "Argument2: " << ZenUnit::ToStringer::ToString(sevenArgumentCallRef.secondArgumentReference.value) << '\n' <<
               "Argument3: " << ZenUnit::ToStringer::ToString(sevenArgumentCallRef.thirdArgumentReference.value) << '\n' <<
               "Argument4: " << ZenUnit::ToStringer::ToString(sevenArgumentCallRef.fourthArgumentReference.value) << '\n' <<
               "Argument5: " << ZenUnit::ToStringer::ToString(sevenArgumentCallRef.fifthArgumentReference.value) << '\n' <<
               "Argument6: " << ZenUnit::ToStringer::ToString(sevenArgumentCallRef.sixthArgumentReference.value) << '\n' <<
               "Argument7: " << ZenUnit::ToStringer::ToString(sevenArgumentCallRef.seventhArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
   struct Printer<ZenMock::EightArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
   {
      static void Print(std::ostream& os, const ZenMock::EightArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& eightArgumentCallRef)
      {
         os << "ZenMock::EightArgumentFunctionCall:\n"
               "Argument1: " << ZenUnit::ToStringer::ToString(eightArgumentCallRef.firstArgumentReference.value) << '\n' <<
               "Argument2: " << ZenUnit::ToStringer::ToString(eightArgumentCallRef.secondArgumentReference.value) << '\n' <<
               "Argument3: " << ZenUnit::ToStringer::ToString(eightArgumentCallRef.thirdArgumentReference.value) << '\n' <<
               "Argument4: " << ZenUnit::ToStringer::ToString(eightArgumentCallRef.fourthArgumentReference.value) << '\n' <<
               "Argument5: " << ZenUnit::ToStringer::ToString(eightArgumentCallRef.fifthArgumentReference.value) << '\n' <<
               "Argument6: " << ZenUnit::ToStringer::ToString(eightArgumentCallRef.sixthArgumentReference.value) << '\n' <<
               "Argument7: " << ZenUnit::ToStringer::ToString(eightArgumentCallRef.seventhArgumentReference.value) << '\n' <<
               "Argument8: " << ZenUnit::ToStringer::ToString(eightArgumentCallRef.eigthArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
   struct Printer<ZenMock::NineArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
   {
      static void Print(std::ostream& os, const ZenMock::NineArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& nineArgumentCallRef)
      {
         os << "ZenMock::NineArgumentFunctionCall:\n"
               "Argument1: " << ZenUnit::ToStringer::ToString(nineArgumentCallRef.firstArgumentReference.value) << '\n' <<
               "Argument2: " << ZenUnit::ToStringer::ToString(nineArgumentCallRef.secondArgumentReference.value) << '\n' <<
               "Argument3: " << ZenUnit::ToStringer::ToString(nineArgumentCallRef.thirdArgumentReference.value) << '\n' <<
               "Argument4: " << ZenUnit::ToStringer::ToString(nineArgumentCallRef.fourthArgumentReference.value) << '\n' <<
               "Argument5: " << ZenUnit::ToStringer::ToString(nineArgumentCallRef.fifthArgumentReference.value) << '\n' <<
               "Argument6: " << ZenUnit::ToStringer::ToString(nineArgumentCallRef.sixthArgumentReference.value) << '\n' <<
               "Argument7: " << ZenUnit::ToStringer::ToString(nineArgumentCallRef.seventhArgumentReference.value) << '\n' <<
               "Argument8: " << ZenUnit::ToStringer::ToString(nineArgumentCallRef.eigthArgumentReference.value) << '\n' <<
               "Argument9: " << ZenUnit::ToStringer::ToString(nineArgumentCallRef.ninthArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
   struct Printer<ZenMock::TenArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>
   {
      static void Print(std::ostream& os, const ZenMock::TenArgumentFunctionCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& tenArgumentCallRef)
      {
         os << "ZenMock::TenArgumentFunctionCall:\n"
              " Argument1: " << ZenUnit::ToStringer::ToString(tenArgumentCallRef.firstArgumentReference.value) << '\n' <<
              " Argument2: " << ZenUnit::ToStringer::ToString(tenArgumentCallRef.secondArgumentReference.value) << '\n' <<
              " Argument3: " << ZenUnit::ToStringer::ToString(tenArgumentCallRef.thirdArgumentReference.value) << '\n' <<
              " Argument4: " << ZenUnit::ToStringer::ToString(tenArgumentCallRef.fourthArgumentReference.value) << '\n' <<
              " Argument5: " << ZenUnit::ToStringer::ToString(tenArgumentCallRef.fifthArgumentReference.value) << '\n' <<
              " Argument6: " << ZenUnit::ToStringer::ToString(tenArgumentCallRef.sixthArgumentReference.value) << '\n' <<
              " Argument7: " << ZenUnit::ToStringer::ToString(tenArgumentCallRef.seventhArgumentReference.value) << '\n' <<
              " Argument8: " << ZenUnit::ToStringer::ToString(tenArgumentCallRef.eigthArgumentReference.value) << '\n' <<
              " Argument9: " << ZenUnit::ToStringer::ToString(tenArgumentCallRef.ninthArgumentReference.value) << '\n' <<
              "Argument10: " << ZenUnit::ToStringer::ToString(tenArgumentCallRef.tenthArgumentReference.value);
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

      ZENMOCK_NONVOID0_CONST(float, Float)
      ZENMOCK_NONVOID0_CONST(double, Double)

      ZENMOCK_NONVOID0_CONST(std::string, String)
      ZENMOCK_NONVOID0_CONST(std::vector<std::string>, StringVector)

      ZENMOCK_NONVOID0_CONST(fs::path, Path)
   };
}
