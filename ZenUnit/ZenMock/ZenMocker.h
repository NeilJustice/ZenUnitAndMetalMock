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
      std::function<void(int)> _exit_ZenMockable;
      std::function<ZenUnit::ZenUnitArgs()> _TestRunner_GetArgs_ZenMockable;
      bool _zenMockExceptionIsInPlay;
   protected:
      MockableExceptionThrowerType _exceptionThrower;
      bool _expected;
      bool _asserted;
      const std::string ZenMockedFunctionSignature;
   public:
      explicit ZenMocker(std::string zenMockedFunctionSignature)
         : _exit_ZenMockable(::exit)
         , _TestRunner_GetArgs_ZenMockable(ZenUnit::TestRunner::GetArgs)
         , _zenMockExceptionIsInPlay(false)
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
            _zenMockExceptionIsInPlay = true;
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
      void ZenMockExitIfExpectedButNotAsserted() const
      {
         if (_expected && !_asserted && !_zenMockExceptionIsInPlay)
         {
            const ZenUnit::Console console;
            std::cout << "\n";
            console.WriteLineColor("Fatal Expected-But-Not-Asserted ZenMocked Function:\n", ZenUnit::Color::Red);
            console.WriteLineColor(ZenMockedFunctionSignature, ZenUnit::Color::Green);
            const ZenUnit::ZenUnitArgs& zenUnitArgs = _TestRunner_GetArgs_ZenMockable();
            std::cout << R"(
Fix for Expected-But-Not-Asserted:
After Expect()ing then calling the above ZenMocked function,
call ZEN([ZenMockedFunctionName]Mock.
[AssertCalledOnce|AssertCalledOnceWith|AssertCalledNTimes|AssertCalledNTimesWith|AssertCalls]());

Fast failing now with exit code )" <<
(zenUnitArgs.exit0 ? "0 (normally exit code 1 but -exit0 is specified).\n" : "1.\n");
            _exit_ZenMockable(zenUnitArgs.exit0 ? 0 : 1);
         }
      }

      void ZenMockThrowIfAlreadyExpected()
      {
         if (_expected)
         {
            _zenMockExceptionIsInPlay = true;
            throw FunctionAlreadyExpectedException(ZenMockedFunctionSignature);
         }
      }
   };
}
