#pragma once

#include "ZenUnit/ZenUnit.h"
#include <deque>

#if defined _WIN32
#pragma warning(push)
#pragma warning(disable: 4514) // 'ZenMock::Signature::Function': unreferenced inline function has been removed
#pragma warning(disable: 4625) // 'ZenMock::VoidZeroArgumentMocker': copy constructor was implicitly defined as deleted	ZenUnit
#pragma warning(disable: 4626) // 'ZenMock::VoidZeroArgumentMocker': assignment operator was implicitly defined as deleted
#pragma warning(disable: 4820) // 'ZenMock::ZenMocker<MockableExceptionThrowerType>': '5' bytes padding added after data member 'ZenMock::ZenMocker<MockableExceptionThrowerType>::_asserted'
#pragma warning(disable: 5026) // 'ZenMock::VoidZeroArgumentMocker': move constructor was implicitly defined as deleted
#pragma warning(disable: 5027) // 'ZenMock::VoidZeroArgumentMocker': move assignment operator was implicitly defined as deleted
#endif

namespace ZenMock
{
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

   class FunctionAlreadyExpectedException : public ZenUnit::ZenMockException
   {
   private:
      const std::string _what;
   public:
      explicit FunctionAlreadyExpectedException(const std::string& zenMockedFunctionSignature)
         : _what(MakeWhat(zenMockedFunctionSignature))
      {
      }

      virtual ~FunctionAlreadyExpectedException() = default;

      static std::string MakeWhat(const std::string& zenMockedFunctionSignature)
      {
         const std::string what = "For ZenMocked function \"" + zenMockedFunctionSignature + R"(":
Already called [FunctionName]Mock.[Expect|Return|ReturnValues|Throw]().)";
         return what;
      }

      const char* what() const noexcept override
      {
         return _what.c_str();
      }
   };

   class UnexpectedCallException : public ZenUnit::ZenMockException
   {
   private:
      const std::string _what;
   public:
      template<typename... ArgTypes>
      explicit UnexpectedCallException(
         const std::string& zenMockedFunctionSignature, ArgTypes&&... args)
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
      static void AppendToStringedArgs(
         std::ostringstream& outWhatBuilder,
         size_t argIndex,
         ArgType&& arg,
         SubsequentArgTypes&&... args)
      {
         const std::string toStringedArg = ZenUnit::ToStringer::ToString(std::forward<ArgType>(arg));
         outWhatBuilder << "\nArgument" << ++argIndex << ": " << toStringedArg;
         AppendToStringedArgs(outWhatBuilder, argIndex, std::forward<SubsequentArgTypes>(args)...);
      }

      static void AppendToStringedArgs(std::ostringstream&, size_t)
      {
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
ZenMock objects by design do not support asserting that
their corresponding ZenMocked functions were called zero times.
To assert that a ZenMocked function was called zero times,
simply do not call Expect(), Return(), or Throw() on a ZenMock object.)");
         return what;
      }

      const char* what() const noexcept override
      {
         return _what.c_str();
      }
   };

#define ZEN(ZenMockAssertStatement) \
try \
{ \
   ZenMockAssertStatement; \
} \
catch (const ZenUnit::Anomaly& zenWrappedAnomaly) \
{ \
   throw ZenUnit::Anomaly::ZENWrapped( \
      "ZEN("#ZenMockAssertStatement")", zenWrappedAnomaly, FILELINE); \
}

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

   template<typename FunctionReturnType>
   class ValueReturner
   {
      friend class ValueReturnerTests;
   public:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   private:
      const std::string _zenMockedFunctionSignature;
      // deque here instead of vector due to implementation of vector<bool>
      std::deque<DecayedFunctionReturnType> _returnValues;
      size_t _returnValueIndex;
   protected:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
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
            throw std::invalid_argument(
               "ZenMock::ValueReturner::ZenMockAddContainerReturnValues(): Return values container cannot be empty.");
         }
         _returnValues.insert(_returnValues.end(), returnValues.cbegin(), returnValues.cend());
      }

      DecayedFunctionReturnType ZenMockAddRandomReturnValue()
      {
         const DecayedFunctionReturnType randomReturnValue = ZenUnit::Random<DecayedFunctionReturnType>();
         _returnValues.emplace_back(randomReturnValue);
         return randomReturnValue;
      }

      const DecayedFunctionReturnType& ZenMockNextReturnValue()
      {
         if (_returnValues.empty())
         {
            throw ZenMock::ReturnValueMustBeSpecifiedException(_zenMockedFunctionSignature);
         }
         const DecayedFunctionReturnType& nextReturnValue =
            _returnValueIndex < _returnValues.size() ? _returnValues[_returnValueIndex++] : _returnValues.back();
         return nextReturnValue;
      }
   };

   struct ZENAssertionToken
   {
      [[nodiscard]]
      static ZENAssertionToken NoDiscard()
      {
         return ZENAssertionToken();
      }
   };

   template<typename MockableExceptionThrowerType>
   class ZenMocker
   {
      friend class ZenMockerTests;
   private:
      std::function<void(int)> call_exit;
      std::function<ZenUnit::ZenUnitArgs()> call_TestRunner_GetArgs;
      bool _zenMockExceptionIsInFlight;
   protected:
      bool _expected;
      bool _asserted;
      const std::string ZenMockedFunctionSignature;
      MockableExceptionThrowerType _exceptionThrower;
   public:
      explicit ZenMocker(std::string zenMockedFunctionSignature)
         : call_exit(::exit)
         , call_TestRunner_GetArgs(ZenUnit::TestRunner::GetArgs)
         , _zenMockExceptionIsInFlight(false)
         , _expected(false)
         , _asserted(false)
         , ZenMockedFunctionSignature(std::move(zenMockedFunctionSignature))
      {
      }

      //ZenMocker(const ZenMocker&) = delete;
      ZenMocker& operator=(const ZenMocker&) = delete;
      //ZenMocker(ZenMocker&&) = delete;
      //ZenMocker& operator=(ZenMocker&&) = delete;

      template<typename ExceptionType, typename... ExceptionArgTypes>
      void Throw(ExceptionArgTypes&&... exceptionArgs)
      {
         if (_expected)
         {
            _zenMockExceptionIsInFlight = true;
            throw FunctionAlreadyExpectedException(ZenMockedFunctionSignature);
         }
         _exceptionThrower.template Throw<ExceptionType>(
            std::forward<ExceptionArgTypes>(exceptionArgs)...);
         _expected = true;
      }

      ~ZenMocker()
      {
         ZenMockExitIfExpectedButNotAsserted();
      }

   protected:
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
============================================
Expected-But-Not-Asserted ZenMocked Function
============================================)", ZenUnit::Color::Red);
            console.WriteLineColor(ZenMockedFunctionSignature, ZenUnit::Color::Teal);
            console.WriteLine(R"(
Fix for this: Add a call to one of the following ZenMock assert statements:
CalledOnce(), CalledOnceWith(), CalledNTimes(), CalledNTimesWith(), or CalledAsFollows().
)");
            const ZenUnit::ZenUnitArgs& zenUnitArgs = call_TestRunner_GetArgs();
            const int exitCode = zenUnitArgs.exit0 ? 0 : 1;
            call_exit(exitCode);
         }
      }
   };

#define ZENMOCK_BIND0(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::ZenMockItFunctionPointer, &(FunctionName_ZenMock))

#define ZENMOCK_BIND1(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::ZenMockItFunctionPointer, &(FunctionName_ZenMock), \
   std::placeholders::_1)

#define ZENMOCK_BIND2(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::ZenMockItFunctionPointer, &(FunctionName_ZenMock), \
   std::placeholders::_1, std::placeholders::_2)

#define ZENMOCK_BIND3(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::ZenMockItFunctionPointer, &(FunctionName_ZenMock), \
   std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)

#define ZENMOCK_BIND4(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::ZenMockItFunctionPointer, &(FunctionName_ZenMock), \
   std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)

#define ZENMOCK_BIND5(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::ZenMockItFunctionPointer, &(FunctionName_ZenMock), \
   std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, \
   std::placeholders::_5)

#define ZENMOCK_BIND6(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::ZenMockItFunctionPointer, &(FunctionName_ZenMock), \
   std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, \
   std::placeholders::_5, std::placeholders::_6)

#define ZENMOCK_BIND7(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::ZenMockItFunctionPointer, &(FunctionName_ZenMock), \
   std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, \
   std::placeholders::_5, std::placeholders::_6, std::placeholders::_7)

#define ZENMOCK_BIND8(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::ZenMockItFunctionPointer, &(FunctionName_ZenMock), \
   std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, \
   std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8)

#define ZENMOCK_BIND9(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::ZenMockItFunctionPointer, &(FunctionName_ZenMock), \
   std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, \
   std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, \
   std::placeholders::_9)

#define ZENMOCK_BIND10(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::ZenMockItFunctionPointer, &(FunctionName_ZenMock), \
   std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, \
   std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, \
   std::placeholders::_9, std::placeholders::_10)

   class ZeroArgumentMockerTests;

   template<typename MockableExceptionThrowerType = ExceptionThrower>
   class ZeroArgumentMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class ZeroArgumentMockerTests;
   private:
      size_t actualNumberOfCalls;
   public:
      explicit ZeroArgumentMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
         , actualNumberOfCalls(0)
      {
      }

      void ZenMockIt()
      {
         this->ZenMockThrowIfNotExpected();
         ++actualNumberOfCalls;
         this->ZenMockThrowIfExceptionSet();
      }

      ZENAssertionToken CalledOnce()
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->ZenMockedFunctionSignature);
         return ZENAssertionToken::NoDiscard();
      }

      ZENAssertionToken CalledNTimes(size_t expectedNumberOfCalls)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->ZenMockedFunctionSignature);
         return ZENAssertionToken::NoDiscard();
      }
   };

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName()".
#define ZENMOCK_NONVOID0(returnType, functionName) \
        ZENMOCK_NONVOID0_DEFINED(returnType, functionName, virtual,      ,        , final)

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName() const".
#define ZENMOCK_NONVOID0_CONST(returnType, functionName) \
        ZENMOCK_NONVOID0_DEFINED(returnType, functionName, virtual, const, mutable, final)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName()".
#define ZENMOCK_NONVOID0_NONVIRTUAL(returnType, functionName) \
        ZENMOCK_NONVOID0_DEFINED(returnType, functionName,        ,      ,        ,         )

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName() const".
#define ZENMOCK_NONVOID0_NONVIRTUAL_CONST(returnType, functionName) \
        ZENMOCK_NONVOID0_DEFINED(returnType, functionName,        , const, mutable,         )

// Defines a <functionName>_ZenMock object for mocking a free function with signature "returnType functionName()".
#define ZENMOCK_NONVOID0_FREE(returnType, functionName) \
   ZenMock::NonVoidZeroArgFunctionPointerMocker<returnType> functionName##_ZenMock = \
      ZenMock::NonVoidZeroArgFunctionPointerMocker<returnType>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"()"));

// Defines a <functionName>_ZenMock object for mocking a static or namespaced function with signature "returnType qualifiedClassNameOrNamespace::functionName()".
#define ZENMOCK_NONVOID0_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, ...) \
   ZenMock::NonVoidZeroArgFunctionPointerMocker<returnType> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidZeroArgFunctionPointerMocker<returnType>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"()"));

#define ZENMOCK_NONVOID0_DEFINED(returnType, functionName, virtualness, constness, mutableness, finalness) \
returnType functionName() constness finalness \
{ \
   return functionName##Mock.ZenMockItAndReturnValue(); \
} \
struct ZenMock_##functionName : public ZenMock::NonVoidZeroArgumentMocker<returnType> \
{ \
   explicit ZenMock_##functionName(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidZeroArgumentMocker<returnType>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"()", #constness)) {} \
} mutableness functionName##Mock = ZenMock_##functionName(this->ZenMockedClassName());

   template<typename FunctionReturnType>
   class NonVoidZeroArgumentMocker : public ZeroArgumentMocker<ExceptionThrower>, protected ValueReturner<FunctionReturnType>
   {
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

      template<typename ReturnType, typename... ReturnTypes>
      void ReturnValues(ReturnType&& firstReturnValue, ReturnTypes&&... subsequentReturnValues)
      {
         ZeroArgumentMocker<ExceptionThrower>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(
            std::forward<ReturnType>(firstReturnValue),
            std::forward<ReturnTypes>(subsequentReturnValues)...);
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

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual void functionName()".
#define ZENMOCK_VOID0(functionName) \
        ZENMOCK_VOID0_DEFINED(functionName, virtual,      ,        , final)

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual void functionName() const".
#define ZENMOCK_VOID0_CONST(functionName) \
        ZENMOCK_VOID0_DEFINED(functionName, virtual, const, mutable, final)

// Defines a <functionName>Mock object for mocking a base class function with signature "void functionName()".
#define ZENMOCK_VOID0_NONVIRTUAL(functionName) \
        ZENMOCK_VOID0_DEFINED(functionName,        ,        ,      ,         )

// Defines a <functionName>Mock object for mocking a base class function with signature "void functionName() const".
#define ZENMOCK_VOID0_NONVIRTUAL_CONST(functionName) \
        ZENMOCK_VOID0_DEFINED(functionName,        , const, mutable,         )

// Defines a <functionName>_ZenMock object for mocking a free function with signature "void functionName()".
#define ZENMOCK_VOID0_FREE(functionName) \
   ZenMock::VoidZeroArgFunctionPointerMocker functionName##_ZenMock = \
      ZenMock::VoidZeroArgFunctionPointerMocker(ZenMock::Signature::FunctionPointer("void", "::"#functionName"()"));

// Defines a <functionName>_ZenMock object for mocking a static or namespaced function with signature "void qualifiedClassNameOrNamespace::functionName()".
#define ZENMOCK_VOID0_STATIC(qualifiedClassNameOrNamespace, functionName, ...) \
   ZenMock::VoidZeroArgFunctionPointerMocker functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidZeroArgFunctionPointerMocker( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"()"));

#define ZENMOCK_VOID0_DEFINED(functionName, virtualness, constness, mutableness, finalness) \
void functionName() constness finalness \
{ \
   functionName##Mock.ZenMockIt(); \
} \
struct ZenMock_##functionName : public ZenMock::VoidZeroArgumentMocker \
{ \
   explicit ZenMock_##functionName(const std::string* zenMockedClassName) \
      : ZenMock::VoidZeroArgumentMocker(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"()", #constness)) {} \
} mutableness functionName##Mock = ZenMock_##functionName(this->ZenMockedClassName());

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

   template<typename Arg1Type>
   struct OneArgumentCall
   {
      typename std::decay<Arg1Type>::type argument;

      OneArgumentCall()
         : argument()
      {
      }

      OneArgumentCall(const Arg1Type& argument)
         : argument(argument)
      {
      }
   };

   template<typename ArgType>
   struct OneArgumentCallRef
   {
      const ArgType& argument;

      OneArgumentCallRef(const ArgType& argument)
         : argument(argument)
      {
      }

      explicit OneArgumentCallRef(const OneArgumentCall<ArgType>& oneArgumentCall)
         : argument(oneArgumentCall.argument)
      {
      }
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
      std::vector<OneArgumentCall<ArgType>> callHistory;
   public:
      explicit OneArgumentMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(const ArgType& argument)
      {
         this->ZenMockThrowIfNotExpected(argument);
         callHistory.emplace_back(argument);
         this->ZenMockThrowIfExceptionSet();
      }

      ZENAssertionToken CalledOnceWith(const ArgType& expectedArgument)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument, callHistory[0].argument, this->ZenMockedFunctionSignature);
         return ZENAssertionToken::NoDiscard();
      }

      ZENAssertionToken CalledNTimesWith(size_t expectedNumberOfCalls, const ArgType& expectedArgument)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex =
               ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArgument, callHistory[i].argument, zenMockedFunctionSignatureAndCallIndex);
         }
         return ZENAssertionToken::NoDiscard();
      }

      ZENAssertionToken CalledAsFollows(const std::vector<OneArgumentCallRef<ArgType>>& expectedOneArgumentCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedOneArgumentCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<OneArgumentCallRef<ArgType>>
            actualOneArgumentCalls = PrivateCallsToCallRefs(callHistory);
         VECTORS_EQUAL(expectedOneArgumentCalls, actualOneArgumentCalls, this->ZenMockedFunctionSignature);
         return ZENAssertionToken::NoDiscard();
      }
   private:
      static std::vector<OneArgumentCallRef<ArgType>>
         PrivateCallsToCallRefs(const std::vector<OneArgumentCall<ArgType>>& callHistory)
      {
         std::vector<OneArgumentCallRef<ArgType>> oneArgumentCallRefs;
         oneArgumentCallRefs.reserve(callHistory.size());
         std::for_each(callHistory.cbegin(), callHistory.cend(),
            [&](const OneArgumentCall<ArgType>& oneArgumentCall)
         {
            oneArgumentCallRefs.emplace_back(oneArgumentCall);
         });
         return oneArgumentCallRefs;
      }
   };

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type)".
#define ZENMOCK_NONVOID1(returnType, functionName, arg1Type, ...) \
        ZENMOCK_NONVOID1_DEFINED(returnType, functionName, arg1Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type) const".
#define ZENMOCK_NONVOID1_CONST(returnType, functionName, arg1Type, ...) \
        ZENMOCK_NONVOID1_DEFINED(returnType, functionName, arg1Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type)".
#define ZENMOCK_NONVOID1_NONVIRTUAL(returnType, functionName, arg1Type, ...) \
        ZENMOCK_NONVOID1_DEFINED(returnType, functionName, arg1Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type) const".
#define ZENMOCK_NONVOID1_NONVIRTUAL_CONST(returnType, functionName, arg1Type, ...) \
        ZENMOCK_NONVOID1_DEFINED(returnType, functionName, arg1Type,        , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "returnType functionName(arg1Type)".
#define ZENMOCK_NONVOID1_FREE(returnType, functionName, arg1Type, ...) \
   ZenMock::NonVoidOneArgFunctionPointerMocker<returnType, arg1Type> \
      functionName##_ZenMock##__VA_ARGS__ = ZenMock::NonVoidOneArgFunctionPointerMocker<returnType, arg1Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type")"));

// Defines a functionName_ZenMock object for mocking a static or namespaced function with signature "returnType qualifiedClassNameOrNamespace::functionName(arg1Type)".
#define ZENMOCK_NONVOID1_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, ...) \
   ZenMock::NonVoidOneArgFunctionPointerMocker<returnType, arg1Type> \
      functionName##_ZenMock##__VA_ARGS__ = ZenMock::NonVoidOneArgFunctionPointerMocker<returnType, arg1Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type")"));

#define ZENMOCK_NONVOID1_DEFINED(returnType, functionName, arg1Type, virtualness, constness, mutableness, finalness, ...) \
returnType functionName(arg1Type arg) constness finalness \
{ \
   return functionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(arg); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidOneArgumentMocker<returnType, arg1Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidOneArgumentMocker<returnType, arg1Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

   template<typename FunctionReturnType, typename ArgType>
   class NonVoidOneArgumentMocker : public OneArgumentMocker<ArgType>, protected ValueReturner<FunctionReturnType>
   {
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

      template<typename ReturnValueURef, typename... ReturnValueURefs>
      void ReturnValues(ReturnValueURef&& firstReturnValue, ReturnValueURefs&&... subsequentReturnValues)
      {
         OneArgumentMocker<ArgType>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(
            std::forward<ReturnValueURef>(firstReturnValue),
            std::forward<ReturnValueURef>(subsequentReturnValues)...);
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

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual void functionName(arg1Type)".
#define ZENMOCK_VOID1(functionName, arg1Type, ...) \
        ZENMOCK_VOID1_DEFINED(functionName, arg1Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual void functionName(arg1Type) const".
#define ZENMOCK_VOID1_CONST(functionName, arg1Type, ...) \
        ZENMOCK_VOID1_DEFINED(functionName, arg1Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "void functionName(arg1Type)".
#define ZENMOCK_VOID1_NONVIRTUAL(functionName, arg1Type, ...) \
        ZENMOCK_VOID1_DEFINED(functionName, arg1Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "void functionName(arg1Type) const".
#define ZENMOCK_VOID1_NONVIRTUAL_CONST(functionName, arg1Type, ...) \
        ZENMOCK_VOID1_DEFINED(functionName, arg1Type,        , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "void functionName(arg1Type)".
#define ZENMOCK_VOID1_FREE(functionName, arg1Type, ...) \
   ZenMock::VoidOneArgFunctionPointerMocker<arg1Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidOneArgFunctionPointerMocker<arg1Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#functionName"("#arg1Type")"));

// Defines a <functionName>_ZenMock object for mocking a static or namespaced function with signature "void qualifiedClassNameOrNamespace::functionName(arg1Type)".
#define ZENMOCK_VOID1_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, ...) \
   ZenMock::VoidOneArgFunctionPointerMocker<arg1Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidOneArgFunctionPointerMocker<arg1Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type")"));

#define ZENMOCK_VOID1_DEFINED(functionName, arg1Type, virtualness, constness, mutableness, finalness, ...) \
void functionName(arg1Type arg) constness finalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(arg); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::VoidOneArgumentMocker<arg1Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidOneArgumentMocker<arg1Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

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

   template<typename Arg1Type, typename Arg2Type>
   struct TwoArgumentCall
   {
      typename std::decay<Arg1Type>::type firstArgument;
      typename std::decay<Arg2Type>::type secondArgument;

      TwoArgumentCall()
         : firstArgument()
         , secondArgument()
      {
      }

      TwoArgumentCall(const Arg1Type& firstArgument, const Arg2Type& secondArgument)
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
      {
      }
   };

   template<typename Arg1Type, typename Arg2Type>
   struct TwoArgumentCallRef
   {
      const Arg1Type& firstArgument;
      const Arg2Type& secondArgument;

      TwoArgumentCallRef(const Arg1Type& firstArgument, const Arg2Type& secondArgument)
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
      {
      }

      explicit TwoArgumentCallRef(const TwoArgumentCall<Arg1Type, Arg2Type>& twoArgumentCall)
         : firstArgument(twoArgumentCall.firstArgument)
         , secondArgument(twoArgumentCall.secondArgument)
      {
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
      std::vector<TwoArgumentCall<Arg1Type, Arg2Type>> callHistory;
   public:
      explicit TwoArgumentMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(const Arg1Type& firstArgument, const Arg2Type& secondArgument)
      {
         this->ZenMockThrowIfNotExpected(firstArgument, secondArgument);
         callHistory.emplace_back(firstArgument, secondArgument);
         this->ZenMockThrowIfExceptionSet();
      }

      ZENAssertionToken CalledOnceWith(
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, callHistory[0].firstArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, callHistory[0].secondArgument, this->ZenMockedFunctionSignature);
         return ZENAssertionToken::NoDiscard();
      }

      ZENAssertionToken CalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, ", at i=", i);
            ARE_EQUAL(expectedFirstArgument, callHistory[i].firstArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, callHistory[i].secondArgument, zenMockedFunctionSignatureAndCallIndex);
         }
         return ZENAssertionToken::NoDiscard();
      }

      ZENAssertionToken CalledAsFollows(const std::vector<TwoArgumentCallRef<Arg1Type, Arg2Type>>& expectedTwoArgumentCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedTwoArgumentCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<TwoArgumentCallRef<Arg1Type, Arg2Type>>
            actualTwoArgumentCalls = PrivateCallsToCallRefs(callHistory);
         VECTORS_EQUAL(expectedTwoArgumentCalls, actualTwoArgumentCalls, this->ZenMockedFunctionSignature);
         return ZENAssertionToken::NoDiscard();
      }
   private:
      static std::vector<TwoArgumentCallRef<Arg1Type, Arg2Type>>
         PrivateCallsToCallRefs(const std::vector<TwoArgumentCall<Arg1Type, Arg2Type>>& callHistory)
      {
         std::vector<TwoArgumentCallRef<Arg1Type, Arg2Type>> twoArgumentCallRefs;
         twoArgumentCallRefs.reserve(callHistory.size());
         std::for_each(callHistory.cbegin(), callHistory.cend(),
            [&](const TwoArgumentCall<Arg1Type, Arg2Type>& twoArgumentCall)
         {
            twoArgumentCallRefs.emplace_back(twoArgumentCall);
         });
         return twoArgumentCallRefs;
      }
   };

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type, arg2Type)".
#define ZENMOCK_NONVOID2(returnType, functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_NONVOID2_DEFINED(returnType, functionName, arg1Type, arg2Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type, arg2Type) const".
#define ZENMOCK_NONVOID2_CONST(returnType, functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_NONVOID2_DEFINED(returnType, functionName, arg1Type, arg2Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type, arg2Type)".
#define ZENMOCK_NONVOID2_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_NONVOID2_DEFINED(returnType, functionName, arg1Type, arg2Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type, arg2Type) const".
#define ZENMOCK_NONVOID2_NONVIRTUAL_CONST(returnType, functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_NONVOID2_DEFINED(returnType, functionName, arg1Type, arg2Type,        , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "returnType functionName(arg1Type, arg2Type)".
#define ZENMOCK_NONVOID2_FREE(returnType, functionName, arg1Type, arg2Type, ...) \
   ZenMock::NonVoidTwoArgFunctionPointerMocker<returnType, arg1Type, arg2Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidTwoArgFunctionPointerMocker<returnType, arg1Type, arg2Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type", "#arg2Type")"));

// Defines a functionName_ZenMock object for mocking a static or namespaced function with signature "returnType qualifiedClassNameOrNamespace::functionName(arg1Type, arg2Type)".
#define ZENMOCK_NONVOID2_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, ...) \
   ZenMock::NonVoidTwoArgFunctionPointerMocker<returnType, arg1Type, arg2Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidTwoArgFunctionPointerMocker<returnType, arg1Type, arg2Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type")"));

#define ZENMOCK_NONVOID2_DEFINED(returnType, functionName, arg1Type, arg2Type, virtualness, constness, mutableness, finalness, ...) \
returnType functionName(arg1Type firstArgument, arg2Type secondArgument) constness finalness \
{ \
   return functionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(firstArgument, secondArgument); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidTwoArgumentMocker<returnType, arg1Type, arg2Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidTwoArgumentMocker<returnType, arg1Type, arg2Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type", "#arg2Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type>
   class NonVoidTwoArgumentMocker : public TwoArgumentMocker<Arg1Type, Arg2Type>, protected ValueReturner<FunctionReturnType>
   {
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
      void ReturnValues(const FirstReturnValue& firstReturnValue, const SubsequentReturnValues&... subsequentReturnValues)
      {
         TwoArgumentMocker<Arg1Type, Arg2Type>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(firstReturnValue, subsequentReturnValues...);
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

// Defines a <functionName>Mock object for mocking a virtual function with signature "void functionName(arg1Type, arg2Type)".
#define ZENMOCK_VOID2(functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_VOID2_DEFINED(functionName, arg1Type, arg2Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a virtual function with signature "void functionName(arg1Type, arg2Type) const".
#define ZENMOCK_VOID2_CONST(functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_VOID2_DEFINED(functionName, arg1Type, arg2Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a non-virtual function with signature "void functionName(arg1Type, arg2Type)".
#define ZENMOCK_VOID2_NONVIRTUAL(functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_VOID2_DEFINED(functionName, arg1Type, arg2Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a non-virtual function with signature "void functionName(arg1Type, arg2Type) const".
#define ZENMOCK_VOID2_NONVIRTUAL_CONST(functionName, arg1Type, arg2Type, ...) \
        ZENMOCK_VOID2_DEFINED(functionName, arg1Type, arg2Type,        , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "void functionName(arg1Type, arg2Type)".
#define ZENMOCK_VOID2_FREE(functionName, arg1Type, arg2Type, ...) \
   ZenMock::VoidTwoArgFunctionPointerMocker<arg1Type, arg2Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidTwoArgFunctionPointerMocker<arg1Type, arg2Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#functionName"("#arg1Type", "#arg2Type")"));

// Defines a <functionName>_ZenMock object for mocking a static or namespaced function with signature "void qualifiedClassNameOrNamespace::functionName(arg1Type, arg2Type)".
#define ZENMOCK_VOID2_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, ...) \
   ZenMock::VoidTwoArgFunctionPointerMocker<arg1Type, arg2Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidTwoArgFunctionPointerMocker<arg1Type, arg2Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type")"));

#define ZENMOCK_VOID2_DEFINED(functionName, arg1Type, arg2Type, virtualness, constness, mutableness, finalness, ...) \
void functionName(arg1Type firstArgument, arg2Type secondArgument) constness finalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(firstArgument, secondArgument); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::VoidTwoArgumentMocker<arg1Type, arg2Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidTwoArgumentMocker<arg1Type, arg2Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type", "#arg2Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

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

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   struct ThreeArgumentCall
   {
      typename std::decay<Arg1Type>::type firstArgument;
      typename std::decay<Arg2Type>::type secondArgument;
      typename std::decay<Arg3Type>::type thirdArgument;

      ThreeArgumentCall()
         : firstArgument()
         , secondArgument()
         , thirdArgument()
      {
      }

      ThreeArgumentCall(const Arg1Type& firstArgument, const Arg2Type& secondArgument, const Arg3Type& thirdArgument)
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
         , thirdArgument(thirdArgument)
      {
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   struct ThreeArgumentCallRef
   {
      const Arg1Type& firstArgument;
      const Arg2Type& secondArgument;
      const Arg3Type& thirdArgument;

      ThreeArgumentCallRef(const Arg1Type& firstArgument, const Arg2Type& secondArgument, const Arg3Type& thirdArgument)
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
         , thirdArgument(thirdArgument)
      {
      }

      explicit ThreeArgumentCallRef(const ThreeArgumentCall<Arg1Type, Arg2Type, Arg3Type>& threeArgumentCall)
         : firstArgument(threeArgumentCall.firstArgument)
         , secondArgument(threeArgumentCall.secondArgument)
         , thirdArgument(threeArgumentCall.thirdArgument)
      {
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
      std::vector<ThreeArgumentCall<Arg1Type, Arg2Type, Arg3Type>> callHistory;
   public:
      explicit ThreeArgumentMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(const Arg1Type& firstArgument, const Arg2Type& secondArgument, const Arg3Type& thirdArgument)
      {
         this->ZenMockThrowIfNotExpected(firstArgument, secondArgument, thirdArgument);
         callHistory.emplace_back(firstArgument, secondArgument, thirdArgument);
         this->ZenMockThrowIfExceptionSet();
      }

      ZENAssertionToken CalledOnceWith(
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, callHistory[0].firstArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, callHistory[0].secondArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, callHistory[0].thirdArgument, this->ZenMockedFunctionSignature);
         return ZENAssertionToken::NoDiscard();
      }

      ZENAssertionToken CalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, callHistory[i].firstArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, callHistory[i].secondArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, callHistory[i].thirdArgument, zenMockedFunctionSignatureAndCallIndex);
         }
         return ZENAssertionToken::NoDiscard();
      }

      ZENAssertionToken CalledAsFollows(const std::vector<
         ThreeArgumentCallRef<Arg1Type, Arg2Type, Arg3Type>>& expectedThreeArgumentCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedThreeArgumentCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<ThreeArgumentCallRef<Arg1Type, Arg2Type, Arg3Type>>
            actualThreeArgumentCalls = PrivateCallsToCallRefs(callHistory);
         VECTORS_EQUAL(expectedThreeArgumentCalls, actualThreeArgumentCalls, this->ZenMockedFunctionSignature);
         return ZENAssertionToken::NoDiscard();
      }

   private:
      static std::vector<ThreeArgumentCallRef<Arg1Type, Arg2Type, Arg3Type>>
         PrivateCallsToCallRefs(const std::vector<ThreeArgumentCall<Arg1Type, Arg2Type, Arg3Type>>& callHistory)
      {
         std::vector<ThreeArgumentCallRef<Arg1Type, Arg2Type, Arg3Type>> threeArgumentCallRefs;
         threeArgumentCallRefs.reserve(callHistory.size());
         std::for_each(callHistory.cbegin(), callHistory.cend(),
            [&](const ThreeArgumentCall<Arg1Type, Arg2Type, Arg3Type>& threeArgumentCall)
         {
            threeArgumentCallRefs.emplace_back(threeArgumentCall);
         });
         return threeArgumentCallRefs;
      }
   };

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type, arg2Type, arg3Type)".
#define ZENMOCK_NONVOID3(returnType, functionName, arg1Type, arg2Type, arg3Type, ...) \
        ZENMOCK_NONVOID3_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type, arg2Type, arg3Type) const".
#define ZENMOCK_NONVOID3_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, ...) \
        ZENMOCK_NONVOID3_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type, arg2Type, arg3Type)".
#define ZENMOCK_NONVOID3_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, ...) \
        ZENMOCK_NONVOID3_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type, arg2Type, arg3Type) const".
#define ZENMOCK_NONVOID3_NONVIRTUAL_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, ...) \
        ZENMOCK_NONVOID3_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type,        , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "returnType functionName(arg1Type, arg2Type, arg3Type)".
#define ZENMOCK_NONVOID3_FREE(returnType, functionName, arg1Type, arg2Type, arg3Type, ...) \
   ZenMock::NonVoidThreeArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidThreeArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type")"));

// Defines a functionName_ZenMock object for mocking a static or namespaced function with signature "returnType qualifiedClassNameOrNamespace::functionName(arg1Type, arg2Type, arg3Type)".
#define ZENMOCK_NONVOID3_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, ...) \
   ZenMock::NonVoidThreeArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidThreeArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type")"));

#define ZENMOCK_NONVOID3_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, virtualness, constness, mutableness, finalness, ...) \
returnType functionName(arg1Type firstArgument, arg2Type secondArgument, arg3Type thirdArgument) constness finalness \
{ \
   return functionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidThreeArgumentMocker<returnType, arg1Type, arg2Type, arg3Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidThreeArgumentMocker<returnType, arg1Type, arg2Type, arg3Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class NonVoidThreeArgumentMocker : public ThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>, protected ValueReturner<FunctionReturnType>
   {
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
      void ReturnValues(const FirstReturnValue& firstReturnValue, const SubsequentReturnValues&... subsequentReturnValues)
      {
         ThreeArgumentMocker<Arg1Type, Arg2Type, Arg3Type>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(firstReturnValue, subsequentReturnValues...);
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

// Defines a <functionName>Mock object for mocking a virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type)".
#define ZENMOCK_VOID3(functionName, arg1Type, arg2Type, arg3Type, ...) \
        ZENMOCK_VOID3_DEFINED(functionName, arg1Type, arg2Type, arg3Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type) const".
#define ZENMOCK_VOID3_CONST(functionName, arg1Type, arg2Type, arg3Type, ...) \
        ZENMOCK_VOID3_DEFINED(functionName, arg1Type, arg2Type, arg3Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a non-virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type)".
#define ZENMOCK_VOID3_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, ...) \
        ZENMOCK_VOID3_DEFINED(functionName, arg1Type, arg2Type, arg3Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a non-virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type) const".
#define ZENMOCK_VOID3_NONVIRTUAL_CONST(functionName, arg1Type, arg2Type, arg3Type, ...) \
        ZENMOCK_VOID3_DEFINED(functionName, arg1Type, arg2Type, arg3Type,        , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "void functionName(arg1Type, arg2Type, arg3Type)".
#define ZENMOCK_VOID3_FREE(functionName, arg1Type, arg2Type, arg3Type, ...) \
   ZenMock::VoidThreeArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidThreeArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type")"));

// Defines a <functionName>_ZenMock object for mocking a static or namespaced function with signature "void qualifiedClassNameOrNamespace::functionName(arg1Type, arg2Type, arg3Type)".
#define ZENMOCK_VOID3_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, ...) \
   ZenMock::VoidThreeArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidThreeArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type")"));

#define ZENMOCK_VOID3_DEFINED(functionName, arg1Type, arg2Type, arg3Type, virtualness, constness, mutableness, finalness, ...) \
void functionName(arg1Type firstArgument, arg2Type secondArgument, arg3Type thirdArgument) constness finalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(firstArgument, secondArgument, thirdArgument); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::VoidThreeArgumentMocker<arg1Type, arg2Type, arg3Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidThreeArgumentMocker<arg1Type, arg2Type, arg3Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

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

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   struct FourArgumentCall
   {
      typename std::decay<Arg1Type>::type firstArgument;
      typename std::decay<Arg2Type>::type secondArgument;
      typename std::decay<Arg3Type>::type thirdArgument;
      typename std::decay<Arg4Type>::type fourthArgument;

      FourArgumentCall()
         : firstArgument()
         , secondArgument()
         , thirdArgument()
         , fourthArgument()
      {
      }

      FourArgumentCall(const Arg1Type& firstArgument, const Arg2Type& secondArgument, const Arg3Type& thirdArgument, const Arg4Type& fourthArgument)
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
         , thirdArgument(thirdArgument)
         , fourthArgument(fourthArgument)
      {
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   struct FourArgumentCallRef
   {
      const Arg1Type& firstArgument;
      const Arg2Type& secondArgument;
      const Arg3Type& thirdArgument;
      const Arg4Type& fourthArgument;

      FourArgumentCallRef(const Arg1Type& firstArgument, const Arg2Type& secondArgument, const Arg3Type& thirdArgument, const Arg4Type& fourthArgument)
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
         , thirdArgument(thirdArgument)
         , fourthArgument(fourthArgument)
      {
      }

      explicit FourArgumentCallRef(const FourArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& fourArgumentCall)
         : firstArgument(fourArgumentCall.firstArgument)
         , secondArgument(fourArgumentCall.secondArgument)
         , thirdArgument(fourArgumentCall.thirdArgument)
         , fourthArgument(fourArgumentCall.fourthArgument)
      {
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
      std::vector<FourArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>> callHistory;
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
         callHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument);
         this->ZenMockThrowIfExceptionSet();
      }

      ZENAssertionToken CalledOnceWith(
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, callHistory[0].firstArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, callHistory[0].secondArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, callHistory[0].thirdArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, callHistory[0].fourthArgument, this->ZenMockedFunctionSignature);
         return ZENAssertionToken::NoDiscard();
      }

      ZENAssertionToken CalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, callHistory[i].firstArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, callHistory[i].secondArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, callHistory[i].thirdArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, callHistory[i].fourthArgument, zenMockedFunctionSignatureAndCallIndex);
         }
         return ZENAssertionToken::NoDiscard();
      }

      ZENAssertionToken CalledAsFollows(const std::vector<
         FourArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>& expectedFourArgumentCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedFourArgumentCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<FourArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
            actualFourArgumentCalls = PrivateCallsToCallRefs(callHistory);
         VECTORS_EQUAL(expectedFourArgumentCalls, actualFourArgumentCalls, this->ZenMockedFunctionSignature);
         return ZENAssertionToken::NoDiscard();
      }

   private:
      static std::vector<FourArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
         PrivateCallsToCallRefs(const std::vector<FourArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>& callHistory)
      {
         std::vector<FourArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>> fourArgumentCallRefs;
         fourArgumentCallRefs.reserve(callHistory.size());
         std::for_each(callHistory.cbegin(), callHistory.cend(),
            [&](const FourArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& fourArgumentCall)
         {
            fourArgumentCallRefs.emplace_back(fourArgumentCall);
         });
         return fourArgumentCallRefs;
      }
   };

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type)".
#define ZENMOCK_NONVOID4(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
        ZENMOCK_NONVOID4_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type) const".
#define ZENMOCK_NONVOID4_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
        ZENMOCK_NONVOID4_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type)".
#define ZENMOCK_NONVOID4_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
        ZENMOCK_NONVOID4_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type) const".
#define ZENMOCK_NONVOID4_NONVIRTUAL_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
        ZENMOCK_NONVOID4_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type,        , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type)".
#define ZENMOCK_NONVOID4_FREE(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
   ZenMock::NonVoidFourArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidFourArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type")"));

// Defines a functionName_ZenMock object for mocking a static or namespaced function with signature "returnType qualifiedClassNameOrNamespace::functionName(arg1Type, arg2Type, arg3Type, arg4Type)".
#define ZENMOCK_NONVOID4_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
   ZenMock::NonVoidFourArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidFourArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type")"));

#define ZENMOCK_NONVOID4_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, virtualness, constness, mutableness, finalness, ...) \
returnType functionName(arg1Type firstArgument, arg2Type secondArgument, arg3Type thirdArgument, arg4Type fourthArgument) constness finalness \
{ \
   return functionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidFourArgumentMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidFourArgumentMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class NonVoidFourArgumentMocker : public FourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>, protected ValueReturner<FunctionReturnType>
   {
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
      void ReturnValues(const FirstReturnValue& firstReturnValue, const SubsequentReturnValues&... subsequentReturnValues)
      {
         FourArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(firstReturnValue, subsequentReturnValues...);
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

// Defines a <functionName>Mock object for mocking a virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type)".
#define ZENMOCK_VOID4(functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
        ZENMOCK_VOID4_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type) const".
#define ZENMOCK_VOID4_CONST(functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
        ZENMOCK_VOID4_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a non-virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type)".
#define ZENMOCK_VOID4_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
        ZENMOCK_VOID4_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a non-virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type) const".
#define ZENMOCK_VOID4_NONVIRTUAL_CONST(functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
        ZENMOCK_VOID4_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type,        , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type)".
#define ZENMOCK_VOID4_FREE(functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
   ZenMock::VoidFourArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidFourArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type")"));

// Defines a <functionName>_ZenMock object for mocking a static or namespaced function with signature "void qualifiedClassNameOrNamespace::functionName(arg1Type, arg2Type, arg3Type, arg4Type)".
#define ZENMOCK_VOID4_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
   ZenMock::VoidFourArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidFourArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type")"));

#define ZENMOCK_VOID4_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, virtualness, constness, mutableness, finalness, ...) \
void functionName(arg1Type firstArgument, arg2Type secondArgument, arg3Type thirdArgument, arg4Type fourthArgument) constness finalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::VoidFourArgumentMocker<arg1Type, arg2Type, arg3Type, arg4Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidFourArgumentMocker<arg1Type, arg2Type, arg3Type, arg4Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

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

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   struct FiveArgumentCall
   {
      typename std::decay<Arg1Type>::type firstArgument;
      typename std::decay<Arg2Type>::type secondArgument;
      typename std::decay<Arg3Type>::type thirdArgument;
      typename std::decay<Arg4Type>::type fourthArgument;
      typename std::decay<Arg5Type>::type fifthArgument;

      FiveArgumentCall()
         : firstArgument()
         , secondArgument()
         , thirdArgument()
         , fourthArgument()
         , fifthArgument()
      {
      }

      FiveArgumentCall(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument)
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
         , thirdArgument(thirdArgument)
         , fourthArgument(fourthArgument)
         , fifthArgument(fifthArgument)
      {
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   struct FiveArgumentCallRef
   {
      const Arg1Type& firstArgument;
      const Arg2Type& secondArgument;
      const Arg3Type& thirdArgument;
      const Arg4Type& fourthArgument;
      const Arg5Type& fifthArgument;

      FiveArgumentCallRef(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument)
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
         , thirdArgument(thirdArgument)
         , fourthArgument(fourthArgument)
         , fifthArgument(fifthArgument)
      {
      }

      explicit FiveArgumentCallRef(const FiveArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& fiveArgumentCall)
         : firstArgument(fiveArgumentCall.firstArgument)
         , secondArgument(fiveArgumentCall.secondArgument)
         , thirdArgument(fiveArgumentCall.thirdArgument)
         , fourthArgument(fiveArgumentCall.fourthArgument)
         , fifthArgument(fiveArgumentCall.fifthArgument)
      {
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
      std::vector<FiveArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>> callHistory;
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
         callHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument);
         this->ZenMockThrowIfExceptionSet();
      }

      ZENAssertionToken CalledOnceWith(
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument,
         const Arg5Type& expectedFifthArgument)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, callHistory[0].firstArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, callHistory[0].secondArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, callHistory[0].thirdArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, callHistory[0].fourthArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFifthArgument, callHistory[0].fifthArgument, this->ZenMockedFunctionSignature);
         return ZENAssertionToken::NoDiscard();
      }

      ZENAssertionToken CalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument,
         const Arg5Type& expectedFifthArgument)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, callHistory[i].firstArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, callHistory[i].secondArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, callHistory[i].thirdArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, callHistory[i].fourthArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFifthArgument, callHistory[i].fifthArgument, zenMockedFunctionSignatureAndCallIndex);
            return ZENAssertionToken::NoDiscard();
         }
      }

      ZENAssertionToken CalledAsFollows(const std::vector<
         FiveArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>& expectedFiveArgumentCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedFiveArgumentCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<FiveArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
            actualFiveArgumentCalls = PrivateCallsToCallRefs(callHistory);
         VECTORS_EQUAL(expectedFiveArgumentCalls, actualFiveArgumentCalls, this->ZenMockedFunctionSignature);
         return ZENAssertionToken::NoDiscard();
      }

   private:
      static std::vector<FiveArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
         PrivateCallsToCallRefs(const std::vector<FiveArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>& callHistory)
      {
         std::vector<FiveArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>> fiveArgumentCallRefs;
         fiveArgumentCallRefs.reserve(callHistory.size());
         std::for_each(callHistory.cbegin(), callHistory.cend(),
            [&](const FiveArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& fiveArgumentCall)
         {
            fiveArgumentCallRefs.emplace_back(fiveArgumentCall);
         });
         return fiveArgumentCallRefs;
      }
   };

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type)".
#define ZENMOCK_NONVOID5(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
        ZENMOCK_NONVOID5_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type) const".
#define ZENMOCK_NONVOID5_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
        ZENMOCK_NONVOID5_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type)".
#define ZENMOCK_NONVOID5_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
        ZENMOCK_NONVOID5_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type) const".
#define ZENMOCK_NONVOID5_NONVIRTUAL_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
        ZENMOCK_NONVOID5_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type,        , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type)".
#define ZENMOCK_NONVOID5_FREE(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
   ZenMock::NonVoidFiveArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidFiveArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type")"));

// Defines a functionName_ZenMock object for mocking a static or namespaced function with signature "returnType qualifiedClassNameOrNamespace::functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type)".
#define ZENMOCK_NONVOID5_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
   ZenMock::NonVoidFiveArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidFiveArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type")"));

#define ZENMOCK_NONVOID5_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, virtualness, constness, mutableness, finalness, ...) \
returnType functionName(arg1Type firstArgument, arg2Type secondArgument, arg3Type thirdArgument, arg4Type fourthArgument, arg5Type fifthArgument) constness finalness \
{ \
   return functionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidFiveArgumentMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidFiveArgumentMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   class NonVoidFiveArgumentMocker : public FiveArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>, protected ValueReturner<FunctionReturnType>
   {
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
      void ReturnValues(const FirstReturnValue& firstReturnValue, const SubsequentReturnValues&... subsequentReturnValues)
      {
         FiveArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(firstReturnValue, subsequentReturnValues...);
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

// Defines a <functionName>Mock object for mocking a virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type)".
#define ZENMOCK_VOID5(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
        ZENMOCK_VOID5_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type) const".
#define ZENMOCK_VOID5_CONST(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
        ZENMOCK_VOID5_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a non-virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type)".
#define ZENMOCK_VOID5_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
        ZENMOCK_VOID5_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type,       ,      ,        ,          , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a non-virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type) const".
#define ZENMOCK_VOID5_NONVIRTUAL_CONST(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
        ZENMOCK_VOID5_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type,       , const, mutable,          , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type)".
#define ZENMOCK_VOID5_FREE(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
   ZenMock::VoidFiveArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidFiveArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type")"));

// Defines a <functionName>_ZenMock object for mocking a static or namespaced function with signature "void qualifiedClassNameOrNamespace::functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type)".
#define ZENMOCK_VOID5_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
   ZenMock::VoidFiveArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidFiveArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type")"));

#define ZENMOCK_VOID5_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, virtualness, constness, mutableness, finalness, ...) \
void functionName(arg1Type firstArgument, arg2Type secondArgument, arg3Type thirdArgument, arg4Type fourthArgument, arg5Type fifthArgument) constness finalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::VoidFiveArgumentMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::VoidFiveArgumentMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

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

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   struct SixArgumentCall
   {
      typename std::decay<Arg1Type>::type firstArgument;
      typename std::decay<Arg2Type>::type secondArgument;
      typename std::decay<Arg3Type>::type thirdArgument;
      typename std::decay<Arg4Type>::type fourthArgument;
      typename std::decay<Arg5Type>::type fifthArgument;
      typename std::decay<Arg6Type>::type sixthArgument;

      SixArgumentCall()
         : firstArgument()
         , secondArgument()
         , thirdArgument()
         , fourthArgument()
         , fifthArgument()
         , sixthArgument()
      {
      }

      SixArgumentCall(
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
         , sixthArgument(sixthArgument)
      {
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   struct SixArgumentCallRef
   {
      const Arg1Type& firstArgument;
      const Arg2Type& secondArgument;
      const Arg3Type& thirdArgument;
      const Arg4Type& fourthArgument;
      const Arg5Type& fifthArgument;
      const Arg6Type& sixthArgument;

      SixArgumentCallRef(
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
         , sixthArgument(sixthArgument)
      {
      }

      explicit SixArgumentCallRef(const SixArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& sixArgumentCall)
         : firstArgument(sixArgumentCall.firstArgument)
         , secondArgument(sixArgumentCall.secondArgument)
         , thirdArgument(sixArgumentCall.thirdArgument)
         , fourthArgument(sixArgumentCall.fourthArgument)
         , fifthArgument(sixArgumentCall.fifthArgument)
         , sixthArgument(sixArgumentCall.sixthArgument)
      {
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
      std::vector<SixArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>> callHistory;
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
         callHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument);
         this->ZenMockThrowIfExceptionSet();
      }

      ZENAssertionToken CalledOnceWith(
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument,
         const Arg5Type& expectedFifthArgument,
         const Arg6Type& expectedSixthArgument)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, callHistory[0].firstArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, callHistory[0].secondArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, callHistory[0].thirdArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, callHistory[0].fourthArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFifthArgument, callHistory[0].fifthArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSixthArgument, callHistory[0].sixthArgument, this->ZenMockedFunctionSignature);
         return ZENAssertionToken::NoDiscard();
      }

      ZENAssertionToken CalledNTimesWith(
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
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, callHistory[i].firstArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, callHistory[i].secondArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, callHistory[i].thirdArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, callHistory[i].fourthArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFifthArgument, callHistory[i].fifthArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSixthArgument, callHistory[i].sixthArgument, zenMockedFunctionSignatureAndCallIndex);
            return ZENAssertionToken::NoDiscard();
         }
      }

      ZENAssertionToken CalledAsFollows(const std::vector<
         SixArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>& expectedSixArgumentCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedSixArgumentCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<SixArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
            actualSixArgumentCalls = PrivateCallsToCallRefs(callHistory);
         VECTORS_EQUAL(expectedSixArgumentCalls, actualSixArgumentCalls, this->ZenMockedFunctionSignature);
         return ZENAssertionToken::NoDiscard();
      }

   private:
      static std::vector<SixArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
         PrivateCallsToCallRefs(const std::vector<SixArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>& callHistory)
      {
         std::vector<SixArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>> sixArgumentCallRefs;
         sixArgumentCallRefs.reserve(callHistory.size());
         std::for_each(callHistory.cbegin(), callHistory.cend(),
            [&](const SixArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& sixArgumentCall)
         {
            sixArgumentCallRefs.emplace_back(sixArgumentCall);
         });
         return sixArgumentCallRefs;
      }
   };

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type)".
#define ZENMOCK_NONVOID6(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
        ZENMOCK_NONVOID6_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type) const".
#define ZENMOCK_NONVOID6_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
        ZENMOCK_NONVOID6_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type)".
#define ZENMOCK_NONVOID6_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
        ZENMOCK_NONVOID6_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type) const".
#define ZENMOCK_NONVOID6_NONVIRTUAL_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
        ZENMOCK_NONVOID6_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type,        , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type)".
#define ZENMOCK_NONVOID6_FREE(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
   ZenMock::NonVoidSixArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidSixArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type")"));

// Defines a functionName_ZenMock object for mocking a static or namespaced function with signature "returnType qualifiedClassNameOrNamespace::functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type)".
#define ZENMOCK_NONVOID6_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
   ZenMock::NonVoidSixArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidSixArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type")"));

#define ZENMOCK_NONVOID6_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, virtualness, constness, mutableness, finalness, ...) \
returnType functionName(arg1Type firstArgument, arg2Type secondArgument, arg3Type thirdArgument, arg4Type fourthArgument, arg5Type fifthArgument, arg6Type sixthArgument) constness finalness \
{ \
   return functionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidSixArgumentMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidSixArgumentMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   class NonVoidSixArgumentMocker : public SixArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>, protected ValueReturner<FunctionReturnType>
   {
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
      void ReturnValues(const FirstReturnValue& firstReturnValue, const SubsequentReturnValues&... subsequentReturnValues)
      {
         SixArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(firstReturnValue, subsequentReturnValues...);
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

// Defines a <functionName>Mock object for mocking a virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type)".
#define ZENMOCK_VOID6(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
        ZENMOCK_VOID6_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type) const".
#define ZENMOCK_VOID6_CONST(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
        ZENMOCK_VOID6_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a non-virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type)".
#define ZENMOCK_VOID6_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
        ZENMOCK_VOID6_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a non-virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type) const".
#define ZENMOCK_VOID6_NONVIRTUAL_CONST(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
        ZENMOCK_VOID6_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type,        , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type)".
#define ZENMOCK_VOID6_FREE(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
   ZenMock::VoidSixArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidSixArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type")"));

// Defines a <functionName>_ZenMock object for mocking a static or namespaced function with signature "void qualifiedClassNameOrNamespace::functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type)".
#define ZENMOCK_VOID6_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
   ZenMock::VoidSixArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidSixArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type")"));

#define ZENMOCK_VOID6_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, virtualness, constness, mutableness, finalness, ...) \
void functionName(arg1Type firstArgument, arg2Type secondArgument, arg3Type thirdArgument, arg4Type fourthArgument, arg5Type fifthArgument, arg6Type sixthArgument) constness finalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::ZenMockVoidSixArgs<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::ZenMockVoidSixArgs<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

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

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   struct SevenArgumentCall
   {
      typename std::decay<Arg1Type>::type firstArgument;
      typename std::decay<Arg2Type>::type secondArgument;
      typename std::decay<Arg3Type>::type thirdArgument;
      typename std::decay<Arg4Type>::type fourthArgument;
      typename std::decay<Arg5Type>::type fifthArgument;
      typename std::decay<Arg6Type>::type sixthArgument;
      typename std::decay<Arg7Type>::type seventhArgument;

      SevenArgumentCall()
         : firstArgument()
         , secondArgument()
         , thirdArgument()
         , fourthArgument()
         , fifthArgument()
         , sixthArgument()
         , seventhArgument()
      {
      }

      SevenArgumentCall(
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
         , seventhArgument(seventhArgument)
      {
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   struct SevenArgumentCallRef
   {
      const Arg1Type& firstArgument;
      const Arg2Type& secondArgument;
      const Arg3Type& thirdArgument;
      const Arg4Type& fourthArgument;
      const Arg5Type& fifthArgument;
      const Arg6Type& sixthArgument;
      const Arg7Type& seventhArgument;

      SevenArgumentCallRef(
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
         , seventhArgument(seventhArgument)
      {
      }

      explicit SevenArgumentCallRef(const SevenArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& sevenArgumentCall)
         : firstArgument(sevenArgumentCall.firstArgument)
         , secondArgument(sevenArgumentCall.secondArgument)
         , thirdArgument(sevenArgumentCall.thirdArgument)
         , fourthArgument(sevenArgumentCall.fourthArgument)
         , fifthArgument(sevenArgumentCall.fifthArgument)
         , sixthArgument(sevenArgumentCall.sixthArgument)
         , seventhArgument(sevenArgumentCall.seventhArgument)
      {
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
      std::vector<SevenArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>> callHistory;
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
         callHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument);
         this->ZenMockThrowIfExceptionSet();
      }

      ZENAssertionToken CalledOnceWith(
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
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, callHistory[0].firstArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, callHistory[0].secondArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, callHistory[0].thirdArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, callHistory[0].fourthArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFifthArgument, callHistory[0].fifthArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSixthArgument, callHistory[0].sixthArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSeventhArgument, callHistory[0].seventhArgument, this->ZenMockedFunctionSignature);
         return ZENAssertionToken::NoDiscard();
      }

      ZENAssertionToken CalledNTimesWith(
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
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, callHistory[i].firstArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, callHistory[i].secondArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, callHistory[i].thirdArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, callHistory[i].fourthArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFifthArgument, callHistory[i].fifthArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSixthArgument, callHistory[i].sixthArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSeventhArgument, callHistory[i].seventhArgument, zenMockedFunctionSignatureAndCallIndex);
         }
         return ZENAssertionToken::NoDiscard();
      }

      ZENAssertionToken CalledAsFollows(const std::vector<SevenArgumentCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>& expectedSevenArgumentCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedSevenArgumentCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<SevenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
            actualSevenArgumentCalls = PrivateCallsToCallRefs(callHistory);
         VECTORS_EQUAL(expectedSevenArgumentCalls, actualSevenArgumentCalls, this->ZenMockedFunctionSignature);
         return ZENAssertionToken::NoDiscard();
      }

   private:
      static std::vector<SevenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
         PrivateCallsToCallRefs(const std::vector<SevenArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>& callHistory)
      {
         std::vector<SevenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>> sevenArgumentCallRefs;
         sevenArgumentCallRefs.reserve(callHistory.size());
         std::for_each(callHistory.cbegin(), callHistory.cend(),
            [&](const SevenArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& sevenArgumentCall)
         {
            sevenArgumentCallRefs.emplace_back(sevenArgumentCall);
         });
         return sevenArgumentCallRefs;
      }
   };

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type)".
#define ZENMOCK_NONVOID7(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
        ZENMOCK_NONVOID7_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type) const".
#define ZENMOCK_NONVOID7_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
        ZENMOCK_NONVOID7_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type)".
#define ZENMOCK_NONVOID7_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
        ZENMOCK_NONVOID7_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type) const".
#define ZENMOCK_NONVOID7_NONVIRTUAL_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
        ZENMOCK_NONVOID7_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type,        , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type)".
#define ZENMOCK_NONVOID7_FREE(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
   ZenMock::NonVoidSevenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidSevenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type")"));

// Defines a functionName_ZenMock object for mocking a static or namespaced function with signature "returnType qualifiedClassNameOrNamespace::functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type)".
#define ZENMOCK_NONVOID7_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
   ZenMock::NonVoidSevenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidSevenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type")"));

#define ZENMOCK_NONVOID7_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, virtualness, constness, mutableness, finalness, ...) \
returnType functionName(arg1Type firstArgument, arg2Type secondArgument, arg3Type thirdArgument, arg4Type fourthArgument, arg5Type fifthArgument, arg6Type sixthArgument, arg7Type seventhArgument) constness finalness \
{ \
   return functionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidSevenArgumentMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidSevenArgumentMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   class NonVoidSevenArgumentMocker : public SevenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ExceptionThrower>, protected ValueReturner<FunctionReturnType>
   {
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
      void ReturnValues(const FirstReturnValue& firstReturnValue, const SubsequentReturnValues&... subsequentReturnValues)
      {
         SevenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ExceptionThrower>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(firstReturnValue, subsequentReturnValues...);
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

// Defines a <functionName>Mock object for mocking a virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type)".
#define ZENMOCK_VOID7(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
        ZENMOCK_VOID7_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type) const".
#define ZENMOCK_VOID7_CONST(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
        ZENMOCK_VOID7_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a non-virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type)".
#define ZENMOCK_VOID7_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
        ZENMOCK_VOID7_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a non-virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type) const".
#define ZENMOCK_VOID7_NONVIRTUAL_CONST(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
        ZENMOCK_VOID7_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type,        , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type)".
#define ZENMOCK_VOID7_FREE(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
   ZenMock::VoidSevenArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidSevenArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type")"));

// Defines a <functionName>_ZenMock object for mocking a static or namespaced function with signature "void qualifiedClassNameOrNamespace::functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type)".
#define ZENMOCK_VOID7_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
   ZenMock::VoidSevenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidSevenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type")"));

#define ZENMOCK_VOID7_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, virtualness, constness, mutableness, finalness, ...) \
void functionName(arg1Type firstArgument, arg2Type secondArgument, arg3Type thirdArgument, arg4Type fourthArgument, arg5Type fifthArgument, arg6Type sixthArgument, arg7Type seventhArgument) constness finalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::ZenMockVoidSevenArgs<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::ZenMockVoidSevenArgs<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

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
      typename Arg8Type>
      struct EightArgumentCall
   {
      typename std::decay<Arg1Type>::type firstArgument;
      typename std::decay<Arg2Type>::type secondArgument;
      typename std::decay<Arg3Type>::type thirdArgument;
      typename std::decay<Arg4Type>::type fourthArgument;
      typename std::decay<Arg5Type>::type fifthArgument;
      typename std::decay<Arg6Type>::type sixthArgument;
      typename std::decay<Arg7Type>::type seventhArgument;
      typename std::decay<Arg8Type>::type eigthArgument;

      EightArgumentCall()
         : firstArgument()
         , secondArgument()
         , thirdArgument()
         , fourthArgument()
         , fifthArgument()
         , sixthArgument()
         , seventhArgument()
         , eigthArgument()
      {
      }

      EightArgumentCall(
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
         , eigthArgument(eigthArgument)
      {
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
      typename Arg8Type>
      struct EightArgumentCallRef
   {
      const Arg1Type& firstArgument;
      const Arg2Type& secondArgument;
      const Arg3Type& thirdArgument;
      const Arg4Type& fourthArgument;
      const Arg5Type& fifthArgument;
      const Arg6Type& sixthArgument;
      const Arg7Type& seventhArgument;
      const Arg8Type& eigthArgument;

      EightArgumentCallRef(
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
         , eigthArgument(eigthArgument)
      {
      }

      explicit EightArgumentCallRef(const EightArgumentCall<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& eightArgumentCall)
         : firstArgument(eightArgumentCall.firstArgument)
         , secondArgument(eightArgumentCall.secondArgument)
         , thirdArgument(eightArgumentCall.thirdArgument)
         , fourthArgument(eightArgumentCall.fourthArgument)
         , fifthArgument(eightArgumentCall.fifthArgument)
         , sixthArgument(eightArgumentCall.sixthArgument)
         , seventhArgument(eightArgumentCall.seventhArgument)
         , eigthArgument(eightArgumentCall.eigthArgument)
      {
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
      std::vector<EightArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>> callHistory;
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
         callHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument);
         this->ZenMockThrowIfExceptionSet();
      }

      ZENAssertionToken CalledOnceWith(
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
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, callHistory[0].firstArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, callHistory[0].secondArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, callHistory[0].thirdArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, callHistory[0].fourthArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFifthArgument, callHistory[0].fifthArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSixthArgument, callHistory[0].sixthArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSeventhArgument, callHistory[0].seventhArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedEigthArgument, callHistory[0].eigthArgument, this->ZenMockedFunctionSignature);
         return ZENAssertionToken::NoDiscard();
      }

      ZENAssertionToken CalledNTimesWith(
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
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, callHistory[i].firstArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, callHistory[i].secondArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, callHistory[i].thirdArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, callHistory[i].fourthArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFifthArgument, callHistory[i].fifthArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSixthArgument, callHistory[i].sixthArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSeventhArgument, callHistory[i].seventhArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedEigthArgument, callHistory[i].eigthArgument, zenMockedFunctionSignatureAndCallIndex);
         }
         return ZENAssertionToken::NoDiscard();
      }

      ZENAssertionToken CalledAsFollows(const std::vector<EightArgumentCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type>>& expectedEightArgumentCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedEightArgumentCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<EightArgumentCallRef<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
            actualEightArgumentCalls = PrivateCallsToCallRefs(callHistory);
         VECTORS_EQUAL(expectedEightArgumentCalls, actualEightArgumentCalls, this->ZenMockedFunctionSignature);
         return ZENAssertionToken::NoDiscard();
      }

   private:
      static std::vector<EightArgumentCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
         PrivateCallsToCallRefs(const std::vector<EightArgumentCall<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type>>& callHistory)
      {
         std::vector<EightArgumentCallRef<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type>> eightArgumentCallRefs;
         eightArgumentCallRefs.reserve(callHistory.size());
         std::for_each(callHistory.cbegin(), callHistory.cend(),
            [&](const EightArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& eightArgumentCall)
         {
            eightArgumentCallRefs.emplace_back(eightArgumentCall);
         });
         return eightArgumentCallRefs;
      }
   };

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type)".
#define ZENMOCK_NONVOID8(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
        ZENMOCK_NONVOID8_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type) const".
#define ZENMOCK_NONVOID8_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
        ZENMOCK_NONVOID8_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type)".
#define ZENMOCK_NONVOID8_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
        ZENMOCK_NONVOID8_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type) const".
#define ZENMOCK_NONVOID8_NONVIRTUAL_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
        ZENMOCK_NONVOID8_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type,        , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type)".
#define ZENMOCK_NONVOID8_FREE(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
   ZenMock::NonVoidEightArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidEightArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type")"));

// Defines a functionName_ZenMock object for mocking a static or namespaced function with signature "returnType qualifiedClassNameOrNamespace::functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type)".
#define ZENMOCK_NONVOID8_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
   ZenMock::NonVoidEightArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidEightArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type")"));

#define ZENMOCK_NONVOID8_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, virtualness, constness, mutableness, finalness, ...) \
returnType functionName(arg1Type firstArgument, arg2Type secondArgument, arg3Type thirdArgument, arg4Type fourthArgument, arg5Type fifthArgument, arg6Type sixthArgument, arg7Type seventhArgument, arg8Type eigthArgument) constness finalness \
{ \
   return functionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidEightArgumentMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidEightArgumentMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
   class NonVoidEightArgumentMocker : public EightArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ExceptionThrower>, protected ValueReturner<FunctionReturnType>
   {
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
      void ReturnValues(const FirstReturnValue& firstReturnValue, const SubsequentReturnValues&... subsequentReturnValues)
      {
         EightArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ExceptionThrower>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(firstReturnValue, subsequentReturnValues...);
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

// Defines a <functionName>Mock object for mocking a virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type)".
#define ZENMOCK_VOID8(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
        ZENMOCK_VOID8_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type) const".
#define ZENMOCK_VOID8_CONST(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
        ZENMOCK_VOID8_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a non-virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type)".
#define ZENMOCK_VOID8_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
        ZENMOCK_VOID8_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a non-virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type) const".
#define ZENMOCK_VOID8_NONVIRTUAL_CONST(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
        ZENMOCK_VOID8_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type,        , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type)".
#define ZENMOCK_VOID8_FREE(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
   ZenMock::VoidEightArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidEightArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type")"));

// Defines a <functionName>_ZenMock object for mocking a static or namespaced function with signature "void qualifiedClassNameOrNamespace::functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type)".
#define ZENMOCK_VOID8_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
   ZenMock::VoidEightArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidEightArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type")"));

#define ZENMOCK_VOID8_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, virtualness, constness, mutableness, finalness, ...) \
void functionName(arg1Type firstArgument, arg2Type secondArgument, arg3Type thirdArgument, arg4Type fourthArgument, arg5Type fifthArgument, arg6Type sixthArgument, arg7Type seventhArgument, arg8Type eigthArgument) constness finalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::ZenMockVoidEightArgs<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::ZenMockVoidEightArgs<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

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
      typename Arg9Type>
      struct NineArgumentCall
   {
      typename std::decay<Arg1Type>::type firstArgument;
      typename std::decay<Arg2Type>::type secondArgument;
      typename std::decay<Arg3Type>::type thirdArgument;
      typename std::decay<Arg4Type>::type fourthArgument;
      typename std::decay<Arg5Type>::type fifthArgument;
      typename std::decay<Arg6Type>::type sixthArgument;
      typename std::decay<Arg7Type>::type seventhArgument;
      typename std::decay<Arg8Type>::type eigthArgument;
      typename std::decay<Arg9Type>::type ninthArgument;

      NineArgumentCall()
         : firstArgument()
         , secondArgument()
         , thirdArgument()
         , fourthArgument()
         , fifthArgument()
         , sixthArgument()
         , seventhArgument()
         , eigthArgument()
         , ninthArgument()
      {
      }

      NineArgumentCall(
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
         , ninthArgument(ninthArgument)
      {
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
      typename Arg9Type>
      struct NineArgumentCallRef
   {
      const Arg1Type& firstArgument;
      const Arg2Type& secondArgument;
      const Arg3Type& thirdArgument;
      const Arg4Type& fourthArgument;
      const Arg5Type& fifthArgument;
      const Arg6Type& sixthArgument;
      const Arg7Type& seventhArgument;
      const Arg8Type& eigthArgument;
      const Arg9Type& ninthArgument;

      NineArgumentCallRef(
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
         , ninthArgument(ninthArgument)
      {
      }

      explicit NineArgumentCallRef(const NineArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& nineArgumentCall)
         : firstArgument(nineArgumentCall.firstArgument)
         , secondArgument(nineArgumentCall.secondArgument)
         , thirdArgument(nineArgumentCall.thirdArgument)
         , fourthArgument(nineArgumentCall.fourthArgument)
         , fifthArgument(nineArgumentCall.fifthArgument)
         , sixthArgument(nineArgumentCall.sixthArgument)
         , seventhArgument(nineArgumentCall.seventhArgument)
         , eigthArgument(nineArgumentCall.eigthArgument)
         , ninthArgument(nineArgumentCall.ninthArgument)
      {
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
      std::vector<NineArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>> callHistory;
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
         callHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument);
         this->ZenMockThrowIfExceptionSet();
      }

      ZENAssertionToken CalledOnceWith(
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
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, callHistory[0].firstArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, callHistory[0].secondArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, callHistory[0].thirdArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, callHistory[0].fourthArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFifthArgument, callHistory[0].fifthArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSixthArgument, callHistory[0].sixthArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSeventhArgument, callHistory[0].seventhArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedEigthArgument, callHistory[0].eigthArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedNinthArgument, callHistory[0].ninthArgument, this->ZenMockedFunctionSignature);
         return ZENAssertionToken::NoDiscard();
      }

      ZENAssertionToken CalledNTimesWith(
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
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, callHistory[i].firstArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, callHistory[i].secondArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, callHistory[i].thirdArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, callHistory[i].fourthArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFifthArgument, callHistory[i].fifthArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSixthArgument, callHistory[i].sixthArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSeventhArgument, callHistory[i].seventhArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedEigthArgument, callHistory[i].eigthArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedNinthArgument, callHistory[i].ninthArgument, zenMockedFunctionSignatureAndCallIndex);
         }
         return ZENAssertionToken::NoDiscard();
      }

      ZENAssertionToken CalledAsFollows(const std::vector<NineArgumentCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>& expectedNineArgumentCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedNineArgumentCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<NineArgumentCallRef<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
            actualNineArgumentCalls = PrivateCallsToCallRefs(callHistory);
         VECTORS_EQUAL(expectedNineArgumentCalls, actualNineArgumentCalls, this->ZenMockedFunctionSignature);
         return ZENAssertionToken::NoDiscard();
      }

   private:
      static std::vector<NineArgumentCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
         PrivateCallsToCallRefs(const std::vector<NineArgumentCall<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>& callHistory)
      {
         std::vector<NineArgumentCallRef<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>> nineArgumentCallRefs;
         nineArgumentCallRefs.reserve(callHistory.size());
         std::for_each(callHistory.cbegin(), callHistory.cend(),
            [&](const NineArgumentCall<
               Arg1Type, Arg2Type, Arg3Type, Arg4Type,
               Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& nineArgumentCall)
         {
            nineArgumentCallRefs.emplace_back(nineArgumentCall);
         });
         return nineArgumentCallRefs;
      }
   };

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type)".
#define ZENMOCK_NONVOID9(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, ...) \
        ZENMOCK_NONVOID9_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type) const".
#define ZENMOCK_NONVOID9_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, ...) \
        ZENMOCK_NONVOID9_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type)".
#define ZENMOCK_NONVOID9_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, ...) \
        ZENMOCK_NONVOID9_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type,       ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type) const".
#define ZENMOCK_NONVOID9_NONVIRTUAL_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, ...) \
        ZENMOCK_NONVOID9_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type,       , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type)".
#define ZENMOCK_NONVOID9_FREE(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, ...) \
   ZenMock::NonVoidNineArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidNineArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type")"));

// Defines a functionName_ZenMock object for mocking a static or namespaced function with signature "returnType qualifiedClassNameOrNamespace::functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type)".
#define ZENMOCK_NONVOID9_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, ...) \
   ZenMock::NonVoidNineArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidNineArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type")"));

#define ZENMOCK_NONVOID9_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, virtualness, constness, mutableness, finalness, ...) \
returnType functionName(arg1Type firstArgument, arg2Type secondArgument, arg3Type thirdArgument, arg4Type fourthArgument, arg5Type fifthArgument, arg6Type sixthArgument, arg7Type seventhArgument, arg8Type eigthArgument, arg9Type ninthArgument) constness finalness \
{ \
   return functionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidNineArgumentMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidNineArgumentMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
   class NonVoidNineArgumentMocker : public NineArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ExceptionThrower>, protected ValueReturner<FunctionReturnType>
   {
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
      void ReturnValues(const FirstReturnValue& firstReturnValue, const SubsequentReturnValues&... subsequentReturnValues)
      {
         NineArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ExceptionThrower>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(firstReturnValue, subsequentReturnValues...);
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

// Defines a <functionName>Mock object for mocking a virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type)".
#define ZENMOCK_VOID9(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, ...) \
        ZENMOCK_VOID9_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type) const".
#define ZENMOCK_VOID9_CONST(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, ...) \
        ZENMOCK_VOID9_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a non-virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type)".
#define ZENMOCK_VOID9_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, ...) \
        ZENMOCK_VOID9_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a non-virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type) const".
#define ZENMOCK_VOID9_NONVIRTUAL_CONST(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, ...) \
        ZENMOCK_VOID9_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type,        , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type)".
#define ZENMOCK_VOID9_FREE(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, ...) \
   ZenMock::VoidNineArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidNineArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type")"));

// Defines a <functionName>_ZenMock object for mocking a static or namespaced function with signature "void qualifiedClassNameOrNamespace::functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type)".
#define ZENMOCK_VOID9_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, ...) \
   ZenMock::VoidNineArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidNineArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type")"));

#define ZENMOCK_VOID9_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, virtualness, constness, mutableness, finalness, ...) \
void functionName(arg1Type firstArgument, arg2Type secondArgument, arg3Type thirdArgument, arg4Type fourthArgument, arg5Type fifthArgument, arg6Type sixthArgument, arg7Type seventhArgument, arg8Type eigthArgument, arg9Type ninthArgument) constness finalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::ZenMockVoidNineArgs<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::ZenMockVoidNineArgs<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

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
      typename Arg10Type>
      struct TenArgumentCall
   {
      typename std::decay<Arg1Type>::type firstArgument;
      typename std::decay<Arg2Type>::type secondArgument;
      typename std::decay<Arg3Type>::type thirdArgument;
      typename std::decay<Arg4Type>::type fourthArgument;
      typename std::decay<Arg5Type>::type fifthArgument;
      typename std::decay<Arg6Type>::type sixthArgument;
      typename std::decay<Arg7Type>::type seventhArgument;
      typename std::decay<Arg8Type>::type eigthArgument;
      typename std::decay<Arg9Type>::type ninthArgument;
      typename std::decay<Arg10Type>::type tenthArgument;

      TenArgumentCall()
         : firstArgument()
         , secondArgument()
         , thirdArgument()
         , fourthArgument()
         , fifthArgument()
         , sixthArgument()
         , seventhArgument()
         , eigthArgument()
         , ninthArgument()
         , tenthArgument()
      {
      }

      TenArgumentCall(
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
         , tenthArgument(tenthArgument)
      {
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
      typename Arg10Type>
      struct TenArgumentCallRef
   {
      const Arg1Type& firstArgument;
      const Arg2Type& secondArgument;
      const Arg3Type& thirdArgument;
      const Arg4Type& fourthArgument;
      const Arg5Type& fifthArgument;
      const Arg6Type& sixthArgument;
      const Arg7Type& seventhArgument;
      const Arg8Type& eigthArgument;
      const Arg9Type& ninthArgument;
      const Arg10Type& tenthArgument;

      TenArgumentCallRef(
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
         , tenthArgument(tenthArgument)
      {
      }

      explicit TenArgumentCallRef(const TenArgumentCall<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& tenArgumentCall)
         : firstArgument(tenArgumentCall.firstArgument)
         , secondArgument(tenArgumentCall.secondArgument)
         , thirdArgument(tenArgumentCall.thirdArgument)
         , fourthArgument(tenArgumentCall.fourthArgument)
         , fifthArgument(tenArgumentCall.fifthArgument)
         , sixthArgument(tenArgumentCall.sixthArgument)
         , seventhArgument(tenArgumentCall.seventhArgument)
         , eigthArgument(tenArgumentCall.eigthArgument)
         , ninthArgument(tenArgumentCall.ninthArgument)
         , tenthArgument(tenArgumentCall.tenthArgument)
      {
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
      std::vector<TenArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>> callHistory;
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
         callHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument, tenthArgument);
         this->ZenMockThrowIfExceptionSet();
      }

      ZENAssertionToken CalledOnceWith(
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
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, callHistory[0].firstArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, callHistory[0].secondArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, callHistory[0].thirdArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, callHistory[0].fourthArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFifthArgument, callHistory[0].fifthArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSixthArgument, callHistory[0].sixthArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSeventhArgument, callHistory[0].seventhArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedEigthArgument, callHistory[0].eigthArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedNinthArgument, callHistory[0].ninthArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedTenthArgument, callHistory[0].tenthArgument, this->ZenMockedFunctionSignature);
         return ZENAssertionToken::NoDiscard();
      }

      ZENAssertionToken CalledNTimesWith(
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
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, callHistory[i].firstArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, callHistory[i].secondArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, callHistory[i].thirdArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, callHistory[i].fourthArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFifthArgument, callHistory[i].fifthArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSixthArgument, callHistory[i].sixthArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSeventhArgument, callHistory[i].seventhArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedEigthArgument, callHistory[i].eigthArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedNinthArgument, callHistory[i].ninthArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedTenthArgument, callHistory[i].tenthArgument, zenMockedFunctionSignatureAndCallIndex);
         }
         return ZENAssertionToken::NoDiscard();
      }

      ZENAssertionToken CalledAsFollows(const std::vector<TenArgumentCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>& expectedTenArgumentCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedTenArgumentCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<TenArgumentCallRef<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>
            actualTenArgumentCalls = PrivateCallsToCallRefs(callHistory);
         VECTORS_EQUAL(expectedTenArgumentCalls, actualTenArgumentCalls, this->ZenMockedFunctionSignature);
         return ZENAssertionToken::NoDiscard();
      }

   private:
      static std::vector<TenArgumentCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>
         PrivateCallsToCallRefs(const std::vector<TenArgumentCall<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>& callHistory)
      {
         std::vector<TenArgumentCallRef<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>> tenArgumentCallRefs;
         tenArgumentCallRefs.reserve(callHistory.size());
         std::for_each(callHistory.cbegin(), callHistory.cend(),
            [&](const TenArgumentCall<
               Arg1Type, Arg2Type, Arg3Type, Arg4Type,
               Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& tenArgumentCall)
         {
            tenArgumentCallRefs.emplace_back(tenArgumentCall);
         });
         return tenArgumentCallRefs;
      }
   };

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type)".
#define ZENMOCK_NONVOID10(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
        ZENMOCK_NONVOID10_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "virtual returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type) const".
#define ZENMOCK_NONVOID10_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
        ZENMOCK_NONVOID10_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type)".
#define ZENMOCK_NONVOID10_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
        ZENMOCK_NONVOID10_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type,      ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a base class function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type) const".
#define ZENMOCK_NONVOID10_NONVIRTUAL_CONST(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
        ZENMOCK_NONVOID10_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type,      , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "returnType functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type)".
#define ZENMOCK_NONVOID10_FREE(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
   ZenMock::NonVoidTenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidTenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type", "#arg10Type")"));

// Defines a functionName_ZenMock object for mocking a static or namespaced function with signature "returnType qualifiedClassNameOrNamespace::functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type)".
#define ZENMOCK_NONVOID10_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
   ZenMock::NonVoidTenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::NonVoidTenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type>( \
         ZenMock::Signature::FunctionPointer(#returnType, #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type", "#arg10Type")"));

#define ZENMOCK_NONVOID10_DEFINED(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, virtualness, constness, mutableness, finalness, ...) \
returnType functionName(arg1Type firstArgument, arg2Type secondArgument, arg3Type thirdArgument, arg4Type fourthArgument, arg5Type fifthArgument, arg6Type sixthArgument, arg7Type seventhArgument, arg8Type eigthArgument, arg9Type ninthArgument, arg10Type tenthArgument) constness finalness \
{ \
   return functionName##Mock##__VA_ARGS__.ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument, tenthArgument); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::NonVoidTenArgumentMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::NonVoidTenArgumentMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type>(ZenMock::Signature::Function( \
         #virtualness, #returnType, zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type", "#arg10Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

   template<typename FunctionReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
   class NonVoidTenArgumentMocker : public TenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ExceptionThrower>, protected ValueReturner<FunctionReturnType>
   {
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
      void ReturnValues(const FirstReturnValue& firstReturnValue, const SubsequentReturnValues&... subsequentReturnValues)
      {
         TenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ExceptionThrower>::_expected = true;
         ValueReturner<FunctionReturnType>::ZenMockAddReturnValues(firstReturnValue, subsequentReturnValues...);
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
         : NonVoidTenArgumentMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(zenMockedFunctionSignature)
      {
      }

      static const FunctionReturnType& ZenMockItFunctionPointer(
         NonVoidTenArgFunctionPointerMocker<FunctionReturnType, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument, Arg9Type ninthArgument, Arg10Type tenthArgument)
      {
         return functionMocker->ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument, tenthArgument);
      }
   };

// Defines a <functionName>Mock object for mocking a virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type)".
#define ZENMOCK_VOID10(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
        ZENMOCK_VOID10_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, virtual,      ,        , final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type) const".
#define ZENMOCK_VOID10_CONST(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
        ZENMOCK_VOID10_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, virtual, const, mutable, final, __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a non-virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type)".
#define ZENMOCK_VOID10_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
        ZENMOCK_VOID10_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type,        ,      ,        ,         , __VA_ARGS__)

// Defines a <functionName>Mock object for mocking a non-virtual function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type) const".
#define ZENMOCK_VOID10_NONVIRTUAL_CONST(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
        ZENMOCK_VOID10_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type,        , const, mutable,         , __VA_ARGS__)

// Defines a <functionName>_ZenMock object for mocking a free function with signature "void functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type)".
#define ZENMOCK_VOID10_FREE(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
   ZenMock::VoidTenArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidTenArgFunctionPointerMocker<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type>( \
         ZenMock::Signature::FunctionPointer("void", "::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type", "#arg10Type")"));

// Defines a <functionName>_ZenMock object for mocking a static or namespaced function with signature "void qualifiedClassNameOrNamespace::functionName(arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type)".
#define ZENMOCK_VOID10_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
   ZenMock::VoidTenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type> functionName##_ZenMock##__VA_ARGS__ = \
      ZenMock::VoidTenArgFunctionPointerMocker<returnType, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type>( \
         ZenMock::Signature::FunctionPointer("void", #qualifiedClassNameOrNamespace"::"#functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type", "#arg10Type")"));

#define ZENMOCK_VOID10_DEFINED(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, virtualness, constness, mutableness, finalness, ...) \
void functionName(arg1Type firstArgument, arg2Type secondArgument, arg3Type thirdArgument, arg4Type fourthArgument, arg5Type fifthArgument, arg6Type sixthArgument, arg7Type seventhArgument, arg8Type eigthArgument, arg9Type ninthArgument, arg10Type tenthArgument) constness finalness \
{ \
   functionName##Mock##__VA_ARGS__.ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument, tenthArgument); \
} \
struct ZenMock_##functionName##__VA_ARGS__ : public ZenMock::ZenMockVoidTenArgs<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type> \
{ \
   explicit ZenMock_##functionName##__VA_ARGS__(const std::string* zenMockedClassName) \
      : ZenMock::ZenMockVoidTenArgs<arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type>(ZenMock::Signature::Function( \
         #virtualness, "void", zenMockedClassName, #functionName"("#arg1Type", "#arg2Type", "#arg3Type", "#arg4Type", "#arg5Type", "#arg6Type", "#arg7Type", "#arg8Type", "#arg9Type", "#arg10Type")", #constness)) {} \
} mutableness functionName##Mock##__VA_ARGS__ = ZenMock_##functionName##__VA_ARGS__(this->ZenMockedClassName());

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
   class VoidTenArgumentMocker : public TenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ExceptionThrower>
   {
   public:
      explicit VoidTenArgumentMocker(const std::string& zenMockedFunctionSignature)
         : TenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(zenMockedFunctionSignature)
      {
      }

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
         : VoidTenArgumentMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>(zenMockedFunctionSignature)
      {
      }

      static void ZenMockItFunctionPointer(
         VoidTenArgFunctionPointerMocker<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>* functionMocker,
         Arg1Type firstArgument, Arg2Type secondArgument, Arg3Type thirdArgument, Arg4Type fourthArgument, Arg5Type fifthArgument, Arg6Type sixthArgument, Arg7Type seventhArgument, Arg8Type eigthArgument, Arg9Type ninthArgument, Arg10Type tenthArgument)
      {
         functionMocker->ZenMockIt(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument, tenthArgument);
      }
   };

   class Signature
   {
      friend class SignatureTests;
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

      static std::string FunctionPointer(
         const char* returnType,
         const char* unadornedFunctionSignature)
      {
         const std::string zenMockedFunctionPointerSignature =
            ZenUnit::String::Concat(returnType, " ", unadornedFunctionSignature);
         return zenMockedFunctionPointerSignature;
      }
   };
}

namespace ZenUnit
{
   template<typename ArgType>
   struct Equalizer<ZenMock::OneArgumentCall<ArgType>>
   {
      static void AssertEqual(
         const ZenMock::OneArgumentCall<ArgType>& expectedOneArgumentCall,
         const ZenMock::OneArgumentCall<ArgType>& actualOneArgumentCall)
      {
         ARE_EQUAL(expectedOneArgumentCall.argument, actualOneArgumentCall.argument);
      }
   };

   template<typename ArgType>
   struct Equalizer<ZenMock::OneArgumentCallRef<ArgType>>
   {
      static void AssertEqual(
         const ZenMock::OneArgumentCallRef<ArgType>& expectedOneArgumentCall,
         const ZenMock::OneArgumentCallRef<ArgType>& actualOneArgumentCall)
      {
         ARE_EQUAL(expectedOneArgumentCall.argument, actualOneArgumentCall.argument);
      }
   };

   template<typename Arg1Type, typename Arg2Type>
   struct Equalizer<ZenMock::TwoArgumentCall<Arg1Type, Arg2Type>>
   {
      static void AssertEqual(
         const ZenMock::TwoArgumentCall<Arg1Type, Arg2Type>& expectedTwoArgumentCall,
         const ZenMock::TwoArgumentCall<Arg1Type, Arg2Type>& actualTwoArgumentCall)
      {
         ARE_EQUAL(expectedTwoArgumentCall.firstArgument, actualTwoArgumentCall.firstArgument);
         ARE_EQUAL(expectedTwoArgumentCall.secondArgument, actualTwoArgumentCall.secondArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type>
   struct Equalizer<ZenMock::TwoArgumentCallRef<Arg1Type, Arg2Type>>
   {
      static void AssertEqual(
         const ZenMock::TwoArgumentCallRef<Arg1Type, Arg2Type>& expectedTwoArgumentCall,
         const ZenMock::TwoArgumentCallRef<Arg1Type, Arg2Type>& actualTwoArgumentCall)
      {
         ARE_EQUAL(expectedTwoArgumentCall.firstArgument, actualTwoArgumentCall.firstArgument);
         ARE_EQUAL(expectedTwoArgumentCall.secondArgument, actualTwoArgumentCall.secondArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   struct Equalizer<ZenMock::ThreeArgumentCall<Arg1Type, Arg2Type, Arg3Type>>
   {
      static void AssertEqual(
         const ZenMock::ThreeArgumentCall<Arg1Type, Arg2Type, Arg3Type>& expectedThreeArgumentCall,
         const ZenMock::ThreeArgumentCall<Arg1Type, Arg2Type, Arg3Type>& actualThreeArgumentCall)
      {
         ARE_EQUAL(expectedThreeArgumentCall.firstArgument, actualThreeArgumentCall.firstArgument);
         ARE_EQUAL(expectedThreeArgumentCall.secondArgument, actualThreeArgumentCall.secondArgument);
         ARE_EQUAL(expectedThreeArgumentCall.thirdArgument, actualThreeArgumentCall.thirdArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   struct Equalizer<ZenMock::ThreeArgumentCallRef<Arg1Type, Arg2Type, Arg3Type>>
   {
      static void AssertEqual(
         const ZenMock::ThreeArgumentCallRef<Arg1Type, Arg2Type, Arg3Type>& expectedThreeArgumentCall,
         const ZenMock::ThreeArgumentCallRef<Arg1Type, Arg2Type, Arg3Type>& actualThreeArgumentCall)
      {
         ARE_EQUAL(expectedThreeArgumentCall.firstArgument, actualThreeArgumentCall.firstArgument);
         ARE_EQUAL(expectedThreeArgumentCall.secondArgument, actualThreeArgumentCall.secondArgument);
         ARE_EQUAL(expectedThreeArgumentCall.thirdArgument, actualThreeArgumentCall.thirdArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   struct Equalizer<ZenMock::FourArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
   {
      static void AssertEqual(
         const ZenMock::FourArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& expectedFourArgumentCall,
         const ZenMock::FourArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& actualFourArgumentCall)
      {
         ARE_EQUAL(expectedFourArgumentCall.firstArgument, actualFourArgumentCall.firstArgument);
         ARE_EQUAL(expectedFourArgumentCall.secondArgument, actualFourArgumentCall.secondArgument);
         ARE_EQUAL(expectedFourArgumentCall.thirdArgument, actualFourArgumentCall.thirdArgument);
         ARE_EQUAL(expectedFourArgumentCall.fourthArgument, actualFourArgumentCall.fourthArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   struct Equalizer<ZenMock::FourArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
   {
      static void AssertEqual(
         const ZenMock::FourArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& expectedFourArgumentCall,
         const ZenMock::FourArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& actualFourArgumentCall)
      {
         ARE_EQUAL(expectedFourArgumentCall.firstArgument, actualFourArgumentCall.firstArgument);
         ARE_EQUAL(expectedFourArgumentCall.secondArgument, actualFourArgumentCall.secondArgument);
         ARE_EQUAL(expectedFourArgumentCall.thirdArgument, actualFourArgumentCall.thirdArgument);
         ARE_EQUAL(expectedFourArgumentCall.fourthArgument, actualFourArgumentCall.fourthArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   struct Equalizer<ZenMock::FiveArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
   {
      static void AssertEqual(
         const ZenMock::FiveArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& expectedFiveArgumentCall,
         const ZenMock::FiveArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& actualFiveArgumentCall)
      {
         ARE_EQUAL(expectedFiveArgumentCall.firstArgument, actualFiveArgumentCall.firstArgument);
         ARE_EQUAL(expectedFiveArgumentCall.secondArgument, actualFiveArgumentCall.secondArgument);
         ARE_EQUAL(expectedFiveArgumentCall.thirdArgument, actualFiveArgumentCall.thirdArgument);
         ARE_EQUAL(expectedFiveArgumentCall.fourthArgument, actualFiveArgumentCall.fourthArgument);
         ARE_EQUAL(expectedFiveArgumentCall.fifthArgument, actualFiveArgumentCall.fifthArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   struct Equalizer<ZenMock::FiveArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
   {
      static void AssertEqual(
         const ZenMock::FiveArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& expectedFiveArgumentCall,
         const ZenMock::FiveArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& actualFiveArgumentCall)
      {
         ARE_EQUAL(expectedFiveArgumentCall.firstArgument, actualFiveArgumentCall.firstArgument);
         ARE_EQUAL(expectedFiveArgumentCall.secondArgument, actualFiveArgumentCall.secondArgument);
         ARE_EQUAL(expectedFiveArgumentCall.thirdArgument, actualFiveArgumentCall.thirdArgument);
         ARE_EQUAL(expectedFiveArgumentCall.fourthArgument, actualFiveArgumentCall.fourthArgument);
         ARE_EQUAL(expectedFiveArgumentCall.fifthArgument, actualFiveArgumentCall.fifthArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   struct Equalizer<ZenMock::SixArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
   {
      static void AssertEqual(
         const ZenMock::SixArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& expectedSixArgumentCall,
         const ZenMock::SixArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& actualSixArgumentCall)
      {
         ARE_EQUAL(expectedSixArgumentCall.firstArgument, actualSixArgumentCall.firstArgument);
         ARE_EQUAL(expectedSixArgumentCall.secondArgument, actualSixArgumentCall.secondArgument);
         ARE_EQUAL(expectedSixArgumentCall.thirdArgument, actualSixArgumentCall.thirdArgument);
         ARE_EQUAL(expectedSixArgumentCall.fourthArgument, actualSixArgumentCall.fourthArgument);
         ARE_EQUAL(expectedSixArgumentCall.fifthArgument, actualSixArgumentCall.fifthArgument);
         ARE_EQUAL(expectedSixArgumentCall.sixthArgument, actualSixArgumentCall.sixthArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   struct Equalizer<ZenMock::SixArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
   {
      static void AssertEqual(
         const ZenMock::SixArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& expectedSixArgumentCall,
         const ZenMock::SixArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& actualSixArgumentCall)
      {
         ARE_EQUAL(expectedSixArgumentCall.firstArgument, actualSixArgumentCall.firstArgument);
         ARE_EQUAL(expectedSixArgumentCall.secondArgument, actualSixArgumentCall.secondArgument);
         ARE_EQUAL(expectedSixArgumentCall.thirdArgument, actualSixArgumentCall.thirdArgument);
         ARE_EQUAL(expectedSixArgumentCall.fourthArgument, actualSixArgumentCall.fourthArgument);
         ARE_EQUAL(expectedSixArgumentCall.fifthArgument, actualSixArgumentCall.fifthArgument);
         ARE_EQUAL(expectedSixArgumentCall.sixthArgument, actualSixArgumentCall.sixthArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   struct Equalizer<ZenMock::SevenArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
   {
      static void AssertEqual(
         const ZenMock::SevenArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& expectedSevenArgumentCall,
         const ZenMock::SevenArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& actualSevenArgumentCall)
      {
         ARE_EQUAL(expectedSevenArgumentCall.firstArgument, actualSevenArgumentCall.firstArgument);
         ARE_EQUAL(expectedSevenArgumentCall.secondArgument, actualSevenArgumentCall.secondArgument);
         ARE_EQUAL(expectedSevenArgumentCall.thirdArgument, actualSevenArgumentCall.thirdArgument);
         ARE_EQUAL(expectedSevenArgumentCall.fourthArgument, actualSevenArgumentCall.fourthArgument);
         ARE_EQUAL(expectedSevenArgumentCall.fifthArgument, actualSevenArgumentCall.fifthArgument);
         ARE_EQUAL(expectedSevenArgumentCall.sixthArgument, actualSevenArgumentCall.sixthArgument);
         ARE_EQUAL(expectedSevenArgumentCall.seventhArgument, actualSevenArgumentCall.seventhArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   struct Equalizer<ZenMock::SevenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
   {
      static void AssertEqual(
         const ZenMock::SevenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& expectedSevenArgumentCall,
         const ZenMock::SevenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& actualSevenArgumentCall)
      {
         ARE_EQUAL(expectedSevenArgumentCall.firstArgument, actualSevenArgumentCall.firstArgument);
         ARE_EQUAL(expectedSevenArgumentCall.secondArgument, actualSevenArgumentCall.secondArgument);
         ARE_EQUAL(expectedSevenArgumentCall.thirdArgument, actualSevenArgumentCall.thirdArgument);
         ARE_EQUAL(expectedSevenArgumentCall.fourthArgument, actualSevenArgumentCall.fourthArgument);
         ARE_EQUAL(expectedSevenArgumentCall.fifthArgument, actualSevenArgumentCall.fifthArgument);
         ARE_EQUAL(expectedSevenArgumentCall.sixthArgument, actualSevenArgumentCall.sixthArgument);
         ARE_EQUAL(expectedSevenArgumentCall.seventhArgument, actualSevenArgumentCall.seventhArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
   struct Equalizer<ZenMock::EightArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
   {
      static void AssertEqual(
         const ZenMock::EightArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& expectedEightArgumentCall,
         const ZenMock::EightArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& actualEightArgumentCall)
      {
         ARE_EQUAL(expectedEightArgumentCall.firstArgument, actualEightArgumentCall.firstArgument);
         ARE_EQUAL(expectedEightArgumentCall.secondArgument, actualEightArgumentCall.secondArgument);
         ARE_EQUAL(expectedEightArgumentCall.thirdArgument, actualEightArgumentCall.thirdArgument);
         ARE_EQUAL(expectedEightArgumentCall.fourthArgument, actualEightArgumentCall.fourthArgument);
         ARE_EQUAL(expectedEightArgumentCall.fifthArgument, actualEightArgumentCall.fifthArgument);
         ARE_EQUAL(expectedEightArgumentCall.sixthArgument, actualEightArgumentCall.sixthArgument);
         ARE_EQUAL(expectedEightArgumentCall.seventhArgument, actualEightArgumentCall.seventhArgument);
         ARE_EQUAL(expectedEightArgumentCall.eigthArgument, actualEightArgumentCall.eigthArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
   struct Equalizer<ZenMock::EightArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
   {
      static void AssertEqual(
         const ZenMock::EightArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& expectedEightArgumentCall,
         const ZenMock::EightArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& actualEightArgumentCall)
      {
         ARE_EQUAL(expectedEightArgumentCall.firstArgument, actualEightArgumentCall.firstArgument);
         ARE_EQUAL(expectedEightArgumentCall.secondArgument, actualEightArgumentCall.secondArgument);
         ARE_EQUAL(expectedEightArgumentCall.thirdArgument, actualEightArgumentCall.thirdArgument);
         ARE_EQUAL(expectedEightArgumentCall.fourthArgument, actualEightArgumentCall.fourthArgument);
         ARE_EQUAL(expectedEightArgumentCall.fifthArgument, actualEightArgumentCall.fifthArgument);
         ARE_EQUAL(expectedEightArgumentCall.sixthArgument, actualEightArgumentCall.sixthArgument);
         ARE_EQUAL(expectedEightArgumentCall.seventhArgument, actualEightArgumentCall.seventhArgument);
         ARE_EQUAL(expectedEightArgumentCall.eigthArgument, actualEightArgumentCall.eigthArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
   struct Equalizer<ZenMock::NineArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
   {
      static void AssertEqual(
         const ZenMock::NineArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& expectedNineArgumentCall,
         const ZenMock::NineArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& actualNineArgumentCall)
      {
         ARE_EQUAL(expectedNineArgumentCall.firstArgument, actualNineArgumentCall.firstArgument);
         ARE_EQUAL(expectedNineArgumentCall.secondArgument, actualNineArgumentCall.secondArgument);
         ARE_EQUAL(expectedNineArgumentCall.thirdArgument, actualNineArgumentCall.thirdArgument);
         ARE_EQUAL(expectedNineArgumentCall.fourthArgument, actualNineArgumentCall.fourthArgument);
         ARE_EQUAL(expectedNineArgumentCall.fifthArgument, actualNineArgumentCall.fifthArgument);
         ARE_EQUAL(expectedNineArgumentCall.sixthArgument, actualNineArgumentCall.sixthArgument);
         ARE_EQUAL(expectedNineArgumentCall.seventhArgument, actualNineArgumentCall.seventhArgument);
         ARE_EQUAL(expectedNineArgumentCall.eigthArgument, actualNineArgumentCall.eigthArgument);
         ARE_EQUAL(expectedNineArgumentCall.ninthArgument, actualNineArgumentCall.ninthArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
   struct Equalizer<ZenMock::NineArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
   {
      static void AssertEqual(
         const ZenMock::NineArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& expectedNineArgumentCall,
         const ZenMock::NineArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& actualNineArgumentCall)
      {
         ARE_EQUAL(expectedNineArgumentCall.firstArgument, actualNineArgumentCall.firstArgument);
         ARE_EQUAL(expectedNineArgumentCall.secondArgument, actualNineArgumentCall.secondArgument);
         ARE_EQUAL(expectedNineArgumentCall.thirdArgument, actualNineArgumentCall.thirdArgument);
         ARE_EQUAL(expectedNineArgumentCall.fourthArgument, actualNineArgumentCall.fourthArgument);
         ARE_EQUAL(expectedNineArgumentCall.fifthArgument, actualNineArgumentCall.fifthArgument);
         ARE_EQUAL(expectedNineArgumentCall.sixthArgument, actualNineArgumentCall.sixthArgument);
         ARE_EQUAL(expectedNineArgumentCall.seventhArgument, actualNineArgumentCall.seventhArgument);
         ARE_EQUAL(expectedNineArgumentCall.eigthArgument, actualNineArgumentCall.eigthArgument);
         ARE_EQUAL(expectedNineArgumentCall.ninthArgument, actualNineArgumentCall.ninthArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
   struct Equalizer<ZenMock::TenArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>
   {
      static void AssertEqual(
         const ZenMock::TenArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& expectedTenArgumentCall,
         const ZenMock::TenArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& actualTenArgumentCall)
      {
         ARE_EQUAL(expectedTenArgumentCall.firstArgument, actualTenArgumentCall.firstArgument);
         ARE_EQUAL(expectedTenArgumentCall.secondArgument, actualTenArgumentCall.secondArgument);
         ARE_EQUAL(expectedTenArgumentCall.thirdArgument, actualTenArgumentCall.thirdArgument);
         ARE_EQUAL(expectedTenArgumentCall.fourthArgument, actualTenArgumentCall.fourthArgument);
         ARE_EQUAL(expectedTenArgumentCall.fifthArgument, actualTenArgumentCall.fifthArgument);
         ARE_EQUAL(expectedTenArgumentCall.sixthArgument, actualTenArgumentCall.sixthArgument);
         ARE_EQUAL(expectedTenArgumentCall.seventhArgument, actualTenArgumentCall.seventhArgument);
         ARE_EQUAL(expectedTenArgumentCall.eigthArgument, actualTenArgumentCall.eigthArgument);
         ARE_EQUAL(expectedTenArgumentCall.ninthArgument, actualTenArgumentCall.ninthArgument);
         ARE_EQUAL(expectedTenArgumentCall.tenthArgument, actualTenArgumentCall.tenthArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
   struct Equalizer<ZenMock::TenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>
   {
      static void AssertEqual(
         const ZenMock::TenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& expectedTenArgumentCall,
         const ZenMock::TenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& actualTenArgumentCall)
      {
         ARE_EQUAL(expectedTenArgumentCall.firstArgument, actualTenArgumentCall.firstArgument);
         ARE_EQUAL(expectedTenArgumentCall.secondArgument, actualTenArgumentCall.secondArgument);
         ARE_EQUAL(expectedTenArgumentCall.thirdArgument, actualTenArgumentCall.thirdArgument);
         ARE_EQUAL(expectedTenArgumentCall.fourthArgument, actualTenArgumentCall.fourthArgument);
         ARE_EQUAL(expectedTenArgumentCall.fifthArgument, actualTenArgumentCall.fifthArgument);
         ARE_EQUAL(expectedTenArgumentCall.sixthArgument, actualTenArgumentCall.sixthArgument);
         ARE_EQUAL(expectedTenArgumentCall.seventhArgument, actualTenArgumentCall.seventhArgument);
         ARE_EQUAL(expectedTenArgumentCall.eigthArgument, actualTenArgumentCall.eigthArgument);
         ARE_EQUAL(expectedTenArgumentCall.ninthArgument, actualTenArgumentCall.ninthArgument);
         ARE_EQUAL(expectedTenArgumentCall.tenthArgument, actualTenArgumentCall.tenthArgument);
      }
   };

   template<typename ArgType>
   struct Printer<ZenMock::OneArgumentCallRef<ArgType>>
   {
      static void Print(std::ostream& os, const ZenMock::OneArgumentCallRef<ArgType>& oneArgumentCall)
      {
         const std::string toStringedArg = ZenUnit::ToStringer::ToString(oneArgumentCall.argument);
         os << "ZenMock::OneArgumentCall:\n"
            << "Argument: " << toStringedArg;
      }
   };

   template<typename Arg1Type, typename Arg2Type>
   struct Printer<ZenMock::TwoArgumentCallRef<Arg1Type, Arg2Type>>
   {
      static void Print(std::ostream& os, const ZenMock::TwoArgumentCallRef<Arg1Type, Arg2Type>& twoArgumentCallRef)
      {
         const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(twoArgumentCallRef.firstArgument);
         const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(twoArgumentCallRef.secondArgument);
         os << "ZenMock::TwoArgumentCall:\n"
            "Argument1: " << toStringedArg1 << '\n' <<
            "Argument2: " << toStringedArg2;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   struct Printer<ZenMock::ThreeArgumentCallRef<Arg1Type, Arg2Type, Arg3Type>>
   {
      static void Print(std::ostream& os, const ZenMock::ThreeArgumentCallRef<Arg1Type, Arg2Type, Arg3Type>& threeArgumentCallRef)
      {
         const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(threeArgumentCallRef.firstArgument);
         const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(threeArgumentCallRef.secondArgument);
         const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(threeArgumentCallRef.thirdArgument);
         os << "ZenMock::ThreeArgumentCall:\n"
            "Argument1: " << toStringedArg1 << '\n' <<
            "Argument2: " << toStringedArg2 << '\n' <<
            "Argument3: " << toStringedArg3;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   struct Printer<ZenMock::FourArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
   {
      static void Print(std::ostream& os, const ZenMock::FourArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& fourArgumentCallRef)
      {
         const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(fourArgumentCallRef.firstArgument);
         const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(fourArgumentCallRef.secondArgument);
         const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(fourArgumentCallRef.thirdArgument);
         const std::string toStringedArg4 = ZenUnit::ToStringer::ToString(fourArgumentCallRef.fourthArgument);
         os << "ZenMock::FourArgumentCall:\n"
            "Argument1: " << toStringedArg1 << '\n' <<
            "Argument2: " << toStringedArg2 << '\n' <<
            "Argument3: " << toStringedArg3 << '\n' <<
            "Argument4: " << toStringedArg4;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   struct Printer<ZenMock::FiveArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
   {
      static void Print(std::ostream& os, const ZenMock::FiveArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& fiveArgumentCallRef)
      {
         const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(fiveArgumentCallRef.firstArgument);
         const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(fiveArgumentCallRef.secondArgument);
         const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(fiveArgumentCallRef.thirdArgument);
         const std::string toStringedArg4 = ZenUnit::ToStringer::ToString(fiveArgumentCallRef.fourthArgument);
         const std::string toStringedArg5 = ZenUnit::ToStringer::ToString(fiveArgumentCallRef.fifthArgument);
         os << "ZenMock::FiveArgumentCall:\n"
            "Argument1: " << toStringedArg1 << '\n' <<
            "Argument2: " << toStringedArg2 << '\n' <<
            "Argument3: " << toStringedArg3 << '\n' <<
            "Argument4: " << toStringedArg4 << '\n' <<
            "Argument5: " << toStringedArg5;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   struct Printer<ZenMock::SixArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
   {
      static void Print(std::ostream& os, const ZenMock::SixArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& sixArgumentCallRef)
      {
         const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(sixArgumentCallRef.firstArgument);
         const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(sixArgumentCallRef.secondArgument);
         const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(sixArgumentCallRef.thirdArgument);
         const std::string toStringedArg4 = ZenUnit::ToStringer::ToString(sixArgumentCallRef.fourthArgument);
         const std::string toStringedArg5 = ZenUnit::ToStringer::ToString(sixArgumentCallRef.fifthArgument);
         const std::string toStringedArg6 = ZenUnit::ToStringer::ToString(sixArgumentCallRef.sixthArgument);
         os << "ZenMock::SixArgumentCall:\n"
            "Argument1: " << toStringedArg1 << '\n' <<
            "Argument2: " << toStringedArg2 << '\n' <<
            "Argument3: " << toStringedArg3 << '\n' <<
            "Argument4: " << toStringedArg4 << '\n' <<
            "Argument5: " << toStringedArg5 << '\n' <<
            "Argument6: " << toStringedArg6;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   struct Printer<ZenMock::SevenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
   {
      static void Print(std::ostream& os, const ZenMock::SevenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& sevenArgumentCallRef)
      {
         const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(sevenArgumentCallRef.firstArgument);
         const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(sevenArgumentCallRef.secondArgument);
         const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(sevenArgumentCallRef.thirdArgument);
         const std::string toStringedArg4 = ZenUnit::ToStringer::ToString(sevenArgumentCallRef.fourthArgument);
         const std::string toStringedArg5 = ZenUnit::ToStringer::ToString(sevenArgumentCallRef.fifthArgument);
         const std::string toStringedArg6 = ZenUnit::ToStringer::ToString(sevenArgumentCallRef.sixthArgument);
         const std::string toStringedArg7 = ZenUnit::ToStringer::ToString(sevenArgumentCallRef.seventhArgument);
         os << "ZenMock::SevenArgumentCall:\n"
            "Argument1: " << toStringedArg1 << '\n' <<
            "Argument2: " << toStringedArg2 << '\n' <<
            "Argument3: " << toStringedArg3 << '\n' <<
            "Argument4: " << toStringedArg4 << '\n' <<
            "Argument5: " << toStringedArg5 << '\n' <<
            "Argument6: " << toStringedArg6 << '\n' <<
            "Argument7: " << toStringedArg7;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
   struct Printer<ZenMock::EightArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
   {
      static void Print(std::ostream& os, const ZenMock::EightArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& eightArgumentCallRef)
      {
         const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(eightArgumentCallRef.firstArgument);
         const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(eightArgumentCallRef.secondArgument);
         const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(eightArgumentCallRef.thirdArgument);
         const std::string toStringedArg4 = ZenUnit::ToStringer::ToString(eightArgumentCallRef.fourthArgument);
         const std::string toStringedArg5 = ZenUnit::ToStringer::ToString(eightArgumentCallRef.fifthArgument);
         const std::string toStringedArg6 = ZenUnit::ToStringer::ToString(eightArgumentCallRef.sixthArgument);
         const std::string toStringedArg7 = ZenUnit::ToStringer::ToString(eightArgumentCallRef.seventhArgument);
         const std::string toStringedArg8 = ZenUnit::ToStringer::ToString(eightArgumentCallRef.eigthArgument);
         os << "ZenMock::EightArgumentCall:\n"
            "Argument1: " << toStringedArg1 << '\n' <<
            "Argument2: " << toStringedArg2 << '\n' <<
            "Argument3: " << toStringedArg3 << '\n' <<
            "Argument4: " << toStringedArg4 << '\n' <<
            "Argument5: " << toStringedArg5 << '\n' <<
            "Argument6: " << toStringedArg6 << '\n' <<
            "Argument7: " << toStringedArg7 << '\n' <<
            "Argument8: " << toStringedArg8;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
   struct Printer<ZenMock::NineArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
   {
      static void Print(std::ostream& os, const ZenMock::NineArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& nineArgumentCallRef)
      {
         const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(nineArgumentCallRef.firstArgument);
         const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(nineArgumentCallRef.secondArgument);
         const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(nineArgumentCallRef.thirdArgument);
         const std::string toStringedArg4 = ZenUnit::ToStringer::ToString(nineArgumentCallRef.fourthArgument);
         const std::string toStringedArg5 = ZenUnit::ToStringer::ToString(nineArgumentCallRef.fifthArgument);
         const std::string toStringedArg6 = ZenUnit::ToStringer::ToString(nineArgumentCallRef.sixthArgument);
         const std::string toStringedArg7 = ZenUnit::ToStringer::ToString(nineArgumentCallRef.seventhArgument);
         const std::string toStringedArg8 = ZenUnit::ToStringer::ToString(nineArgumentCallRef.eigthArgument);
         const std::string toStringedArg9 = ZenUnit::ToStringer::ToString(nineArgumentCallRef.ninthArgument);
         os << "ZenMock::NineArgumentCall:\n"
            "Argument1: " << toStringedArg1 << '\n' <<
            "Argument2: " << toStringedArg2 << '\n' <<
            "Argument3: " << toStringedArg3 << '\n' <<
            "Argument4: " << toStringedArg4 << '\n' <<
            "Argument5: " << toStringedArg5 << '\n' <<
            "Argument6: " << toStringedArg6 << '\n' <<
            "Argument7: " << toStringedArg7 << '\n' <<
            "Argument8: " << toStringedArg8 << '\n' <<
            "Argument9: " << toStringedArg9;
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
   struct Printer<ZenMock::TenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>
   {
      static void Print(std::ostream& os, const ZenMock::TenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& tenArgumentCallRef)
      {
         const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.firstArgument);
         const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.secondArgument);
         const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.thirdArgument);
         const std::string toStringedArg4 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.fourthArgument);
         const std::string toStringedArg5 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.fifthArgument);
         const std::string toStringedArg6 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.sixthArgument);
         const std::string toStringedArg7 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.seventhArgument);
         const std::string toStringedArg8 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.eigthArgument);
         const std::string toStringedArg9 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.ninthArgument);
         const std::string toStringedArg10 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.tenthArgument);
         os << "ZenMock::TenArgumentCall:\n"
            " Argument1: " << toStringedArg1 << '\n' <<
            " Argument2: " << toStringedArg2 << '\n' <<
            " Argument3: " << toStringedArg3 << '\n' <<
            " Argument4: " << toStringedArg4 << '\n' <<
            " Argument5: " << toStringedArg5 << '\n' <<
            " Argument6: " << toStringedArg6 << '\n' <<
            " Argument7: " << toStringedArg7 << '\n' <<
            " Argument8: " << toStringedArg8 << '\n' <<
            " Argument9: " << toStringedArg9 << '\n' <<
            "Argument10: " << toStringedArg10;
      }
   };
}

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

      static_assert(std::has_virtual_destructor<ZenMockedClass>::value,
         "ZenMocked classes must define a virtual destructor so as to not introduce a memory leak as detected by Clang AddressSanitizer.");
   };
}

#if defined _WIN32
#pragma warning(pop)
#endif
