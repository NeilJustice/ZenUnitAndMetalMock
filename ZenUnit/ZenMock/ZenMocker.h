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
      std::function<void(int)> zenMockableExitFunction;
      std::function<ZenUnit::ZenUnitArgs()> zenMockableGetZenUnitArgs;
      bool zenMockExceptionIsInPlay;
   protected:
      MockableExceptionThrowerType exceptionThrower;
      bool expected;
      bool asserted;
      const std::string ZenMockedFunctionSignature;
   public:
      ZenMocker(const std::string& zenMockedFunctionSignature)
         : zenMockableExitFunction(::exit)
         , zenMockableGetZenUnitArgs(ZenUnit::TestRunner::GetArgs)
         , zenMockExceptionIsInPlay(false)
         , expected(false)
         , asserted(false)
         , ZenMockedFunctionSignature(zenMockedFunctionSignature)
      {
      }

      void Expect()
      {
         ThrowIfAlreadyExpected();
         expected = true;
      }

      template<typename ExceptionType, typename... ExceptionArgTypes>
      void ExpectAndThrow(ExceptionArgTypes&&... exceptionArgs)
      {
         ThrowIfAlreadyExpected();
         exceptionThrower.template ExpectAndThrow<ExceptionType>(
            std::forward<ExceptionArgTypes>(exceptionArgs)...);
         expected = true;
      }

      void ThrowIfExceptionSet()
      {
         exceptionThrower.ThrowIfExceptionSet();
      }

      ~ZenMocker()
      {
         ExitIfExpectedAndNotAsserted();
      }

   protected:
      template<typename... ArgTypes>
      void ThrowIfNotExpected(const ArgTypes&... args)
      {
         if (!expected)
         {
            zenMockExceptionIsInPlay = true;
            throw UnexpectedCallException(ZenMockedFunctionSignature, args...);
         }
      }

      void SetAsserted()
      {
         asserted = true;
      }

      void ThrowIfExpectedNumberOfCalls0(size_t expectedNumberOfCalls)
      {
         if (expectedNumberOfCalls == 0)
         {
            zenMockExceptionIsInPlay = true;
            throw UnsupportedAssertCalledZeroTimesException(ZenMockedFunctionSignature);
         }
      }

      void ThrowIfExpectedCallsSizeIsZero(size_t expectedCallsSize)
      {
         if (expectedCallsSize == 0)
         {
            zenMockExceptionIsInPlay = true;
            throw UnsupportedAssertCalledZeroTimesException(ZenMockedFunctionSignature);
         }
      }

   private:
      void ExitIfExpectedAndNotAsserted() const
      {
         if (expected && !asserted && !zenMockExceptionIsInPlay)
         {
            const ZenUnit::Console console;
            std::cout << "\n\n";
            console.WriteLineColor("Fatal Unasserted ZenMock Expectation:", ZenUnit::Color::Red);
            std::cout << '\n' <<
ZenMockedFunctionSignature << R"(

This ZenMocked function was expected then not later asserted as having been called.
Fail fasting with exit code 1.

)";
            ZenUnit::ZenUnitArgs zenUnitArgs = zenMockableGetZenUnitArgs();
            zenMockableExitFunction(zenUnitArgs.exit0 ? 0 : 1);
         }
      }

      void ThrowIfAlreadyExpected()
      {
         if (expected)
         {
            zenMockExceptionIsInPlay = true;
            throw FunctionAlreadyExpectedException(ZenMockedFunctionSignature);
         }
      }
   };
}
