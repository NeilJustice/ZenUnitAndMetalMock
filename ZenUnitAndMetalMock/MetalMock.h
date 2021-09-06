// C++ Mocking Framework MetalMock v0.11.0
// https://github.com/NeilJustice/ZenUnitAndMetalMock
// MIT License

#pragma once
#include "ZenUnitAndMetalMock/ZenUnit.h"
#include <atomic>
#include <deque>

namespace Metal
{
   // Inherit from Metal::Mock<T> to define a MetalMock class for type T.
   //
   // Example MetalMock class definition:
   //
   // class Widget
   // {
   // public:
   //    virtual ~Widget() = default;
   //    virtual void Foo() {}
   //    virtual int Add(int, int) { return 0; }
   // };
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

namespace MetalMock
{
   struct FunctionCallSequenceNumber;
}

template<typename MetalMockAssertionCall>
inline MetalMock::FunctionCallSequenceNumber MetalMockThen(
   MetalMockAssertionCall&& metalMockAssertStatement,
   const char* metalMockAssertStatementText,
   const ZenUnit::FilePathLineNumber& filePathLineNumber)
{
   try
   {
      MetalMock::FunctionCallSequenceNumber functionCallSequenceNumber = std::forward<MetalMockAssertionCall>(metalMockAssertStatement)();
      return functionCallSequenceNumber;
   }
   catch (const ZenUnit::Anomaly& metalMockWrappedAnomaly)
   {
      const std::string message = ZenUnit::String::ConcatStrings("METALMOCK(", metalMockAssertStatementText, ")");
      throw ZenUnit::Anomaly::METALMOCKWrapped(message, metalMockWrappedAnomaly, filePathLineNumber);
   }
}

// METALMOCK adds file path and line number information to potential MetalMock assertion failed error messages
#define METALMOCKTHEN(MetalMockAssertStatement) MetalMockThen([&]{ return (MetalMockAssertStatement); }, #MetalMockAssertStatement, ZENUNIT_FILELINE)

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
void FunctionName(Arg1Type arg1, Arg2Type arg2) Constness Finalness \
{ \
   FunctionName##Mock.MetalMockIt(arg1, arg2); \
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
ReturnType FunctionName(Arg1Type arg1, Arg2Type arg2) Constness Finalness \
{ \
   return FunctionName##Mock.MetalMockItAndReturnValue(arg1, arg2); \
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
void FunctionName(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3) Constness Finalness \
{ \
   FunctionName##Mock.MetalMockIt(arg1, arg2, arg3); \
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
ReturnType FunctionName(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3) Constness Finalness \
{ \
   return FunctionName##Mock.MetalMockItAndReturnValue(arg1, arg2, arg3); \
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
void FunctionName(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4) Constness Finalness \
{ \
   FunctionName##Mock.MetalMockIt(arg1, arg2, arg3, arg4); \
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
ReturnType FunctionName(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4) Constness Finalness \
{ \
   return FunctionName##Mock.MetalMockItAndReturnValue(arg1, arg2, arg3, arg4); \
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
void FunctionName(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4, Arg5Type arg5) Constness Finalness \
{ \
   FunctionName##Mock.MetalMockIt(arg1, arg2, arg3, arg4, arg5); \
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
ReturnType FunctionName(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4, Arg5Type arg5) Constness Finalness \
{ \
   return FunctionName##Mock.MetalMockItAndReturnValue(arg1, arg2, arg3, arg4, arg5); \
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
void FunctionName(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4, Arg5Type arg5, Arg6Type arg6) Constness Finalness \
{ \
   FunctionName##Mock.MetalMockIt(arg1, arg2, arg3, arg4, arg5, arg6); \
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
ReturnType FunctionName(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4, Arg5Type arg5, Arg6Type arg6) Constness Finalness \
{ \
   return FunctionName##Mock.MetalMockItAndReturnValue(arg1, arg2, arg3, arg4, arg5, arg6); \
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
void FunctionName(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4, Arg5Type arg5, Arg6Type arg6, Arg7Type arg7) Constness Finalness \
{ \
   FunctionName##Mock.MetalMockIt(arg1, arg2, arg3, arg4, arg5, arg6, arg7); \
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
ReturnType FunctionName(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4, Arg5Type arg5, Arg6Type arg6, Arg7Type arg7) Constness Finalness \
{ \
   return FunctionName##Mock.MetalMockItAndReturnValue(arg1, arg2, arg3, arg4, arg5, arg6, arg7); \
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

namespace MetalMock
{
   inline std::atomic<unsigned long long> _globalMetalMockedFunctionCallSequenceNumber;

   struct FunctionCallSequenceNumber
   {
      unsigned long long value;
      const std::string* metalMockedFunctionSignature;

      FunctionCallSequenceNumber()
         : value(_globalMetalMockedFunctionCallSequenceNumber++)
         , metalMockedFunctionSignature(nullptr)
      {
      }

      FunctionCallSequenceNumber Then(FunctionCallSequenceNumber expectedNextFunctionCallSequenceNumber) const
      {
         const std::string incorrectMetalMockedFunctionOrderErrorMessage = ZenUnit::String::ConcatStrings("Unexpected MetalMocked function call ordering:\n",
            "Expected function called first: ", *metalMockedFunctionSignature, "\n",
            "  Actual function called first: ", *expectedNextFunctionCallSequenceNumber.metalMockedFunctionSignature);
         const unsigned long long expectedFirstFunctionCallSequenceNumber = this->value;
         IS_LESS_THAN(expectedFirstFunctionCallSequenceNumber, expectedNextFunctionCallSequenceNumber.value, incorrectMetalMockedFunctionOrderErrorMessage);
         return expectedNextFunctionCallSequenceNumber;
      }
   };

   class UnexpectedCallException : public ZenUnit::MetalMockException
   {
   private:
      const std::string _exceptionMessage;
   public:
      template<typename... ArgTypes>
      explicit UnexpectedCallException(const std::string& metalMockedFunctionSignature, ArgTypes&&... args)
         : _exceptionMessage(MakeExceptionMessage(metalMockedFunctionSignature, std::forward<ArgTypes>(args)...))
      {
      }

      virtual ~UnexpectedCallException() = default;

      template<typename... ArgTypes>
      static std::string MakeExceptionMessage(const std::string& metalMockedFunctionSignature, ArgTypes&&... args)
      {
         std::ostringstream exceptionMessageBuilder;
         exceptionMessageBuilder << "Unexpected call to MetalMocked function:\n" << metalMockedFunctionSignature;
         AppendToStringedArgs(exceptionMessageBuilder, 0, std::forward<ArgTypes>(args)...);
         std::string exceptionMessage = exceptionMessageBuilder.str();
         return exceptionMessage;
      }

      const char* what() const noexcept override
      {
         return _exceptionMessage.c_str();
      }
   private:
      template<typename ArgType, typename... SubsequentArgTypes>
      static void AppendToStringedArgs(
         std::ostringstream& outExceptionMessageBuilder, size_t argIndex, ArgType&& arg, SubsequentArgTypes&&... args)
      {
         const std::string toStringedArg = ZenUnit::ToStringer::ToString(std::forward<ArgType>(arg));
         outExceptionMessageBuilder << "\nArgument" << ++argIndex << ": " << toStringedArg;
         AppendToStringedArgs(outExceptionMessageBuilder, argIndex, std::forward<SubsequentArgTypes>(args)...);
      }

      static void AppendToStringedArgs(std::ostringstream&, size_t)
      {
      }
   };

   class ReturnValueMustBeSpecifiedException : public ZenUnit::MetalMockException
   {
   private:
      const std::string _exceptionMessage;
   public:
      explicit ReturnValueMustBeSpecifiedException(const std::string& metalMockedFunctionSignature)
         : _exceptionMessage(MakeExceptionMessage(metalMockedFunctionSignature))
      {
      }

      virtual ~ReturnValueMustBeSpecifiedException() = default;

      const char* what() const noexcept override
      {
         return _exceptionMessage.c_str();
      }

      static std::string MakeExceptionMessage(std::string_view metalMockedFunctionSignature)
      {
         std::string exceptionMessage = ZenUnit::String::ConcatStrings(
"For MetalMocked function \"", metalMockedFunctionSignature, R"(":
MetalMocked functions with non-void return types must have their return value or values set explicitly by calling:
[FunctionName]Mock.[Return|ReturnValues]())");
         return exceptionMessage;
      }
   };

   class FunctionAssertedOneMoreTimeThanItWasCalledException : public ZenUnit::MetalMockException
   {
   private:
      const std::string _exceptionMessage;
   public:
      explicit FunctionAssertedOneMoreTimeThanItWasCalledException(
         const std::string& metalMockedFunctionSignature, size_t metalMockedFunctionCallCount)
         : _exceptionMessage(MakeExceptionMessage(metalMockedFunctionSignature, metalMockedFunctionCallCount))
      {
      }

      virtual ~FunctionAssertedOneMoreTimeThanItWasCalledException() = default;

      const char* what() const noexcept override
      {
         return _exceptionMessage.c_str();
      }

      static std::string MakeExceptionMessage(std::string_view metalMockedFunctionSignature, size_t metalMockedFunctionCallCount)
      {
         std::string exceptionMessage = ZenUnit::String::ConcatValues(
            "MetalMocked function \"", metalMockedFunctionSignature,
            "\" was asserted one more time than it was called. MetalMocked function call count = ", metalMockedFunctionCallCount);
         return exceptionMessage;
      }
   };

   class UnsupportedCalledZeroTimesException : public ZenUnit::MetalMockException
   {
   private:
      const std::string _exceptionMessage;
   public:
      explicit UnsupportedCalledZeroTimesException(const std::string& metalMockedFunctionSignature)
         : _exceptionMessage(MakeExceptionMessage(metalMockedFunctionSignature))
      {
      }

      virtual ~UnsupportedCalledZeroTimesException() = default;

      static std::string MakeExceptionMessage(const std::string& metalMockedFunctionSignature)
      {
         std::string exceptionMessage = ZenUnit::String::ConcatStrings(
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
         return _exceptionMessage.c_str();
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
         _returnValues.insert(_returnValues.end(), returnValues.cbegin(), returnValues.cend());
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
      size_t _functionCallAssertionIndex = 0;
      bool _metalMockExceptionIsInFlight = false;
   protected:
      // Mutable Components
      // Mockable template parameter instead of mockable unique_ptr for performance reasons
      MockableExceptionThrowerType _exceptionThrower;
      // Constant Fields
      const std::string metalMockedFunctionSignature;
      // Mutable Fields
      bool wasExpected = false;
      bool wasAsserted = false;
   public:
      MetalMocker()
      {
      }

      explicit MetalMocker(std::string_view metalMockedFunctionSignature)
         // Function Pointers
         : _call_exit(::exit)
         , _call_ZenUnitTestRunner_GetZenUnitArgs(ZenUnit::ZenUnitTestRunner::GetZenUnitArgs)
         // Constant Fields
         , metalMockedFunctionSignature(metalMockedFunctionSignature)
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
         this->wasExpected = true;
      }
   protected:
      void MetalMockThrowExceptionIfExceptionSet()
      {
         _exceptionThrower.MetalMockThrowExceptionIfExceptionSet();
      }

      template<typename... ArgTypes>
      void MetalMockThrowIfNotExpected(ArgTypes&&... args)
      {
         if (!this->wasExpected)
         {
            _metalMockExceptionIsInFlight = true;
            throw UnexpectedCallException(metalMockedFunctionSignature, std::forward<ArgTypes>(args)...);
         }
      }

      void MetalMockSetAsserted()
      {
         this->wasAsserted = true;
      }

      void MetalMockThrowIfExpectedNumberOfFunctionCalls0(size_t expectedNumberOfFunctionCalls)
      {
         if (expectedNumberOfFunctionCalls == 0)
         {
            _metalMockExceptionIsInFlight = true;
            throw UnsupportedCalledZeroTimesException(metalMockedFunctionSignature);
         }
      }

      void MetalMockThrowIfExpectedCallsSizeIsZero(size_t expectedCallsSize)
      {
         if (expectedCallsSize == 0)
         {
            _metalMockExceptionIsInFlight = true;
            throw UnsupportedCalledZeroTimesException(metalMockedFunctionSignature);
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

      template<typename MetalMockFunctionCallType>
      FunctionCallSequenceNumber NextFunctionCallSequenceNumber(std::vector<MetalMockFunctionCallType>& metalMockedFunctionCallHistory)
      {
         const size_t functionCallAssertionIndex = this->_functionCallAssertionIndex++;
         const size_t metalMockedFunctionCallCount = metalMockedFunctionCallHistory.size();
         if (functionCallAssertionIndex == metalMockedFunctionCallCount)
         {
            throw FunctionAssertedOneMoreTimeThanItWasCalledException(this->metalMockedFunctionSignature, metalMockedFunctionCallCount);
         }
         MetalMockFunctionCallType& nextFunctionCallSequenceNumber = metalMockedFunctionCallHistory[functionCallAssertionIndex];
         nextFunctionCallSequenceNumber.functionCallSequenceNumber.metalMockedFunctionSignature = &this->metalMockedFunctionSignature;
         return nextFunctionCallSequenceNumber.functionCallSequenceNumber;
      }
   private:
      void MetalMockExitIfExpectedButNotAsserted() const
      {
         if (this->wasExpected && !this->wasAsserted && !_metalMockExceptionIsInFlight)
         {
            const ZenUnit::Console console;
            console.WriteLineColor(R"(
==============================================================================
MetalMocked Function Was Expected But Not Later Asserted As Having Been Called
==============================================================================)", ZenUnit::Color::Red);
            console.WriteLine("MetalMocked Function:\n" + metalMockedFunctionSignature);
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
            const std::string testRunNumberLine = ZenUnit::String::ConcatValues(
               "    TestRun: ", ZenUnit::globalZenUnitMode.currentTestRunNumber, " of ", zenUnitArgs.testRuns);
            console.WriteLine(testRunNumberLine);

            console.WriteColor(">>------>", ZenUnit::Color::Red);
            console.WriteLine("     Result: MetalMocked Function Was Expected But Not Later Asserted As Having Been Called");

            console.WriteColor(">>-FAIL->", ZenUnit::Color::Red);
            const int exitCode = zenUnitArgs.alwaysExit0 ? 0 : 1;
            console.WriteLine("   ExitCode: " + std::to_string(exitCode));

            _call_exit(exitCode);
         }
      }
   };

   struct ZeroArgumentFunctionCall
   {
      FunctionCallSequenceNumber functionCallSequenceNumber;

      ZeroArgumentFunctionCall() noexcept
         : functionCallSequenceNumber() {}
   };

   template<typename MockableExceptionThrowerType = MetalMockExceptionThrower>
   class ZeroArgumentMetalMocker : public MetalMocker<MockableExceptionThrowerType>
   {
      template<
         typename MetalMockObjectType,
         typename FreeFunctionMockObjectType,
         typename StaticFunctionMockObjectType>
      friend class MetalMock0ArgsTester;
      friend class ZeroArgumentMetalMockerTests;
   private:
      std::vector<ZeroArgumentFunctionCall> metalMockedFunctionCallHistory;
   protected:
      std::function<void()> callInsteadFunction;
   public:
      explicit ZeroArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : MetalMocker<MockableExceptionThrowerType>(metalMockedFunctionSignature)
      {
      }

      void MetalMockIt()
      {
         this->MetalMockThrowIfNotExpected();
         this->metalMockedFunctionCallHistory.emplace_back();
         if (this->callInsteadFunction)
         {
            this->callInsteadFunction();
         }
         this->MetalMockThrowExceptionIfExceptionSet();
      }

      void CallInstead(const std::function<void()>& voidZeroArgFunction)
      {
         this->callInsteadFunction = voidZeroArgFunction;
         ZeroArgumentMetalMocker::wasExpected = true;
         ZeroArgumentMetalMocker::wasAsserted = true;
      }

      void CalledNTimes(size_t expectedNumberOfFunctionCalls)
      {
         this->MetalMockThrowIfExpectedNumberOfFunctionCalls0(expectedNumberOfFunctionCalls);
         this->MetalMockSetAsserted();
         ARE_EQUAL(expectedNumberOfFunctionCalls, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature);
      }

      FunctionCallSequenceNumber Called()
      {
         this->MetalMockSetAsserted();
         IS_NOT_EMPTY(this->metalMockedFunctionCallHistory, this->metalMockedFunctionSignature);
         return this->NextFunctionCallSequenceNumber(this->metalMockedFunctionCallHistory);
      }

      FunctionCallSequenceNumber CalledOnce()
      {
         this->MetalMockSetAsserted();
         constexpr size_t expectedNumberOfFunctionCalls = 1;
         ARE_EQUAL(expectedNumberOfFunctionCalls, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature);
         return this->NextFunctionCallSequenceNumber(this->metalMockedFunctionCallHistory);
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
         ZeroArgumentMetalMocker<MetalMockExceptionThrower>::wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         ZeroArgumentMetalMocker<MetalMockExceptionThrower>::wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         ZeroArgumentMetalMocker<MetalMockExceptionThrower>::wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         ZeroArgumentMetalMocker<MetalMockExceptionThrower>::wasExpected = true;
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
         ZeroArgumentMetalMocker<MetalMockExceptionThrower>::wasExpected = true;
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
      FunctionCallSequenceNumber functionCallSequenceNumber;

      OneArgumentFunctionCall() noexcept
         : argument()
         , functionCallSequenceNumber() {}

      OneArgumentFunctionCall(const Arg1Type& argument)
         : argument(argument)
         , functionCallSequenceNumber() {}
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
      ArgumentStorage<Arg1Type> arg1;
      ArgumentStorage<Arg2Type> arg2;
      FunctionCallSequenceNumber functionCallSequenceNumber;

      TwoArgumentFunctionCall() noexcept
         : arg1()
         , arg2()
         , functionCallSequenceNumber() {}

      TwoArgumentFunctionCall(const Arg1Type& arg1, const Arg2Type& arg2)
         : arg1(arg1)
         , arg2(arg2)
         , functionCallSequenceNumber() {}
   };

   template<typename Arg1Type, typename Arg2Type>
   struct TwoArgumentFunctionCallReferences
   {
      const ReferenceStorage<Arg1Type> arg1Reference;
      const ReferenceStorage<Arg2Type> arg2Reference;

      TwoArgumentFunctionCallReferences(const Arg1Type& arg1, const Arg2Type& arg2)
         : arg1Reference(arg1)
         , arg2Reference(arg2) {}

      explicit TwoArgumentFunctionCallReferences(const TwoArgumentFunctionCall<Arg1Type, Arg2Type>& twoArgumentFunctionCall)
         : arg1Reference(twoArgumentFunctionCall.arg1.value)
         , arg2Reference(twoArgumentFunctionCall.arg2.value) {}
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   struct ThreeArgumentFunctionCall
   {
      ArgumentStorage<Arg1Type> arg1;
      ArgumentStorage<Arg2Type> arg2;
      ArgumentStorage<Arg3Type> arg3;
      FunctionCallSequenceNumber functionCallSequenceNumber;

      ThreeArgumentFunctionCall() noexcept
         : arg1()
         , arg2()
         , arg3()
         , functionCallSequenceNumber() {}

      ThreeArgumentFunctionCall(const Arg1Type& arg1, const Arg2Type& arg2, const Arg3Type& arg3)
         : arg1(arg1)
         , arg2(arg2)
         , arg3(arg3)
         , functionCallSequenceNumber() {}
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   struct ThreeArgumentFunctionCallReferences
   {
      const ReferenceStorage<Arg1Type> arg1Reference;
      const ReferenceStorage<Arg2Type> arg2Reference;
      const ReferenceStorage<Arg3Type> arg3Reference;

      ThreeArgumentFunctionCallReferences(const Arg1Type& arg1, const Arg2Type& arg2, const Arg3Type& arg3)
         : arg1Reference(arg1)
         , arg2Reference(arg2)
         , arg3Reference(arg3) {}

      explicit ThreeArgumentFunctionCallReferences(const ThreeArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type>& threeArgumentFunctionCall)
         : arg1Reference(threeArgumentFunctionCall.arg1.value)
         , arg2Reference(threeArgumentFunctionCall.arg2.value)
         , arg3Reference(threeArgumentFunctionCall.arg3.value) {}
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   struct FourArgumentFunctionCall
   {
      ArgumentStorage<Arg1Type> arg1;
      ArgumentStorage<Arg2Type> arg2;
      ArgumentStorage<Arg3Type> arg3;
      ArgumentStorage<Arg4Type> arg4;
      FunctionCallSequenceNumber functionCallSequenceNumber;

      FourArgumentFunctionCall() noexcept
         : arg1()
         , arg2()
         , arg3()
         , arg4()
         , functionCallSequenceNumber() {}

      FourArgumentFunctionCall(const Arg1Type& arg1, const Arg2Type& arg2, const Arg3Type& arg3, const Arg4Type& arg4)
         : arg1(arg1)
         , arg2(arg2)
         , arg3(arg3)
         , arg4(arg4)
         , functionCallSequenceNumber() {}
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   struct FourArgumentFunctionCallReferences
   {
      const ReferenceStorage<Arg1Type> arg1Reference;
      const ReferenceStorage<Arg2Type> arg2Reference;
      const ReferenceStorage<Arg3Type> arg3Reference;
      const ReferenceStorage<Arg4Type> arg4Reference;

      FourArgumentFunctionCallReferences(const Arg1Type& arg1, const Arg2Type& arg2, const Arg3Type& arg3, const Arg4Type& arg4)
         : arg1Reference(arg1)
         , arg2Reference(arg2)
         , arg3Reference(arg3)
         , arg4Reference(arg4) {}

      explicit FourArgumentFunctionCallReferences(const FourArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& fourArgumentFunctionCall)
         : arg1Reference(fourArgumentFunctionCall.arg1.value)
         , arg2Reference(fourArgumentFunctionCall.arg2.value)
         , arg3Reference(fourArgumentFunctionCall.arg3.value)
         , arg4Reference(fourArgumentFunctionCall.arg4.value) {}
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   struct FiveArgumentFunctionCall
   {
      ArgumentStorage<Arg1Type> arg1;
      ArgumentStorage<Arg2Type> arg2;
      ArgumentStorage<Arg3Type> arg3;
      ArgumentStorage<Arg4Type> arg4;
      ArgumentStorage<Arg5Type> arg5;
      FunctionCallSequenceNumber functionCallSequenceNumber;

      FiveArgumentFunctionCall() noexcept
         : arg1()
         , arg2()
         , arg3()
         , arg4()
         , arg5()
         , functionCallSequenceNumber() {}

      FiveArgumentFunctionCall(
         const Arg1Type& arg1,
         const Arg2Type& arg2,
         const Arg3Type& arg3,
         const Arg4Type& arg4,
         const Arg5Type& arg5)
         : arg1(arg1)
         , arg2(arg2)
         , arg3(arg3)
         , arg4(arg4)
         , arg5(arg5)
         , functionCallSequenceNumber() {}
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   struct FiveArgumentFunctionCallReferences
   {
      const ReferenceStorage<Arg1Type> arg1Reference;
      const ReferenceStorage<Arg2Type> arg2Reference;
      const ReferenceStorage<Arg3Type> arg3Reference;
      const ReferenceStorage<Arg4Type> arg4Reference;
      const ReferenceStorage<Arg5Type> arg5Reference;

      FiveArgumentFunctionCallReferences(
         const Arg1Type& arg1,
         const Arg2Type& arg2,
         const Arg3Type& arg3,
         const Arg4Type& arg4,
         const Arg5Type& arg5)
         : arg1Reference(arg1)
         , arg2Reference(arg2)
         , arg3Reference(arg3)
         , arg4Reference(arg4)
         , arg5Reference(arg5) {}

      explicit FiveArgumentFunctionCallReferences(const FiveArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& fiveArgumentFunctionCall)
         : arg1Reference(fiveArgumentFunctionCall.arg1.value)
         , arg2Reference(fiveArgumentFunctionCall.arg2.value)
         , arg3Reference(fiveArgumentFunctionCall.arg3.value)
         , arg4Reference(fiveArgumentFunctionCall.arg4.value)
         , arg5Reference(fiveArgumentFunctionCall.arg5.value) {}
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   struct SixArgumentFunctionCall
   {
      ArgumentStorage<Arg1Type> arg1;
      ArgumentStorage<Arg2Type> arg2;
      ArgumentStorage<Arg3Type> arg3;
      ArgumentStorage<Arg4Type> arg4;
      ArgumentStorage<Arg5Type> arg5;
      ArgumentStorage<Arg6Type> arg6;
      FunctionCallSequenceNumber functionCallSequenceNumber;

      SixArgumentFunctionCall() noexcept
         : arg1()
         , arg2()
         , arg3()
         , arg4()
         , arg5()
         , arg6()
         , functionCallSequenceNumber() {}

      SixArgumentFunctionCall(
         const Arg1Type& arg1,
         const Arg2Type& arg2,
         const Arg3Type& arg3,
         const Arg4Type& arg4,
         const Arg5Type& arg5,
         const Arg6Type& arg6)
         : arg1(arg1)
         , arg2(arg2)
         , arg3(arg3)
         , arg4(arg4)
         , arg5(arg5)
         , arg6(arg6)
         , functionCallSequenceNumber() {}
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   struct SixArgumentFunctionCallReferences
   {
      const ReferenceStorage<Arg1Type> arg1Reference;
      const ReferenceStorage<Arg2Type> arg2Reference;
      const ReferenceStorage<Arg3Type> arg3Reference;
      const ReferenceStorage<Arg4Type> arg4Reference;
      const ReferenceStorage<Arg5Type> arg5Reference;
      const ReferenceStorage<Arg6Type> arg6Reference;

      SixArgumentFunctionCallReferences(
         const Arg1Type& arg1,
         const Arg2Type& arg2,
         const Arg3Type& arg3,
         const Arg4Type& arg4,
         const Arg5Type& arg5,
         const Arg6Type& arg6)
         : arg1Reference(arg1)
         , arg2Reference(arg2)
         , arg3Reference(arg3)
         , arg4Reference(arg4)
         , arg5Reference(arg5)
         , arg6Reference(arg6) {}

      explicit SixArgumentFunctionCallReferences(const SixArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& sixArgumentFunctionCall)
         : arg1Reference(sixArgumentFunctionCall.arg1.value)
         , arg2Reference(sixArgumentFunctionCall.arg2.value)
         , arg3Reference(sixArgumentFunctionCall.arg3.value)
         , arg4Reference(sixArgumentFunctionCall.arg4.value)
         , arg5Reference(sixArgumentFunctionCall.arg5.value)
         , arg6Reference(sixArgumentFunctionCall.arg6.value) {}
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   struct SevenArgumentFunctionCall
   {
      ArgumentStorage<Arg1Type> arg1;
      ArgumentStorage<Arg2Type> arg2;
      ArgumentStorage<Arg3Type> arg3;
      ArgumentStorage<Arg4Type> arg4;
      ArgumentStorage<Arg5Type> arg5;
      ArgumentStorage<Arg6Type> arg6;
      ArgumentStorage<Arg7Type> arg7;
      FunctionCallSequenceNumber functionCallSequenceNumber;

      SevenArgumentFunctionCall() noexcept
         : arg1()
         , arg2()
         , arg3()
         , arg4()
         , arg5()
         , arg6()
         , arg7()
         , functionCallSequenceNumber() {}

      SevenArgumentFunctionCall(
         const Arg1Type& arg1,
         const Arg2Type& arg2,
         const Arg3Type& arg3,
         const Arg4Type& arg4,
         const Arg5Type& arg5,
         const Arg6Type& arg6,
         const Arg7Type& arg7)
         : arg1(arg1)
         , arg2(arg2)
         , arg3(arg3)
         , arg4(arg4)
         , arg5(arg5)
         , arg6(arg6)
         , arg7(arg7)
         , functionCallSequenceNumber() {}
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   struct SevenArgumentFunctionCallReferences
   {
      const ReferenceStorage<Arg1Type> arg1Reference;
      const ReferenceStorage<Arg2Type> arg2Reference;
      const ReferenceStorage<Arg3Type> arg3Reference;
      const ReferenceStorage<Arg4Type> arg4Reference;
      const ReferenceStorage<Arg5Type> arg5Reference;
      const ReferenceStorage<Arg6Type> arg6Reference;
      const ReferenceStorage<Arg7Type> arg7Reference;

      SevenArgumentFunctionCallReferences(
         const Arg1Type& arg1,
         const Arg2Type& arg2,
         const Arg3Type& arg3,
         const Arg4Type& arg4,
         const Arg5Type& arg5,
         const Arg6Type& arg6,
         const Arg7Type& arg7)
         : arg1Reference(arg1)
         , arg2Reference(arg2)
         , arg3Reference(arg3)
         , arg4Reference(arg4)
         , arg5Reference(arg5)
         , arg6Reference(arg6)
         , arg7Reference(arg7) {}

      explicit SevenArgumentFunctionCallReferences(const SevenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& sevenArgumentFunctionCall)
         : arg1Reference(sevenArgumentFunctionCall.arg1.value)
         , arg2Reference(sevenArgumentFunctionCall.arg2.value)
         , arg3Reference(sevenArgumentFunctionCall.arg3.value)
         , arg4Reference(sevenArgumentFunctionCall.arg4.value)
         , arg5Reference(sevenArgumentFunctionCall.arg5.value)
         , arg6Reference(sevenArgumentFunctionCall.arg6.value)
         , arg7Reference(sevenArgumentFunctionCall.arg7.value) {}
   };

   template<typename ArgType>
   bool operator==(
      const MetalMock::OneArgumentFunctionCallReference<ArgType>& expectedOneArgumentFunctionCallReference,
      const MetalMock::OneArgumentFunctionCallReference<ArgType>& actualOneArgumentFunctionCallReference)
   {
      try
      {
         ZenUnit::Equalizer<MetalMock::OneArgumentFunctionCallReference<ArgType>>::AssertEqual(
            expectedOneArgumentFunctionCallReference, actualOneArgumentFunctionCallReference);
      }
      catch (const ZenUnit::Anomaly&)
      {
         return false;
      }
      return true;
   }

   template<
      typename ArgType,
      typename MockableExceptionThrowerType = MetalMockExceptionThrower>
   class OneArgumentMetalMocker : public MetalMocker<MockableExceptionThrowerType>
   {
      template<
         typename MetalMockObjectType,
         typename FreeFunctionMockObjectType,
         typename StaticFunctionMockObjectType>
      friend class MetalMock1ArgTester;
      friend class OneArgumentMetalMockerTests;
   private:
      std::vector<OneArgumentFunctionCall<ArgType>> metalMockedFunctionCallHistory;
   public:
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

      FunctionCallSequenceNumber CalledWith(const ArgType& expectedArgument)
      {
         this->MetalMockSetAsserted();
         const OneArgumentFunctionCallReference<ArgType> expectedOneArgumentFunctionCall(expectedArgument);
         const std::vector<OneArgumentFunctionCallReference<ArgType>> actualOneArgumentFunctionCalls =
            MetalMocker<MockableExceptionThrowerType>::template ConvertMetalMockFunctionCallsToMetalMockFunctionCallReferences<
               OneArgumentFunctionCallReference<ArgType>,
               OneArgumentFunctionCall<ArgType>>(this->metalMockedFunctionCallHistory);
         CONTAINS_ELEMENT(expectedOneArgumentFunctionCall, actualOneArgumentFunctionCalls, this->metalMockedFunctionSignature);
         return this->NextFunctionCallSequenceNumber(metalMockedFunctionCallHistory);
      }

      FunctionCallSequenceNumber CalledOnceWith(const ArgType& expectedArgument)
      {
         this->MetalMockSetAsserted();
         constexpr size_t expectedNumberOfFunctionCalls = 1;
         ARE_EQUAL(expectedNumberOfFunctionCalls, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature);
         ARE_EQUAL(expectedArgument, this->metalMockedFunctionCallHistory[0].argument.value, this->metalMockedFunctionSignature);
         return this->NextFunctionCallSequenceNumber(metalMockedFunctionCallHistory);
      }

      void CalledNTimes(size_t expectedNumberOfFunctionCalls)
      {
         this->MetalMockThrowIfExpectedNumberOfFunctionCalls0(expectedNumberOfFunctionCalls);
         this->MetalMockSetAsserted();
         ARE_EQUAL(expectedNumberOfFunctionCalls, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature);
      }

      void CalledNTimesWith(
         size_t expectedNumberOfFunctionCalls,
         const ArgType& expectedArgument)
      {
         this->MetalMockThrowIfExpectedNumberOfFunctionCalls0(expectedNumberOfFunctionCalls);
         this->MetalMockSetAsserted();
         ARE_EQUAL(expectedNumberOfFunctionCalls, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfFunctionCalls; ++i)
         {
            const std::string metalMockedFunctionSignatureAndCallIndex = ZenUnit::String::ConcatValues(this->metalMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArgument, this->metalMockedFunctionCallHistory[i].argument.value, metalMockedFunctionSignatureAndCallIndex);
         }
      }

      FunctionCallSequenceNumber CalledAsFollows(
         const std::vector<OneArgumentFunctionCallReference<ArgType>>& expectedOneArgumentFunctionCalls)
      {
         this->MetalMockThrowIfExpectedCallsSizeIsZero(expectedOneArgumentFunctionCalls.size());
         this->MetalMockSetAsserted();
         const std::vector<OneArgumentFunctionCallReference<ArgType>> actualOneArgumentFunctionCalls =
            MetalMocker<MockableExceptionThrowerType>::template ConvertMetalMockFunctionCallsToMetalMockFunctionCallReferences<
               OneArgumentFunctionCallReference<ArgType>,
               OneArgumentFunctionCall<ArgType>>(this->metalMockedFunctionCallHistory);
         VECTORS_ARE_EQUAL(expectedOneArgumentFunctionCalls, actualOneArgumentFunctionCalls, this->metalMockedFunctionSignature);
         return this->NextFunctionCallSequenceNumber(metalMockedFunctionCallHistory);
      }

      FunctionCallSequenceNumber CalledAsFollowsInAnyOrder(
         const std::vector<OneArgumentFunctionCallReference<ArgType>>& expectedOneArgumentFunctionCalls)
      {
         this->MetalMockThrowIfExpectedCallsSizeIsZero(expectedOneArgumentFunctionCalls.size());
         this->MetalMockSetAsserted();
         const std::vector<OneArgumentFunctionCallReference<ArgType>> actualOneArgumentFunctionCalls =
            MetalMocker<MockableExceptionThrowerType>::template ConvertMetalMockFunctionCallsToMetalMockFunctionCallReferences<
               OneArgumentFunctionCallReference<ArgType>,
               OneArgumentFunctionCall<ArgType>>(this->metalMockedFunctionCallHistory);
         INDEXABLES_ARE_EQUAL_IN_ANY_ORDER(expectedOneArgumentFunctionCalls, actualOneArgumentFunctionCalls, this->metalMockedFunctionSignature);
         return this->NextFunctionCallSequenceNumber(metalMockedFunctionCallHistory);
      }
   };

   template<typename ArgType>
   class VoidOneArgumentMetalMocker : public OneArgumentMetalMocker<ArgType>
   {
      friend class VoidOneArgumentMetalMockerTests;
   private:
      std::function<void(ArgType)> callInsteadFunction;
   public:
      explicit VoidOneArgumentMetalMocker(std::string_view metalMockedFunctionSignature)
         : OneArgumentMetalMocker<ArgType>(metalMockedFunctionSignature)
      {
      }

      void CallInstead(const std::function<void(ArgType)>& voidOneArgFunction)
      {
         this->callInsteadFunction = voidOneArgFunction;
         OneArgumentMetalMocker<ArgType>::wasExpected = true;
         OneArgumentMetalMocker<ArgType>::wasAsserted = true;
      }

      void Expect()
      {
         OneArgumentMetalMocker<ArgType>::wasExpected = true;
      }

      void MetalMockIt(const ArgType& arg)
      {
         if (this->callInsteadFunction)
         {
            this->callInsteadFunction(arg);
         }
         OneArgumentMetalMocker<ArgType>::MetalMockIt(arg);
      }
   };

   template<typename FunctionReturnType, typename ArgType>
   class NonVoidOneArgumentMetalMocker : public OneArgumentMetalMocker<ArgType>, protected ValueReturner<FunctionReturnType>
   {
      friend class NonVoidOneArgumentMetalMockerTests;
   private:
      std::function<FunctionReturnType(ArgType)> callInsteadFunction;
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

      void CallInstead(const std::function<FunctionReturnType(ArgType)>& nonVoidOneArgFunction)
      {
         this->callInsteadFunction = nonVoidOneArgFunction;
         OneArgumentMetalMocker<ArgType>::wasExpected = true;
         OneArgumentMetalMocker<ArgType>::wasAsserted = true;
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         OneArgumentMetalMocker<ArgType>::wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         OneArgumentMetalMocker<ArgType>::wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         OneArgumentMetalMocker<ArgType>::wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         OneArgumentMetalMocker<ArgType>::wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::MetalMockAddRandomReturnValue();
         return randomReturnValue;
      }

      FunctionReturnType MetalMockItAndReturnValue(ArgType argument)
      {
         OneArgumentMetalMocker<ArgType>::MetalMockIt(argument);
         if (this->callInsteadFunction)
         {
            const FunctionReturnType& returnValue = this->callInsteadFunction(argument);
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

   template<typename Arg1Type, typename Arg2Type>
   bool operator==(
      const MetalMock::TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>& expectedTwoArgumentFunctionCallReference,
      const MetalMock::TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>& actualTwoArgumentFunctionCallReference)
   {
      try
      {
         ZenUnit::Equalizer<MetalMock::TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>>::AssertEqual(
            expectedTwoArgumentFunctionCallReference, actualTwoArgumentFunctionCallReference);
      }
      catch (const ZenUnit::Anomaly&)
      {
         return false;
      }
      return true;
   }

   template<
      typename Arg1Type,
      typename Arg2Type,
      typename MockableExceptionThrowerType = MetalMockExceptionThrower>
   class TwoArgumentMetalMocker : public MetalMocker<MockableExceptionThrowerType>
   {
      template<
         typename MetalMockObjectType,
         typename FreeFunctionMockObjectType,
         typename StaticFunctionMockObjectType>
      friend class MetalMock2ArgsTester;
      friend class TwoArgumentMetalMockerTests;
   protected:
      std::function<void(Arg1Type, Arg2Type)> baseVoidCallInsteadFunction;
   public:
      std::vector<TwoArgumentFunctionCall<Arg1Type, Arg2Type>> metalMockedFunctionCallHistory;

      explicit TwoArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : MetalMocker<MockableExceptionThrowerType>(metalMockedFunctionSignature)
      {
      }

      void MetalMockIt(const Arg1Type& arg1, const Arg2Type& arg2)
      {
         this->MetalMockThrowIfNotExpected(arg1, arg2);
         this->metalMockedFunctionCallHistory.emplace_back(arg1, arg2);
         if (this->baseVoidCallInsteadFunction)
         {
            this->baseVoidCallInsteadFunction(arg1, arg2);
         }
         this->MetalMockThrowExceptionIfExceptionSet();
      }

      FunctionCallSequenceNumber CalledWith(const Arg1Type& expectedArg1, const Arg2Type& expectedArg2)
      {
         this->MetalMockSetAsserted();
         const TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type> expectedTwoArgumentFunctionCall(expectedArg1, expectedArg2);
         const std::vector<TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>> actualTwoArgumentFunctionCalls =
            MetalMocker<MockableExceptionThrowerType>::template ConvertMetalMockFunctionCallsToMetalMockFunctionCallReferences<
               TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>,
               TwoArgumentFunctionCall<Arg1Type, Arg2Type>>(this->metalMockedFunctionCallHistory);
         CONTAINS_ELEMENT(expectedTwoArgumentFunctionCall, actualTwoArgumentFunctionCalls, this->metalMockedFunctionSignature);
         return this->NextFunctionCallSequenceNumber(metalMockedFunctionCallHistory);
      }

      FunctionCallSequenceNumber CalledOnceWith(
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2)
      {
         this->MetalMockSetAsserted();
         constexpr size_t expectedNumberOfFunctionCalls = 1;
         ARE_EQUAL(expectedNumberOfFunctionCalls, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature);
         ARE_EQUAL(expectedArg1, this->metalMockedFunctionCallHistory[0].arg1.value, this->metalMockedFunctionSignature);
         ARE_EQUAL(expectedArg2, this->metalMockedFunctionCallHistory[0].arg2.value, this->metalMockedFunctionSignature);
         return this->NextFunctionCallSequenceNumber(metalMockedFunctionCallHistory);
      }

      void CalledNTimes(size_t expectedNumberOfFunctionCalls)
      {
         this->MetalMockThrowIfExpectedNumberOfFunctionCalls0(expectedNumberOfFunctionCalls);
         this->MetalMockSetAsserted();
         ARE_EQUAL(expectedNumberOfFunctionCalls, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature);
      }

      void CalledNTimesWith(
         size_t expectedNumberOfFunctionCalls,
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2)
      {
         this->MetalMockThrowIfExpectedNumberOfFunctionCalls0(expectedNumberOfFunctionCalls);
         this->MetalMockSetAsserted();
         ARE_EQUAL(expectedNumberOfFunctionCalls, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfFunctionCalls; ++i)
         {
            const std::string metalMockedFunctionSignatureAndCallIndex = ZenUnit::String::ConcatValues(this->metalMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArg1, this->metalMockedFunctionCallHistory[i].arg1.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg2, this->metalMockedFunctionCallHistory[i].arg2.value, metalMockedFunctionSignatureAndCallIndex);
         }
      }

      FunctionCallSequenceNumber CalledAsFollows(
         const std::vector<TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>>& expectedTwoArgumentFunctionCalls)
      {
         this->MetalMockThrowIfExpectedCallsSizeIsZero(expectedTwoArgumentFunctionCalls.size());
         this->MetalMockSetAsserted();
         const std::vector<TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>> actualTwoArgumentFunctionCalls =
            MetalMocker<MockableExceptionThrowerType>::template ConvertMetalMockFunctionCallsToMetalMockFunctionCallReferences<
               TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>,
               TwoArgumentFunctionCall<Arg1Type, Arg2Type>>(this->metalMockedFunctionCallHistory);
         VECTORS_ARE_EQUAL(expectedTwoArgumentFunctionCalls, actualTwoArgumentFunctionCalls, this->metalMockedFunctionSignature);
         return this->NextFunctionCallSequenceNumber(metalMockedFunctionCallHistory);
      }

      FunctionCallSequenceNumber CalledAsFollowsInAnyOrder(
         const std::vector<TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>>& expectedTwoArgumentFunctionCalls)
      {
         this->MetalMockThrowIfExpectedCallsSizeIsZero(expectedTwoArgumentFunctionCalls.size());
         this->MetalMockSetAsserted();
         const std::vector<TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>> actualTwoArgumentFunctionCalls =
            MetalMocker<MockableExceptionThrowerType>::template ConvertMetalMockFunctionCallsToMetalMockFunctionCallReferences<
               TwoArgumentFunctionCallReferences<Arg1Type, Arg2Type>,
               TwoArgumentFunctionCall<Arg1Type, Arg2Type>>(this->metalMockedFunctionCallHistory);
         INDEXABLES_ARE_EQUAL_IN_ANY_ORDER(expectedTwoArgumentFunctionCalls, actualTwoArgumentFunctionCalls, this->metalMockedFunctionSignature);
         return this->NextFunctionCallSequenceNumber(metalMockedFunctionCallHistory);
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type>
   class NonVoidTwoArgumentMetalMocker : public TwoArgumentMetalMocker<Arg1Type, Arg2Type>, protected ValueReturner<FunctionReturnType>
   {
      friend class NonVoidTwoArgumentMetalMockerTests;
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
      std::function<FunctionReturnType(Arg1Type, Arg2Type)> derivedNonVoidCallInsteadFunction;
   public:
      explicit NonVoidTwoArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : TwoArgumentMetalMocker<Arg1Type, Arg2Type>(metalMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(metalMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         TwoArgumentMetalMocker<Arg1Type, Arg2Type>::wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         TwoArgumentMetalMocker<Arg1Type, Arg2Type>::wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         TwoArgumentMetalMocker<Arg1Type, Arg2Type>::wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         TwoArgumentMetalMocker<Arg1Type, Arg2Type>::wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::MetalMockAddRandomReturnValue();
         return randomReturnValue;
      }

      void CallInstead(const std::function<FunctionReturnType(Arg1Type, Arg2Type)>& nonVoidTwoArgFunction)
      {
         this->derivedNonVoidCallInsteadFunction = nonVoidTwoArgFunction;
         TwoArgumentMetalMocker<Arg1Type, Arg2Type>::wasExpected = true;
         TwoArgumentMetalMocker<Arg1Type, Arg2Type>::wasAsserted = true;
      }

      FunctionReturnType MetalMockItAndReturnValue(Arg1Type arg1, Arg2Type arg2)
      {
         TwoArgumentMetalMocker<Arg1Type, Arg2Type>::MetalMockIt(arg1, arg2);
         if (this->derivedNonVoidCallInsteadFunction)
         {
            const FunctionReturnType& returnValue = this->derivedNonVoidCallInsteadFunction(arg1, arg2);
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
         Arg1Type arg1, Arg2Type arg2)
      {
         const FunctionReturnType& returnValue = functionMocker->MetalMockItAndReturnValue(arg1, arg2);
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
         TwoArgumentMetalMocker<Arg1Type, Arg2Type>::wasExpected = true;
      }

      void CallInstead(const std::function<void(Arg1Type, Arg2Type)>& voidTwoArgFunction)
      {
         this->baseVoidCallInsteadFunction = voidTwoArgFunction;
         TwoArgumentMetalMocker<Arg1Type, Arg2Type>::wasExpected = true;
         TwoArgumentMetalMocker<Arg1Type, Arg2Type>::wasAsserted = true;
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
         VoidTwoArgFunctionPointerMetalMocker<Arg1Type, Arg2Type>* functionMocker, Arg1Type arg1, Arg2Type arg2)
      {
         functionMocker->MetalMockIt(arg1, arg2);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   bool operator==(
      const MetalMock::ThreeArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type>& expectedThreeArgumentFunctionCallReference,
      const MetalMock::ThreeArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type>& actualThreeArgumentFunctionCallReference)
   {
      try
      {
         ZenUnit::Equalizer<MetalMock::ThreeArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type>>::AssertEqual(
            expectedThreeArgumentFunctionCallReference, actualThreeArgumentFunctionCallReference);
      }
      catch (const ZenUnit::Anomaly&)
      {
         return false;
      }
      return true;
   }

   template<
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename MockableExceptionThrowerType = MetalMockExceptionThrower>
   class ThreeArgumentMetalMocker : public MetalMocker<MockableExceptionThrowerType>
   {
      template<
         typename MetalMockObjectType,
         typename FreeFunctionMockObjectType,
         typename StaticFunctionMockObjectType>
      friend class MetalMock3ArgsTester;
      friend class ThreeArgumentMetalMockerTests;
   public:
      std::vector<ThreeArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type>> metalMockedFunctionCallHistory;

      explicit ThreeArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : MetalMocker<MockableExceptionThrowerType>(metalMockedFunctionSignature)
      {
      }

      virtual ~ThreeArgumentMetalMocker() = default;

      virtual void MetalMockIt(const Arg1Type& arg1, const Arg2Type& arg2, const Arg3Type& arg3)
      {
         this->MetalMockThrowIfNotExpected(arg1, arg2, arg3);
         this->metalMockedFunctionCallHistory.emplace_back(arg1, arg2, arg3);
         this->MetalMockThrowExceptionIfExceptionSet();
      }

      FunctionCallSequenceNumber CalledWith(const Arg1Type& expectedArg1, const Arg2Type& expectedArg2, const Arg3Type& expectedArg3)
      {
         this->MetalMockSetAsserted();
         const ThreeArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type> expectedThreeArgumentFunctionCall(expectedArg1, expectedArg2, expectedArg3);
         const std::vector<ThreeArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type>> actualThreeArgumentFunctionCalls =
            MetalMocker<MockableExceptionThrowerType>::template ConvertMetalMockFunctionCallsToMetalMockFunctionCallReferences<
               ThreeArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type>,
               ThreeArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type>>(this->metalMockedFunctionCallHistory);
         CONTAINS_ELEMENT(expectedThreeArgumentFunctionCall, actualThreeArgumentFunctionCalls, this->metalMockedFunctionSignature);
         return this->NextFunctionCallSequenceNumber(metalMockedFunctionCallHistory);
      }

      FunctionCallSequenceNumber CalledOnceWith(
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2,
         const Arg3Type& expectedArg3)
      {
         this->MetalMockSetAsserted();
         constexpr size_t expectedNumberOfFunctionCalls = 1;
         ARE_EQUAL(expectedNumberOfFunctionCalls, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature);
         ARE_EQUAL(expectedArg1, this->metalMockedFunctionCallHistory[0].arg1.value, this->metalMockedFunctionSignature);
         ARE_EQUAL(expectedArg2, this->metalMockedFunctionCallHistory[0].arg2.value, this->metalMockedFunctionSignature);
         ARE_EQUAL(expectedArg3, this->metalMockedFunctionCallHistory[0].arg3.value, this->metalMockedFunctionSignature);
         return this->NextFunctionCallSequenceNumber(metalMockedFunctionCallHistory);
      }

      void CalledNTimes(size_t expectedNumberOfFunctionCalls)
      {
         this->MetalMockThrowIfExpectedNumberOfFunctionCalls0(expectedNumberOfFunctionCalls);
         this->MetalMockSetAsserted();
         ARE_EQUAL(expectedNumberOfFunctionCalls, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature);
      }

      void CalledNTimesWith(
         size_t expectedNumberOfFunctionCalls,
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2,
         const Arg3Type& expectedArg3)
      {
         this->MetalMockThrowIfExpectedNumberOfFunctionCalls0(expectedNumberOfFunctionCalls);
         this->MetalMockSetAsserted();
         ARE_EQUAL(expectedNumberOfFunctionCalls, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfFunctionCalls; ++i)
         {
            const std::string metalMockedFunctionSignatureAndCallIndex = ZenUnit::String::ConcatValues(this->metalMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArg1, this->metalMockedFunctionCallHistory[i].arg1.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg2, this->metalMockedFunctionCallHistory[i].arg2.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg3, this->metalMockedFunctionCallHistory[i].arg3.value, metalMockedFunctionSignatureAndCallIndex);
         }
      }

      FunctionCallSequenceNumber CalledAsFollows(
         const std::vector<ThreeArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type>>& expectedThreeArgumentFunctionCalls)
      {
         this->MetalMockThrowIfExpectedCallsSizeIsZero(expectedThreeArgumentFunctionCalls.size());
         this->MetalMockSetAsserted();
         // One line to fix apparent lcov/Codecov.io bug whereby if this line is line-breaked it is labeled as covered
         const std::vector<ThreeArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type>> actualThreeArgumentFunctionCalls = MetalMocker<MockableExceptionThrowerType>::template ConvertMetalMockFunctionCallsToMetalMockFunctionCallReferences<ThreeArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type>, ThreeArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type>>(this->metalMockedFunctionCallHistory);
         VECTORS_ARE_EQUAL(expectedThreeArgumentFunctionCalls, actualThreeArgumentFunctionCalls, this->metalMockedFunctionSignature);
         return this->NextFunctionCallSequenceNumber(metalMockedFunctionCallHistory);
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class NonVoidThreeArgumentMetalMocker : public ThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>, protected ValueReturner<FunctionReturnType>
   {
      friend class NonVoidThreeArgumentMetalMockerTests;
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
      std::function<FunctionReturnType(Arg1Type, Arg2Type, Arg3Type)> derivedNonVoidCallInsteadFunction;
   public:
      explicit NonVoidThreeArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : ThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>(metalMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(metalMockedFunctionSignature)
      {
      }

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         ThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>::wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         ThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>::wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         ThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>::wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         ThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>::wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::MetalMockAddRandomReturnValue();
         return randomReturnValue;
      }

      void CallInstead(const std::function<FunctionReturnType(Arg1Type, Arg2Type, Arg3Type)>& nonVoidThreeArgFunction)
      {
         this->derivedNonVoidCallInsteadFunction = nonVoidThreeArgFunction;
         ThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>::wasExpected = true;
         ThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>::wasAsserted = true;
      }

      FunctionReturnType MetalMockItAndReturnValue(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3)
      {
         ThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>::MetalMockIt(arg1, arg2, arg3);
         if (this->derivedNonVoidCallInsteadFunction)
         {
            const FunctionReturnType& returnValue = this->derivedNonVoidCallInsteadFunction(arg1, arg2, arg3);
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
         Arg1Type arg1, Arg2Type arg2, Arg3Type arg3)
      {
         const FunctionReturnType& returnValue = functionMocker->MetalMockItAndReturnValue(arg1, arg2, arg3);
         return returnValue;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class VoidThreeArgumentMetalMocker : public ThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>
   {
   protected:
      std::function<void(Arg1Type, Arg2Type, Arg3Type)> callInsteadFunction;
   public:
      explicit VoidThreeArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : ThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>(metalMockedFunctionSignature)
      {
      }

      void Expect()
      {
         ThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>::wasExpected = true;
      }

      void CallInstead(const std::function<void(Arg1Type, Arg2Type, Arg3Type)>& voidThreeArgFunction)
      {
         this->callInsteadFunction = voidThreeArgFunction;
         ThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>::wasExpected = true;
         ThreeArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type>::wasAsserted = true;
      }

      void MetalMockIt(const Arg1Type& arg1, const Arg2Type& arg2, const Arg3Type& arg3) override
      {
         this->MetalMockThrowIfNotExpected(arg1, arg2, arg3);
         this->metalMockedFunctionCallHistory.emplace_back(arg1, arg2, arg3);
         if (this->callInsteadFunction)
         {
            this->callInsteadFunction(arg1, arg2, arg3);
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
         Arg1Type arg1, Arg2Type arg2, Arg3Type arg3)
      {
         functionMocker->MetalMockIt(arg1, arg2, arg3);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   bool operator==(
      const MetalMock::FourArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& expectedFourArgumentFunctionCallReference,
      const MetalMock::FourArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& actualFourArgumentFunctionCallReference)
   {
      try
      {
         ZenUnit::Equalizer<MetalMock::FourArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>::AssertEqual(
            expectedFourArgumentFunctionCallReference, actualFourArgumentFunctionCallReference);
      }
      catch (const ZenUnit::Anomaly&)
      {
         return false;
      }
      return true;
   }

   template<
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename Arg4Type,
      typename MockableExceptionThrowerType = MetalMockExceptionThrower>
   class FourArgumentMetalMocker : public MetalMocker<MockableExceptionThrowerType>
   {
      template<
         typename MetalMockObjectType,
         typename FreeFunctionMockObjectType,
         typename StaticFunctionMockObjectType>
      friend class MetalMock4ArgsTester;
      friend class FourArgumentMetalMockerTests;
   public:
      std::vector<FourArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>> metalMockedFunctionCallHistory;

      explicit FourArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : MetalMocker<MockableExceptionThrowerType>(metalMockedFunctionSignature)
      {
      }

      void MetalMockIt(
         const Arg1Type& arg1,
         const Arg2Type& arg2,
         const Arg3Type& arg3,
         const Arg4Type& arg4)
      {
         this->MetalMockThrowIfNotExpected(arg1, arg2, arg3, arg4);
         metalMockedFunctionCallHistory.emplace_back(arg1, arg2, arg3, arg4);
         this->MetalMockThrowExceptionIfExceptionSet();
      }

      FunctionCallSequenceNumber CalledWith(
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2,
         const Arg3Type& expectedArg3,
         const Arg4Type& expectedArg4)
      {
         this->MetalMockSetAsserted();
         const FourArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type> expectedFourArgumentFunctionCall(expectedArg1, expectedArg2, expectedArg3, expectedArg4);
         const std::vector<FourArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type>> actualFourArgumentFunctionCalls =
            MetalMocker<MockableExceptionThrowerType>::template ConvertMetalMockFunctionCallsToMetalMockFunctionCallReferences<
               FourArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type>,
               FourArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>(this->metalMockedFunctionCallHistory);
         CONTAINS_ELEMENT(expectedFourArgumentFunctionCall, actualFourArgumentFunctionCalls, this->metalMockedFunctionSignature);
         return this->NextFunctionCallSequenceNumber(metalMockedFunctionCallHistory);
      }

      FunctionCallSequenceNumber CalledOnceWith(
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2,
         const Arg3Type& expectedArg3,
         const Arg4Type& expectedArg4)
      {
         this->MetalMockSetAsserted();
         constexpr size_t expectedNumberOfFunctionCalls = 1;
         ARE_EQUAL(expectedNumberOfFunctionCalls, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature);
         ARE_EQUAL(expectedArg1, this->metalMockedFunctionCallHistory[0].arg1.value, this->metalMockedFunctionSignature);
         ARE_EQUAL(expectedArg2, this->metalMockedFunctionCallHistory[0].arg2.value, this->metalMockedFunctionSignature);
         ARE_EQUAL(expectedArg3, this->metalMockedFunctionCallHistory[0].arg3.value, this->metalMockedFunctionSignature);
         ARE_EQUAL(expectedArg4, this->metalMockedFunctionCallHistory[0].arg4.value, this->metalMockedFunctionSignature);
         return this->NextFunctionCallSequenceNumber(metalMockedFunctionCallHistory);
      }

      void CalledNTimes(size_t expectedNumberOfFunctionCalls)
      {
         this->MetalMockThrowIfExpectedNumberOfFunctionCalls0(expectedNumberOfFunctionCalls);
         this->MetalMockSetAsserted();
         ARE_EQUAL(expectedNumberOfFunctionCalls, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature);
      }

      void CalledNTimesWith(
         size_t expectedNumberOfFunctionCalls,
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2,
         const Arg3Type& expectedArg3,
         const Arg4Type& expectedArg4)
      {
         this->MetalMockThrowIfExpectedNumberOfFunctionCalls0(expectedNumberOfFunctionCalls);
         this->MetalMockSetAsserted();
         ARE_EQUAL(expectedNumberOfFunctionCalls, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfFunctionCalls; ++i)
         {
            const std::string metalMockedFunctionSignatureAndCallIndex = ZenUnit::String::ConcatValues(this->metalMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArg1, this->metalMockedFunctionCallHistory[i].arg1.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg2, this->metalMockedFunctionCallHistory[i].arg2.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg3, this->metalMockedFunctionCallHistory[i].arg3.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg4, this->metalMockedFunctionCallHistory[i].arg4.value, metalMockedFunctionSignatureAndCallIndex);
         }
      }

      FunctionCallSequenceNumber CalledAsFollows(
         const std::vector<FourArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>& expectedFourArgumentFunctionCalls)
      {
         this->MetalMockThrowIfExpectedCallsSizeIsZero(expectedFourArgumentFunctionCalls.size());
         this->MetalMockSetAsserted();
         const std::vector<FourArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type>> actualFourArgumentFunctionCalls =
            MetalMocker<MockableExceptionThrowerType>::template ConvertMetalMockFunctionCallsToMetalMockFunctionCallReferences<
               FourArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type>,
               FourArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>(this->metalMockedFunctionCallHistory);
         VECTORS_ARE_EQUAL(expectedFourArgumentFunctionCalls, actualFourArgumentFunctionCalls, this->metalMockedFunctionSignature);
         return this->NextFunctionCallSequenceNumber(metalMockedFunctionCallHistory);
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class NonVoidFourArgumentMetalMocker : public FourArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>, protected ValueReturner<FunctionReturnType>
   {
      friend class NonVoidFourArgumentMetalMockerTests;
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
      std::function<FunctionReturnType(Arg1Type, Arg2Type, Arg3Type, Arg4Type)> callInsteadFunction;
   public:
      explicit NonVoidFourArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : FourArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>(metalMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(metalMockedFunctionSignature)
      {
      }

      virtual ~NonVoidFourArgumentMetalMocker() = default;

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         FourArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         FourArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         FourArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         FourArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::MetalMockAddRandomReturnValue();
         return randomReturnValue;
      }

      void CallInstead(const std::function<FunctionReturnType(Arg1Type, Arg2Type, Arg3Type, Arg4Type)>& nonVoidFourArgFunction)
      {
         this->callInsteadFunction = nonVoidFourArgFunction;
         FourArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::wasExpected = true;
         FourArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::wasAsserted = true;
      }

      virtual FunctionReturnType MetalMockItAndReturnValue(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4)
      {
         FourArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::MetalMockIt(arg1, arg2, arg3, arg4);
         if (this->callInsteadFunction)
         {
            const FunctionReturnType& returnValue = this->callInsteadFunction(arg1, arg2, arg3, arg4);
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

      virtual ~NonVoidFourArgFunctionPointerMetalMocker() = default;

      static FunctionReturnType MetalMockItFunctionPointer(
         NonVoidFourArgFunctionPointerMetalMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>* functionMocker,
         Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4)
      {
         const FunctionReturnType& returnValue = functionMocker->MetalMockItAndReturnValue(arg1, arg2, arg3, arg4);
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
         FourArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::wasExpected = true;
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
         Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4)
      {
         functionMocker->MetalMockIt(arg1, arg2, arg3, arg4);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   bool operator==(
      const MetalMock::FiveArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& expectedFiveArgumentFunctionCallReference,
      const MetalMock::FiveArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& actualFiveArgumentFunctionCallReference)
   {
      try
      {
         ZenUnit::Equalizer<MetalMock::FiveArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>::AssertEqual(
            expectedFiveArgumentFunctionCallReference, actualFiveArgumentFunctionCallReference);
      }
      catch (const ZenUnit::Anomaly&)
      {
         return false;
      }
      return true;
   }

   template<
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename Arg4Type,
      typename Arg5Type,
      typename MockableExceptionThrowerType = MetalMockExceptionThrower>
   class FiveArgumentMetalMocker : public MetalMocker<MockableExceptionThrowerType>
   {
      template<
         typename MetalMockObjectType,
         typename FreeFunctionMockObjectType,
         typename StaticFunctionMockObjectType>
      friend class MetalMock5ArgsTester;
      friend class FiveArgumentMetalMockerTests;
   public:
      std::vector<FiveArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>> metalMockedFunctionCallHistory;

      explicit FiveArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : MetalMocker<MockableExceptionThrowerType>(metalMockedFunctionSignature)
      {
      }

      void MetalMockIt(
         const Arg1Type& arg1,
         const Arg2Type& arg2,
         const Arg3Type& arg3,
         const Arg4Type& arg4,
         const Arg5Type& arg5)
      {
         this->MetalMockThrowIfNotExpected(arg1, arg2, arg3, arg4, arg5);
         metalMockedFunctionCallHistory.emplace_back(arg1, arg2, arg3, arg4, arg5);
         this->MetalMockThrowExceptionIfExceptionSet();
      }

      FunctionCallSequenceNumber CalledWith(
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2,
         const Arg3Type& expectedArg3,
         const Arg4Type& expectedArg4,
         const Arg5Type& expectedArg5)
      {
         this->MetalMockSetAsserted();
         const FiveArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type> expectedFiveArgumentFunctionCall(expectedArg1, expectedArg2, expectedArg3, expectedArg4, expectedArg5);
         const std::vector<FiveArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>> actualFiveArgumentFunctionCalls =
            MetalMocker<MockableExceptionThrowerType>::template ConvertMetalMockFunctionCallsToMetalMockFunctionCallReferences<
               FiveArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>,
               FiveArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>(this->metalMockedFunctionCallHistory);
         CONTAINS_ELEMENT(expectedFiveArgumentFunctionCall, actualFiveArgumentFunctionCalls, this->metalMockedFunctionSignature);
         return this->NextFunctionCallSequenceNumber(metalMockedFunctionCallHistory);
      }

      FunctionCallSequenceNumber CalledOnceWith(
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2,
         const Arg3Type& expectedArg3,
         const Arg4Type& expectedArg4,
         const Arg5Type& expectedArg5)
      {
         this->MetalMockSetAsserted();
         constexpr size_t expectedNumberOfFunctionCalls = 1;
         ARE_EQUAL(expectedNumberOfFunctionCalls, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature);
         ARE_EQUAL(expectedArg1, this->metalMockedFunctionCallHistory[0].arg1.value, this->metalMockedFunctionSignature);
         ARE_EQUAL(expectedArg2, this->metalMockedFunctionCallHistory[0].arg2.value, this->metalMockedFunctionSignature);
         ARE_EQUAL(expectedArg3, this->metalMockedFunctionCallHistory[0].arg3.value, this->metalMockedFunctionSignature);
         ARE_EQUAL(expectedArg4, this->metalMockedFunctionCallHistory[0].arg4.value, this->metalMockedFunctionSignature);
         ARE_EQUAL(expectedArg5, this->metalMockedFunctionCallHistory[0].arg5.value, this->metalMockedFunctionSignature);
         return this->NextFunctionCallSequenceNumber(metalMockedFunctionCallHistory);
      }

      void CalledNTimes(size_t expectedNumberOfFunctionCalls)
      {
         this->MetalMockThrowIfExpectedNumberOfFunctionCalls0(expectedNumberOfFunctionCalls);
         this->MetalMockSetAsserted();
         ARE_EQUAL(expectedNumberOfFunctionCalls, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature);
      }

      void CalledNTimesWith(
         size_t expectedNumberOfFunctionCalls,
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2,
         const Arg3Type& expectedArg3,
         const Arg4Type& expectedArg4,
         const Arg5Type& expectedArg5)
      {
         this->MetalMockThrowIfExpectedNumberOfFunctionCalls0(expectedNumberOfFunctionCalls);
         this->MetalMockSetAsserted();
         ARE_EQUAL(expectedNumberOfFunctionCalls, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfFunctionCalls; ++i)
         {
            const std::string metalMockedFunctionSignatureAndCallIndex = ZenUnit::String::ConcatValues(this->metalMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArg1, this->metalMockedFunctionCallHistory[i].arg1.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg2, this->metalMockedFunctionCallHistory[i].arg2.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg3, this->metalMockedFunctionCallHistory[i].arg3.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg4, this->metalMockedFunctionCallHistory[i].arg4.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg5, this->metalMockedFunctionCallHistory[i].arg5.value, metalMockedFunctionSignatureAndCallIndex);
         }
      }

      FunctionCallSequenceNumber CalledAsFollows(
         const std::vector<FiveArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>& expectedFiveArgumentFunctionCalls)
      {
         this->MetalMockThrowIfExpectedCallsSizeIsZero(expectedFiveArgumentFunctionCalls.size());
         this->MetalMockSetAsserted();
         const std::vector<FiveArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>> actualFiveArgumentFunctionCalls =
            MetalMocker<MockableExceptionThrowerType>::template ConvertMetalMockFunctionCallsToMetalMockFunctionCallReferences<
               FiveArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>,
               FiveArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>(this->metalMockedFunctionCallHistory);
         VECTORS_ARE_EQUAL(expectedFiveArgumentFunctionCalls, actualFiveArgumentFunctionCalls, this->metalMockedFunctionSignature);
         return this->NextFunctionCallSequenceNumber(metalMockedFunctionCallHistory);
      }
   };

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   class NonVoidFiveArgumentMetalMocker : public FiveArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>, protected ValueReturner<FunctionReturnType>
   {
      friend class NonVoidFiveArgumentMetalMockerTests;
   private:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
      std::function<FunctionReturnType(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)> callInsteadFunction;
   public:
      explicit NonVoidFiveArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : FiveArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>(metalMockedFunctionSignature)
         , ValueReturner<FunctionReturnType>(metalMockedFunctionSignature)
      {
      }

      virtual ~NonVoidFiveArgumentMetalMocker() = default;

      template<typename ReturnType>
      void Return(ReturnType&& returnValue)
      {
         FiveArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         FiveArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         FiveArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         FiveArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::MetalMockAddRandomReturnValue();
         return randomReturnValue;
      }

      void CallInstead(const std::function<FunctionReturnType(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)>& nonVoidFiveArgFunction)
      {
         this->callInsteadFunction = nonVoidFiveArgFunction;
         FiveArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::wasExpected = true;
         FiveArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::wasAsserted = true;
      }

      virtual FunctionReturnType MetalMockItAndReturnValue(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4, Arg5Type arg5)
      {
         FiveArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::MetalMockIt(arg1, arg2, arg3, arg4, arg5);
         if (this->callInsteadFunction)
         {
            const FunctionReturnType& returnValue = this->callInsteadFunction(arg1, arg2, arg3, arg4, arg5);
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

      virtual ~NonVoidFiveArgFunctionPointerMetalMocker() = default;

      static FunctionReturnType MetalMockItFunctionPointer(
         NonVoidFiveArgFunctionPointerMetalMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>* functionMocker,
         Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4, Arg5Type arg5)
      {
         const FunctionReturnType& returnValue = functionMocker->MetalMockItAndReturnValue(arg1, arg2, arg3, arg4, arg5);
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
         FiveArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::wasExpected = true;
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
         Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4, Arg5Type arg5)
      {
         functionMocker->MetalMockIt(arg1, arg2, arg3, arg4, arg5);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   bool operator==(
      const MetalMock::SixArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& expectedSixArgumentFunctionCallReference,
      const MetalMock::SixArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& actualSixArgumentFunctionCallReference)
   {
      try
      {
         ZenUnit::Equalizer<MetalMock::SixArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>::AssertEqual(
            expectedSixArgumentFunctionCallReference, actualSixArgumentFunctionCallReference);
      }
      catch (const ZenUnit::Anomaly&)
      {
         return false;
      }
      return true;
   }

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
      template<
         typename MetalMockObjectType,
         typename FreeFunctionMockObjectType,
         typename StaticFunctionMockObjectType>
      friend class MetalMock6ArgsTester;
      friend class SixArgumentMetalMockerTests;
   public:
      std::vector<SixArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>> metalMockedFunctionCallHistory;

      explicit SixArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : MetalMocker<MockableExceptionThrowerType>(metalMockedFunctionSignature)
      {
      }

      void MetalMockIt(
         const Arg1Type& arg1,
         const Arg2Type& arg2,
         const Arg3Type& arg3,
         const Arg4Type& arg4,
         const Arg5Type& arg5,
         const Arg6Type& arg6)
      {
         this->MetalMockThrowIfNotExpected(arg1, arg2, arg3, arg4, arg5, arg6);
         metalMockedFunctionCallHistory.emplace_back(arg1, arg2, arg3, arg4, arg5, arg6);
         this->MetalMockThrowExceptionIfExceptionSet();
      }

      FunctionCallSequenceNumber CalledWith(
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2,
         const Arg3Type& expectedArg3,
         const Arg4Type& expectedArg4,
         const Arg5Type& expectedArg5,
         const Arg6Type& expectedArg6)
      {
         this->MetalMockSetAsserted();
         const SixArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type> expectedSixArgumentFunctionCall(expectedArg1, expectedArg2, expectedArg3, expectedArg4, expectedArg5, expectedArg6);
         const std::vector<SixArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>> actualSixArgumentFunctionCalls =
            MetalMocker<MockableExceptionThrowerType>::template ConvertMetalMockFunctionCallsToMetalMockFunctionCallReferences<
               SixArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>,
               SixArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>(this->metalMockedFunctionCallHistory);
         CONTAINS_ELEMENT(expectedSixArgumentFunctionCall, actualSixArgumentFunctionCalls, this->metalMockedFunctionSignature);
         return this->NextFunctionCallSequenceNumber(metalMockedFunctionCallHistory);
      }

      FunctionCallSequenceNumber CalledOnceWith(
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2,
         const Arg3Type& expectedArg3,
         const Arg4Type& expectedArg4,
         const Arg5Type& expectedArg5,
         const Arg6Type& expectedArg6)
      {
         this->MetalMockSetAsserted();
         constexpr size_t expectedNumberOfFunctionCalls = 1;
         ARE_EQUAL(expectedNumberOfFunctionCalls, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature);
         ARE_EQUAL(expectedArg1, this->metalMockedFunctionCallHistory[0].arg1.value, this->metalMockedFunctionSignature);
         ARE_EQUAL(expectedArg2, this->metalMockedFunctionCallHistory[0].arg2.value, this->metalMockedFunctionSignature);
         ARE_EQUAL(expectedArg3, this->metalMockedFunctionCallHistory[0].arg3.value, this->metalMockedFunctionSignature);
         ARE_EQUAL(expectedArg4, this->metalMockedFunctionCallHistory[0].arg4.value, this->metalMockedFunctionSignature);
         ARE_EQUAL(expectedArg5, this->metalMockedFunctionCallHistory[0].arg5.value, this->metalMockedFunctionSignature);
         ARE_EQUAL(expectedArg6, this->metalMockedFunctionCallHistory[0].arg6.value, this->metalMockedFunctionSignature);
         return this->NextFunctionCallSequenceNumber(metalMockedFunctionCallHistory);
      }

      void CalledNTimes(size_t expectedNumberOfFunctionCalls)
      {
         this->MetalMockThrowIfExpectedNumberOfFunctionCalls0(expectedNumberOfFunctionCalls);
         this->MetalMockSetAsserted();
         ARE_EQUAL(expectedNumberOfFunctionCalls, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature);
      }

      void CalledNTimesWith(
         size_t expectedNumberOfFunctionCalls,
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2,
         const Arg3Type& expectedArg3,
         const Arg4Type& expectedArg4,
         const Arg5Type& expectedArg5,
         const Arg6Type& expectedArg6)
      {
         this->MetalMockThrowIfExpectedNumberOfFunctionCalls0(expectedNumberOfFunctionCalls);
         this->MetalMockSetAsserted();
         ARE_EQUAL(expectedNumberOfFunctionCalls, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfFunctionCalls; ++i)
         {
            const std::string metalMockedFunctionSignatureAndCallIndex = ZenUnit::String::ConcatValues(this->metalMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArg1, this->metalMockedFunctionCallHistory[i].arg1.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg2, this->metalMockedFunctionCallHistory[i].arg2.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg3, this->metalMockedFunctionCallHistory[i].arg3.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg4, this->metalMockedFunctionCallHistory[i].arg4.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg5, this->metalMockedFunctionCallHistory[i].arg5.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg6, this->metalMockedFunctionCallHistory[i].arg6.value, metalMockedFunctionSignatureAndCallIndex);
         }
      }

      FunctionCallSequenceNumber CalledAsFollows(
         const std::vector<SixArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>& expectedSixArgumentFunctionCalls)
      {
         this->MetalMockThrowIfExpectedCallsSizeIsZero(expectedSixArgumentFunctionCalls.size());
         this->MetalMockSetAsserted();
         const std::vector<SixArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>> actualSixArgumentFunctionCalls =
            MetalMocker<MockableExceptionThrowerType>::template ConvertMetalMockFunctionCallsToMetalMockFunctionCallReferences<
               SixArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>,
               SixArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>(this->metalMockedFunctionCallHistory);
         VECTORS_ARE_EQUAL(expectedSixArgumentFunctionCalls, actualSixArgumentFunctionCalls, this->metalMockedFunctionSignature);
         return this->NextFunctionCallSequenceNumber(metalMockedFunctionCallHistory);
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
         SixArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>::wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         SixArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>::wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         SixArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>::wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         SixArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>::wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::MetalMockAddRandomReturnValue();
         return randomReturnValue;
      }

      FunctionReturnType MetalMockItAndReturnValue(
         Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4, Arg5Type arg5, Arg6Type arg6)
      {
         SixArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, MetalMockExceptionThrower>::MetalMockIt(
            arg1, arg2, arg3, arg4, arg5, arg6);
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
         Arg1Type arg1,
         Arg2Type arg2,
         Arg3Type arg3,
         Arg4Type arg4,
         Arg5Type arg5,
         Arg6Type arg6)
      {
         const FunctionReturnType& returnValue = functionMocker->MetalMockItAndReturnValue(
            arg1, arg2, arg3, arg4, arg5, arg6);
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
         SixArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>::wasExpected = true;
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
         Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4, Arg5Type arg5, Arg6Type arg6)
      {
         functionMocker->MetalMockIt(arg1, arg2, arg3, arg4, arg5, arg6);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   bool operator==(
      const MetalMock::SevenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& expectedSevenArgumentFunctionCallReference,
      const MetalMock::SevenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& actualSevenArgumentFunctionCallReference)
   {
      try
      {
         ZenUnit::Equalizer<MetalMock::SevenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>::AssertEqual(
            expectedSevenArgumentFunctionCallReference, actualSevenArgumentFunctionCallReference);
      }
      catch (const ZenUnit::Anomaly&)
      {
         return false;
      }
      return true;
   }

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
      template<
         typename MetalMockObjectType,
         typename FreeFunctionMockObjectType,
         typename StaticFunctionMockObjectType>
      friend class MetalMock7ArgsTester;
      friend class SevenArgumentMetalMockerTests;
   public:
      std::vector<SevenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>> metalMockedFunctionCallHistory;

      explicit SevenArgumentMetalMocker(const std::string& metalMockedFunctionSignature)
         : MetalMocker<MockableExceptionThrowerType>(metalMockedFunctionSignature)
      {
      }

      void MetalMockIt(
         const Arg1Type& arg1,
         const Arg2Type& arg2,
         const Arg3Type& arg3,
         const Arg4Type& arg4,
         const Arg5Type& arg5,
         const Arg6Type& arg6,
         const Arg7Type& arg7)
      {
         this->MetalMockThrowIfNotExpected(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
         metalMockedFunctionCallHistory.emplace_back(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
         this->MetalMockThrowExceptionIfExceptionSet();
      }

      FunctionCallSequenceNumber CalledWith(
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2,
         const Arg3Type& expectedArg3,
         const Arg4Type& expectedArg4,
         const Arg5Type& expectedArg5,
         const Arg6Type& expectedArg6,
         const Arg7Type& expectedArg7)
      {
         this->MetalMockSetAsserted();
         const SevenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type> expectedSevenArgumentFunctionCall(expectedArg1, expectedArg2, expectedArg3, expectedArg4, expectedArg5, expectedArg6, expectedArg7);
         const std::vector<SevenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>> actualSevenArgumentFunctionCalls =
            MetalMocker<MockableExceptionThrowerType>::template ConvertMetalMockFunctionCallsToMetalMockFunctionCallReferences<
               SevenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>,
               SevenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>(this->metalMockedFunctionCallHistory);
         CONTAINS_ELEMENT(expectedSevenArgumentFunctionCall, actualSevenArgumentFunctionCalls, this->metalMockedFunctionSignature);
         return this->NextFunctionCallSequenceNumber(metalMockedFunctionCallHistory);
      }

      FunctionCallSequenceNumber CalledOnceWith(
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2,
         const Arg3Type& expectedArg3,
         const Arg4Type& expectedArg4,
         const Arg5Type& expectedArg5,
         const Arg6Type& expectedArg6,
         const Arg7Type& expectedArg7)
      {
         this->MetalMockSetAsserted();
         constexpr size_t expectedNumberOfFunctionCalls = 1;
         ARE_EQUAL(expectedNumberOfFunctionCalls, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature);
         ARE_EQUAL(expectedArg1, this->metalMockedFunctionCallHistory[0].arg1.value, this->metalMockedFunctionSignature);
         ARE_EQUAL(expectedArg2, this->metalMockedFunctionCallHistory[0].arg2.value, this->metalMockedFunctionSignature);
         ARE_EQUAL(expectedArg3, this->metalMockedFunctionCallHistory[0].arg3.value, this->metalMockedFunctionSignature);
         ARE_EQUAL(expectedArg4, this->metalMockedFunctionCallHistory[0].arg4.value, this->metalMockedFunctionSignature);
         ARE_EQUAL(expectedArg5, this->metalMockedFunctionCallHistory[0].arg5.value, this->metalMockedFunctionSignature);
         ARE_EQUAL(expectedArg6, this->metalMockedFunctionCallHistory[0].arg6.value, this->metalMockedFunctionSignature);
         ARE_EQUAL(expectedArg7, this->metalMockedFunctionCallHistory[0].arg7.value, this->metalMockedFunctionSignature);
         return this->NextFunctionCallSequenceNumber(metalMockedFunctionCallHistory);
      }

      void CalledNTimes(size_t expectedNumberOfFunctionCalls)
      {
         this->MetalMockThrowIfExpectedNumberOfFunctionCalls0(expectedNumberOfFunctionCalls);
         this->MetalMockSetAsserted();
         ARE_EQUAL(expectedNumberOfFunctionCalls, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature);
      }

      void CalledNTimesWith(
         size_t expectedNumberOfFunctionCalls,
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2,
         const Arg3Type& expectedArg3,
         const Arg4Type& expectedArg4,
         const Arg5Type& expectedArg5,
         const Arg6Type& expectedArg6,
         const Arg7Type& expectedArg7)
      {
         this->MetalMockThrowIfExpectedNumberOfFunctionCalls0(expectedNumberOfFunctionCalls);
         this->MetalMockSetAsserted();
         ARE_EQUAL(expectedNumberOfFunctionCalls, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfFunctionCalls; ++i)
         {
            const std::string metalMockedFunctionSignatureAndCallIndex = ZenUnit::String::ConcatValues(this->metalMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArg1, this->metalMockedFunctionCallHistory[i].arg1.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg2, this->metalMockedFunctionCallHistory[i].arg2.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg3, this->metalMockedFunctionCallHistory[i].arg3.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg4, this->metalMockedFunctionCallHistory[i].arg4.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg5, this->metalMockedFunctionCallHistory[i].arg5.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg6, this->metalMockedFunctionCallHistory[i].arg6.value, metalMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg7, this->metalMockedFunctionCallHistory[i].arg7.value, metalMockedFunctionSignatureAndCallIndex);
         }
      }

      FunctionCallSequenceNumber CalledAsFollows(
         const std::vector<SevenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>& expectedSevenArgumentFunctionCalls)
      {
         this->MetalMockThrowIfExpectedCallsSizeIsZero(expectedSevenArgumentFunctionCalls.size());
         this->MetalMockSetAsserted();
         const std::vector<SevenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>> actualSevenArgumentFunctionCalls =
            MetalMocker<MockableExceptionThrowerType>::template ConvertMetalMockFunctionCallsToMetalMockFunctionCallReferences<
               SevenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>,
               SevenArgumentFunctionCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>(this->metalMockedFunctionCallHistory);
         VECTORS_ARE_EQUAL(expectedSevenArgumentFunctionCalls, actualSevenArgumentFunctionCalls, this->metalMockedFunctionSignature);
         return this->NextFunctionCallSequenceNumber(metalMockedFunctionCallHistory);
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
         SevenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, MetalMockExceptionThrower>::wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValue(std::forward<ReturnType>(returnValue));
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ReturnValues(FirstReturnValue&& firstReturnValue, SubsequentReturnValues&&... subsequentReturnValues)
      {
         SevenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, MetalMockExceptionThrower>::wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddReturnValues(
            std::forward<FirstReturnValue>(firstReturnValue),
            std::forward<SubsequentReturnValues>(subsequentReturnValues)...);
      }

      template<typename ContainerType>
      void ReturnValues(ContainerType&& returnValues)
      {
         SevenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, MetalMockExceptionThrower>::wasExpected = true;
         ValueReturner<FunctionReturnType>::MetalMockAddContainerReturnValues(std::forward<ContainerType>(returnValues));
      }

      DecayedFunctionReturnType ReturnRandom()
      {
         SevenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, MetalMockExceptionThrower>::wasExpected = true;
         const DecayedFunctionReturnType randomReturnValue = ValueReturner<FunctionReturnType>::MetalMockAddRandomReturnValue();
         return randomReturnValue;
      }

      FunctionReturnType MetalMockItAndReturnValue(
         Arg1Type arg1,
         Arg2Type arg2,
         Arg3Type arg3,
         Arg4Type arg4,
         Arg5Type arg5,
         Arg6Type arg6,
         Arg7Type arg7)
      {
         SevenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>::MetalMockIt(
            arg1, arg2, arg3, arg4, arg5, arg6, arg7);
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
         Arg1Type arg1,
         Arg2Type arg2,
         Arg3Type arg3,
         Arg4Type arg4,
         Arg5Type arg5,
         Arg6Type arg6,
         Arg7Type arg7)
      {
         const FunctionReturnType& returnValue = functionMocker->MetalMockItAndReturnValue(
            arg1, arg2, arg3, arg4, arg5, arg6, arg7);
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
         SevenArgumentMetalMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, MetalMockExceptionThrower>::wasExpected = true;
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
         Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4, Arg5Type arg5, Arg6Type arg6, Arg7Type arg7)
      {
         functionMocker->MetalMockIt(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
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
         std::string metalMockedFunctionSignature = builder.str();
         return metalMockedFunctionSignature;
      }

      static std::string FunctionPointer(const char* returnType, const char* unadornedFunctionSignature)
      {
         std::string metalMockedFunctionPointerSignature = ZenUnit::String::ConcatStrings(returnType, " ", unadornedFunctionSignature);
         return metalMockedFunctionPointerSignature;
      }
   };
}

namespace ZenUnit
{
   template<>
   class Equalizer<MetalMock::FunctionCallSequenceNumber>
   {
   public:
      static void AssertEqual(
         const MetalMock::FunctionCallSequenceNumber& expectedFunctionCallSequenceNumber,
         const MetalMock::FunctionCallSequenceNumber& actualFunctionCallSequenceNumber)
      {
         ARE_EQUAL(expectedFunctionCallSequenceNumber.value, actualFunctionCallSequenceNumber.value);
      }
   };

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
         ARE_EQUAL(expectedTwoArgumentFunctionCall.arg1.value, actualTwoArgumentFunctionCall.arg1.value);
         ARE_EQUAL(expectedTwoArgumentFunctionCall.arg2.value, actualTwoArgumentFunctionCall.arg2.value);
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
         ARE_EQUAL(expectedTwoArgumentFunctionCall.arg1Reference.value, actualTwoArgumentFunctionCall.arg1Reference.value);
         ARE_EQUAL(expectedTwoArgumentFunctionCall.arg2Reference.value, actualTwoArgumentFunctionCall.arg2Reference.value);
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
         ARE_EQUAL(expectedThreeArgumentFunctionCall.arg1.value, actualThreeArgumentFunctionCall.arg1.value);
         ARE_EQUAL(expectedThreeArgumentFunctionCall.arg2.value, actualThreeArgumentFunctionCall.arg2.value);
         ARE_EQUAL(expectedThreeArgumentFunctionCall.arg3.value, actualThreeArgumentFunctionCall.arg3.value);
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
         ARE_EQUAL(expectedThreeArgumentFunctionCall.arg1Reference.value, actualThreeArgumentFunctionCall.arg1Reference.value);
         ARE_EQUAL(expectedThreeArgumentFunctionCall.arg2Reference.value, actualThreeArgumentFunctionCall.arg2Reference.value);
         ARE_EQUAL(expectedThreeArgumentFunctionCall.arg3Reference.value, actualThreeArgumentFunctionCall.arg3Reference.value);
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
         ARE_EQUAL(expectedFourArgumentFunctionCall.arg1.value, actualFourArgumentFunctionCall.arg1.value);
         ARE_EQUAL(expectedFourArgumentFunctionCall.arg2.value, actualFourArgumentFunctionCall.arg2.value);
         ARE_EQUAL(expectedFourArgumentFunctionCall.arg3.value, actualFourArgumentFunctionCall.arg3.value);
         ARE_EQUAL(expectedFourArgumentFunctionCall.arg4.value, actualFourArgumentFunctionCall.arg4.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class Equalizer<MetalMock::FourArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
   {
   public:
      static void AssertEqual(
         const MetalMock::FourArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& expectedFourArgumentFunctionCall,
         const MetalMock::FourArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& actualFourArgumentFunctionCall)
      {
         ARE_EQUAL(expectedFourArgumentFunctionCall.arg1Reference.value, actualFourArgumentFunctionCall.arg1Reference.value);
         ARE_EQUAL(expectedFourArgumentFunctionCall.arg2Reference.value, actualFourArgumentFunctionCall.arg2Reference.value);
         ARE_EQUAL(expectedFourArgumentFunctionCall.arg3Reference.value, actualFourArgumentFunctionCall.arg3Reference.value);
         ARE_EQUAL(expectedFourArgumentFunctionCall.arg4Reference.value, actualFourArgumentFunctionCall.arg4Reference.value);
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
         ARE_EQUAL(expectedFiveArgumentFunctionCall.arg1.value, actualFiveArgumentFunctionCall.arg1.value);
         ARE_EQUAL(expectedFiveArgumentFunctionCall.arg2.value, actualFiveArgumentFunctionCall.arg2.value);
         ARE_EQUAL(expectedFiveArgumentFunctionCall.arg3.value, actualFiveArgumentFunctionCall.arg3.value);
         ARE_EQUAL(expectedFiveArgumentFunctionCall.arg4.value, actualFiveArgumentFunctionCall.arg4.value);
         ARE_EQUAL(expectedFiveArgumentFunctionCall.arg5.value, actualFiveArgumentFunctionCall.arg5.value);
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
         ARE_EQUAL(expectedFiveArgumentFunctionCall.arg1Reference.value, actualFiveArgumentFunctionCall.arg1Reference.value);
         ARE_EQUAL(expectedFiveArgumentFunctionCall.arg2Reference.value, actualFiveArgumentFunctionCall.arg2Reference.value);
         ARE_EQUAL(expectedFiveArgumentFunctionCall.arg3Reference.value, actualFiveArgumentFunctionCall.arg3Reference.value);
         ARE_EQUAL(expectedFiveArgumentFunctionCall.arg4Reference.value, actualFiveArgumentFunctionCall.arg4Reference.value);
         ARE_EQUAL(expectedFiveArgumentFunctionCall.arg5Reference.value, actualFiveArgumentFunctionCall.arg5Reference.value);
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
         ARE_EQUAL(expectedSixArgumentFunctionCall.arg1.value, actualSixArgumentFunctionCall.arg1.value);
         ARE_EQUAL(expectedSixArgumentFunctionCall.arg2.value, actualSixArgumentFunctionCall.arg2.value);
         ARE_EQUAL(expectedSixArgumentFunctionCall.arg3.value, actualSixArgumentFunctionCall.arg3.value);
         ARE_EQUAL(expectedSixArgumentFunctionCall.arg4.value, actualSixArgumentFunctionCall.arg4.value);
         ARE_EQUAL(expectedSixArgumentFunctionCall.arg5.value, actualSixArgumentFunctionCall.arg5.value);
         ARE_EQUAL(expectedSixArgumentFunctionCall.arg6.value, actualSixArgumentFunctionCall.arg6.value);
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
         ARE_EQUAL(expectedSixArgumentFunctionCall.arg1Reference.value, actualSixArgumentFunctionCall.arg1Reference.value);
         ARE_EQUAL(expectedSixArgumentFunctionCall.arg2Reference.value, actualSixArgumentFunctionCall.arg2Reference.value);
         ARE_EQUAL(expectedSixArgumentFunctionCall.arg3Reference.value, actualSixArgumentFunctionCall.arg3Reference.value);
         ARE_EQUAL(expectedSixArgumentFunctionCall.arg4Reference.value, actualSixArgumentFunctionCall.arg4Reference.value);
         ARE_EQUAL(expectedSixArgumentFunctionCall.arg5Reference.value, actualSixArgumentFunctionCall.arg5Reference.value);
         ARE_EQUAL(expectedSixArgumentFunctionCall.arg6Reference.value, actualSixArgumentFunctionCall.arg6Reference.value);
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
         ARE_EQUAL(expectedSevenArgumentFunctionCall.arg1.value, actualSevenArgumentFunctionCall.arg1.value);
         ARE_EQUAL(expectedSevenArgumentFunctionCall.arg2.value, actualSevenArgumentFunctionCall.arg2.value);
         ARE_EQUAL(expectedSevenArgumentFunctionCall.arg3.value, actualSevenArgumentFunctionCall.arg3.value);
         ARE_EQUAL(expectedSevenArgumentFunctionCall.arg4.value, actualSevenArgumentFunctionCall.arg4.value);
         ARE_EQUAL(expectedSevenArgumentFunctionCall.arg5.value, actualSevenArgumentFunctionCall.arg5.value);
         ARE_EQUAL(expectedSevenArgumentFunctionCall.arg6.value, actualSevenArgumentFunctionCall.arg6.value);
         ARE_EQUAL(expectedSevenArgumentFunctionCall.arg7.value, actualSevenArgumentFunctionCall.arg7.value);
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
         ARE_EQUAL(expectedSevenArgumentFunctionCall.arg1Reference.value, actualSevenArgumentFunctionCall.arg1Reference.value);
         ARE_EQUAL(expectedSevenArgumentFunctionCall.arg2Reference.value, actualSevenArgumentFunctionCall.arg2Reference.value);
         ARE_EQUAL(expectedSevenArgumentFunctionCall.arg3Reference.value, actualSevenArgumentFunctionCall.arg3Reference.value);
         ARE_EQUAL(expectedSevenArgumentFunctionCall.arg4Reference.value, actualSevenArgumentFunctionCall.arg4Reference.value);
         ARE_EQUAL(expectedSevenArgumentFunctionCall.arg5Reference.value, actualSevenArgumentFunctionCall.arg5Reference.value);
         ARE_EQUAL(expectedSevenArgumentFunctionCall.arg6Reference.value, actualSevenArgumentFunctionCall.arg6Reference.value);
         ARE_EQUAL(expectedSevenArgumentFunctionCall.arg7Reference.value, actualSevenArgumentFunctionCall.arg7Reference.value);
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
         // One line because when line-breaked, Codecov.io incorrectly reports this line as uncovered
         os << "MetalMock::TwoArgumentFunctionCall:\n" "Argument1: " << ZenUnit::ToStringer::ToString(twoArgumentFunctionCallRef.arg1Reference.value) << '\n' << "Argument2: " << ZenUnit::ToStringer::ToString(twoArgumentFunctionCallRef.arg2Reference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class Printer<MetalMock::ThreeArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type>>
   {
   public:
      static void Print(std::ostream& os, const MetalMock::ThreeArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type>& threeArgumentFunctionCallRef)
      {
         os << "MetalMock::ThreeArgumentFunctionCall:\n"
               "Argument1: " << ZenUnit::ToStringer::ToString(threeArgumentFunctionCallRef.arg1Reference.value) << '\n' <<
               "Argument2: " << ZenUnit::ToStringer::ToString(threeArgumentFunctionCallRef.arg2Reference.value) << '\n' <<
               "Argument3: " << ZenUnit::ToStringer::ToString(threeArgumentFunctionCallRef.arg3Reference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class Printer<MetalMock::FourArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
   {
   public:
      static void Print(std::ostream& os, const MetalMock::FourArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& fourArgumentFunctionCallRef)
      {
         os << "MetalMock::FourArgumentFunctionCall:\n"
               "Argument1: " << ZenUnit::ToStringer::ToString(fourArgumentFunctionCallRef.arg1Reference.value) << '\n' <<
               "Argument2: " << ZenUnit::ToStringer::ToString(fourArgumentFunctionCallRef.arg2Reference.value) << '\n' <<
               "Argument3: " << ZenUnit::ToStringer::ToString(fourArgumentFunctionCallRef.arg3Reference.value) << '\n' <<
               "Argument4: " << ZenUnit::ToStringer::ToString(fourArgumentFunctionCallRef.arg4Reference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   class Printer<MetalMock::FiveArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
   {
   public:
      static void Print(std::ostream& os, const MetalMock::FiveArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& fiveArgumentFunctionCallRef)
      {
         os << "MetalMock::FiveArgumentFunctionCall:\n"
               "Argument1: " << ZenUnit::ToStringer::ToString(fiveArgumentFunctionCallRef.arg1Reference.value) << '\n' <<
               "Argument2: " << ZenUnit::ToStringer::ToString(fiveArgumentFunctionCallRef.arg2Reference.value) << '\n' <<
               "Argument3: " << ZenUnit::ToStringer::ToString(fiveArgumentFunctionCallRef.arg3Reference.value) << '\n' <<
               "Argument4: " << ZenUnit::ToStringer::ToString(fiveArgumentFunctionCallRef.arg4Reference.value) << '\n' <<
               "Argument5: " << ZenUnit::ToStringer::ToString(fiveArgumentFunctionCallRef.arg5Reference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   class Printer<MetalMock::SixArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
   {
   public:
      static void Print(std::ostream& os, const MetalMock::SixArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& sixArgumentFunctionCallRef)
      {
         os << "MetalMock::SixArgumentFunctionCall:\n"
               "Argument1: " << ZenUnit::ToStringer::ToString(sixArgumentFunctionCallRef.arg1Reference.value) << '\n' <<
               "Argument2: " << ZenUnit::ToStringer::ToString(sixArgumentFunctionCallRef.arg2Reference.value) << '\n' <<
               "Argument3: " << ZenUnit::ToStringer::ToString(sixArgumentFunctionCallRef.arg3Reference.value) << '\n' <<
               "Argument4: " << ZenUnit::ToStringer::ToString(sixArgumentFunctionCallRef.arg4Reference.value) << '\n' <<
               "Argument5: " << ZenUnit::ToStringer::ToString(sixArgumentFunctionCallRef.arg5Reference.value) << '\n' <<
               "Argument6: " << ZenUnit::ToStringer::ToString(sixArgumentFunctionCallRef.arg6Reference.value);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   class Printer<MetalMock::SevenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
   {
   public:
      static void Print(std::ostream& os, const MetalMock::SevenArgumentFunctionCallReferences<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& sevenArgumentFunctionCallRef)
      {
         os << "MetalMock::SevenArgumentFunctionCall:\n"
               "Argument1: " << ZenUnit::ToStringer::ToString(sevenArgumentFunctionCallRef.arg1Reference.value) << '\n' <<
               "Argument2: " << ZenUnit::ToStringer::ToString(sevenArgumentFunctionCallRef.arg2Reference.value) << '\n' <<
               "Argument3: " << ZenUnit::ToStringer::ToString(sevenArgumentFunctionCallRef.arg3Reference.value) << '\n' <<
               "Argument4: " << ZenUnit::ToStringer::ToString(sevenArgumentFunctionCallRef.arg4Reference.value) << '\n' <<
               "Argument5: " << ZenUnit::ToStringer::ToString(sevenArgumentFunctionCallRef.arg5Reference.value) << '\n' <<
               "Argument6: " << ZenUnit::ToStringer::ToString(sevenArgumentFunctionCallRef.arg6Reference.value) << '\n' <<
               "Argument7: " << ZenUnit::ToStringer::ToString(sevenArgumentFunctionCallRef.arg7Reference.value);
      }
   };
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
      METALMOCK_NONVOID2_CONST(int, IntBetween, int, int)
      METALMOCK_NONVOID0_CONST(unsigned int, UnsignedInt)

      METALMOCK_NONVOID1_CONST(int, Enum, int)

      METALMOCK_NONVOID0_CONST(long long, LongLong)
      METALMOCK_NONVOID0_CONST(unsigned long long, UnsignedLongLong)
      METALMOCK_NONVOID0_CONST(size_t, SizeT)
      METALMOCK_NONVOID2_CONST(size_t, SizeTBetween, size_t, size_t)

      METALMOCK_NONVOID0_CONST(float, Float)
      METALMOCK_NONVOID2_CONST(float, FloatBetween, float, float)
      METALMOCK_NONVOID0_CONST(std::vector<float>, FloatVector)

      METALMOCK_NONVOID0_CONST(double, Double)
      METALMOCK_NONVOID2_CONST(double, DoubleBetween, double, double)
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
