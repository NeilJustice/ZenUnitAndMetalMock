#pragma once
#include "ZenUnit/Args/ZenUnitArgs.h"
#include "ZenUnit/Console/Console.h"
#include "ZenUnit/TestRunners/TestRunner.h"
#include "ZenUnit/ZenMock/Exceptions/ExceptionThrower.h"
#include "ZenUnit/ZenMock/Exceptions/FunctionAlreadyExpectedException.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenUnit/ZenMock/Exceptions/UnsupportedAssertCalledZeroTimesException.h"

namespace ZenMock
{
   template<typename MockableExceptionThrowerType>
   class ZenMocker
   {
      friend class ZenMockerTests;
   private:
      std::function<void(int)> call_exit;
      std::function<ZenUnit::ZenUnitArgs()> call_TestRunner_GetArgs;
      bool _zenMockExceptionIsInFlight;
   protected:
      MockableExceptionThrowerType _exceptionThrower;
      bool _expected;
      bool _asserted;
      const std::string ZenMockedFunctionSignature;
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

      void Expect()
      {
         ZenMockThrowIfAlreadyExpected();
         _expected = true;
      }

      template<typename ExceptionType, typename... ExceptionArgTypes>
      void ExpectAndThrow(ExceptionArgTypes&&... exceptionArgs)
      {
         ZenMockThrowIfAlreadyExpected();
         _exceptionThrower.template ExpectAndThrow<ExceptionType>(
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
            throw UnsupportedAssertCalledZeroTimesException(ZenMockedFunctionSignature);
         }
      }

      void ZenMockThrowIfExpectedCallsSizeIsZero(size_t expectedCallsSize)
      {
         if (expectedCallsSize == 0)
         {
            _zenMockExceptionIsInFlight = true;
            throw UnsupportedAssertCalledZeroTimesException(ZenMockedFunctionSignature);
         }
      }

   private:
      void ZenMockExitIfExpectedButNotAsserted() const
      {
         if (_expected && !_asserted && !_zenMockExceptionIsInFlight)
         {
            const ZenUnit::Console console;
            std::cout << "\n";
            console.WriteLineColor("Fatal Expected-But-Not-Asserted ZenMocked Function:", ZenUnit::Color::Red);
            console.WriteLineColor(ZenMockedFunctionSignature, ZenUnit::Color::White);
            const ZenUnit::ZenUnitArgs& zenUnitArgs = call_TestRunner_GetArgs();
            int exitCode = zenUnitArgs.exit0 ? 0 : 1;
            call_exit(exitCode);
         }
      }

      void ZenMockThrowIfAlreadyExpected()
      {
         if (_expected)
         {
            _zenMockExceptionIsInFlight = true;
            throw FunctionAlreadyExpectedException(ZenMockedFunctionSignature);
         }
      }
   };
}
