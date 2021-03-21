// C++ Mocking Framework MetalMock v0.10.0
// https://github.com/NeilJustice/ZenUnitAndMetalMock
// MIT License

#ifndef METALMOCKDOTH
#define METALMOCKDOTH
#include "ZenUnitAndMetalMock/ZenUnit.h"
#include <atomic>
#include <deque>

namespace Metal
{
   // Inherit from Metal::Mock<T> to define a MetalMock mock object class.
   //
   // Example MetalMock class definition:
   //
   // class WidgetMock : public Metal::Mock<Widget>
   // {
   // public:
   //    METALMOCK_VOID0_CONST(Foo)
   //    METALMOCK_NONVOID2_CONST(int, Add, int, int)
   // };

   template<typename MetalMockedClass>
   class Mock : public MetalMockedClass
   {
   public:
      template<typename... ArgTypes>
      explicit Mock(ArgTypes&&... args)
         : MetalMockedClass(std::forward<ArgTypes>(args)...)
      {
      }

      static const std::string* MetalMockedClassName()
      {
         const std::string* const metalMockedClassName = ZenUnit::Type::GetName<MetalMockedClass>();
         return metalMockedClassName;
      }
   };
}

// METALMOCK adds file path and line number information to potential MetalMock assertion failed error messages
#define METALMOCK(MetalMockAssertStatement) \
try \
{ \
   (MetalMockAssertStatement); \
} \
catch (const ZenUnit::Anomaly& metalMockWrappedAnomaly) \
{ \
   throw ZenUnit::Anomaly::METALMOCKWrapped("METALMOCK("#MetalMockAssertStatement")", metalMockWrappedAnomaly, ZENUNIT_FILELINE); \
}

//
// Macros For MetalMocking 0-Argument Functions
//

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a base class function with signature "virtual void VirtualFunctionName()".
#define METALMOCK_VOID0(VirtualFunctionName) \
        METALMOCK_VOID0_DEFINED(VirtualFunctionName, virtual,      ,        , final)

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a base class function with signature "virtual void VirtualFunctionName() const".
#define METALMOCK_VOID0_CONST(VirtualFunctionName) \
        METALMOCK_VOID0_DEFINED(VirtualFunctionName, virtual, const, mutable, final)

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a base class function with signature "void NonVirtualFunctionName()".
#define METALMOCK_VOID0_NONVIRTUAL(NonVirtualFunctionName) \
        METALMOCK_VOID0_DEFINED(NonVirtualFunctionName,        ,        ,      ,         )

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a base class function with signature "void NonVirtualFunctionName() const".
#define METALMOCK_VOID0_NONVIRTUAL_CONST(NonVirtualFunctionName) \
        METALMOCK_VOID0_DEFINED(NonVirtualFunctionName,        , const, mutable,         )

// Defines a MetalMock object named <StaticFunctionName>Mock for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName()".
#define METALMOCK_VOID0_STATIC(NamespaceQualifiedClassName, StaticFunctionName) \
   MetalMock::VoidZeroArgFunctionPointerMetalMocker StaticFunctionName##Mock = \
      MetalMock::VoidZeroArgFunctionPointerMetalMocker( \
         MetalMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"()"));

// Defines a MetalMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "void ::FreeFunctionName()".
#define METALMOCK_VOID0_FREE(GlobalFreeFunctionName) \
   MetalMock::VoidZeroArgFunctionPointerMetalMocker GlobalFreeFunctionName##Mock = \
      MetalMock::VoidZeroArgFunctionPointerMetalMocker(MetalMock::FunctionSignature::FunctionPointer("void", #GlobalFreeFunctionName"()"));

#define METALMOCK_VOID0_DEFINED(FunctionName, Virtualness, Constness, Mutableness, Finalness) \
struct MetalMock_##FunctionName : public MetalMock::VoidZeroArgumentMetalMocker \
{ \
   explicit MetalMock_##FunctionName(const std::string* metalMockedClassName) \
      : MetalMock::VoidZeroArgumentMetalMocker(MetalMock::FunctionSignature::Function( \
         #Virtualness, "void", metalMockedClassName, #FunctionName"()", #Constness)) {} \
} Mutableness FunctionName##Mock = MetalMock_##FunctionName(this->MetalMockedClassName()); \
void FunctionName() Constness Finalness \
{ \
   FunctionName##Mock.MetalMockIt(); \
}

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName()".
#define METALMOCK_NONVOID0(ReturnType, VirtualFunctionName) \
        METALMOCK_NONVOID0_DEFINED(ReturnType, VirtualFunctionName, virtual,      ,        , final)

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName() const".
#define METALMOCK_NONVOID0_CONST(ReturnType, VirtualFunctionName) \
        METALMOCK_NONVOID0_DEFINED(ReturnType, VirtualFunctionName, virtual, const, mutable, final)

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName()".
#define METALMOCK_NONVOID0_NONVIRTUAL(ReturnType, VirtualFunctionName) \
        METALMOCK_NONVOID0_DEFINED(ReturnType, VirtualFunctionName,        ,      ,        ,         )

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName() const".
#define METALMOCK_NONVOID0_NONVIRTUAL_CONST(ReturnType, VirtualFunctionName) \
        METALMOCK_NONVOID0_DEFINED(ReturnType, VirtualFunctionName,        , const, mutable,         )

// Defines a MetalMock object named <StaticFunctionName>Mock for mocking a static function with signature "ReturnType NamespaceQualifiedClassName::StaticFunctionName()".
#define METALMOCK_NONVOID0_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName) \
   MetalMock::NonVoidZeroArgFunctionPointerMetalMocker<ReturnType> StaticFunctionName##Mock = \
      MetalMock::NonVoidZeroArgFunctionPointerMetalMocker<ReturnType>( \
         MetalMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"()"));

// Defines a MetalMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName()".
#define METALMOCK_NONVOID0_FREE(ReturnType, GlobalFreeFunctionName) \
   MetalMock::NonVoidZeroArgFunctionPointerMetalMocker<ReturnType> GlobalFreeFunctionName##Mock = \
      MetalMock::NonVoidZeroArgFunctionPointerMetalMocker<ReturnType>( \
         MetalMock::FunctionSignature::FunctionPointer(#ReturnType, #GlobalFreeFunctionName"()"));

#define METALMOCK_NONVOID0_DEFINED(ReturnType, FunctionName, Virtualness, Constness, Mutableness, Finalness) \
struct MetalMock_##FunctionName : public MetalMock::NonVoidZeroArgumentMetalMocker<ReturnType> \
{ \
   explicit MetalMock_##FunctionName(const std::string* metalMockedClassName) \
      : MetalMock::NonVoidZeroArgumentMetalMocker<ReturnType>(MetalMock::FunctionSignature::Function( \
         #Virtualness, #ReturnType, metalMockedClassName, #FunctionName"()", #Constness)) {} \
} Mutableness FunctionName##Mock = MetalMock_##FunctionName(this->MetalMockedClassName()); \
ReturnType FunctionName() Constness Finalness \
{ \
   return FunctionName##Mock.MetalMockItAndReturnValue(); \
}

//
// Macros For MetalMocking 1-Argument Functions
//

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a base class function with signature "virtual void VirtualFunctionName(Arg1Type)".
#define METALMOCK_VOID1(VirtualFunctionName, Arg1Type) \
        METALMOCK_VOID1_DEFINED(VirtualFunctionName, Arg1Type, virtual,      ,        , final)

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a base class function with signature "virtual void VirtualFunctionName(Arg1Type) const".
#define METALMOCK_VOID1_CONST(VirtualFunctionName, Arg1Type) \
        METALMOCK_VOID1_DEFINED(VirtualFunctionName, Arg1Type, virtual, const, mutable, final)

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a base class function with signature "void FunctionName(Arg1Type)".
#define METALMOCK_VOID1_NONVIRTUAL(NonVirtualFunctionName, Arg1Type) \
        METALMOCK_VOID1_DEFINED(NonVirtualFunctionName, Arg1Type,        ,      ,        ,         )

// Defines a MetalMock object named <FunctionName>Mock for mocking a base class function with signature "void FunctionName(Arg1Type) const".
#define METALMOCK_VOID1_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type) \
        METALMOCK_VOID1_DEFINED(NonVirtualFunctionName, Arg1Type,        , const, mutable,         )

// Defines a MetalMock object named <StaticFunctionName>Mock for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName(Arg1Type)".
#define METALMOCK_VOID1_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type) \
   MetalMock::VoidOneArgFunctionPointerMetalMocker<Arg1Type> StaticFunctionName##Mock = \
      MetalMock::VoidOneArgFunctionPointerMetalMocker<Arg1Type>( \
         MetalMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type")"));

// Defines a MetalMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type)".
#define METALMOCK_VOID1_FREE(GlobalFreeFunctionName, Arg1Type) \
   MetalMock::VoidOneArgFunctionPointerMetalMocker<Arg1Type> GlobalFreeFunctionName##Mock = \
      MetalMock::VoidOneArgFunctionPointerMetalMocker<Arg1Type>( \
         MetalMock::FunctionSignature::FunctionPointer("void", #GlobalFreeFunctionName"("#Arg1Type")"));

#define METALMOCK_VOID1_DEFINED(FunctionName, Arg1Type, Virtualness, Constness, Mutableness, Finalness) \
struct MetalMock_##FunctionName : public MetalMock::VoidOneArgumentMetalMocker<Arg1Type> \
{ \
   explicit MetalMock_##FunctionName(const std::string* metalMockedClassName) \
      : MetalMock::VoidOneArgumentMetalMocker<Arg1Type>(MetalMock::FunctionSignature::Function( \
         #Virtualness, "void", metalMockedClassName, #FunctionName"("#Arg1Type")", #Constness)) {} \
} Mutableness FunctionName##Mock = MetalMock_##FunctionName(this->MetalMockedClassName()); \
void FunctionName(Arg1Type arg) Constness Finalness \
{ \
   FunctionName##Mock.MetalMockIt(arg); \
}

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type)".
#define METALMOCK_NONVOID1(ReturnType, VirtualFunctionName, Arg1Type) \
        METALMOCK_NONVOID1_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, virtual,      ,        , final)

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type) const".
#define METALMOCK_NONVOID1_CONST(ReturnType, VirtualFunctionName, Arg1Type) \
        METALMOCK_NONVOID1_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, virtual, const, mutable, final)

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type)".
#define METALMOCK_NONVOID1_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type) \
        METALMOCK_NONVOID1_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type,        ,      ,        ,         )

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type) const".
#define METALMOCK_NONVOID1_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type) \
        METALMOCK_NONVOID1_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type,        , const, mutable,         )

// Defines a MetalMock object named <StaticFunctionName>Mock for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type)".
#define METALMOCK_NONVOID1_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type) \
   MetalMock::NonVoidOneArgFunctionPointerMetalMocker<ReturnType, Arg1Type> \
      StaticFunctionName##Mock = MetalMock::NonVoidOneArgFunctionPointerMetalMocker<ReturnType, Arg1Type>( \
         MetalMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type")"));

// Defines a MetalMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type)".
#define METALMOCK_NONVOID1_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type) \
   MetalMock::NonVoidOneArgFunctionPointerMetalMocker<ReturnType, Arg1Type> \
      GlobalFreeFunctionName##Mock = MetalMock::NonVoidOneArgFunctionPointerMetalMocker<ReturnType, Arg1Type>( \
         MetalMock::FunctionSignature::FunctionPointer(#ReturnType, #GlobalFreeFunctionName"("#Arg1Type")"));

#define METALMOCK_NONVOID1_DEFINED(ReturnType, FunctionName, Arg1Type, Virtualness, Constness, Mutableness, Finalness) \
struct MetalMock_##FunctionName : public MetalMock::NonVoidOneArgumentMetalMocker<ReturnType, Arg1Type> \
{ \
   explicit MetalMock_##FunctionName(const std::string* metalMockedClassName) \
      : MetalMock::NonVoidOneArgumentMetalMocker<ReturnType, Arg1Type>(MetalMock::FunctionSignature::Function( \
         #Virtualness, #ReturnType, metalMockedClassName, #FunctionName"("#Arg1Type")", #Constness)) {} \
} Mutableness FunctionName##Mock = MetalMock_##FunctionName(this->MetalMockedClassName()); \
ReturnType FunctionName(Arg1Type arg) Constness Finalness \
{ \
   return FunctionName##Mock.MetalMockItAndReturnValue(arg); \
}

//
// Macros For MetalMocking 2-Argument Functions
//

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type)".
#define METALMOCK_VOID2(VirtualFunctionName, Arg1Type, Arg2Type) \
        METALMOCK_VOID2_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, virtual,      ,        , final)

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type) const".
#define METALMOCK_VOID2_CONST(VirtualFunctionName, Arg1Type, Arg2Type) \
        METALMOCK_VOID2_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, virtual, const, mutable, final)

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type)".
#define METALMOCK_VOID2_NONVIRTUAL(NonVirtualFunctionName, Arg1Type, Arg2Type) \
        METALMOCK_VOID2_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type,        ,      ,        ,         )

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type) const".
#define METALMOCK_VOID2_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type, Arg2Type) \
        METALMOCK_VOID2_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type,        , const, mutable,         )

// Defines a MetalMock object named <FunctionName>Mock for mocking a static function with signature "void QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type)".
#define METALMOCK_VOID2_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type) \
   MetalMock::VoidTwoArgFunctionPointerMetalMocker<Arg1Type, Arg2Type> StaticFunctionName##Mock = \
      MetalMock::VoidTwoArgFunctionPointerMetalMocker<Arg1Type, Arg2Type>( \
         MetalMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type")"));

// Defines a MetalMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type, Arg2Type)".
#define METALMOCK_VOID2_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type) \
   MetalMock::VoidTwoArgFunctionPointerMetalMocker<Arg1Type, Arg2Type> GlobalFreeFunctionName##Mock = \
      MetalMock::VoidTwoArgFunctionPointerMetalMocker<Arg1Type, Arg2Type>( \
         MetalMock::FunctionSignature::FunctionPointer("void", #GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type")"));

#define METALMOCK_VOID2_DEFINED(FunctionName, Arg1Type, Arg2Type, Virtualness, Constness, Mutableness, Finalness) \
struct MetalMock_##FunctionName : public MetalMock::VoidTwoArgumentMetalMocker<Arg1Type, Arg2Type> \
{ \
   explicit MetalMock_##FunctionName(const std::string* metalMockedClassName) \
      : MetalMock::VoidTwoArgumentMetalMocker<Arg1Type, Arg2Type>(MetalMock::FunctionSignature::Function( \
         #Virtualness, "void", metalMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type")", #Constness)) {} \
} Mutableness FunctionName##Mock = MetalMock_##FunctionName(this->MetalMockedClassName()); \
void FunctionName(Arg1Type firstArgument, Arg2Type secondArgument) Constness Finalness \
{ \
   FunctionName##Mock.MetalMockIt(firstArgument, secondArgument); \
}

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type)".
#define METALMOCK_NONVOID2(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type) \
        METALMOCK_NONVOID2_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, virtual,      ,        , final)

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type) const".
#define METALMOCK_NONVOID2_CONST(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type) \
        METALMOCK_NONVOID2_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, virtual, const, mutable, final)

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type)".
#define METALMOCK_NONVOID2_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type) \
        METALMOCK_NONVOID2_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type,        ,      ,        ,         )

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type) const".
#define METALMOCK_NONVOID2_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type) \
        METALMOCK_NONVOID2_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type,        , const, mutable,         )

// Defines a MetalMock object named <StaticFunctionName>Mock for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type)".
#define METALMOCK_NONVOID2_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type) \
   MetalMock::NonVoidTwoArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type> StaticFunctionName##Mock = \
      MetalMock::NonVoidTwoArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type>( \
         MetalMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type")"));

// Defines a MetalMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type, Arg2Type)".
#define METALMOCK_NONVOID2_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type) \
   MetalMock::NonVoidTwoArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type> GlobalFreeFunctionName##Mock = \
      MetalMock::NonVoidTwoArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type>( \
         MetalMock::FunctionSignature::FunctionPointer(#ReturnType, #GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type")"));

#define METALMOCK_NONVOID2_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Virtualness, Constness, Mutableness, Finalness) \
struct MetalMock_##FunctionName : public MetalMock::NonVoidTwoArgumentMetalMocker<ReturnType, Arg1Type, Arg2Type> \
{ \
   explicit MetalMock_##FunctionName(const std::string* metalMockedClassName) \
      : MetalMock::NonVoidTwoArgumentMetalMocker<ReturnType, Arg1Type, Arg2Type>(MetalMock::FunctionSignature::Function( \
         #Virtualness, #ReturnType, metalMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type")", #Constness)) {} \
} Mutableness FunctionName##Mock = MetalMock_##FunctionName(this->MetalMockedClassName()); \
ReturnType FunctionName(Arg1Type firstArgument, Arg2Type secondArgument) Constness Finalness \
{ \
   return FunctionName##Mock.MetalMockItAndReturnValue(firstArgument, secondArgument); \
}

//
// Macros For MetalMocking 3-Argument Functions
//

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type)".
#define METALMOCK_VOID3(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type) \
        METALMOCK_VOID3_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, virtual,      ,        , final)

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type) const".
#define METALMOCK_VOID3_CONST(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type) \
        METALMOCK_VOID3_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, virtual, const, mutable, final)

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type)".
#define METALMOCK_VOID3_NONVIRTUAL(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type) \
        METALMOCK_VOID3_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type,        ,      ,        ,         )

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type) const".
#define METALMOCK_VOID3_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type) \
        METALMOCK_VOID3_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type,        , const, mutable,         )

// Defines a MetalMock object named <StaticFunctionName>Mock for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type)".
#define METALMOCK_VOID3_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type) \
   MetalMock::VoidThreeArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type> StaticFunctionName##Mock = \
      MetalMock::VoidThreeArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type>( \
         MetalMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type")"));

// Defines a MetalMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type)".
#define METALMOCK_VOID3_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type) \
   MetalMock::VoidThreeArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type> GlobalFreeFunctionName##Mock = \
      MetalMock::VoidThreeArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type>( \
         MetalMock::FunctionSignature::FunctionPointer("void", #GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type")"));

#define METALMOCK_VOID3_DEFINED(FunctionName, Arg1Type, Arg2Type, Arg3Type, Virtualness, Constness, Mutableness, Finalness) \
struct MetalMock_##FunctionName : public MetalMock::VoidThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type> \
{ \
   explicit MetalMock_##FunctionName(const std::string* metalMockedClassName) \
      : MetalMock::VoidThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>(MetalMock::FunctionSignature::Function( \
         #Virtualness, "void", metalMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type")", #Constness)) {} \
} Mutableness FunctionName##Mock = MetalMock_##FunctionName(this->MetalMockedClassName()); \
void FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument) Constness Finalness \
{ \
   FunctionName##Mock.MetalMockIt(firstArgument, secondArgument, thirdArgument); \
}

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type)".
#define METALMOCK_NONVOID3(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type) \
        METALMOCK_NONVOID3_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, virtual,      ,        , final)

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type) const".
#define METALMOCK_NONVOID3_CONST(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type) \
        METALMOCK_NONVOID3_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, virtual, const, mutable, final)

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type)".
#define METALMOCK_NONVOID3_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type) \
        METALMOCK_NONVOID3_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type,        ,      ,        ,         )

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type) const".
#define METALMOCK_NONVOID3_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type) \
        METALMOCK_NONVOID3_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type,        , const, mutable,         )

// Defines a MetalMock object named <StaticFunctionName>Mock for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type)".
#define METALMOCK_NONVOID3_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type) \
   MetalMock::NonVoidThreeArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type> StaticFunctionName##Mock = \
      MetalMock::NonVoidThreeArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type>( \
         MetalMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type")"));

// Defines a MetalMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type)".
#define METALMOCK_NONVOID3_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type) \
   MetalMock::NonVoidThreeArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type> GlobalFreeFunctionName##Mock = \
      MetalMock::NonVoidThreeArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type>( \
         MetalMock::FunctionSignature::FunctionPointer(#ReturnType, #GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type")"));

#define METALMOCK_NONVOID3_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Arg3Type, Virtualness, Constness, Mutableness, Finalness) \
struct MetalMock_##FunctionName : public MetalMock::NonVoidThreeArgumentMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type> \
{ \
   explicit MetalMock_##FunctionName(const std::string* metalMockedClassName) \
      : MetalMock::NonVoidThreeArgumentMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type>(MetalMock::FunctionSignature::Function( \
         #Virtualness, #ReturnType, metalMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type")", #Constness)) {} \
} Mutableness FunctionName##Mock = MetalMock_##FunctionName(this->MetalMockedClassName()); \
ReturnType FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument) Constness Finalness \
{ \
   return FunctionName##Mock.MetalMockItAndReturnValue(firstArgument, secondArgument, thirdArgument); \
}

//
// Macros For MetalMocking 4-Argument Functions
//

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type)".
#define METALMOCK_VOID4(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type) \
        METALMOCK_VOID4_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, virtual,      ,        , final)

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type) const".
#define METALMOCK_VOID4_CONST(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type) \
        METALMOCK_VOID4_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, virtual, const, mutable, final)

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type)".
#define METALMOCK_VOID4_NONVIRTUAL(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type) \
        METALMOCK_VOID4_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type,        ,      ,        ,         )

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type) const".
#define METALMOCK_VOID4_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type) \
        METALMOCK_VOID4_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type,        , const, mutable,         )

// Defines a MetalMock object named <StaticFunctionName>Mock for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type)".
#define METALMOCK_VOID4_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type) \
   MetalMock::VoidFourArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type> StaticFunctionName##Mock = \
      MetalMock::VoidFourArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>( \
         MetalMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type")"));

// Defines a MetalMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type)".
#define METALMOCK_VOID4_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type) \
   MetalMock::VoidFourArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type> GlobalFreeFunctionName##Mock = \
      MetalMock::VoidFourArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>( \
         MetalMock::FunctionSignature::FunctionPointer("void", #GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type")"));

#define METALMOCK_VOID4_DEFINED(FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Virtualness, Constness, Mutableness, Finalness) \
struct MetalMock_##FunctionName : public MetalMock::VoidFourArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type> \
{ \
   explicit MetalMock_##FunctionName(const std::string* metalMockedClassName) \
      : MetalMock::VoidFourArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>(MetalMock::FunctionSignature::Function( \
         #Virtualness, "void", metalMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type")", #Constness)) {} \
} Mutableness FunctionName##Mock = MetalMock_##FunctionName(this->MetalMockedClassName()); \
void FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument) Constness Finalness \
{ \
   FunctionName##Mock.MetalMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument); \
}

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type)".
#define METALMOCK_NONVOID4(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type) \
        METALMOCK_NONVOID4_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, virtual,      ,        , final)

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type) const".
#define METALMOCK_NONVOID4_CONST(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type) \
        METALMOCK_NONVOID4_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, virtual, const, mutable, final)

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type)".
#define METALMOCK_NONVOID4_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type) \
        METALMOCK_NONVOID4_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type,        ,      ,        ,         )

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type) const".
#define METALMOCK_NONVOID4_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type) \
        METALMOCK_NONVOID4_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type,        , const, mutable,         )

// Defines a MetalMock object named <StaticFunctionName>Mock for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type)".
#define METALMOCK_NONVOID4_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type) \
   MetalMock::NonVoidFourArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type> StaticFunctionName##Mock = \
      MetalMock::NonVoidFourArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>( \
         MetalMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type")"));

// Defines a MetalMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type)".
#define METALMOCK_NONVOID4_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type) \
   MetalMock::NonVoidFourArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type> GlobalFreeFunctionName##Mock = \
      MetalMock::NonVoidFourArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>( \
         MetalMock::FunctionSignature::FunctionPointer(#ReturnType, #GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type")"));

#define METALMOCK_NONVOID4_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Virtualness, Constness, Mutableness, Finalness) \
struct MetalMock_##FunctionName : public MetalMock::NonVoidFourArgumentMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type> \
{ \
   explicit MetalMock_##FunctionName(const std::string* metalMockedClassName) \
      : MetalMock::NonVoidFourArgumentMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>(MetalMock::FunctionSignature::Function( \
         #Virtualness, #ReturnType, metalMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type")", #Constness)) {} \
} Mutableness FunctionName##Mock = MetalMock_##FunctionName(this->MetalMockedClassName()); \
ReturnType FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument) Constness Finalness \
{ \
   return FunctionName##Mock.MetalMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument); \
}

//
// Macros For MetalMocking 5-Argument Functions
//

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)".
#define METALMOCK_VOID5(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type) \
        METALMOCK_VOID5_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, virtual,      ,        , final)

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type) const".
#define METALMOCK_VOID5_CONST(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type) \
        METALMOCK_VOID5_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, virtual, const, mutable, final)

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)".
#define METALMOCK_VOID5_NONVIRTUAL(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type) \
        METALMOCK_VOID5_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type,       ,      ,        ,          )

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type) const".
#define METALMOCK_VOID5_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type) \
        METALMOCK_VOID5_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type,       , const, mutable,          )

// Defines a MetalMock object named <StaticFunctionName>Mock for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)".
#define METALMOCK_VOID5_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type) \
   MetalMock::VoidFiveArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type> StaticFunctionName##Mock = \
      MetalMock::VoidFiveArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>( \
         MetalMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type")"));

// Defines a MetalMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)".
#define METALMOCK_VOID5_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type) \
   MetalMock::VoidFiveArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type> GlobalFreeFunctionName##Mock = \
      MetalMock::VoidFiveArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>( \
         MetalMock::FunctionSignature::FunctionPointer("void", #GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type")"));

#define METALMOCK_VOID5_DEFINED(FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Virtualness, Constness, Mutableness, Finalness) \
struct MetalMock_##FunctionName : public MetalMock::VoidFiveArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type> \
{ \
   explicit MetalMock_##FunctionName(const std::string* metalMockedClassName) \
      : MetalMock::VoidFiveArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>(MetalMock::FunctionSignature::Function( \
         #Virtualness, "void", metalMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type")", #Constness)) {} \
} Mutableness FunctionName##Mock = MetalMock_##FunctionName(this->MetalMockedClassName()); \
void FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument) Constness Finalness \
{ \
   FunctionName##Mock.MetalMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument); \
}

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)".
#define METALMOCK_NONVOID5(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type) \
        METALMOCK_NONVOID5_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, virtual,      ,        , final)

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type) const".
#define METALMOCK_NONVOID5_CONST(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type) \
        METALMOCK_NONVOID5_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, virtual, const, mutable, final)

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)".
#define METALMOCK_NONVOID5_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type) \
        METALMOCK_NONVOID5_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type,        ,      ,        ,         )

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type) const".
#define METALMOCK_NONVOID5_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type) \
        METALMOCK_NONVOID5_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type,        , const, mutable,         )

// Defines a MetalMock object named <StaticFunctionName>Mock for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)".
#define METALMOCK_NONVOID5_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type) \
   MetalMock::NonVoidFiveArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type> StaticFunctionName##Mock = \
      MetalMock::NonVoidFiveArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>( \
         MetalMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type")"));

// Defines a MetalMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)".
#define METALMOCK_NONVOID5_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type) \
   MetalMock::NonVoidFiveArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type> GlobalFreeFunctionName##Mock = \
      MetalMock::NonVoidFiveArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>( \
         MetalMock::FunctionSignature::FunctionPointer(#ReturnType, #GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type")"));

#define METALMOCK_NONVOID5_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Virtualness, Constness, Mutableness, Finalness) \
struct MetalMock_##FunctionName : public MetalMock::NonVoidFiveArgumentMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type> \
{ \
   explicit MetalMock_##FunctionName(const std::string* metalMockedClassName) \
      : MetalMock::NonVoidFiveArgumentMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>(MetalMock::FunctionSignature::Function( \
         #Virtualness, #ReturnType, metalMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type")", #Constness)) {} \
} Mutableness FunctionName##Mock = MetalMock_##FunctionName(this->MetalMockedClassName()); \
ReturnType FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument) Constness Finalness \
{ \
   return FunctionName##Mock.MetalMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument); \
}

//
// Macros For MetalMocking 6-Argument Functions
//

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)".
#define METALMOCK_VOID6(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type) \
        METALMOCK_VOID6_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, virtual,      ,        , final)

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type) const".
#define METALMOCK_VOID6_CONST(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type) \
        METALMOCK_VOID6_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, virtual, const, mutable, final)

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)".
#define METALMOCK_VOID6_NONVIRTUAL(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type) \
        METALMOCK_VOID6_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type,        ,      ,        ,         )

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type) const".
#define METALMOCK_VOID6_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type) \
        METALMOCK_VOID6_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type,        , const, mutable,         )

// Defines a MetalMock object named <StaticFunctionName>Mock for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)".
#define METALMOCK_VOID6_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type) \
   MetalMock::VoidSixArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type> StaticFunctionName##Mock = \
      MetalMock::VoidSixArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>( \
         MetalMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type")"));

// Defines a MetalMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)".
#define METALMOCK_VOID6_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type) \
   MetalMock::VoidSixArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type> GlobalFreeFunctionName##Mock = \
      MetalMock::VoidSixArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>( \
         MetalMock::FunctionSignature::FunctionPointer("void", #GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type")"));

#define METALMOCK_VOID6_DEFINED(FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Virtualness, Constness, Mutableness, Finalness) \
struct MetalMock_##FunctionName : public MetalMock::VoidSixArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type> \
{ \
   explicit MetalMock_##FunctionName(const std::string* metalMockedClassName) \
      : MetalMock::VoidSixArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>(MetalMock::FunctionSignature::Function( \
         #Virtualness, "void", metalMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type")", #Constness)) {} \
} Mutableness FunctionName##Mock = MetalMock_##FunctionName(this->MetalMockedClassName()); \
void FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument) Constness Finalness \
{ \
   FunctionName##Mock.MetalMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument); \
}

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)".
#define METALMOCK_NONVOID6(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type) \
        METALMOCK_NONVOID6_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, virtual,      ,        , final)

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type) const".
#define METALMOCK_NONVOID6_CONST(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type) \
        METALMOCK_NONVOID6_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, virtual, const, mutable, final)

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)".
#define METALMOCK_NONVOID6_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type) \
        METALMOCK_NONVOID6_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type,        ,      ,        ,         )

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type) const".
#define METALMOCK_NONVOID6_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type) \
        METALMOCK_NONVOID6_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type,        , const, mutable,         )

// Defines a MetalMock object named <StaticFunctionName>Mock for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)".
#define METALMOCK_NONVOID6_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type) \
   MetalMock::NonVoidSixArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type> StaticFunctionName##Mock = \
      MetalMock::NonVoidSixArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>( \
         MetalMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type")"));

// Defines a MetalMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)".
#define METALMOCK_NONVOID6_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type) \
   MetalMock::NonVoidSixArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type> GlobalFreeFunctionName##Mock = \
      MetalMock::NonVoidSixArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>( \
         MetalMock::FunctionSignature::FunctionPointer(#ReturnType, #GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type")"));

#define METALMOCK_NONVOID6_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Virtualness, Constness, Mutableness, Finalness) \
struct MetalMock_##FunctionName : public MetalMock::NonVoidSixArgumentMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type> \
{ \
   explicit MetalMock_##FunctionName(const std::string* metalMockedClassName) \
      : MetalMock::NonVoidSixArgumentMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>(MetalMock::FunctionSignature::Function( \
         #Virtualness, #ReturnType, metalMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type")", #Constness)) {} \
} Mutableness FunctionName##Mock = MetalMock_##FunctionName(this->MetalMockedClassName()); \
ReturnType FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument) Constness Finalness \
{ \
   return FunctionName##Mock.MetalMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument); \
}

//
// Macros For MetalMocking 7-Argument Functions
//

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)".
#define METALMOCK_VOID7(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type) \
        METALMOCK_VOID7_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, virtual,      ,        , final)

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type) const".
#define METALMOCK_VOID7_CONST(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type) \
        METALMOCK_VOID7_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, virtual, const, mutable, final)

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)".
#define METALMOCK_VOID7_NONVIRTUAL(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type) \
        METALMOCK_VOID7_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type,        ,      ,        ,         )

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type) const".
#define METALMOCK_VOID7_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type) \
        METALMOCK_VOID7_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type,        , const, mutable,         )

// Defines a MetalMock object named <StaticFunctionName>Mock for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)".
#define METALMOCK_VOID7_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type) \
   MetalMock::VoidSevenArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type> StaticFunctionName##Mock = \
      MetalMock::VoidSevenArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>( \
         MetalMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type")"));

// Defines a MetalMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)".
#define METALMOCK_VOID7_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type) \
   MetalMock::VoidSevenArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type> GlobalFreeFunctionName##Mock = \
      MetalMock::VoidSevenArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>( \
         MetalMock::FunctionSignature::FunctionPointer("void", #GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type")"));

#define METALMOCK_VOID7_DEFINED(FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Virtualness, Constness, Mutableness, Finalness) \
struct MetalMock_##FunctionName : public MetalMock::VoidSevenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type> \
{ \
   explicit MetalMock_##FunctionName(const std::string* metalMockedClassName) \
      : MetalMock::VoidSevenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>(MetalMock::FunctionSignature::Function( \
         #Virtualness, "void", metalMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type")", #Constness)) {} \
} Mutableness FunctionName##Mock = MetalMock_##FunctionName(this->MetalMockedClassName()); \
void FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument) Constness Finalness \
{ \
   FunctionName##Mock.MetalMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument); \
}

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)".
#define METALMOCK_NONVOID7(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type) \
        METALMOCK_NONVOID7_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, virtual,      ,        , final)

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type) const".
#define METALMOCK_NONVOID7_CONST(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type) \
        METALMOCK_NONVOID7_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, virtual, const, mutable, final)

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)".
#define METALMOCK_NONVOID7_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type) \
        METALMOCK_NONVOID7_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type,        ,      ,        ,         )

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type) const".
#define METALMOCK_NONVOID7_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type) \
        METALMOCK_NONVOID7_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type,        , const, mutable,         )

// Defines a MetalMock object named <StaticFunctionName>Mock for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)".
#define METALMOCK_NONVOID7_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type) \
   MetalMock::NonVoidSevenArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type> StaticFunctionName##Mock = \
      MetalMock::NonVoidSevenArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>( \
         MetalMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type")"));

// Defines a MetalMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)".
#define METALMOCK_NONVOID7_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type) \
   MetalMock::NonVoidSevenArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type> GlobalFreeFunctionName##Mock = \
      MetalMock::NonVoidSevenArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>( \
         MetalMock::FunctionSignature::FunctionPointer(#ReturnType, #GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type")"));

#define METALMOCK_NONVOID7_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Virtualness, Constness, Mutableness, Finalness) \
struct MetalMock_##FunctionName : public MetalMock::NonVoidSevenArgumentMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type> \
{ \
   explicit MetalMock_##FunctionName(const std::string* metalMockedClassName) \
      : MetalMock::NonVoidSevenArgumentMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>(MetalMock::FunctionSignature::Function( \
         #Virtualness, #ReturnType, metalMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type")", #Constness)) {} \
} Mutableness FunctionName##Mock = MetalMock_##FunctionName(this->MetalMockedClassName()); \
ReturnType FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument) Constness Finalness \
{ \
   return FunctionName##Mock.MetalMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument); \
}

//
// Macros For MetalMocking 8-Argument Functions
//

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)".
#define METALMOCK_VOID8(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type) \
        METALMOCK_VOID8_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, virtual,      ,        , final)

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type) const".
#define METALMOCK_VOID8_CONST(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type) \
        METALMOCK_VOID8_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, virtual, const, mutable, final)

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)".
#define METALMOCK_VOID8_NONVIRTUAL(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type) \
        METALMOCK_VOID8_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type,        ,      ,        ,         )

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type) const".
#define METALMOCK_VOID8_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type) \
        METALMOCK_VOID8_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type,        , const, mutable,         )

// Defines a MetalMock object named <StaticFunctionName>Mock for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)".
#define METALMOCK_VOID8_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type) \
   MetalMock::VoidEightArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type> StaticFunctionName##Mock = \
      MetalMock::VoidEightArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>( \
         MetalMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type")"));

// Defines a MetalMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)".
#define METALMOCK_VOID8_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type) \
   MetalMock::VoidEightArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type> GlobalFreeFunctionName##Mock = \
      MetalMock::VoidEightArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>( \
         MetalMock::FunctionSignature::FunctionPointer("void", #GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type")"));

#define METALMOCK_VOID8_DEFINED(FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Virtualness, Constness, Mutableness, Finalness) \
struct MetalMock_##FunctionName : public MetalMock::VoidEightArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type> \
{ \
   explicit MetalMock_##FunctionName(const std::string* metalMockedClassName) \
      : MetalMock::VoidEightArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>(MetalMock::FunctionSignature::Function( \
         #Virtualness, "void", metalMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type")", #Constness)) {} \
} Mutableness FunctionName##Mock = MetalMock_##FunctionName(this->MetalMockedClassName()); \
void FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument) Constness Finalness \
{ \
   FunctionName##Mock.MetalMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument); \
}

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)".
#define METALMOCK_NONVOID8(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type) \
        METALMOCK_NONVOID8_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, virtual,      ,        , final)

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type) const".
#define METALMOCK_NONVOID8_CONST(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type) \
        METALMOCK_NONVOID8_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, virtual, const, mutable, final)

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)".
#define METALMOCK_NONVOID8_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type) \
        METALMOCK_NONVOID8_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type,        ,      ,        ,         )

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type) const".
#define METALMOCK_NONVOID8_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type) \
        METALMOCK_NONVOID8_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type,        , const, mutable,         )

// Defines a MetalMock object named <StaticFunctionName>Mock for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)".
#define METALMOCK_NONVOID8_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type) \
   MetalMock::NonVoidEightArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type> StaticFunctionName##Mock = \
      MetalMock::NonVoidEightArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>( \
         MetalMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type")"));

// Defines a MetalMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)".
#define METALMOCK_NONVOID8_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type) \
   MetalMock::NonVoidEightArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type> GlobalFreeFunctionName##Mock = \
      MetalMock::NonVoidEightArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>( \
         MetalMock::FunctionSignature::FunctionPointer(#ReturnType, #GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type")"));

#define METALMOCK_NONVOID8_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Virtualness, Constness, Mutableness, Finalness) \
struct MetalMock_##FunctionName : public MetalMock::NonVoidEightArgumentMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type> \
{ \
   explicit MetalMock_##FunctionName(const std::string* metalMockedClassName) \
      : MetalMock::NonVoidEightArgumentMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>(MetalMock::FunctionSignature::Function( \
         #Virtualness, #ReturnType, metalMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type")", #Constness)) {} \
} Mutableness FunctionName##Mock = MetalMock_##FunctionName(this->MetalMockedClassName()); \
ReturnType FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument) Constness Finalness \
{ \
   return FunctionName##Mock.MetalMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument); \
}

//
// Macros For MetalMocking 9-Argument Functions
//

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type)".
#define METALMOCK_VOID9(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type) \
        METALMOCK_VOID9_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, virtual,      ,        , final)

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type) const".
#define METALMOCK_VOID9_CONST(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type) \
        METALMOCK_VOID9_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, virtual, const, mutable, final)

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type)".
#define METALMOCK_VOID9_NONVIRTUAL(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type) \
        METALMOCK_VOID9_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type,        ,      ,        ,         )

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type) const".
#define METALMOCK_VOID9_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type) \
        METALMOCK_VOID9_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type,        , const, mutable,         )

// Defines a MetalMock object named <StaticFunctionName>Mock for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type)".
#define METALMOCK_VOID9_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type) \
   MetalMock::VoidNineArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type> StaticFunctionName##Mock = \
      MetalMock::VoidNineArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>( \
         MetalMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type")"));

// Defines a MetalMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type)".
#define METALMOCK_VOID9_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type) \
   MetalMock::VoidNineArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type> GlobalFreeFunctionName##Mock = \
      MetalMock::VoidNineArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>( \
         MetalMock::FunctionSignature::FunctionPointer("void", #GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type")"));

#define METALMOCK_VOID9_DEFINED(FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Virtualness, Constness, Mutableness, Finalness) \
struct MetalMock_##FunctionName : public MetalMock::VoidNineArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type> \
{ \
   explicit MetalMock_##FunctionName(const std::string* metalMockedClassName) \
      : MetalMock::VoidNineArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>(MetalMock::FunctionSignature::Function( \
         #Virtualness, "void", metalMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type")", #Constness)) {} \
} Mutableness FunctionName##Mock = MetalMock_##FunctionName(this->MetalMockedClassName()); \
void FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument, Arg9Type ninthArgument) Constness Finalness \
{ \
   FunctionName##Mock.MetalMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument); \
}

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type)".
#define METALMOCK_NONVOID9(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type) \
        METALMOCK_NONVOID9_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, virtual,      ,        , final)

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type) const".
#define METALMOCK_NONVOID9_CONST(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type) \
        METALMOCK_NONVOID9_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, virtual, const, mutable, final)

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type)".
#define METALMOCK_NONVOID9_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type) \
        METALMOCK_NONVOID9_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type,       ,      ,        ,         )

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type) const".
#define METALMOCK_NONVOID9_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type) \
        METALMOCK_NONVOID9_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type,       , const, mutable,         )

// Defines a MetalMock object named <StaticFunctionName>Mock for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type)".
#define METALMOCK_NONVOID9_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type) \
   MetalMock::NonVoidNineArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type> StaticFunctionName##Mock = \
      MetalMock::NonVoidNineArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>( \
         MetalMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type")"));

// Defines a MetalMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type)".
#define METALMOCK_NONVOID9_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type) \
   MetalMock::NonVoidNineArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type> GlobalFreeFunctionName##Mock = \
      MetalMock::NonVoidNineArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>( \
         MetalMock::FunctionSignature::FunctionPointer(#ReturnType, #GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type")"));

#define METALMOCK_NONVOID9_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Virtualness, Constness, Mutableness, Finalness) \
struct MetalMock_##FunctionName : public MetalMock::NonVoidNineArgumentMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type> \
{ \
   explicit MetalMock_##FunctionName(const std::string* metalMockedClassName) \
      : MetalMock::NonVoidNineArgumentMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>(MetalMock::FunctionSignature::Function( \
         #Virtualness, #ReturnType, metalMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type")", #Constness)) {} \
} Mutableness FunctionName##Mock = MetalMock_##FunctionName(this->MetalMockedClassName()); \
ReturnType FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument, Arg9Type ninthArgument) Constness Finalness \
{ \
   return FunctionName##Mock.MetalMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument); \
}

//
// Macros For MetalMocking 10-Argument Functions
//

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)".
#define METALMOCK_VOID10(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type) \
        METALMOCK_VOID10_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, virtual,      ,        , final)

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "void VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type) const".
#define METALMOCK_VOID10_CONST(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type) \
        METALMOCK_VOID10_DEFINED(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, virtual, const, mutable, final)

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)".
#define METALMOCK_VOID10_NONVIRTUAL(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type) \
        METALMOCK_VOID10_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type,        ,      ,        ,         )

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "void NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type) const".
#define METALMOCK_VOID10_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type) \
        METALMOCK_VOID10_DEFINED(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type,        , const, mutable,         )

// Defines a MetalMock object named <StaticFunctionName>Mock for mocking a static function with signature "void NamespaceQualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)".
#define METALMOCK_VOID10_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type) \
   MetalMock::VoidTenArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type> StaticFunctionName##Mock = \
      MetalMock::VoidTenArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>( \
         MetalMock::FunctionSignature::FunctionPointer("void", #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type", "#Arg10Type")"));

// Defines a MetalMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "void ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)".
#define METALMOCK_VOID10_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type) \
   MetalMock::VoidTenArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type> GlobalFreeFunctionName##Mock = \
      MetalMock::VoidTenArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>( \
         MetalMock::FunctionSignature::FunctionPointer("void", #GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type", "#Arg10Type")"));

#define METALMOCK_VOID10_DEFINED(FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, Virtualness, Constness, Mutableness, Finalness) \
struct MetalMock_##FunctionName : public MetalMock::VoidTenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type> \
{ \
   explicit MetalMock_##FunctionName(const std::string* metalMockedClassName) \
      : MetalMock::VoidTenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(MetalMock::FunctionSignature::Function( \
         #Virtualness, "void", metalMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type", "#Arg10Type")", #Constness)) {} \
} Mutableness FunctionName##Mock = MetalMock_##FunctionName(this->MetalMockedClassName()); \
void FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument, Arg9Type ninthArgument, Arg10Type tenthArgument) Constness Finalness \
{ \
   FunctionName##Mock.MetalMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument, tenthArgument); \
}

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)".
#define METALMOCK_NONVOID10(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type) \
        METALMOCK_NONVOID10_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, virtual,      ,        , final)

// Defines a MetalMock object named <VirtualFunctionName>Mock for mocking a virtual base class function with signature "virtual ReturnType VirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type) const".
#define METALMOCK_NONVOID10_CONST(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type) \
        METALMOCK_NONVOID10_DEFINED(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, virtual, const, mutable, final)

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)".
#define METALMOCK_NONVOID10_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type) \
        METALMOCK_NONVOID10_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type,      ,      ,        ,         )

// Defines a MetalMock object named <NonVirtualFunctionName>Mock for mocking a non-virtual base class function with signature "ReturnType NonVirtualFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type) const".
#define METALMOCK_NONVOID10_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type) \
        METALMOCK_NONVOID10_DEFINED(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type,      , const, mutable,         )

// Defines a MetalMock object named <StaticFunctionName>Mock for mocking a static function with signature "ReturnType QualifiedClassName::StaticFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)".
#define METALMOCK_NONVOID10_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type) \
   MetalMock::NonVoidTenArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type> StaticFunctionName##Mock = \
      MetalMock::NonVoidTenArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>( \
         MetalMock::FunctionSignature::FunctionPointer(#ReturnType, #NamespaceQualifiedClassName"::"#StaticFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type", "#Arg10Type")"));

// Defines a MetalMock object named <GlobalFreeFunctionName>Mock for mocking a global free function with signature "ReturnType ::GlobalFreeFunctionName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)".
#define METALMOCK_NONVOID10_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type) \
   MetalMock::NonVoidTenArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type> GlobalFreeFunctionName##Mock = \
      MetalMock::NonVoidTenArgFunctionPointerMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>( \
         MetalMock::FunctionSignature::FunctionPointer(#ReturnType, #GlobalFreeFunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type", "#Arg10Type")"));

#define METALMOCK_NONVOID10_DEFINED(ReturnType, FunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, Virtualness, Constness, Mutableness, Finalness) \
struct MetalMock_##FunctionName : public MetalMock::NonVoidTenArgumentMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type> \
{ \
   explicit MetalMock_##FunctionName(const std::string* metalMockedClassName) \
      : MetalMock::NonVoidTenArgumentMetalMocker<ReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(MetalMock::FunctionSignature::Function( \
         #Virtualness, #ReturnType, metalMockedClassName, #FunctionName"("#Arg1Type", "#Arg2Type", "#Arg3Type", "#Arg4Type", "#Arg5Type", "#Arg6Type", "#Arg7Type", "#Arg8Type", "#Arg9Type", "#Arg10Type")", #Constness)) {} \
} Mutableness FunctionName##Mock = MetalMock_##FunctionName(this->MetalMockedClassName()); \
ReturnType FunctionName(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument, Arg9Type ninthArgument, Arg10Type tenthArgument) Constness Finalness \
{ \
   return FunctionName##Mock.MetalMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument, tenthArgument); \
}

//
// MetalMock Binding Macros For Overwriting std::functions With Static And Free MetalMock Objects
//

// std::binds a 0-argument MetalMock object
#define BIND_0ARG_METALMOCK_OBJECT(FunctionNameMock) \
   std::bind(&decltype(FunctionNameMock)::MetalMockItFunctionPointer, &FunctionNameMock)

// std::binds a 1-argument MetalMock object
#define BIND_1ARG_METALMOCK_OBJECT(FunctionNameMock) \
   std::bind(&decltype(FunctionNameMock)::MetalMockItFunctionPointer, &FunctionNameMock, std::placeholders::_1)

// std::binds a 2-argument MetalMock object
#define BIND_2ARG_METALMOCK_OBJECT(FunctionNameMock) \
   std::bind(&decltype(FunctionNameMock)::MetalMockItFunctionPointer, &FunctionNameMock, std::placeholders::_1, std::placeholders::_2)

// std::binds a 3-argument MetalMock object
#define BIND_3ARG_METALMOCK_OBJECT(FunctionNameMock) \
   std::bind(&decltype(FunctionNameMock)::MetalMockItFunctionPointer, &FunctionNameMock, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)

// std::binds a 4-argument MetalMock object
#define BIND_4ARG_METALMOCK_OBJECT(FunctionNameMock) \
   std::bind(&decltype(FunctionNameMock)::MetalMockItFunctionPointer, &FunctionNameMock, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)

// std::binds a 5-argument MetalMock object
#define BIND_5ARG_METALMOCK_OBJECT(FunctionNameMock) \
   std::bind(&decltype(FunctionNameMock)::MetalMockItFunctionPointer, &FunctionNameMock, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5)

// std::binds a 6-argument MetalMock object
#define BIND_6ARG_METALMOCK_OBJECT(FunctionNameMock) \
   std::bind(&decltype(FunctionNameMock)::MetalMockItFunctionPointer, &FunctionNameMock, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6)

// std::binds a 7-argument MetalMock object
#define BIND_7ARG_METALMOCK_OBJECT(FunctionNameMock) \
   std::bind(&decltype(FunctionNameMock)::MetalMockItFunctionPointer, &FunctionNameMock, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7)

// std::binds an 8-argument MetalMock object
#define BIND_8ARG_METALMOCK_OBJECT(FunctionNameMock) \
   std::bind(&decltype(FunctionNameMock)::MetalMockItFunctionPointer, &FunctionNameMock, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8)

// std::binds a 9-argument MetalMock object
#define BIND_9ARG_METALMOCK_OBJECT(FunctionNameMock) \
   std::bind(&decltype(FunctionNameMock)::MetalMockItFunctionPointer, &FunctionNameMock, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, std::placeholders::_9)

// std::binds a 10-argument MetalMock object
#define BIND_10ARG_METALMOCK_OBJECT(FunctionNameMock) \
   std::bind(&decltype(FunctionNameMock)::MetalMockItFunctionPointer, &FunctionNameMock, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, std::placeholders::_9, std::placeholders::_10)

namespace MetalMock
{
   inline std::atomic<unsigned long long> _atomicFunctionSequencingIndex;

   struct FunctionSequencingToken
   {
      unsigned long long sequencingIndex;

      FunctionSequencingToken() : sequencingIndex(_atomicFunctionSequencingIndex++) {}

      FunctionSequencingToken Then(FunctionSequencingToken functionSequencingToken)
      {
         IS_TRUE(sequencingIndex < functionSequencingToken.sequencingIndex);
         return functionSequencingToken;
      }
   };

   class UnexpectedCallException : public ZenUnit::MetalMockException
   {
   private:
      const std::string _what;
   public:
      template<typename... ArgTypes>
      explicit UnexpectedCallException(const std::string& metalMockedFunctionSignature, ArgTypes&&... args)
         : _what(MakeExceptionMessage(metalMockedFunctionSignature, std::forward<ArgTypes>(args)...))
      {
      }

      virtual ~UnexpectedCallException() = default;

      template<typename... ArgTypes>
      static std::string MakeExceptionMessage(const std::string& metalMockedFunctionSignature, ArgTypes&&... args)
      {
         std::ostringstream whatBuilder;
         whatBuilder << "Unexpected call to MetalMocked function:\n" << metalMockedFunctionSignature;
         AppendToStringedArgs(whatBuilder, 0, std::forward<ArgTypes>(args)...);
         const std::string exceptionMessage = whatBuilder.str();
         return exceptionMessage;
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

   class ReturnValueMustBeSpecifiedException : public ZenUnit::MetalMockException
   {
   private:
      const std::string _what;
   public:
      explicit ReturnValueMustBeSpecifiedException(const std::string& metalMockedFunctionSignature)
         : _what(MakeExceptionMessage(metalMockedFunctionSignature))
      {
      }

      virtual ~ReturnValueMustBeSpecifiedException() = default;

      const char* what() const noexcept override
      {
         return _what.c_str();
      }

      static std::string MakeExceptionMessage(std::string_view metalMockedFunctionSignature)
      {
         const std::string exceptionMessage = ZenUnit::String::Concat(
"For MetalMocked function \"", metalMockedFunctionSignature, R"(":
MetalMocked functions with non-void return types must have their return value or values set explicitly by calling:
[FunctionName]Mock.[Return|ReturnValues]())");
         return exceptionMessage;
      }
   };

   class UnsupportedCalledZeroTimesException : public ZenUnit::MetalMockException
   {
   private:
      const std::string _what;
   public:
      explicit UnsupportedCalledZeroTimesException(const std::string& metalMockedFunctionSignature)
         : _what(MakeExceptionMessage(metalMockedFunctionSignature))
      {
      }

      virtual ~UnsupportedCalledZeroTimesException() = default;

      static std::string MakeExceptionMessage(const std::string& metalMockedFunctionSignature)
      {
         const std::string exceptionMessage = ZenUnit::String::Concat(
            "For MetalMocked function \"", metalMockedFunctionSignature, R"(":

Because MetalMock is a strict mocking framework,
by design MetalMock objects do not support asserting that
their corresponding MetalMocked functions were called zero times.
To effectively assert that a MetalMocked function is expected to be called zero times,
simply do not call any of the expectation functions:
MetalMockObject.Expect()
MetalMockObject.Return()
MetalMockObject.ReturnValues()
MetalMockObject.ReturnRandom() or
MetalMockObject.ThrowExceptionWhenCalled<T>())");
         return exceptionMessage;
      }

      const char* what() const noexcept override
      {
         return _what.c_str();
      }
   };

   class IExceptionThrower
   {
   public:
      virtual void ThrowException() const = 0;
      virtual ~IExceptionThrower() = default;
   };

   template<typename ExceptionType>
   class TemplatedExceptionThrower : public IExceptionThrower
   {
      template<typename T>
      friend class TemplatedExceptionThrowerTests;
   private:
      std::unique_ptr<const ExceptionType> _exceptionToBeThrown;
   public:
      template<typename... ExceptionArgTypes>
      static const IExceptionThrower* New(ExceptionArgTypes&&... exceptionArgs)
      {
         TemplatedExceptionThrower<ExceptionType>* const newTemplatedExceptionThrower = new TemplatedExceptionThrower<ExceptionType>;
         newTemplatedExceptionThrower->_exceptionToBeThrown = std::make_unique<ExceptionType>(std::forward<ExceptionArgTypes>(exceptionArgs)...);
         return newTemplatedExceptionThrower;
      }

      void ThrowException() const override
      {
         if (_exceptionToBeThrown != nullptr)
         {
            throw *_exceptionToBeThrown;
         }
      }
   };

   class MetalMockExceptionThrower
   {
   private:
      std::shared_ptr<const IExceptionThrower> _exceptionThrower;
   public:
      template<typename ExceptionType, typename... ExceptionArgTypes>
      void ThrowExceptionWhenCalled(ExceptionArgTypes&&... exceptionArgs)
      {
         if (_exceptionThrower != nullptr)
         {
            throw std::logic_error("MetalMock::MetalMockExceptionThrower::ThrowExceptionWhenCalled<T>() called twice");
         }
         _exceptionThrower.reset(TemplatedExceptionThrower<ExceptionType>::New(std::forward<ExceptionArgTypes>(exceptionArgs)...));
      }

      void MetalMockThrowExceptionIfExceptionSet() const
      {
         if (_exceptionThrower != nullptr)
         {
            _exceptionThrower->ThrowException();
         }
      }
   };

   template<typename FunctionReturnType>
   class ValueReturner
   {
      friend class ValueReturnerTests;
      friend class NonVoidOneArgumentMetalMockerTests;
   public:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   private:
      const std::string _metalMockedFunctionSignature;
      // std::deque of return values instead of std::vector due to the implementation of std::vector<bool>
      std::deque<DecayedFunctionReturnType> _returnValues;
      size_t _returnValueIndex;
   public:
      ValueReturner()
         : _returnValueIndex(0)
      {
      }

      explicit ValueReturner(std::string_view metalMockedFunctionSignature)
         : _metalMockedFunctionSignature(metalMockedFunctionSignature)
         , _returnValueIndex(0)
      {
      }

      template<typename ReturnType>
      void MetalMockAddReturnValue(ReturnType&& returnValue)
      {
         _returnValues.emplace_back(std::forward<ReturnType>(returnValue));
      }

      template<typename ReturnType, typename... ReturnTypes>
      void MetalMockAddReturnValues(ReturnType&& firstReturnValue, ReturnTypes&&... subsequentReturnValues)
      {
         MetalMockAddReturnValue(std::forward<ReturnType>(firstReturnValue));
         MetalMockAddReturnValues(std::forward<ReturnTypes>(subsequentReturnValues)...);
      }

      void MetalMockAddReturnValues()
      {
      }

      template<typename ContainerType>
      void MetalMockAddContainerReturnValues(const ContainerType& returnValues)
      {
         if (returnValues.empty())
         {
            throw std::invalid_argument("MetalMock::ValueReturner::MetalMockAddContainerReturnValues(const ContainerType& returnValues): returnValues cannot be empty");
         }
         std::copy(returnValues.cbegin(), returnValues.cend(), std::back_inserter(_returnValues));
      }

      template<typename ContainerType>
      void MetalMockAddContainerReturnValues(ContainerType&& returnValues)
      {
         if (returnValues.empty())
         {
            throw std::invalid_argument("MetalMock::ValueReturner::MetalMockAddContainerReturnValues(const ContainerType& returnValues): returnValues cannot be empty");
         }
         for (auto& returnValue : returnValues)
         {
            _returnValues.emplace_back(std::move(returnValue));
         }
      }

      DecayedFunctionReturnType MetalMockAddRandomReturnValue()
      {
         DecayedFunctionReturnType randomReturnValue = ZenUnit::Random<DecayedFunctionReturnType>();
         _returnValues.push_back(randomReturnValue);
         return randomReturnValue;
      }

      const DecayedFunctionReturnType& MetalMockNextReturnValue()
      {
         if (_returnValues.empty())
         {
            throw MetalMock::ReturnValueMustBeSpecifiedException(_metalMockedFunctionSignature);
         }
         const DecayedFunctionReturnType& nextReturnValue =
            _returnValueIndex < _returnValues.size() ? _returnValues[_returnValueIndex++] : _returnValues.back();
         return nextReturnValue;
      }
   };

   template<typename MockableExceptionThrowerType>
   class MetalMocker
   {
      friend class MetalMockerTests;
   private:
      // Function Pointers
      std::function<void(int)> _call_exit;
      std::function<const ZenUnit::ZenUnitArgs&()> _call_ZenUnitTestRunner_GetZenUnitArgs;
      // Mutable Fields
      bool _metalMockExceptionIsInFlight = false;
   protected:
      // Mutable Components
      // Mockable template parameter instead of mockable unique_ptr for performance reasons
      MockableExceptionThrowerType _exceptionThrower;
      // Constant Fields
      const std::string MetalMockedFunctionSignature;
      // Mutable Fields
      FunctionSequencingToken _functionSequencingToken;
      bool _wasExpected = false;
      bool _wasAsserted = false;
   public:
      MetalMocker()
      {
      }

      explicit MetalMocker(std::string_view metalMockedFunctionSignature)
         // Function Pointers
         : _call_exit(::exit)
         , _call_ZenUnitTestRunner_GetZenUnitArgs(ZenUnit::ZenUnitTestRunner::GetZenUnitArgs)
         // Constant Fields
         , MetalMockedFunctionSignature(metalMockedFunctionSignature)
      {
      }

      ~MetalMocker()
      {
         MetalMockExitIfExpectedButNotAsserted();
      }

      MetalMocker& operator=(const MetalMocker&) = delete;

      template<typename ExceptionType, typename... ExceptionArgTypes>
      void ThrowExceptionWhenCalled(ExceptionArgTypes&&... exceptionArgs)
      {
         _exceptionThrower.template ThrowExceptionWhenCalled<ExceptionType>(std::forward<ExceptionArgTypes>(exceptionArgs)...);
         _wasExpected = true;
      }
   protected:
      void AssignAndIncrementFunctionSequenceIndex()
      {
         _functionSequencingToken.sequencingIndex = _atomicFunctionSequencingIndex++;
      }

      void MetalMockThrowExceptionIfExceptionSet()
      {
         _exceptionThrower.MetalMockThrowExceptionIfExceptionSet();
      }

      template<typename... ArgTypes>
      void MetalMockThrowIfNotExpected(ArgTypes&&... args)
      {
         if (!_wasExpected)
         {
            _metalMockExceptionIsInFlight = true;
            throw UnexpectedCallException(MetalMockedFunctionSignature, std::forward<ArgTypes>(args)...);
         }
      }

      void MetalMockSetAsserted()
      {
         _wasAsserted = true;
      }

      void MetalMockThrowIfExpectedNumberOfCalls0(size_t expectedNumberOfCallsToMetalMockedFunction)
      {
         if (expectedNumberOfCallsToMetalMockedFunction == 0)
         {
            _metalMockExceptionIsInFlight = true;
            throw UnsupportedCalledZeroTimesException(MetalMockedFunctionSignature);
         }
      }

      void MetalMockThrowIfExpectedCallsSizeIsZero(size_t expectedCallsSize)
      {
         if (expectedCallsSize == 0)
         {
            _metalMockExceptionIsInFlight = true;
            throw UnsupportedCalledZeroTimesException(MetalMockedFunctionSignature);
         }
      }

      template<typename NArgumentFunctionCallReferencesType, typename NArgumentFunctionCallType>
      static std::vector<NArgumentFunctionCallReferencesType> ConvertMetalMockFunctionCallsToMetalMockFunctionCallReferences(
         const std::vector<NArgumentFunctionCallType>& metalMockFunctionCalls)
      {
         std::vector<NArgumentFunctionCallReferencesType> metalMockFunctionCallReferences;
         metalMockFunctionCallReferences.reserve(metalMockFunctionCalls.size());
         std::for_each(metalMockFunctionCalls.cbegin(), metalMockFunctionCalls.cend(),
            [&](const NArgumentFunctionCallType& metalMockFunctionCall)
            {
               metalMockFunctionCallReferences.emplace_back(metalMockFunctionCall);
            });
         return metalMockFunctionCallReferences;
      }
   private:
      void MetalMockExitIfExpectedButNotAsserted() const
      {
         if (_wasExpected && !_wasAsserted && !_metalMockExceptionIsInFlight)
         {
            const ZenUnit::Console console;
            console.WriteLineColor(R"(
==============================================================================
MetalMocked Function Was Expected But Not Later Asserted As Having Been Called
==============================================================================)", ZenUnit::Color::Red);
            console.WriteLine("MetalMocked Function:\n" + MetalMockedFunctionSignature);
            const ZenUnit::ZenUnitArgs& zenUnitArgs = _call_ZenUnitTestRunner_GetZenUnitArgs();
            console.WriteColor("\n>>------>", ZenUnit::Color::Red);
            console.WriteLine("  Completed: " + zenUnitArgs.commandLine);
            console.WriteColor(">>------>", ZenUnit::Color::Red);
            console.WriteLine(" RandomSeed: --random-seed=" + std::to_string(ZenUnit::globalZenUnitMode.randomSeed));
            console.WriteColor(">>------>", ZenUnit::Color::Red);
            console.WriteLine("  StartTime: " + zenUnitArgs.startDateTime);
            console.WriteColor(">>------>", ZenUnit::Color::Red);
            ZenUnit::Watch watch;
            const std::string endDateTime = watch.DateTimeNow();
            console.WriteLine("    EndTime: " + endDateTime);
            console.WriteColor(">>------>", ZenUnit::Color::Red);
            const std::string testRunDurationInSeconds = ZenUnit::ZenUnitTestRunner::Instance()->StopTestRunStopwatchAndGetElapsedSeconds();
            console.WriteLine("   Duration: " + testRunDurationInSeconds + " seconds");
            console.WriteColor(">>------>", ZenUnit::Color::Red);
            console.WriteLine("     Result: MetalMocked Function Was Expected But Not Later Asserted As Having Been Called");
            console.WriteColor(">>-FAIL->", ZenUnit::Color::Red);
            const int exitCode = zenUnitArgs.alwaysExit0 ? 0 : 1;
            console.WriteLine("   ExitCode: " + std::to_string(exitCode));
            _call_exit(exitCode);
         }
      }
   };

   class ZeroArgumentMetalMockerTests;

   template<typename MockableExceptionThrowerType = MetalMockExceptionThrower>
   class ZeroArgumentMetalMocker : public MetalMocker<MockableExceptionThrowerType>
   {
      friend class ZeroArgumentMetalMockerTests;
   private:
      size_t numberOfCallsToMetalMockedFunction;
   protected:
      std::function<void()> _callInsteadFunction;
   public:
      explicit ZeroArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : MetalMocker<MockableExceptionThrowerType>(metalMockedFunctionSignature)
         , numberOfCallsToMetalMockedFunction(0)
      {
      }

      ~ZeroArgumentMetalMocker()
      {
         if (_callInsteadFunction)
         {
            this->_wasAsserted = true;
         }
      }

      void MetalMockIt()
      {
         this->MetalMockThrowIfNotExpected();
         ++this->numberOfCallsToMetalMockedFunction;
         if (this->_callInsteadFunction)
         {
            this->_callInsteadFunction();
         }
         this->AssignAndIncrementFunctionSequenceIndex();
         this->MetalMockThrowExceptionIfExceptionSet();
      }

      void CallInstead(const std::function<void()>& callInsteadFunction)
      {
         ZeroArgumentMetalMocker::_wasExpected = true;
         this->_callInsteadFunction = callInsteadFunction;
      }

      FunctionSequencingToken CalledOnce()
      {
         this->MetalMockSetAsserted();
         const size_t expectedNumberOfCallsToMetalMockedFunction = 1;
         ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->numberOfCallsToMetalMockedFunction, this->MetalMockedFunctionSignature);
         return this->_functionSequencingToken;
      }

      FunctionSequencingToken CalledNTimes(size_t expectedNumberOfCallsToMetalMockedFunction)
      {
         this->MetalMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCallsToMetalMockedFunction);
         this->MetalMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->numberOfCallsToMetalMockedFunction, this->MetalMockedFunctionSignature);
         return this->_functionSequencingToken;
      }
   };

   template<typename FunctionReturnType>
   class NonVoidZeroArgumentMetalMocker : public ZeroArgumentMetalMocker<MetalMockExceptionThrower>, protected ValueReturner<FunctionReturnType>
   {
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   public:
      explicit NonVoidZeroArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : ZeroArgumentMetalMocker<MetalMockExceptionThrower>(metalMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(metalMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         ZeroArgumentMetalMocker<MetalMockExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         ZeroArgumentMetalMocker<MetalMockExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         ZeroArgumentMetalMocker<MetalMockExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         ZeroArgumentMetalMocker<MetalMockExceptionThrower>::_wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::MetalMockAddRandomReturnValue();
         return randomReturnValue;
      }

      const FunctionReturnType& MetalMockItAndReturnValue()
      {
         ZeroArgumentMetalMocker::MetalMockIt();
         const FunctionReturnType& returnValue = ValueReturner<FunctionReturnType>::MetalMockNextReturnValue();
         return returnValue;
      }
   };

   template<typename FunctionReturnType>
   class NonVoidZeroArgFunctionPointerMetalMocker : public NonVoidZeroArgumentMetalMocker<FunctionReturnType>
   {
   public:
      explicit NonVoidZeroArgFunctionPointerMetalMocker(const std::string& metalMockedFunctionSignature)
         : NonVoidZeroArgumentMetalMocker<FunctionReturnType>(metalMockedFunctionSignature)
      {
      }

      static FunctionReturnType MetalMockItFunctionPointer(NonVoidZeroArgFunctionPointerMetalMocker<FunctionReturnType>* functionPointerMetalMocker)
      {
         const FunctionReturnType& returnValue = functionPointerMetalMocker->MetalMockItAndReturnValue();
         return returnValue;
      }
   };

   class VoidZeroArgumentMetalMocker : public ZeroArgumentMetalMocker<MetalMockExceptionThrower>
   {
   public:
      explicit VoidZeroArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : ZeroArgumentMetalMocker<MetalMockExceptionThrower>(metalMockedFunctionSignature)
      {
      }

      void Expect()
      {
         ZeroArgumentMetalMocker<MetalMockExceptionThrower>::_wasExpected = true;
      }
   };

   class VoidZeroArgFunctionPointerMetalMocker : public VoidZeroArgumentMetalMocker
   {
   public:
      explicit VoidZeroArgFunctionPointerMetalMocker(const std::string& metalMockedFunctionSignature)
         : VoidZeroArgumentMetalMocker(metalMockedFunctionSignature)
      {
      }

      static void MetalMockItFunctionPointer(VoidZeroArgFunctionPointerMetalMocker* functionPointerMetalMocker)
      {
         functionPointerMetalMocker->MetalMockIt();
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
   struct ArgumentStorage<std::span<char>>
   {
      std::string value;

      ArgumentStorage() = default;

      explicit ArgumentStorage(std::span<char> dynamicCharSpan)
         : value(dynamicCharSpan.data(), dynamicCharSpan.size()) {}
   };

   template<>
   struct ArgumentStorage<std::span<const char>>
   {
      std::string value;

      ArgumentStorage() = default;

      explicit ArgumentStorage(std::span<const char> dynamicCharSpan)
         : value(dynamicCharSpan.data(), dynamicCharSpan.size()) {}
   };

   template<>
   struct ArgumentStorage<std::string_view>
   {
      std::string value;

      ArgumentStorage() = default;

      explicit ArgumentStorage(std::string_view stringView)
         : value(stringView) {}
   };

   template<>
   struct ArgumentStorage<std::wstring_view>
   {
      std::wstring value;

      ArgumentStorage() = default;

      explicit ArgumentStorage(std::wstring_view wideStringView)
         : value(wideStringView) {}
   };

   template<typename T>
   struct ArgumentStorage<std::unique_ptr<T>>
   {
      const T* const value;

      ArgumentStorage() = delete;

      explicit ArgumentStorage(const std::unique_ptr<T>& uniquePtr)
         : value(uniquePtr.get()) {}
   };

   template<typename T>
   struct ReferenceStorage
   {
      const T& value;

      ReferenceStorage()
         : value() {}

      explicit ReferenceStorage(const T& argument)
         : value(argument) {}
   };

   template<>
   struct ReferenceStorage<std::string_view>
   {
      std::string value;

      ReferenceStorage() = default;

      explicit ReferenceStorage(std::string_view argument)
         : value(argument) {}
   };

   template<typename T>
   struct ReferenceStorage<std::unique_ptr<T>>
   {
      const T* const value;

      ReferenceStorage() = delete;

      explicit ReferenceStorage(const std::unique_ptr<T>& uniquePtr)
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
      typename MockableExceptionThrowerType = MetalMockExceptionThrower>
   class OneArgumentMetalMocker : public MetalMocker<MockableExceptionThrowerType>
   {
      friend class OneArgumentMetalMockerTests;
      template<
         typename MetalMockObjectType,
         typename FreeMockType,
         typename StaticMockType,
         typename StaticNameClashMockType>
      friend class MetalMock1Tester;
   public:
      std::vector<OneArgumentFunctionCall<ArgType>> metalMockedFunctionCallHistory;

      OneArgumentMetalMocker()
      {
      }

      explicit OneArgumentMetalMocker(std::string_view metalMockedFunctionSignature)
         : MetalMocker<MockableExceptionThrowerType>(metalMockedFunctionSignature)
      {
      }

      void MetalMockIt(const ArgType& argument)
      {
         this->MetalMockThrowIfNotExpected(argument);
         this->metalMockedFunctionCallHistory.emplace_back(argument);
         this->MetalMockThrowExceptionIfExceptionSet();
      }

      FunctionSequencingToken CalledOnceWith(const ArgType& expectedArgument)
      {
         this->MetalMockSetAsserted();
         const size_t expectedNumberOfCallsToMetalMockedFunction = 1;
         ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedArgument, this->metalMockedFunctionCallHistory[0].argument.value, this->MetalMockedFunctionSignature);
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledOnceWithAny()
      {
         this->MetalMockSetAsserted();
         const size_t expectedNumberOfCallsToMetalMockedFunction = 1;
         ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature);
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledNTimesWith(size_t expectedNumberOfCallsToMetalMockedFunction, const ArgType& expectedArgument)
      {
         this->MetalMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCallsToMetalMockedFunction);
         this->MetalMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCallsToMetalMockedFunction; ++i)
         {
            const std::string metalMockedFunctionSignatureAndCallIndex =
               ZenUnit::String::Concat(this->MetalMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArgument, this->metalMockedFunctionCallHistory[i].argument.value, metalMockedFunctionSignatureAndCallIndex);
         }
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(
         const std::vector<OneArgumentFunctionCallReference<ArgType>>& expectedOneArgumentFunctionCalls)
      {
         this->MetalMockThrowIfExpectedCallsSizeIsZero(expectedOneArgumentFunctionCalls.size());
         this->MetalMockSetAsserted();
         const std::vector<OneArgumentFunctionCallReference<ArgType>> actualOneArgumentFunctionCalls =
            MetalMocker<MockableExceptionThrowerType>::template ConvertMetalMockFunctionCallsToMetalMockFunctionCallReferences<
               OneArgumentFunctionCallReference<ArgType>,
               OneArgumentFunctionCall<ArgType>>(this->metalMockedFunctionCallHistory);
         VECTORS_ARE_EQUAL(expectedOneArgumentFunctionCalls, actualOneArgumentFunctionCalls, this->MetalMockedFunctionSignature);
         return FunctionSequencingToken();
      }
   };

   template<typename ArgType>
   class VoidOneArgumentMetalMocker : public OneArgumentMetalMocker<ArgType>
   {
      friend class VoidOneArgumentMetalMockerTests;
   private:
      std::function<void(ArgType)> _callInsteadFunction;
   public:
      explicit VoidOneArgumentMetalMocker(std::string_view metalMockedFunctionSignature)
         : OneArgumentMetalMocker<ArgType>(metalMockedFunctionSignature)
      {
      }

      virtual ~VoidOneArgumentMetalMocker()
      {
         if (_callInsteadFunction)
         {
            OneArgumentMetalMocker<ArgType>::_wasAsserted = true;
         }
      }

      void CallInstead(const std::function<void(ArgType)>& callInsteadFunction)
      {
         _callInsteadFunction = callInsteadFunction;
         OneArgumentMetalMocker<ArgType>::_wasExpected = true;
      }

      void Expect()
      {
         OneArgumentMetalMocker<ArgType>::_wasExpected = true;
      }

      void MetalMockIt(const ArgType& arg)
      {
         if (_callInsteadFunction)
         {
            _callInsteadFunction(arg);
         }
         OneArgumentMetalMocker<ArgType>::MetalMockIt(arg);
      }
   };

   template<typename FunctionReturnType, typename ArgType>
   class NonVoidOneArgumentMetalMocker : public OneArgumentMetalMocker<ArgType>, protected ValueReturner<FunctionReturnType>
   {
      friend class NonVoidOneArgumentMetalMockerTests;
   private:
      std::function<FunctionReturnType(ArgType)> _callInsteadFunction;
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   public:
      NonVoidOneArgumentMetalMocker()
      {
      }

      explicit NonVoidOneArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : OneArgumentMetalMocker<ArgType>(metalMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(metalMockedFunctionSignature)
      {
      }

      ~NonVoidOneArgumentMetalMocker()
      {
         if (_callInsteadFunction)
         {
            this->_wasAsserted = true;
         }
      }

      void CallInstead(const std::function<FunctionReturnType(ArgType)>& callInsteadFunction)
      {
         OneArgumentMetalMocker<ArgType>::_wasExpected = true;
         _callInsteadFunction = callInsteadFunction;
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         OneArgumentMetalMocker<ArgType>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         OneArgumentMetalMocker<ArgType>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         OneArgumentMetalMocker<ArgType>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         OneArgumentMetalMocker<ArgType>::_wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::MetalMockAddRandomReturnValue();
         return randomReturnValue;
      }

      FunctionReturnType MetalMockItAndReturnValue(ArgType argument)
      {
         OneArgumentMetalMocker<ArgType>::MetalMockIt(argument);
         if (this->_callInsteadFunction)
         {
            const FunctionReturnType& returnValue = this->_callInsteadFunction(argument);
            return returnValue;
         }
         const FunctionReturnType& returnValue = ValueReturner<FunctionReturnType>::MetalMockNextReturnValue();
         return returnValue;
      }
   };

   template<typename FunctionReturnType, typename Arg1Type>
   class NonVoidOneArgFunctionPointerMetalMocker : public NonVoidOneArgumentMetalMocker<FunctionReturnType, Arg1Type>
   {
   public:
      explicit NonVoidOneArgFunctionPointerMetalMocker(const std::string& metalMockedFunctionSignature)
         : NonVoidOneArgumentMetalMocker<FunctionReturnType, Arg1Type>(metalMockedFunctionSignature)
      {
      }

      static FunctionReturnType MetalMockItFunctionPointer(NonVoidOneArgFunctionPointerMetalMocker* functionMocker, Arg1Type argument)
      {
         const FunctionReturnType& returnValue = functionMocker->MetalMockItAndReturnValue(argument);
         return returnValue;
      }
   };

   template<typename Arg1Type>
   class VoidOneArgFunctionPointerMetalMocker : public VoidOneArgumentMetalMocker<Arg1Type>
   {
   public:
      explicit VoidOneArgFunctionPointerMetalMocker(const std::string& metalMockedFunctionSignature)
         : VoidOneArgumentMetalMocker<Arg1Type>(metalMockedFunctionSignature)
      {
      }

      static void MetalMockItFunctionPointer(VoidOneArgFunctionPointerMetalMocker<Arg1Type>* functionMocker, Arg1Type argument)
      {
         functionMocker->MetalMockIt(argument);
      }
   };

   template<
      typename Arg1Type,
      typename Arg2Type,
      typename MockableExceptionThrowerType = MetalMockExceptionThrower>
   class TwoArgumentMetalMocker : public MetalMocker<MockableExceptionThrowerType>
   {
      friend class TwoArgumentMetalMockerTests;
   protected:
      std::function<void(Arg1Type, Arg2Type)> _baseVoidCallInsteadFunction;
   public:
      std::vector<TwoArgumentFunctionCall<Arg1Type, Arg2Type>> metalMockedFunctionCallHistory;

      explicit TwoArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : MetalMocker<MockableExceptionThrowerType>(metalMockedFunctionSignature)
      {
      }

      ~TwoArgumentMetalMocker()
      {
         if (_baseVoidCallInsteadFunction)
         {
            this->_wasAsserted = true;
         }
      }

      void MetalMockIt(const Arg1Type& firstArgument, const Arg2Type& secondArgument)
      {
         this->MetalMockThrowIfNotExpected(firstArgument, secondArgument);
         metalMockedFunctionCallHistory.emplace_back(firstArgument, secondArgument);
         if (this->_baseVoidCallInsteadFunction)
         {
            this->_baseVoidCallInsteadFunction(firstArgument, secondArgument);
         }
         this->MetalMockThrowExceptionIfExceptionSet();
      }

      FunctionSequencingToken CalledOnceWith(
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument)
      {
         this->MetalMockSetAsserted();
         const size_t expectedNumberOfCallsToMetalMockedFunction = 1;
         ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, this->metalMockedFunctionCallHistory[0].firstArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, this->metalMockedFunctionCallHistory[0].secondArgument.value, this->MetalMockedFunctionSignature);
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledNTimesWith(
         size_t expectedNumberOfCallsToMetalMockedFunction,
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument)
      {
         this->MetalMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCallsToMetalMockedFunction);
         this->MetalMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCallsToMetalMockedFunction; ++i)
         {
            const std::string metalMockedFunctionSignatureAndCallIndex =
               ZenUnit::String::Concat(this->MetalMockedFunctionSignature, ", at i=", i);
            ARE_EQUAL(expectedFirstArgument, this->metalMockedFunctionCallHistory[i].firstArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, this->metalMockedFunctionCallHistory[i].secondArgument.value, metalMockedFunctionSignatureAndCallIndex);
         }
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(
         const std::vector<TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>>& expectedTwoArgumentFunctionCalls)
      {
         this->MetalMockThrowIfExpectedCallsSizeIsZero(expectedTwoArgumentFunctionCalls.size());
         this->MetalMockSetAsserted();
         const std::vector<TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>> actualTwoArgumentFunctionCalls =
            MetalMocker<MockableExceptionThrowerType>::template ConvertMetalMockFunctionCallsToMetalMockFunctionCallReferences<
               TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>,
               TwoArgumentFunctionCall<Arg1Type, Arg2Type>>(this->metalMockedFunctionCallHistory);
         VECTORS_ARE_EQUAL(expectedTwoArgumentFunctionCalls, actualTwoArgumentFunctionCalls, this->MetalMockedFunctionSignature);
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollowsInAnyOrder(
         const std::vector<TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>>& expectedTwoArgumentFunctionCalls)
      {
         this->MetalMockThrowIfExpectedCallsSizeIsZero(expectedTwoArgumentFunctionCalls.size());
         this->MetalMockSetAsserted();
         const std::vector<TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>> actualTwoArgumentFunctionCalls =
            MetalMocker<MockableExceptionThrowerType>::template ConvertMetalMockFunctionCallsToMetalMockFunctionCallReferences<
               TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>,
               TwoArgumentFunctionCall<Arg1Type, Arg2Type>>(this->metalMockedFunctionCallHistory);
         INDEXABLES_ARE_EQUAL_IN_ANY_ORDER(expectedTwoArgumentFunctionCalls, actualTwoArgumentFunctionCalls, this->MetalMockedFunctionSignature);
         return FunctionSequencingToken();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type>
   class NonVoidTwoArgumentMetalMocker : public TwoArgumentMetalMocker<Arg1Type, Arg2Type>, protected ValueReturner<FunctionReturnType>
   {
      friend class NonVoidTwoArgumentMetalMockerTests;
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
      std::function<FunctionReturnType(Arg1Type, Arg2Type)> _derivedNonVoidCallInsteadFunction;
   public:
      explicit NonVoidTwoArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : TwoArgumentMetalMocker<Arg1Type, Arg2Type>(metalMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(metalMockedFunctionSignature)
      {
      }

      ~NonVoidTwoArgumentMetalMocker()
      {
         if (_derivedNonVoidCallInsteadFunction)
         {
            this->_wasAsserted = true;
         }
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         TwoArgumentMetalMocker<Arg1Type, Arg2Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         TwoArgumentMetalMocker<Arg1Type, Arg2Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         TwoArgumentMetalMocker<Arg1Type, Arg2Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         TwoArgumentMetalMocker<Arg1Type, Arg2Type>::_wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::MetalMockAddRandomReturnValue();
         return randomReturnValue;
      }

      void CallInstead(const std::function<FunctionReturnType(Arg1Type, Arg2Type)>& callInsteadFunction)
      {
         TwoArgumentMetalMocker<Arg1Type, Arg2Type>::_wasExpected = true;
         this->_derivedNonVoidCallInsteadFunction = callInsteadFunction;
      }

      FunctionReturnType MetalMockItAndReturnValue(Arg1Type firstArgument, Arg2Type secondArgument)
      {
         TwoArgumentMetalMocker<Arg1Type, Arg2Type>::MetalMockIt(firstArgument, secondArgument);
         if (this->_derivedNonVoidCallInsteadFunction)
         {
            const FunctionReturnType& returnValue = this->_derivedNonVoidCallInsteadFunction(firstArgument, secondArgument);
            return returnValue;
         }
         const FunctionReturnType& returnValue = ValueReturner<FunctionReturnType>::MetalMockNextReturnValue();
         return returnValue;
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type>
   class NonVoidTwoArgFunctionPointerMetalMocker : public NonVoidTwoArgumentMetalMocker<FunctionReturnType, Arg1Type, Arg2Type>
   {
   public:
      explicit NonVoidTwoArgFunctionPointerMetalMocker(const std::string& metalMockedFunctionSignature)
         : NonVoidTwoArgumentMetalMocker<FunctionReturnType, Arg1Type, Arg2Type>(metalMockedFunctionSignature)
      {
      }

      static FunctionReturnType MetalMockItFunctionPointer(
         NonVoidTwoArgFunctionPointerMetalMocker<FunctionReturnType, Arg1Type, Arg2Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument)
      {
         const FunctionReturnType& returnValue = functionMocker->MetalMockItAndReturnValue(firstArgument, secondArgument);
         return returnValue;
      }
   };

   template<typename Arg1Type, typename Arg2Type>
   class VoidTwoArgumentMetalMocker : public TwoArgumentMetalMocker<Arg1Type, Arg2Type>
   {
   public:
      explicit VoidTwoArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : TwoArgumentMetalMocker<Arg1Type, Arg2Type>(metalMockedFunctionSignature)
      {
      }

      void Expect()
      {
         TwoArgumentMetalMocker<Arg1Type, Arg2Type>::_wasExpected = true;
      }

      void CallInstead(const std::function<void(Arg1Type, Arg2Type)>& callInsteadFunction)
      {
         TwoArgumentMetalMocker<Arg1Type, Arg2Type>::_wasExpected = true;
         this->_baseVoidCallInsteadFunction = callInsteadFunction;
      }
   };

   template<typename Arg1Type, typename Arg2Type>
   class VoidTwoArgFunctionPointerMetalMocker : public VoidTwoArgumentMetalMocker<Arg1Type, Arg2Type>
   {
   public:
      explicit VoidTwoArgFunctionPointerMetalMocker(const std::string& metalMockedFunctionSignature)
         : VoidTwoArgumentMetalMocker<Arg1Type, Arg2Type>(metalMockedFunctionSignature)
      {
      }

      static void MetalMockItFunctionPointer(
         VoidTwoArgFunctionPointerMetalMocker<Arg1Type, Arg2Type>* functionMocker, Arg1Type firstArgument, Arg2Type secondArgument)
      {
         functionMocker->MetalMockIt(firstArgument, secondArgument);
      }
   };

   template<
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename MockableExceptionThrowerType = MetalMockExceptionThrower>
   class ThreeArgumentMetalMocker : public MetalMocker<MockableExceptionThrowerType>
   {
      friend class ThreeArgumentMetalMockerTests;
   public:
      std::vector<ThreeArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type>> metalMockedFunctionCallHistory;

      explicit ThreeArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : MetalMocker<MockableExceptionThrowerType>(metalMockedFunctionSignature)
      {
      }

      virtual ~ThreeArgumentMetalMocker() = default;

      virtual void MetalMockIt(const Arg1Type& firstArgument, const Arg2Type& secondArgument, const Arg3Type& thirdArgument)
      {
         this->MetalMockThrowIfNotExpected(firstArgument, secondArgument, thirdArgument);
         this->metalMockedFunctionCallHistory.emplace_back(firstArgument, secondArgument, thirdArgument);
         this->MetalMockThrowExceptionIfExceptionSet();
      }

      FunctionSequencingToken CalledOnceWith(
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument)
      {
         this->MetalMockSetAsserted();
         const size_t expectedNumberOfCallsToMetalMockedFunction = 1;
         ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, this->metalMockedFunctionCallHistory[0].firstArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, this->metalMockedFunctionCallHistory[0].secondArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, this->metalMockedFunctionCallHistory[0].thirdArgument.value, this->MetalMockedFunctionSignature);
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledNTimesWith(
         size_t expectedNumberOfCallsToMetalMockedFunction,
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument)
      {
         this->MetalMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCallsToMetalMockedFunction);
         this->MetalMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCallsToMetalMockedFunction; ++i)
         {
            const std::string metalMockedFunctionSignatureAndCallIndex = ZenUnit::String::Concat(this->MetalMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, this->metalMockedFunctionCallHistory[i].firstArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, this->metalMockedFunctionCallHistory[i].secondArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, this->metalMockedFunctionCallHistory[i].thirdArgument.value, metalMockedFunctionSignatureAndCallIndex);
         }
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(
         const std::vector<ThreeArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type>>& expectedThreeArgumentFunctionCalls)
      {
         this->MetalMockThrowIfExpectedCallsSizeIsZero(expectedThreeArgumentFunctionCalls.size());
         this->MetalMockSetAsserted();
         const std::vector<ThreeArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type>> actualThreeArgumentFunctionCalls =
            MetalMocker<MockableExceptionThrowerType>::template ConvertMetalMockFunctionCallsToMetalMockFunctionCallReferences<
               ThreeArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type>,
               ThreeArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type>>(this->metalMockedFunctionCallHistory);
         VECTORS_ARE_EQUAL(expectedThreeArgumentFunctionCalls, actualThreeArgumentFunctionCalls, this->MetalMockedFunctionSignature);
         return FunctionSequencingToken();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class NonVoidThreeArgumentMetalMocker : public ThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>, protected ValueReturner<FunctionReturnType>
   {
      friend class NonVoidThreeArgumentMetalMockerTests;
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
      std::function<FunctionReturnType(Arg1Type, Arg2Type, Arg3Type)> _derivedNonVoidCallInsteadFunction;
   public:
      explicit NonVoidThreeArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : ThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>(metalMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(metalMockedFunctionSignature)
      {
      }

      ~NonVoidThreeArgumentMetalMocker()
      {
         if (_derivedNonVoidCallInsteadFunction)
         {
            this->_wasAsserted = true;
         }
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         ThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         ThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         ThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         ThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>::_wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::MetalMockAddRandomReturnValue();
         return randomReturnValue;
      }

      void CallInstead(const std::function<FunctionReturnType(Arg1Type, Arg2Type, Arg3Type)>& callInsteadFunction)
      {
         ThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>::_wasExpected = true;
         this->_derivedNonVoidCallInsteadFunction = callInsteadFunction;
      }

      FunctionReturnType MetalMockItAndReturnValue(Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument)
      {
         ThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>::MetalMockIt(firstArgument, secondArgument, thirdArgument);
         if (this->_derivedNonVoidCallInsteadFunction)
         {
            const FunctionReturnType& returnValue = this->_derivedNonVoidCallInsteadFunction(firstArgument, secondArgument, thirdArgument);
            return returnValue;
         }
         const FunctionReturnType& returnValue = ValueReturner<FunctionReturnType>::MetalMockNextReturnValue();
         return returnValue;
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class NonVoidThreeArgFunctionPointerMetalMocker : public NonVoidThreeArgumentMetalMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type>
   {
   public:
      explicit NonVoidThreeArgFunctionPointerMetalMocker(const std::string& metalMockedFunctionSignature)
         : NonVoidThreeArgumentMetalMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type>(metalMockedFunctionSignature)
      {
      }

      static FunctionReturnType MetalMockItFunctionPointer(
         NonVoidThreeArgFunctionPointerMetalMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument)
      {
         const FunctionReturnType& returnValue = functionMocker->MetalMockItAndReturnValue(firstArgument, secondArgument, thirdArgument);
         return returnValue;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class VoidThreeArgumentMetalMocker : public ThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>
   {
   protected:
      std::function<void(Arg1Type, Arg2Type, Arg3Type)> _callInsteadFunction;
   public:
      explicit VoidThreeArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : ThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>(metalMockedFunctionSignature)
      {
      }

      ~VoidThreeArgumentMetalMocker()
      {
         if (_callInsteadFunction)
         {
            this->_wasAsserted = true;
         }
      }

      void Expect()
      {
         ThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>::_wasExpected = true;
      }

      void CallInstead(const std::function<void(Arg1Type, Arg2Type, Arg3Type)>& callInsteadFunction)
      {
         ThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>::_wasExpected = true;
         this->_callInsteadFunction = callInsteadFunction;
      }

      void MetalMockIt(const Arg1Type& firstArgument, const Arg2Type& secondArgument, const Arg3Type& thirdArgument) override
      {
         this->MetalMockThrowIfNotExpected(firstArgument, secondArgument, thirdArgument);
         this->metalMockedFunctionCallHistory.emplace_back(firstArgument, secondArgument, thirdArgument);
         if (this->_callInsteadFunction)
         {
            this->_callInsteadFunction(firstArgument, secondArgument, thirdArgument);
         }
         this->MetalMockThrowExceptionIfExceptionSet();
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class VoidThreeArgFunctionPointerMetalMocker : public VoidThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>
   {
   public:
      explicit VoidThreeArgFunctionPointerMetalMocker(const std::string& metalMockedFunctionSignature)
         : VoidThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>(metalMockedFunctionSignature)
      {
      }

      static void MetalMockItFunctionPointer(
         VoidThreeArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument)
      {
         functionMocker->MetalMockIt(firstArgument, secondArgument, thirdArgument);
      }
   };

   template<
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename Arg4Type,
      typename MockableExceptionThrowerType = MetalMockExceptionThrower>
   class FourArgumentMetalMocker : public MetalMocker<MockableExceptionThrowerType>
   {
      friend class FourArgumentMetalMockerTests;
   public:
      std::vector<FourArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>> metalMockedFunctionCallHistory;

      explicit FourArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : MetalMocker<MockableExceptionThrowerType>(metalMockedFunctionSignature)
      {
      }

      void MetalMockIt(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument)
      {
         this->MetalMockThrowIfNotExpected(firstArgument, secondArgument, thirdArgument, fourthArgument);
         metalMockedFunctionCallHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument);
         this->MetalMockThrowExceptionIfExceptionSet();
      }

      FunctionSequencingToken CalledOnceWith(
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument)
      {
         this->MetalMockSetAsserted();
         const size_t expectedNumberOfCallsToMetalMockedFunction = 1;
         ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, this->metalMockedFunctionCallHistory[0].firstArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, this->metalMockedFunctionCallHistory[0].secondArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, this->metalMockedFunctionCallHistory[0].thirdArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, this->metalMockedFunctionCallHistory[0].fourthArgument.value, this->MetalMockedFunctionSignature);
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledNTimesWith(
         size_t expectedNumberOfCallsToMetalMockedFunction,
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument)
      {
         this->MetalMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCallsToMetalMockedFunction);
         this->MetalMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCallsToMetalMockedFunction; ++i)
         {
            const std::string metalMockedFunctionSignatureAndCallIndex = ZenUnit::String::Concat(this->MetalMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, this->metalMockedFunctionCallHistory[i].firstArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, this->metalMockedFunctionCallHistory[i].secondArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, this->metalMockedFunctionCallHistory[i].thirdArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, this->metalMockedFunctionCallHistory[i].fourthArgument.value, metalMockedFunctionSignatureAndCallIndex);
         }
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(
         const std::vector<FourArgumentFunctionCallReference<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>& expectedFourArgumentFunctionCalls)
      {
         this->MetalMockThrowIfExpectedCallsSizeIsZero(expectedFourArgumentFunctionCalls.size());
         this->MetalMockSetAsserted();
         const std::vector<FourArgumentFunctionCallReference<Arg1Type, Arg2Type, Arg3Type, Arg4Type>> actualFourArgumentFunctionCalls =
            MetalMocker<MockableExceptionThrowerType>::template ConvertMetalMockFunctionCallsToMetalMockFunctionCallReferences<
               FourArgumentFunctionCallReference<Arg1Type, Arg2Type, Arg3Type, Arg4Type>,
               FourArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>(this->metalMockedFunctionCallHistory);
         VECTORS_ARE_EQUAL(expectedFourArgumentFunctionCalls, actualFourArgumentFunctionCalls, this->MetalMockedFunctionSignature);
         return FunctionSequencingToken();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class NonVoidFourArgumentMetalMocker : public FourArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>, protected ValueReturner<FunctionReturnType>
   {
      friend class NonVoidFourArgumentMetalMockerTests;
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
      std::function<FunctionReturnType(Arg1Type, Arg2Type, Arg3Type, Arg4Type)> _callInsteadFunction;
   public:
      explicit NonVoidFourArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : FourArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>(metalMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(metalMockedFunctionSignature)
      {
      }

      virtual ~NonVoidFourArgumentMetalMocker()
      {
         if (_callInsteadFunction)
         {
            this->_wasAsserted = true;
         }
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         FourArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         FourArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         FourArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         FourArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::_wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::MetalMockAddRandomReturnValue();
         return randomReturnValue;
      }

      void CallInstead(const std::function<FunctionReturnType(Arg1Type, Arg2Type, Arg3Type, Arg4Type)>& callInsteadFunction)
      {
         FourArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::_wasExpected = true;
         this->_callInsteadFunction = callInsteadFunction;
      }

      virtual FunctionReturnType MetalMockItAndReturnValue(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4)
      {
         FourArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::MetalMockIt(arg1, arg2, arg3, arg4);
         if (this->_callInsteadFunction)
         {
            const FunctionReturnType& returnValue = this->_callInsteadFunction(arg1, arg2, arg3, arg4);
            return returnValue;
         }
         const FunctionReturnType& returnValue = ValueReturner<FunctionReturnType>::MetalMockNextReturnValue();
         return returnValue;
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class NonVoidFourArgFunctionPointerMetalMocker : public NonVoidFourArgumentMetalMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>
   {
   public:
      explicit NonVoidFourArgFunctionPointerMetalMocker(const std::string& metalMockedFunctionSignature)
         : NonVoidFourArgumentMetalMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>(metalMockedFunctionSignature)
      {
      }

      static FunctionReturnType MetalMockItFunctionPointer(
         NonVoidFourArgFunctionPointerMetalMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument)
      {
         const FunctionReturnType& returnValue = functionMocker->MetalMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument);
         return returnValue;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class VoidFourArgumentMetalMocker : public FourArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>
   {
   public:
      explicit VoidFourArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : FourArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>(metalMockedFunctionSignature)
      {
      }

      void Expect()
      {
         FourArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::_wasExpected = true;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class VoidFourArgFunctionPointerMetalMocker : public VoidFourArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>
   {
   public:
      explicit VoidFourArgFunctionPointerMetalMocker(const std::string& metalMockedFunctionSignature)
         : VoidFourArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>(metalMockedFunctionSignature)
      {
      }

      static void MetalMockItFunctionPointer(
         VoidFourArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument)
      {
         functionMocker->MetalMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument);
      }
   };

   template<
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename Arg4Type,
      typename Arg5Type,
      typename MockableExceptionThrowerType = MetalMockExceptionThrower>
   class FiveArgumentMetalMocker : public MetalMocker<MockableExceptionThrowerType>
   {
      friend class FiveArgumentMetalMockerTests;
   public:
      std::vector<FiveArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>> metalMockedFunctionCallHistory;

      explicit FiveArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : MetalMocker<MockableExceptionThrowerType>(metalMockedFunctionSignature)
      {
      }

      void MetalMockIt(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument)
      {
         this->MetalMockThrowIfNotExpected(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument);
         metalMockedFunctionCallHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument);
         this->MetalMockThrowExceptionIfExceptionSet();
      }

      FunctionSequencingToken CalledOnceWith(
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument,
         const Arg5Type& expectedFifthArgument)
      {
         this->MetalMockSetAsserted();
         const size_t expectedNumberOfCallsToMetalMockedFunction = 1;
         ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, this->metalMockedFunctionCallHistory[0].firstArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, this->metalMockedFunctionCallHistory[0].secondArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, this->metalMockedFunctionCallHistory[0].thirdArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, this->metalMockedFunctionCallHistory[0].fourthArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedFifthArgument, this->metalMockedFunctionCallHistory[0].fifthArgument.value, this->MetalMockedFunctionSignature);
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledNTimesWith(
         size_t expectedNumberOfCallsToMetalMockedFunction,
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument,
         const Arg5Type& expectedFifthArgument)
      {
         this->MetalMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCallsToMetalMockedFunction);
         this->MetalMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCallsToMetalMockedFunction; ++i)
         {
            std::string metalMockedFunctionSignatureAndCallIndex = ZenUnit::String::Concat(this->MetalMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, this->metalMockedFunctionCallHistory[i].firstArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, this->metalMockedFunctionCallHistory[i].secondArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, this->metalMockedFunctionCallHistory[i].thirdArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, this->metalMockedFunctionCallHistory[i].fourthArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFifthArgument, this->metalMockedFunctionCallHistory[i].fifthArgument.value, metalMockedFunctionSignatureAndCallIndex);
         }
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(
         const std::vector<FiveArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>& expectedFiveArgumentFunctionCalls)
      {
         this->MetalMockThrowIfExpectedCallsSizeIsZero(expectedFiveArgumentFunctionCalls.size());
         this->MetalMockSetAsserted();
         const std::vector<FiveArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>> actualFiveArgumentFunctionCalls =
            MetalMocker<MockableExceptionThrowerType>::template ConvertMetalMockFunctionCallsToMetalMockFunctionCallReferences<
               FiveArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>,
               FiveArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>(this->metalMockedFunctionCallHistory);
         VECTORS_ARE_EQUAL(expectedFiveArgumentFunctionCalls, actualFiveArgumentFunctionCalls, this->MetalMockedFunctionSignature);
         return FunctionSequencingToken();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   class NonVoidFiveArgumentMetalMocker : public FiveArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>, protected ValueReturner<FunctionReturnType>
   {
      friend class NonVoidFiveArgumentMetalMockerTests;
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
      std::function<FunctionReturnType(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)> _callInsteadFunction;
   public:
      explicit NonVoidFiveArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : FiveArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>(metalMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(metalMockedFunctionSignature)
      {
      }

      virtual ~NonVoidFiveArgumentMetalMocker()
      {
         if (_callInsteadFunction)
         {
            this->_wasAsserted = true;
         }
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         FiveArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         FiveArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         FiveArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         FiveArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::_wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::MetalMockAddRandomReturnValue();
         return randomReturnValue;
      }

      void CallInstead(const std::function<FunctionReturnType(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)>& callInsteadFunction)
      {
         FiveArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::_wasExpected = true;
         this->_callInsteadFunction = callInsteadFunction;
      }

      virtual FunctionReturnType MetalMockItAndReturnValue(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4, Arg5Type arg5)
      {
         FiveArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::MetalMockIt(arg1, arg2, arg3, arg4, arg5);
         if (this->_callInsteadFunction)
         {
            const FunctionReturnType& returnValue = this->_callInsteadFunction(arg1, arg2, arg3, arg4, arg5);
            return returnValue;
         }
         const FunctionReturnType& returnValue = ValueReturner<FunctionReturnType>::MetalMockNextReturnValue();
         return returnValue;
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   class NonVoidFiveArgFunctionPointerMetalMocker : public NonVoidFiveArgumentMetalMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>
   {
   public:
      explicit NonVoidFiveArgFunctionPointerMetalMocker(const std::string& metalMockedFunctionSignature)
         : NonVoidFiveArgumentMetalMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>(metalMockedFunctionSignature)
      {
      }

      static FunctionReturnType MetalMockItFunctionPointer(
         NonVoidFiveArgFunctionPointerMetalMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument)
      {
         const FunctionReturnType& returnValue = functionMocker->MetalMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument);
         return returnValue;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   class VoidFiveArgumentMetalMocker : public FiveArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>
   {
   public:
      explicit VoidFiveArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : FiveArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>(metalMockedFunctionSignature)
      {
      }

      void Expect()
      {
         FiveArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::_wasExpected = true;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   class VoidFiveArgFunctionPointerMetalMocker : public VoidFiveArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>
   {
   public:
      explicit VoidFiveArgFunctionPointerMetalMocker(const std::string& metalMockedFunctionSignature)
         : VoidFiveArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>(metalMockedFunctionSignature)
      {
      }

      static void MetalMockItFunctionPointer(
         VoidFiveArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument)
      {
         functionMocker->MetalMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument);
      }
   };

   template<
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename Arg4Type,
      typename Arg5Type,
      typename Arg6Type,
      typename MockableExceptionThrowerType = MetalMockExceptionThrower>
   class SixArgumentMetalMocker : public MetalMocker<MockableExceptionThrowerType>
   {
      friend class SixArgumentMetalMockerTests;
   public:
      std::vector<SixArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>> metalMockedFunctionCallHistory;

      explicit SixArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : MetalMocker<MockableExceptionThrowerType>(metalMockedFunctionSignature)
      {
      }

      void MetalMockIt(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument,
         const Arg6Type& sixthArgument)
      {
         this->MetalMockThrowIfNotExpected(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument);
         metalMockedFunctionCallHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument);
         this->MetalMockThrowExceptionIfExceptionSet();
      }

      FunctionSequencingToken CalledOnceWith(
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument,
         const Arg5Type& expectedFifthArgument,
         const Arg6Type& expectedSixthArgument)
      {
         this->MetalMockSetAsserted();
         const size_t expectedNumberOfCallsToMetalMockedFunction = 1;
         ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, this->metalMockedFunctionCallHistory[0].firstArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, this->metalMockedFunctionCallHistory[0].secondArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, this->metalMockedFunctionCallHistory[0].thirdArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, this->metalMockedFunctionCallHistory[0].fourthArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedFifthArgument, this->metalMockedFunctionCallHistory[0].fifthArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedSixthArgument, this->metalMockedFunctionCallHistory[0].sixthArgument.value, this->MetalMockedFunctionSignature);
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledNTimesWith(
         size_t expectedNumberOfCallsToMetalMockedFunction,
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument,
         const Arg5Type& expectedFifthArgument,
         const Arg6Type& expectedSixthArgument)
      {
         this->MetalMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCallsToMetalMockedFunction);
         this->MetalMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCallsToMetalMockedFunction; ++i)
         {
            const std::string metalMockedFunctionSignatureAndCallIndex = ZenUnit::String::Concat(this->MetalMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, this->metalMockedFunctionCallHistory[i].firstArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, this->metalMockedFunctionCallHistory[i].secondArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, this->metalMockedFunctionCallHistory[i].thirdArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, this->metalMockedFunctionCallHistory[i].fourthArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFifthArgument, this->metalMockedFunctionCallHistory[i].fifthArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSixthArgument, this->metalMockedFunctionCallHistory[i].sixthArgument.value, metalMockedFunctionSignatureAndCallIndex);
         }
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(
         const std::vector<SixArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>& expectedSixArgumentFunctionCalls)
      {
         this->MetalMockThrowIfExpectedCallsSizeIsZero(expectedSixArgumentFunctionCalls.size());
         this->MetalMockSetAsserted();
         const std::vector<SixArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>> actualSixArgumentFunctionCalls =
            MetalMocker<MockableExceptionThrowerType>::template ConvertMetalMockFunctionCallsToMetalMockFunctionCallReferences<
               SixArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>,
               SixArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>(this->metalMockedFunctionCallHistory);
         VECTORS_ARE_EQUAL(expectedSixArgumentFunctionCalls, actualSixArgumentFunctionCalls, this->MetalMockedFunctionSignature);
         return FunctionSequencingToken();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   class NonVoidSixArgumentMetalMocker : public SixArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>, protected ValueReturner<FunctionReturnType>
   {
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   public:
      explicit NonVoidSixArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : SixArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>(metalMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(metalMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         SixArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         SixArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         SixArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         SixArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>::_wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::MetalMockAddRandomReturnValue();
         return randomReturnValue;
      }

      FunctionReturnType MetalMockItAndReturnValue(
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument)
      {
         SixArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, MetalMockExceptionThrower>::MetalMockIt(
            firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument);
         const FunctionReturnType& returnValue = ValueReturner<FunctionReturnType>::MetalMockNextReturnValue();
         return returnValue;
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   class NonVoidSixArgFunctionPointerMetalMocker : public NonVoidSixArgumentMetalMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>
   {
   public:
      explicit NonVoidSixArgFunctionPointerMetalMocker(const std::string& metalMockedFunctionSignature)
         : NonVoidSixArgumentMetalMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>(metalMockedFunctionSignature)
      {
      }

      static FunctionReturnType MetalMockItFunctionPointer(
         NonVoidSixArgFunctionPointerMetalMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>* functionMocker,
         Arg1Type firstArgument,
         Arg2Type secondArgument,
         Arg3Type thirdArgument,
         Arg4Type fourthArgument,
         Arg5Type fifthArgument,
         Arg6Type sixthArgument)
      {
         const FunctionReturnType& returnValue = functionMocker->MetalMockItAndReturnValue(
            firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument);
         return returnValue;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   class VoidSixArgumentMetalMocker : public SixArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>
   {
   public:
      explicit VoidSixArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : SixArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>(metalMockedFunctionSignature)
      {
      }

      void Expect()
      {
         SixArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>::_wasExpected = true;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   class VoidSixArgFunctionPointerMetalMocker : public VoidSixArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>
   {
   public:
      explicit VoidSixArgFunctionPointerMetalMocker(const std::string& metalMockedFunctionSignature)
         : VoidSixArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>(metalMockedFunctionSignature)
      {
      }

      static void MetalMockItFunctionPointer(
         VoidSixArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument)
      {
         functionMocker->MetalMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument);
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
      typename MockableExceptionThrowerType = MetalMockExceptionThrower>
   class SevenArgumentMetalMocker : public MetalMocker<MockableExceptionThrowerType>
   {
      friend class SevenArgumentMetalMockerTests;
   public:
      std::vector<SevenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>> metalMockedFunctionCallHistory;

      explicit SevenArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : MetalMocker<MockableExceptionThrowerType>(metalMockedFunctionSignature)
      {
      }

      void MetalMockIt(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument,
         const Arg6Type& sixthArgument,
         const Arg7Type& seventhArgument)
      {
         this->MetalMockThrowIfNotExpected(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument);
         metalMockedFunctionCallHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument);
         this->MetalMockThrowExceptionIfExceptionSet();
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
         this->MetalMockSetAsserted();
         const size_t expectedNumberOfCallsToMetalMockedFunction = 1;
         ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, this->metalMockedFunctionCallHistory[0].firstArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, this->metalMockedFunctionCallHistory[0].secondArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, this->metalMockedFunctionCallHistory[0].thirdArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, this->metalMockedFunctionCallHistory[0].fourthArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedFifthArgument, this->metalMockedFunctionCallHistory[0].fifthArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedSixthArgument, this->metalMockedFunctionCallHistory[0].sixthArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedSeventhArgument, this->metalMockedFunctionCallHistory[0].seventhArgument.value, this->MetalMockedFunctionSignature);
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledNTimesWith(
         size_t expectedNumberOfCallsToMetalMockedFunction,
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument,
         const Arg5Type& expectedFifthArgument,
         const Arg6Type& expectedSixthArgument,
         const Arg7Type& expectedSeventhArgument)
      {
         this->MetalMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCallsToMetalMockedFunction);
         this->MetalMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCallsToMetalMockedFunction; ++i)
         {
            const std::string metalMockedFunctionSignatureAndCallIndex = ZenUnit::String::Concat(this->MetalMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, this->metalMockedFunctionCallHistory[i].firstArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, this->metalMockedFunctionCallHistory[i].secondArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, this->metalMockedFunctionCallHistory[i].thirdArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, this->metalMockedFunctionCallHistory[i].fourthArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFifthArgument, this->metalMockedFunctionCallHistory[i].fifthArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSixthArgument, this->metalMockedFunctionCallHistory[i].sixthArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSeventhArgument, this->metalMockedFunctionCallHistory[i].seventhArgument.value, metalMockedFunctionSignatureAndCallIndex);
         }
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(
         const std::vector<SevenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>& expectedSevenArgumentFunctionCalls)
      {
         this->MetalMockThrowIfExpectedCallsSizeIsZero(expectedSevenArgumentFunctionCalls.size());
         this->MetalMockSetAsserted();
         const std::vector<SevenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>> actualSevenArgumentFunctionCalls =
            MetalMocker<MockableExceptionThrowerType>::template ConvertMetalMockFunctionCallsToMetalMockFunctionCallReferences<
               SevenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>,
               SevenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>(this->metalMockedFunctionCallHistory);
         VECTORS_ARE_EQUAL(expectedSevenArgumentFunctionCalls, actualSevenArgumentFunctionCalls, this->MetalMockedFunctionSignature);
         return FunctionSequencingToken();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   class NonVoidSevenArgumentMetalMocker : public SevenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, MetalMockExceptionThrower>, protected ValueReturner<FunctionReturnType>
   {
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   public:
      explicit NonVoidSevenArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : SevenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>(metalMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(metalMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         SevenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, MetalMockExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         SevenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, MetalMockExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         SevenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, MetalMockExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         SevenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, MetalMockExceptionThrower>::_wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::MetalMockAddRandomReturnValue();
         return randomReturnValue;
      }

      FunctionReturnType MetalMockItAndReturnValue(
         Arg1Type firstArgument,
         Arg2Type secondArgument,
         Arg3Type thirdArgument,
         Arg4Type fourthArgument,
         Arg5Type fifthArgument,
         Arg6Type sixthArgument,
         Arg7Type seventhArgument)
      {
         SevenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>::MetalMockIt(
            firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument);
         const FunctionReturnType& returnValue = ValueReturner<FunctionReturnType>::MetalMockNextReturnValue();
         return returnValue;
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   class NonVoidSevenArgFunctionPointerMetalMocker : public NonVoidSevenArgumentMetalMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>
   {
   public:
      explicit NonVoidSevenArgFunctionPointerMetalMocker(const std::string& metalMockedFunctionSignature)
         : NonVoidSevenArgumentMetalMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>(metalMockedFunctionSignature)
      {
      }

      static FunctionReturnType MetalMockItFunctionPointer(
         NonVoidSevenArgFunctionPointerMetalMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>* functionMocker,
         Arg1Type firstArgument,
         Arg2Type secondArgument,
         Arg3Type thirdArgument,
         Arg4Type fourthArgument,
         Arg5Type fifthArgument,
         Arg6Type sixthArgument,
         Arg7Type seventhArgument)
      {
         const FunctionReturnType& returnValue = functionMocker->MetalMockItAndReturnValue(
            firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument);
         return returnValue;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   class VoidSevenArgumentMetalMocker : public SevenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, MetalMockExceptionThrower>
   {
   public:
      explicit VoidSevenArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : SevenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>(metalMockedFunctionSignature)
      {
      }

      void Expect()
      {
         SevenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, MetalMockExceptionThrower>::_wasExpected = true;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   class VoidSevenArgFunctionPointerMetalMocker : public VoidSevenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>
   {
   public:
      explicit VoidSevenArgFunctionPointerMetalMocker(const std::string& metalMockedFunctionSignature)
         : VoidSevenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>(metalMockedFunctionSignature)
      {
      }

      static void MetalMockItFunctionPointer(
         VoidSevenArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument)
      {
         functionMocker->MetalMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument);
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
      typename MockableExceptionThrowerType = MetalMockExceptionThrower>
   class EightArgumentMetalMocker : public MetalMocker<MockableExceptionThrowerType>
   {
      friend class EightArgumentMetalMockerTests;
   public:
      std::vector<EightArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>> metalMockedFunctionCallHistory;

      explicit EightArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : MetalMocker<MockableExceptionThrowerType>(metalMockedFunctionSignature)
      {
      }

      void MetalMockIt(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument,
         const Arg6Type& sixthArgument,
         const Arg7Type& seventhArgument,
         const Arg8Type& eigthArgument)
      {
         this->MetalMockThrowIfNotExpected(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument);
         metalMockedFunctionCallHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument);
         this->MetalMockThrowExceptionIfExceptionSet();
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
         this->MetalMockSetAsserted();
         const size_t expectedNumberOfCallsToMetalMockedFunction = 1;
         ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, this->metalMockedFunctionCallHistory[0].firstArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, this->metalMockedFunctionCallHistory[0].secondArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, this->metalMockedFunctionCallHistory[0].thirdArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, this->metalMockedFunctionCallHistory[0].fourthArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedFifthArgument, this->metalMockedFunctionCallHistory[0].fifthArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedSixthArgument, this->metalMockedFunctionCallHistory[0].sixthArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedSeventhArgument, this->metalMockedFunctionCallHistory[0].seventhArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedEigthArgument, this->metalMockedFunctionCallHistory[0].eigthArgument.value, this->MetalMockedFunctionSignature);
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledNTimesWith(
         size_t expectedNumberOfCallsToMetalMockedFunction,
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument,
         const Arg5Type& expectedFifthArgument,
         const Arg6Type& expectedSixthArgument,
         const Arg7Type& expectedSeventhArgument,
         const Arg8Type& expectedEigthArgument)
      {
         this->MetalMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCallsToMetalMockedFunction);
         this->MetalMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCallsToMetalMockedFunction; ++i)
         {
            const std::string metalMockedFunctionSignatureAndCallIndex = ZenUnit::String::Concat(this->MetalMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, this->metalMockedFunctionCallHistory[i].firstArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, this->metalMockedFunctionCallHistory[i].secondArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, this->metalMockedFunctionCallHistory[i].thirdArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, this->metalMockedFunctionCallHistory[i].fourthArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFifthArgument, this->metalMockedFunctionCallHistory[i].fifthArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSixthArgument, this->metalMockedFunctionCallHistory[i].sixthArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSeventhArgument, this->metalMockedFunctionCallHistory[i].seventhArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedEigthArgument, this->metalMockedFunctionCallHistory[i].eigthArgument.value, metalMockedFunctionSignatureAndCallIndex);
         }
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(
         const std::vector<EightArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>>& expectedEightArgumentFunctionCalls)
      {
         this->MetalMockThrowIfExpectedCallsSizeIsZero(expectedEightArgumentFunctionCalls.size());
         this->MetalMockSetAsserted();
         const std::vector<EightArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>> actualEightArgumentFunctionCalls =
            MetalMocker<MockableExceptionThrowerType>::template ConvertMetalMockFunctionCallsToMetalMockFunctionCallReferences<
               EightArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>,
               EightArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>>(this->metalMockedFunctionCallHistory);
         VECTORS_ARE_EQUAL(expectedEightArgumentFunctionCalls, actualEightArgumentFunctionCalls, this->MetalMockedFunctionSignature);
         return FunctionSequencingToken();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
   class NonVoidEightArgumentMetalMocker : public EightArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, MetalMockExceptionThrower>, protected ValueReturner<FunctionReturnType>
   {
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   public:
      explicit NonVoidEightArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : EightArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>(metalMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(metalMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         EightArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, MetalMockExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         EightArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, MetalMockExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         EightArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, MetalMockExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         EightArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, MetalMockExceptionThrower>::_wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::MetalMockAddRandomReturnValue();
         return randomReturnValue;
      }

      FunctionReturnType MetalMockItAndReturnValue(
         Arg1Type firstArgument,
         Arg2Type secondArgument,
         Arg3Type thirdArgument,
         Arg4Type fourthArgument,
         Arg5Type fifthArgument,
         Arg6Type sixthArgument,
         Arg7Type seventhArgument,
         Arg8Type eigthArgument)
      {
         EightArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>::MetalMockIt(
            firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument);
         const FunctionReturnType& returnValue = ValueReturner<FunctionReturnType>::MetalMockNextReturnValue();
         return returnValue;
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
   class NonVoidEightArgFunctionPointerMetalMocker : public NonVoidEightArgumentMetalMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>
   {
   public:
      explicit NonVoidEightArgFunctionPointerMetalMocker(const std::string& metalMockedFunctionSignature)
         : NonVoidEightArgumentMetalMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>(metalMockedFunctionSignature)
      {
      }

      static FunctionReturnType MetalMockItFunctionPointer(
         NonVoidEightArgFunctionPointerMetalMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>* functionMocker,
         Arg1Type firstArgument,
         Arg2Type secondArgument,
         Arg3Type thirdArgument,
         Arg4Type fourthArgument,
         Arg5Type fifthArgument,
         Arg6Type sixthArgument,
         Arg7Type seventhArgument,
         Arg8Type eigthArgument)
      {
         const FunctionReturnType& returnValue = functionMocker->MetalMockItAndReturnValue(
            firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument);
         return returnValue;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
   class VoidEightArgumentMetalMocker : public EightArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, MetalMockExceptionThrower>
   {
   public:
      explicit VoidEightArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : EightArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>(metalMockedFunctionSignature)
      {
      }

      void Expect()
      {
         EightArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, MetalMockExceptionThrower>::_wasExpected = true;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
   class VoidEightArgFunctionPointerMetalMocker : public VoidEightArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>
   {
   public:
      explicit VoidEightArgFunctionPointerMetalMocker(const std::string& metalMockedFunctionSignature)
         : VoidEightArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>(metalMockedFunctionSignature)
      {
      }

      static void MetalMockItFunctionPointer(
         VoidEightArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument)
      {
         functionMocker->MetalMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument);
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
      typename MockableExceptionThrowerType = MetalMockExceptionThrower>
   class NineArgumentMetalMocker : public MetalMocker<MockableExceptionThrowerType>
   {
      friend class NineArgumentMetalMockerTests;
   public:
      std::vector<NineArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>> metalMockedFunctionCallHistory;

      explicit NineArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : MetalMocker<MockableExceptionThrowerType>(metalMockedFunctionSignature)
      {
      }

      void MetalMockIt(
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
         this->MetalMockThrowIfNotExpected(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument);
         metalMockedFunctionCallHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument);
         this->MetalMockThrowExceptionIfExceptionSet();
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
         this->MetalMockSetAsserted();
         const size_t expectedNumberOfCallsToMetalMockedFunction = 1;
         ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, this->metalMockedFunctionCallHistory[0].firstArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, this->metalMockedFunctionCallHistory[0].secondArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, this->metalMockedFunctionCallHistory[0].thirdArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, this->metalMockedFunctionCallHistory[0].fourthArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedFifthArgument, this->metalMockedFunctionCallHistory[0].fifthArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedSixthArgument, this->metalMockedFunctionCallHistory[0].sixthArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedSeventhArgument, this->metalMockedFunctionCallHistory[0].seventhArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedEigthArgument, this->metalMockedFunctionCallHistory[0].eigthArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedNinthArgument, this->metalMockedFunctionCallHistory[0].ninthArgument.value, this->MetalMockedFunctionSignature);
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledNTimesWith(
         size_t expectedNumberOfCallsToMetalMockedFunction,
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
         this->MetalMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCallsToMetalMockedFunction);
         this->MetalMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCallsToMetalMockedFunction; ++i)
         {
            const std::string metalMockedFunctionSignatureAndCallIndex = ZenUnit::String::Concat(this->MetalMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, this->metalMockedFunctionCallHistory[i].firstArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, this->metalMockedFunctionCallHistory[i].secondArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, this->metalMockedFunctionCallHistory[i].thirdArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, this->metalMockedFunctionCallHistory[i].fourthArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFifthArgument, this->metalMockedFunctionCallHistory[i].fifthArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSixthArgument, this->metalMockedFunctionCallHistory[i].sixthArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSeventhArgument, this->metalMockedFunctionCallHistory[i].seventhArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedEigthArgument, this->metalMockedFunctionCallHistory[i].eigthArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedNinthArgument, this->metalMockedFunctionCallHistory[i].ninthArgument.value, metalMockedFunctionSignatureAndCallIndex);
         }
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(
         const std::vector<NineArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>& expectedNineArgumentFunctionCalls)
      {
         this->MetalMockThrowIfExpectedCallsSizeIsZero(expectedNineArgumentFunctionCalls.size());
         this->MetalMockSetAsserted();
         const std::vector<NineArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>> actualNineArgumentFunctionCalls =
            MetalMocker<MockableExceptionThrowerType>::template ConvertMetalMockFunctionCallsToMetalMockFunctionCallReferences<
               NineArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>,
               NineArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>(this->metalMockedFunctionCallHistory);
         VECTORS_ARE_EQUAL(expectedNineArgumentFunctionCalls, actualNineArgumentFunctionCalls, this->MetalMockedFunctionSignature);
         return FunctionSequencingToken();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
   class NonVoidNineArgumentMetalMocker : public NineArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, MetalMockExceptionThrower>, protected ValueReturner<FunctionReturnType>
   {
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   public:
      explicit NonVoidNineArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : NineArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>(metalMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(metalMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         NineArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, MetalMockExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         NineArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, MetalMockExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         NineArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, MetalMockExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         NineArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, MetalMockExceptionThrower>::_wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::MetalMockAddRandomReturnValue();
         return randomReturnValue;
      }

      FunctionReturnType MetalMockItAndReturnValue(
         Arg1Type firstArgument,
         Arg2Type secondArgument,
         Arg3Type thirdArgument,
         Arg4Type fourthArgument,
         Arg5Type fifthArgument,
         Arg6Type sixthArgument,
         Arg7Type seventhArgument,
         Arg8Type eigthArgument,
         Arg9Type ninthArgument)
      {
         NineArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>::MetalMockIt(
            firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument);
         const FunctionReturnType& returnValue = ValueReturner<FunctionReturnType>::MetalMockNextReturnValue();
         return returnValue;
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
   class NonVoidNineArgFunctionPointerMetalMocker : public NonVoidNineArgumentMetalMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>
   {
   public:
      explicit NonVoidNineArgFunctionPointerMetalMocker(const std::string& metalMockedFunctionSignature)
         : NonVoidNineArgumentMetalMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>(metalMockedFunctionSignature)
      {
      }

      static FunctionReturnType MetalMockItFunctionPointer(
         NonVoidNineArgFunctionPointerMetalMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>* functionMocker,
         Arg1Type firstArgument,
         Arg2Type secondArgument,
         Arg3Type thirdArgument,
         Arg4Type fourthArgument,
         Arg5Type fifthArgument,
         Arg6Type sixthArgument,
         Arg7Type seventhArgument,
         Arg8Type eigthArgument,
         Arg9Type ninthArgument)
      {
         const FunctionReturnType& returnValue = functionMocker->MetalMockItAndReturnValue(
            firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument);
         return returnValue;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
   class VoidNineArgumentMetalMocker : public NineArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, MetalMockExceptionThrower>
   {
   public:
      explicit VoidNineArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : NineArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>(metalMockedFunctionSignature)
      {
      }

      void Expect()
      {
         NineArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, MetalMockExceptionThrower>::_wasExpected = true;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
   class VoidNineArgFunctionPointerMetalMocker : public VoidNineArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>
   {
   public:
      explicit VoidNineArgFunctionPointerMetalMocker(const std::string& metalMockedFunctionSignature)
         : VoidNineArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>(metalMockedFunctionSignature)
      {
      }

      static void MetalMockItFunctionPointer(
         VoidNineArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>* functionMocker,
         Arg1Type firstArgument,
         Arg2Type secondArgument,
         Arg3Type thirdArgument,
         Arg4Type fourthArgument,
         Arg5Type fifthArgument,
         Arg6Type sixthArgument,
         Arg7Type seventhArgument,
         Arg8Type eigthArgument,
         Arg9Type ninthArgument)
      {
         functionMocker->MetalMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument);
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
      typename MockableExceptionThrowerType = MetalMockExceptionThrower>
   class TenArgumentMetalMocker : public MetalMocker<MockableExceptionThrowerType>
   {
      friend class TenArgumentMetalMockerTests;
   public:
      std::vector<TenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>> metalMockedFunctionCallHistory;

      explicit TenArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : MetalMocker<MockableExceptionThrowerType>(metalMockedFunctionSignature)
      {
      }

      void MetalMockIt(
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
         this->MetalMockThrowIfNotExpected(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument, tenthArgument);
         metalMockedFunctionCallHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument, tenthArgument);
         this->MetalMockThrowExceptionIfExceptionSet();
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
         this->MetalMockSetAsserted();
         const size_t expectedNumberOfCallsToMetalMockedFunction = 1;
         ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, this->metalMockedFunctionCallHistory[0].firstArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, this->metalMockedFunctionCallHistory[0].secondArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, this->metalMockedFunctionCallHistory[0].thirdArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, this->metalMockedFunctionCallHistory[0].fourthArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedFifthArgument, this->metalMockedFunctionCallHistory[0].fifthArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedSixthArgument, this->metalMockedFunctionCallHistory[0].sixthArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedSeventhArgument, this->metalMockedFunctionCallHistory[0].seventhArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedEigthArgument, this->metalMockedFunctionCallHistory[0].eigthArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedNinthArgument, this->metalMockedFunctionCallHistory[0].ninthArgument.value, this->MetalMockedFunctionSignature);
         ARE_EQUAL(expectedTenthArgument, this->metalMockedFunctionCallHistory[0].tenthArgument.value, this->MetalMockedFunctionSignature);
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledNTimesWith(
         size_t expectedNumberOfCallsToMetalMockedFunction,
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
         this->MetalMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCallsToMetalMockedFunction);
         this->MetalMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCallsToMetalMockedFunction; ++i)
         {
            const std::string metalMockedFunctionSignatureAndCallIndex = ZenUnit::String::Concat(this->MetalMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, this->metalMockedFunctionCallHistory[i].firstArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, this->metalMockedFunctionCallHistory[i].secondArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, this->metalMockedFunctionCallHistory[i].thirdArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, this->metalMockedFunctionCallHistory[i].fourthArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFifthArgument, this->metalMockedFunctionCallHistory[i].fifthArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSixthArgument, this->metalMockedFunctionCallHistory[i].sixthArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSeventhArgument, this->metalMockedFunctionCallHistory[i].seventhArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedEigthArgument, this->metalMockedFunctionCallHistory[i].eigthArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedNinthArgument, this->metalMockedFunctionCallHistory[i].ninthArgument.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedTenthArgument, this->metalMockedFunctionCallHistory[i].tenthArgument.value, metalMockedFunctionSignatureAndCallIndex);
         }
         return FunctionSequencingToken();
      }

      FunctionSequencingToken CalledAsFollows(
         const std::vector<TenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>& expectedTenArgumentFunctionCalls)
      {
         this->MetalMockThrowIfExpectedCallsSizeIsZero(expectedTenArgumentFunctionCalls.size());
         this->MetalMockSetAsserted();
         const std::vector<TenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>> actualTenArgumentFunctionCalls =
            MetalMocker<MockableExceptionThrowerType>::template ConvertMetalMockFunctionCallsToMetalMockFunctionCallReferences<
               TenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>,
               TenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>(this->metalMockedFunctionCallHistory);
         VECTORS_ARE_EQUAL(expectedTenArgumentFunctionCalls, actualTenArgumentFunctionCalls, this->MetalMockedFunctionSignature);
         return FunctionSequencingToken();
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
   class NonVoidTenArgumentMetalMocker : public TenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, MetalMockExceptionThrower>, protected ValueReturner<FunctionReturnType>
   {
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   public:
      explicit NonVoidTenArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : TenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(metalMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(metalMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         TenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, MetalMockExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         TenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, MetalMockExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         TenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, MetalMockExceptionThrower>::_wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         TenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, MetalMockExceptionThrower>::_wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::MetalMockAddRandomReturnValue();
         return randomReturnValue;
      }

      FunctionReturnType MetalMockItAndReturnValue(
         Arg1Type firstArgument,
         Arg2Type secondArgument,
         Arg3Type thirdArgument,
         Arg4Type fourthArgument,
         Arg5Type fifthArgument,
         Arg6Type sixthArgument,
         Arg7Type seventhArgument,
         Arg8Type eigthArgument,
         Arg9Type ninthArgument,
         Arg10Type tenthArgument)
      {
         TenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>::MetalMockIt(
            firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument, tenthArgument);
         const FunctionReturnType& returnValue = ValueReturner<FunctionReturnType>::MetalMockNextReturnValue();
         return returnValue;
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
   class NonVoidTenArgFunctionPointerMetalMocker : public NonVoidTenArgumentMetalMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>
   {
   public:
      explicit NonVoidTenArgFunctionPointerMetalMocker(const std::string& metalMockedFunctionSignature)
         : NonVoidTenArgumentMetalMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(metalMockedFunctionSignature) {}

      static FunctionReturnType MetalMockItFunctionPointer(
         NonVoidTenArgFunctionPointerMetalMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>* functionMocker,
         Arg1Type firstArgument,
         Arg2Type secondArgument,
         Arg3Type thirdArgument,
         Arg4Type fourthArgument,
         Arg5Type fifthArgument,
         Arg6Type sixthArgument,
         Arg7Type seventhArgument,
         Arg8Type eigthArgument,
         Arg9Type ninthArgument,
         Arg10Type tenthArgument)
      {
         const FunctionReturnType& returnValue = functionMocker->MetalMockItAndReturnValue(
            firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument, tenthArgument);
         return returnValue;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
   class VoidTenArgumentMetalMocker : public TenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, MetalMockExceptionThrower>
   {
   public:
      explicit VoidTenArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : TenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(metalMockedFunctionSignature) {}

      void Expect()
      {
         TenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, MetalMockExceptionThrower>::_wasExpected = true;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
   class VoidTenArgFunctionPointerMetalMocker : public VoidTenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>
   {
   public:
      explicit VoidTenArgFunctionPointerMetalMocker(const std::string& metalMockedFunctionSignature)
         : VoidTenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(metalMockedFunctionSignature) {}

      static void MetalMockItFunctionPointer(
         VoidTenArgFunctionPointerMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>* functionMocker,
         Arg1Type firstArgument,
         Arg2Type secondArgument,
         Arg3Type thirdArgument,
         Arg4Type fourthArgument,
         Arg5Type fifthArgument,
         Arg6Type sixthArgument,
         Arg7Type seventhArgument,
         Arg8Type eigthArgument,
         Arg9Type ninthArgument,
         Arg10Type tenthArgument)
      {
         functionMocker->MetalMockIt(
            firstArgument,
            secondArgument,
            thirdArgument,
            fourthArgument,
            fifthArgument,
            sixthArgument,
            seventhArgument,
            eigthArgument,
            ninthArgument,
            tenthArgument);
      }
   };

   class FunctionSignature
   {
   public:
      static std::string Function(
         const char* virtualOrEmptyString,
         const char* returnType,
         const std::string* metalMockedClassName,
         //   Adorned function signature: "virtual int FunctionName(int) const"
         // Unadorned function signature: "FunctionName(int)"
         const char* unadornedFunctionSignature,
         const char* constOrEmptyString)
      {
         std::ostringstream builder;
         const size_t virtualOrEmptyStringLength = strlen(virtualOrEmptyString);
         if (virtualOrEmptyStringLength > 0)
         {
            builder << virtualOrEmptyString << ' ';
         }
         builder << returnType << ' ' << *metalMockedClassName << "::" << unadornedFunctionSignature;
         const size_t constOrEmptyStringLength = strlen(constOrEmptyString);
         if (constOrEmptyStringLength > 0)
         {
            builder << ' ' << constOrEmptyString;
         }
         const std::string metalMockedFunctionSignature = builder.str();
         return metalMockedFunctionSignature;
      }

      static std::string FunctionPointer(const char* returnType, const char* unadornedFunctionSignature)
      {
         const std::string metalMockedFunctionPointerSignature = ZenUnit::String::Concat(returnType, ' ', unadornedFunctionSignature);
         return metalMockedFunctionPointerSignature;
      }
   };
}

namespace ZenUnit
{
   template<typename ArgType>
   class Equalizer<MetalMock::OneArgumentFunctionCall<ArgType>>
   {
   public:
      static void AssertEqual(
         const MetalMock::OneArgumentFunctionCall<ArgType>& expectedOneArgumentFunctionCall,
         const MetalMock::OneArgumentFunctionCall<ArgType>& actualOneArgumentFunctionCall)
      {
         ARE_EQUAL(expectedOneArgumentFunctionCall.argument.value, actualOneArgumentFunctionCall.argument.value);
      }
   };

   template<typename ArgType>
   class Equalizer<MetalMock::OneArgumentFunctionCallReference<ArgType>>
   {
   public:
      static void AssertEqual(
         const MetalMock::OneArgumentFunctionCallReference<ArgType>& expectedOneArgumentFunctionCall,
         const MetalMock::OneArgumentFunctionCallReference<ArgType>& actualOneArgumentFunctionCall)
      {
         ARE_EQUAL(expectedOneArgumentFunctionCall.argumentReference.value, actualOneArgumentFunctionCall.argumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type>
   class Equalizer<MetalMock::TwoArgumentFunctionCall<Arg1Type, Arg2Type>>
   {
   public:
      static void AssertEqual(
         const MetalMock::TwoArgumentFunctionCall<Arg1Type, Arg2Type>& expectedTwoArgumentFunctionCall,
         const MetalMock::TwoArgumentFunctionCall<Arg1Type, Arg2Type>& actualTwoArgumentFunctionCall)
      {
         ARE_EQUAL(expectedTwoArgumentFunctionCall.firstArgument.value, actualTwoArgumentFunctionCall.firstArgument.value);
         ARE_EQUAL(expectedTwoArgumentFunctionCall.secondArgument.value, actualTwoArgumentFunctionCall.secondArgument.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type>
   class Equalizer<MetalMock::TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>>
   {
   public:
      static void AssertEqual(
         const MetalMock::TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>& expectedTwoArgumentFunctionCall,
         const MetalMock::TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>& actualTwoArgumentFunctionCall)
      {
         ARE_EQUAL(expectedTwoArgumentFunctionCall.firstArgumentReference.value, actualTwoArgumentFunctionCall.firstArgumentReference.value);
         ARE_EQUAL(expectedTwoArgumentFunctionCall.secondArgumentReference.value, actualTwoArgumentFunctionCall.secondArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class Equalizer<MetalMock::ThreeArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type>>
   {
   public:
      static void AssertEqual(
         const MetalMock::ThreeArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type>& expectedThreeArgumentFunctionCall,
         const MetalMock::ThreeArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type>& actualThreeArgumentFunctionCall)
      {
         ARE_EQUAL(expectedThreeArgumentFunctionCall.firstArgument.value, actualThreeArgumentFunctionCall.firstArgument.value);
         ARE_EQUAL(expectedThreeArgumentFunctionCall.secondArgument.value, actualThreeArgumentFunctionCall.secondArgument.value);
         ARE_EQUAL(expectedThreeArgumentFunctionCall.thirdArgument.value, actualThreeArgumentFunctionCall.thirdArgument.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class Equalizer<MetalMock::ThreeArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type>>
   {
   public:
      static void AssertEqual(
         const MetalMock::ThreeArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type>& expectedThreeArgumentFunctionCall,
         const MetalMock::ThreeArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type>& actualThreeArgumentFunctionCall)
      {
         ARE_EQUAL(expectedThreeArgumentFunctionCall.firstArgumentReference.value, actualThreeArgumentFunctionCall.firstArgumentReference.value);
         ARE_EQUAL(expectedThreeArgumentFunctionCall.secondArgumentReference.value, actualThreeArgumentFunctionCall.secondArgumentReference.value);
         ARE_EQUAL(expectedThreeArgumentFunctionCall.thirdArgumentReference.value, actualThreeArgumentFunctionCall.thirdArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class Equalizer<MetalMock::FourArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
   {
   public:
      static void AssertEqual(
         const MetalMock::FourArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& expectedFourArgumentFunctionCall,
         const MetalMock::FourArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& actualFourArgumentFunctionCall)
      {
         ARE_EQUAL(expectedFourArgumentFunctionCall.firstArgument.value, actualFourArgumentFunctionCall.firstArgument.value);
         ARE_EQUAL(expectedFourArgumentFunctionCall.secondArgument.value, actualFourArgumentFunctionCall.secondArgument.value);
         ARE_EQUAL(expectedFourArgumentFunctionCall.thirdArgument.value, actualFourArgumentFunctionCall.thirdArgument.value);
         ARE_EQUAL(expectedFourArgumentFunctionCall.fourthArgument.value, actualFourArgumentFunctionCall.fourthArgument.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class Equalizer<MetalMock::FourArgumentFunctionCallReference<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
   {
   public:
      static void AssertEqual(
         const MetalMock::FourArgumentFunctionCallReference<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& expectedFourArgumentFunctionCall,
         const MetalMock::FourArgumentFunctionCallReference<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& actualFourArgumentFunctionCall)
      {
         ARE_EQUAL(expectedFourArgumentFunctionCall.firstArgumentReference.value, actualFourArgumentFunctionCall.firstArgumentReference.value);
         ARE_EQUAL(expectedFourArgumentFunctionCall.secondArgumentReference.value, actualFourArgumentFunctionCall.secondArgumentReference.value);
         ARE_EQUAL(expectedFourArgumentFunctionCall.thirdArgumentReference.value, actualFourArgumentFunctionCall.thirdArgumentReference.value);
         ARE_EQUAL(expectedFourArgumentFunctionCall.fourthArgumentReference.value, actualFourArgumentFunctionCall.fourthArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   class Equalizer<MetalMock::FiveArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
   {
   public:
      static void AssertEqual(
         const MetalMock::FiveArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& expectedFiveArgumentFunctionCall,
         const MetalMock::FiveArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& actualFiveArgumentFunctionCall)
      {
         ARE_EQUAL(expectedFiveArgumentFunctionCall.firstArgument.value, actualFiveArgumentFunctionCall.firstArgument.value);
         ARE_EQUAL(expectedFiveArgumentFunctionCall.secondArgument.value, actualFiveArgumentFunctionCall.secondArgument.value);
         ARE_EQUAL(expectedFiveArgumentFunctionCall.thirdArgument.value, actualFiveArgumentFunctionCall.thirdArgument.value);
         ARE_EQUAL(expectedFiveArgumentFunctionCall.fourthArgument.value, actualFiveArgumentFunctionCall.fourthArgument.value);
         ARE_EQUAL(expectedFiveArgumentFunctionCall.fifthArgument.value, actualFiveArgumentFunctionCall.fifthArgument.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   class Equalizer<MetalMock::FiveArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
   {
   public:
      static void AssertEqual(
         const MetalMock::FiveArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& expectedFiveArgumentFunctionCall,
         const MetalMock::FiveArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& actualFiveArgumentFunctionCall)
      {
         ARE_EQUAL(expectedFiveArgumentFunctionCall.firstArgumentReference.value, actualFiveArgumentFunctionCall.firstArgumentReference.value);
         ARE_EQUAL(expectedFiveArgumentFunctionCall.secondArgumentReference.value, actualFiveArgumentFunctionCall.secondArgumentReference.value);
         ARE_EQUAL(expectedFiveArgumentFunctionCall.thirdArgumentReference.value, actualFiveArgumentFunctionCall.thirdArgumentReference.value);
         ARE_EQUAL(expectedFiveArgumentFunctionCall.fourthArgumentReference.value, actualFiveArgumentFunctionCall.fourthArgumentReference.value);
         ARE_EQUAL(expectedFiveArgumentFunctionCall.fifthArgumentReference.value, actualFiveArgumentFunctionCall.fifthArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   class Equalizer<MetalMock::SixArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
   {
   public:
      static void AssertEqual(
         const MetalMock::SixArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& expectedSixArgumentFunctionCall,
         const MetalMock::SixArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& actualSixArgumentFunctionCall)
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
   class Equalizer<MetalMock::SixArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
   {
   public:
      static void AssertEqual(
         const MetalMock::SixArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& expectedSixArgumentFunctionCall,
         const MetalMock::SixArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& actualSixArgumentFunctionCall)
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
   class Equalizer<MetalMock::SevenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
   {
   public:
      static void AssertEqual(
         const MetalMock::SevenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& expectedSevenArgumentFunctionCall,
         const MetalMock::SevenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& actualSevenArgumentFunctionCall)
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
   class Equalizer<MetalMock::SevenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
   {
   public:
      static void AssertEqual(
         const MetalMock::SevenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& expectedSevenArgumentFunctionCall,
         const MetalMock::SevenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& actualSevenArgumentFunctionCall)
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
   class Equalizer<MetalMock::EightArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
   {
   public:
      static void AssertEqual(
         const MetalMock::EightArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& expectedEightArgumentFunctionCall,
         const MetalMock::EightArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& actualEightArgumentFunctionCall)
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
   class Equalizer<MetalMock::EightArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
   {
   public:
      static void AssertEqual(
         const MetalMock::EightArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& expectedEightArgumentFunctionCall,
         const MetalMock::EightArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& actualEightArgumentFunctionCall)
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
   class Equalizer<MetalMock::NineArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
   {
   public:
      static void AssertEqual(
         const MetalMock::NineArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& expectedNineArgumentFunctionCall,
         const MetalMock::NineArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& actualNineArgumentFunctionCall)
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
   class Equalizer<MetalMock::NineArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
   {
   public:
      static void AssertEqual(
         const MetalMock::NineArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& expectedNineArgumentFunctionCall,
         const MetalMock::NineArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& actualNineArgumentFunctionCall)
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
   class Equalizer<MetalMock::TenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>
   {
   public:
      static void AssertEqual(
         const MetalMock::TenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& expectedTenArgumentFunctionCall,
         const MetalMock::TenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& actualTenArgumentFunctionCall)
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
   class Equalizer<MetalMock::TenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>
   {
   public:
      static void AssertEqual(
         const MetalMock::TenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& expectedTenArgumentFunctionCall,
         const MetalMock::TenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& actualTenArgumentFunctionCall)
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
   class Printer<MetalMock::OneArgumentFunctionCallReference<ArgType>>
   {
   public:
      static void Print(std::ostream& os, const MetalMock::OneArgumentFunctionCallReference<ArgType>& oneArgumentFunctionCall)
      {
         os << "MetalMock::OneArgumentFunctionCall:\n" <<
               "Argument: " << ZenUnit::ToStringer::ToString(oneArgumentFunctionCall.argumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type>
   class Printer<MetalMock::TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>>
   {
   public:
      static void Print(std::ostream& os, const MetalMock::TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>& twoArgumentFunctionCallRef)
      {
         os << "MetalMock::TwoArgumentFunctionCall:\n"
               "Argument1: " << ZenUnit::ToStringer::ToString(twoArgumentFunctionCallRef.firstArgumentReference.value) << '\n' <<
               "Argument2: " << ZenUnit::ToStringer::ToString(twoArgumentFunctionCallRef.secondArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class Printer<MetalMock::ThreeArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type>>
   {
   public:
      static void Print(std::ostream& os, const MetalMock::ThreeArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type>& threeArgumentFunctionCallRef)
      {
         os << "MetalMock::ThreeArgumentFunctionCall:\n"
               "Argument1: " << ZenUnit::ToStringer::ToString(threeArgumentFunctionCallRef.firstArgumentReference.value) << '\n' <<
               "Argument2: " << ZenUnit::ToStringer::ToString(threeArgumentFunctionCallRef.secondArgumentReference.value) << '\n' <<
               "Argument3: " << ZenUnit::ToStringer::ToString(threeArgumentFunctionCallRef.thirdArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class Printer<MetalMock::FourArgumentFunctionCallReference<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
   {
   public:
      static void Print(std::ostream& os, const MetalMock::FourArgumentFunctionCallReference<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& fourArgumentFunctionCallRef)
      {
         os << "MetalMock::FourArgumentFunctionCall:\n"
               "Argument1: " << ZenUnit::ToStringer::ToString(fourArgumentFunctionCallRef.firstArgumentReference.value) << '\n' <<
               "Argument2: " << ZenUnit::ToStringer::ToString(fourArgumentFunctionCallRef.secondArgumentReference.value) << '\n' <<
               "Argument3: " << ZenUnit::ToStringer::ToString(fourArgumentFunctionCallRef.thirdArgumentReference.value) << '\n' <<
               "Argument4: " << ZenUnit::ToStringer::ToString(fourArgumentFunctionCallRef.fourthArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   class Printer<MetalMock::FiveArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
   {
   public:
      static void Print(std::ostream& os, const MetalMock::FiveArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& fiveArgumentFunctionCallRef)
      {
         os << "MetalMock::FiveArgumentFunctionCall:\n"
               "Argument1: " << ZenUnit::ToStringer::ToString(fiveArgumentFunctionCallRef.firstArgumentReference.value) << '\n' <<
               "Argument2: " << ZenUnit::ToStringer::ToString(fiveArgumentFunctionCallRef.secondArgumentReference.value) << '\n' <<
               "Argument3: " << ZenUnit::ToStringer::ToString(fiveArgumentFunctionCallRef.thirdArgumentReference.value) << '\n' <<
               "Argument4: " << ZenUnit::ToStringer::ToString(fiveArgumentFunctionCallRef.fourthArgumentReference.value) << '\n' <<
               "Argument5: " << ZenUnit::ToStringer::ToString(fiveArgumentFunctionCallRef.fifthArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   class Printer<MetalMock::SixArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
   {
   public:
      static void Print(std::ostream& os, const MetalMock::SixArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& sixArgumentFunctionCallRef)
      {
         os << "MetalMock::SixArgumentFunctionCall:\n"
               "Argument1: " << ZenUnit::ToStringer::ToString(sixArgumentFunctionCallRef.firstArgumentReference.value) << '\n' <<
               "Argument2: " << ZenUnit::ToStringer::ToString(sixArgumentFunctionCallRef.secondArgumentReference.value) << '\n' <<
               "Argument3: " << ZenUnit::ToStringer::ToString(sixArgumentFunctionCallRef.thirdArgumentReference.value) << '\n' <<
               "Argument4: " << ZenUnit::ToStringer::ToString(sixArgumentFunctionCallRef.fourthArgumentReference.value) << '\n' <<
               "Argument5: " << ZenUnit::ToStringer::ToString(sixArgumentFunctionCallRef.fifthArgumentReference.value) << '\n' <<
               "Argument6: " << ZenUnit::ToStringer::ToString(sixArgumentFunctionCallRef.sixthArgumentReference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   class Printer<MetalMock::SevenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
   {
   public:
      static void Print(std::ostream& os, const MetalMock::SevenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& sevenArgumentFunctionCallRef)
      {
         os << "MetalMock::SevenArgumentFunctionCall:\n"
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
   class Printer<MetalMock::EightArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
   {
   public:
      static void Print(std::ostream& os, const MetalMock::EightArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& eightArgumentFunctionCallRef)
      {
         os << "MetalMock::EightArgumentFunctionCall:\n"
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
   class Printer<MetalMock::NineArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
   {
   public:
      static void Print(std::ostream& os, const MetalMock::NineArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& nineArgumentFunctionCallRef)
      {
         os << "MetalMock::NineArgumentFunctionCall:\n"
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
   class Printer<MetalMock::TenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>
   {
   public:
      static void Print(std::ostream& os, const MetalMock::TenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& tenArgumentFunctionCallRef)
      {
         os << "MetalMock::TenArgumentFunctionCall:\n"
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

template<typename Arg1Type, typename Arg2Type>
bool operator==(
   const MetalMock::TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>& expectedTwoArgumentFunctionCall,
   const MetalMock::TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>& actualTwoArgumentFunctionCall)
{
   try
   {
      ZenUnit::Equalizer<MetalMock::TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>>::AssertEqual(
         expectedTwoArgumentFunctionCall, actualTwoArgumentFunctionCall);
   }
   catch (const ZenUnit::Anomaly&)
   {
      return false;
   }
   return true;
}

namespace ZenUnit
{
   class RandomGeneratorMock : public Metal::Mock<ZenUnit::RandomGenerator>
   {
   public:
      METALMOCK_NONVOID0_CONST(bool, Bool)

      METALMOCK_NONVOID0_CONST(char, Char)
      METALMOCK_NONVOID0_CONST(unsigned char, UnsignedChar)

      METALMOCK_NONVOID0_CONST(short, Short)
      METALMOCK_NONVOID0_CONST(unsigned short, UnsignedShort)

      METALMOCK_NONVOID0_CONST(int, Int)
      METALMOCK_NONVOID0_CONST(unsigned int, UnsignedInt)

      METALMOCK_NONVOID1_CONST(int, Enum, int)

      METALMOCK_NONVOID0_CONST(long, Long)
      METALMOCK_NONVOID0_CONST(unsigned long, UnsignedLong)

      METALMOCK_NONVOID0_CONST(long long, LongLong)
      METALMOCK_NONVOID0_CONST(unsigned long long, UnsignedLongLong)
      METALMOCK_NONVOID0_CONST(size_t, SizeT)
      METALMOCK_NONVOID2_CONST(size_t, SizeTBetween, size_t, size_t)

      METALMOCK_NONVOID0_CONST(float, Float)
      METALMOCK_NONVOID0_CONST(std::vector<float>, FloatVector)

      METALMOCK_NONVOID0_CONST(double, Double)
      METALMOCK_NONVOID0_CONST(std::vector<double>, DoubleVector)

      METALMOCK_NONVOID0_CONST(const char*, ConstCharPointer)

      METALMOCK_NONVOID0_CONST(std::string, String)
      METALMOCK_NONVOID0_CONST(std::vector<std::string>, StringVector)

      METALMOCK_NONVOID0_CONST(std::error_code, ErrorCode)

      METALMOCK_NONVOID0_CONST(std::filesystem::path, FilesystemPath)
      METALMOCK_NONVOID0_CONST(std::vector<std::filesystem::path>, FilesystemPathVector)
   };

   template<typename KeyType, typename ValueType>
   class RandomMapGeneratorMock : public Metal::Mock<ZenUnit::RandomMapGenerator<KeyType, ValueType>>
   {
   public:
      using MapType = std::map<KeyType, ValueType>;
      METALMOCK_NONVOID0_CONST(MapType, Map)

      using UnorderedMapType = std::unordered_map<KeyType, ValueType>;
      METALMOCK_NONVOID0_CONST(UnorderedMapType, UnorderedMap)
   };
}

#endif
