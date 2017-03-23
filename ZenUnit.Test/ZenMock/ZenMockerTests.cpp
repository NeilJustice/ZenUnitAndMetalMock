#include "pch.h"
#include "Mock/ExceptionThrowerMock.h"

struct CustomException
{
   CustomException(int, char, double) {}
};

namespace ZenMock
{
   TESTS(ZenMockerTests)
   SPEC(Constructor_SetsFields)
   SPEC(Expect_SetsExpectedTrue_ThrowsIfCalledTwice)
   SPEC(ExpectAndThrow_CallsExceptionThrowerExpectAndThrow_SetsExpectedTrue_ThrowsIfCalledTwice_runtime_error_testcase)
   SPEC(ExpectAndThrow_CallsExceptionThrowerExpectAndThrow_SetsExpectedTrue_ThrowsIfCalledTwice_CustomException_testcase)
   SPEC(SetAsserted_SetsAssertedTrue_CallableTwice)
   SPEC(ThrowIfNotExpected_ExpectedTrue_DoesNotThrow)
   SPEC(ThrowIfNotExpected_ExpectedFalse_Throws)
   SPEC(ThrowIfExpectedNumberOfCalls0_ExpectedNumberOfCalls0_Throws)
   SPECX(ThrowIfExpectedNumberOfCalls0_ExpectedNumberOfCallsGreaterThan0_DoesNotThrow)
   SPEC(ThrowIfExpectedCallsSizeIsZero_ExpectedCallsSize0_Throws)
   SPECX(ThrowIfExpectedCallsSizeIsZero_ExpectedCallsSizeGreaterThan0_DoesNotThrow)
   SPEC(ThrowIfExceptionSet_CallsExceptionThrowerThrowIfExceptionSet)
   SPECX(ExitIfExpectedAndNotAsserted_ExpectedFalse_DoesNothing)
   SPECX(ExitIfExpectedAndNotAsserted_ExpectedTrue_AssertedTrue_DoesNothing)
   SPECX(ExitIfExpectedAndNotAsserted_ExpectedTrue_AssertedFalse_ZenMockExceptionIsInPlayFalse_WritesError_Exits1)
   SPEC(ExitIfExpectedAndNotAsserted_ExpectedTrue_AssertedFalse_ZenMockExceptionIsInPlayTrue_DoesNothing)
   SPECEND

   unique_ptr<ZenMocker<ExceptionThrowerMock>> _zenMocker;
   ZENMOCK_VOID1_GLOBAL(exit, int)
   ZENMOCK_NONVOID0_STATIC(ZenUnit::ZenUnitArgs, ZenUnit::TestRunner, GetArgs)
   const string ZenMockedFunctionSignature = "virtual void ClassName::FunctionName() const";

   STARTUP
   {
      _zenMocker.reset(new ZenMocker<ExceptionThrowerMock>(ZenMockedFunctionSignature));
      _zenMocker->zenMockableExitFunction = ZENBIND1(exit_ZenMock);
      _zenMocker->zenMockableGetZenUnitArgs = ZENBIND0(GetArgs_ZenMock);
   }

   TEST(Constructor_SetsFields)
   {
      ZenMocker<ExceptionThrower> zenMocker(ZenMockedFunctionSignature);
      //
      FUNCTION_TARGETS(exit, zenMocker.zenMockableExitFunction);
      FUNCTION_TARGETS(ZenUnit::TestRunner::GetArgs, zenMocker.zenMockableGetZenUnitArgs);
      ARE_EQUAL(ZenMockedFunctionSignature, zenMocker.ZenMockedFunctionSignature);
      IS_FALSE(zenMocker.expected);
      IS_FALSE(zenMocker.asserted);
      IS_FALSE(zenMocker.zenMockExceptionIsInPlay);
   }

   TEST(Expect_SetsExpectedTrue_ThrowsIfCalledTwice)
   {
      IS_FALSE(_zenMocker->expected);
      //
      _zenMocker->Expect();
      //
      IS_TRUE(_zenMocker->expected);

      THROWS(_zenMocker->Expect(), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(ZenMockedFunctionSignature));
   }

   TEST(ExpectAndThrow_CallsExceptionThrowerExpectAndThrow_SetsExpectedTrue_ThrowsIfCalledTwice_runtime_error_testcase)
   {
      _zenMocker->exceptionThrower.ExpectCallToExpectAndThrow();
      IS_FALSE(_zenMocker->expected);
      //
      _zenMocker->ExpectAndThrow<runtime_error>("what");
      //
      _zenMocker->exceptionThrower.AssertExpectAndThrowCalledOnceWith(
         "std::runtime_error", 1, "what");
      IS_TRUE(_zenMocker->expected);

      THROWS(_zenMocker->ExpectAndThrow<invalid_argument>("what"), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(ZenMockedFunctionSignature));
   }

   TEST(ExpectAndThrow_CallsExceptionThrowerExpectAndThrow_SetsExpectedTrue_ThrowsIfCalledTwice_CustomException_testcase)
   {
      _zenMocker->exceptionThrower.ExpectCallToExpectAndThrow();
      IS_FALSE(_zenMocker->expected);
      //
      _zenMocker->ExpectAndThrow<CustomException>(1, '2', 3.3);
      //
      _zenMocker->exceptionThrower.AssertExpectAndThrowCalledOnceWith("CustomException", 3, "123.3");
      IS_TRUE(_zenMocker->expected);

      THROWS(_zenMocker->ExpectAndThrow<invalid_argument>("what"), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(ZenMockedFunctionSignature));
   }

   TEST(SetAsserted_SetsAssertedTrue_CallableTwice)
   {
      IS_FALSE(_zenMocker->asserted);
      //
      _zenMocker->SetAsserted();
      //
      IS_TRUE(_zenMocker->asserted);

      _zenMocker->SetAsserted();
      IS_TRUE(_zenMocker->asserted);
   }

   TEST(ThrowIfNotExpected_ExpectedTrue_DoesNotThrow)
   {
      _zenMocker->expected = true;
      NOTHROWS(_zenMocker->ThrowIfNotExpected());
      NOTHROWS(_zenMocker->ThrowIfNotExpected(1, 2, 3));
      _zenMocker->asserted = true;
   }

   TEST(ThrowIfNotExpected_ExpectedFalse_Throws)
   {
      IS_FALSE(_zenMocker->expected);
      THROWS(_zenMocker->ThrowIfNotExpected(), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(ZenMockedFunctionSignature));
      THROWS(_zenMocker->ThrowIfNotExpected(1, 2, 3), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(ZenMockedFunctionSignature, 1, 2, 3));
   }

   TEST(ThrowIfExpectedNumberOfCalls0_ExpectedNumberOfCalls0_Throws)
   {
      THROWS(_zenMocker->ThrowIfExpectedNumberOfCalls0(0), UnsupportedAssertCalledZeroTimesException,
         UnsupportedAssertCalledZeroTimesException::MakeWhat(ZenMockedFunctionSignature));
   }

   TEST1X1(ThrowIfExpectedNumberOfCalls0_ExpectedNumberOfCallsGreaterThan0_DoesNotThrow,
      size_t expectedNumberOfCalls,
      1ull,
      2ull)
   {
      NOTHROWS(_zenMocker->ThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls));
   }

   TEST(ThrowIfExpectedCallsSizeIsZero_ExpectedCallsSize0_Throws)
   {
      THROWS(_zenMocker->ThrowIfExpectedCallsSizeIsZero(0), UnsupportedAssertCalledZeroTimesException,
         UnsupportedAssertCalledZeroTimesException::MakeWhat(ZenMockedFunctionSignature));
   }

   TEST1X1(ThrowIfExpectedCallsSizeIsZero_ExpectedCallsSizeGreaterThan0_DoesNotThrow,
      size_t expectedCallsSize,
      1ull,
      2ull)
   {
      NOTHROWS(_zenMocker->ThrowIfExpectedCallsSizeIsZero(expectedCallsSize));
   }

   TEST(ThrowIfExceptionSet_CallsExceptionThrowerThrowIfExceptionSet)
   {
      _zenMocker->exceptionThrower.ExpectCallToThrowIfExceptionSet();
      //
      _zenMocker->ThrowIfExceptionSet();
      //
      ZEN(_zenMocker->exceptionThrower.AssertThrowIfExceptionSetCalledOnce());
   }

   TEST2X2(ExitIfExpectedAndNotAsserted_ExpectedFalse_DoesNothing,
      bool asserted, bool zenMockExceptionIsInPlay,
      false, false,
      true, false,
      false, true,
      true, true)
   {
      _zenMocker->expected = false;
      _zenMocker->asserted = asserted;
      _zenMocker->zenMockExceptionIsInPlay = zenMockExceptionIsInPlay;
      //
      _zenMocker->ExitIfExpectedAndNotAsserted();
   }

   TEST1X1(ExitIfExpectedAndNotAsserted_ExpectedTrue_AssertedTrue_DoesNothing,
      bool zenMockExceptionIsInPlay,
      false,
      true)
   {
      _zenMocker->expected = true;
      _zenMocker->asserted = true;
      _zenMocker->zenMockExceptionIsInPlay = zenMockExceptionIsInPlay;
      //
      _zenMocker->ExitIfExpectedAndNotAsserted();
   }

   TEST2X2(ExitIfExpectedAndNotAsserted_ExpectedTrue_AssertedFalse_ZenMockExceptionIsInPlayFalse_WritesError_Exits1,
      bool exit0, int expectedExitCode,
      false, 1,
      true, 0)
   {
      _zenMocker->expected = true;
      _zenMocker->asserted = false;
      _zenMocker->zenMockExceptionIsInPlay = false;

      ZenUnit::ZenUnitArgs zenUnitArgs;
      zenUnitArgs.exit0 = exit0;
      GetArgs_ZenMock.ExpectAndReturn(zenUnitArgs);
      exit_ZenMock.Expect();

      cout << "\n<ZenMock Error Message Testing>";
      //
      _zenMocker->ExitIfExpectedAndNotAsserted();
      //
      cout << "</ZenMock Error Message Testing>\n";
      ZEN(GetArgs_ZenMock.AssertCalledOnce());
      ZEN(exit_ZenMock.AssertCalledOnceWith(expectedExitCode));
      _zenMocker->asserted = true;
   }

   TEST(ExitIfExpectedAndNotAsserted_ExpectedTrue_AssertedFalse_ZenMockExceptionIsInPlayTrue_DoesNothing)
   {
      _zenMocker->expected = true;
      _zenMocker->asserted = false;
      _zenMocker->zenMockExceptionIsInPlay = true;
      //
      _zenMocker->ExitIfExpectedAndNotAsserted();
   }

   }; RUN(ZenMockerTests)
}
