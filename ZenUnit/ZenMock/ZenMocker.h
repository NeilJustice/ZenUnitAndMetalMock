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
      std::function<void(int)> _zenMockableExitFunction;
      std::function<ZenUnit::ZenUnitArgs()> _zenMockableGetZenUnitArgs;
      bool _zenMockExceptionIsInPlay;
   protected:
      MockableExceptionThrowerType _exceptionThrower;
      bool _expected;
      bool _asserted;
      const std::string ZenMockedFunctionSignature;
   public:
      explicit ZenMocker(std::string zenMockedFunctionSignature)
         : _zenMockableExitFunction(::exit)
         , _zenMockableGetZenUnitArgs(ZenUnit::TestRunner::GetArgs)
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
         if (!_expected)
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
         if (_expected && !_asserted && !_zenMockExceptionIsInPlay)
         {
            const ZenUnit::Console console;
            std::cout << "\n\n";
            console.WriteLineColor("Expected But Not Asserted ZenMocked Function:", ZenUnit::Color::Red);
            std::cout << "\n" <<
ZenMockedFunctionSignature << R"(

Fix for this: After expecting then calling the above ZenMocked function in your unit test, 
call [ZenMockedFunctionName]Mock.
[AssertCalledOnce|AssertCalledOnceWith|AssertCalledNTimes|AssertCalledNTimesWith|AssertCalls]();

Fail fasting with exit code 1.
)";
            ZenUnit::ZenUnitArgs zenUnitArgs = _zenMockableGetZenUnitArgs();
            _zenMockableExitFunction(zenUnitArgs.exit0 ? 0 : 1);
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
