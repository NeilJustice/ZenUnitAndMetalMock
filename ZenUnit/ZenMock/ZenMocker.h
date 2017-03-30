#pragma once
#include "ZenUnit/ZenMock/Exceptions/ExceptionThrower.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenUnit/ZenMock/Exceptions/UnsupportedAssertCalledZeroTimesException.h"
#include "ZenUnit/ZenMock/Exceptions/FunctionAlreadyExpectedException.h"
#include "ZenUnit/Console/Console.h"

namespace ZenMock
{
   template<typename MockableExceptionThrowerType>
   class ZenMocker
   {
      friend class ZenMockerTests;
   private:
      std::function<void(int)> _zenMockableExitFunction;
      std::function<ZenUnit::ZenUnitArgs()> _zenMockableGetZenUnitArgs;
      bool _zenMockExceptionIsInPlay;
   protected:
      MockableExceptionThrowerType _exceptionThrower;
      bool expected;
      bool _asserted;
      const std::string ZenMockedFunctionSignature;
   public:
      ZenMocker(const std::string& zenMockedFunctionSignature)
         : _zenMockableExitFunction(::exit)
         , _zenMockableGetZenUnitArgs(ZenUnit::TestRunner::GetArgs)
         , _zenMockExceptionIsInPlay(false)
         , expected(false)
         , _asserted(false)
         , ZenMockedFunctionSignature(zenMockedFunctionSignature)
      {
      }

      void Expect()
      {
         ZenMockThrowIfAlreadyExpected();
         expected = true;
      }

      template<typename ExceptionType, typename... ExceptionArgTypes>
      void ExpectAndThrow(ExceptionArgTypes&&... exceptionArgs)
      {
         ZenMockThrowIfAlreadyExpected();
         _exceptionThrower.template ExpectAndThrow<ExceptionType>(
            std::forward<ExceptionArgTypes>(exceptionArgs)...);
         expected = true;
      }

      ~ZenMocker()
      {
         ZenMockExitIfExpectedAndNotAsserted();
      }

   protected:
      void ZenMockThrowIfExceptionSet()
      {
         _exceptionThrower.ZenMockThrowIfExceptionSet();
      }

      template<typename... ArgTypes>
      void ZenMockThrowIfNotExpected(const ArgTypes&... args)
      {
         if (!expected)
         {
            _zenMockExceptionIsInPlay = true;
            throw UnexpectedCallException(ZenMockedFunctionSignature, args...);
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
            _zenMockExceptionIsInPlay = true;
            throw UnsupportedAssertCalledZeroTimesException(ZenMockedFunctionSignature);
         }
      }

      void ZenMockThrowIfExpectedCallsSizeIsZero(size_t expectedCallsSize)
      {
         if (expectedCallsSize == 0)
         {
            _zenMockExceptionIsInPlay = true;
            throw UnsupportedAssertCalledZeroTimesException(ZenMockedFunctionSignature);
         }
      }

   private:
      void ZenMockExitIfExpectedAndNotAsserted() const
      {
         if (expected && !_asserted && !_zenMockExceptionIsInPlay)
         {
            const ZenUnit::Console console;
            std::cout << "\n\n";
            console.WriteLineColor("Fatal Unasserted ZenMock Expectation:", ZenUnit::Color::Red);
            std::cout << '\n' <<
ZenMockedFunctionSignature << R"(

This ZenMocked function was expected then not later asserted as having been called.
Fail fasting with exit code 1.

)";
            ZenUnit::ZenUnitArgs zenUnitArgs = _zenMockableGetZenUnitArgs();
            _zenMockableExitFunction(zenUnitArgs.exit0 ? 0 : 1);
         }
      }

      void ZenMockThrowIfAlreadyExpected()
      {
         if (expected)
         {
            _zenMockExceptionIsInPlay = true;
            throw FunctionAlreadyExpectedException(ZenMockedFunctionSignature);
         }
      }
   };
}
