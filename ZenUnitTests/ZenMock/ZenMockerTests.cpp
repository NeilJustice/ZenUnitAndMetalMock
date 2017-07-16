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
   SPEC(ZenMockSetAsserted_SetsAssertedTrue_CallableTwice)
   SPEC(ZenMockThrowIfNotExpected_ExpectedTrue_DoesNotThrow)
   SPEC(ZenMockThrowIfNotExpected_ExpectedFalse_Throws)
   SPEC(ZenMockThrowIfExpectedNumberOfCalls0_ExpectedNumberOfCalls0_Throws)
   SPECX(ZenMockThrowIfExpectedNumberOfCalls0_ExpectedNumberOfCallsGreaterThan0_DoesNotThrow)
   SPEC(ZenMockThrowIfExpectedCallsSizeIsZero_ExpectedCallsSize0_Throws)
   SPECX(ZenMockThrowIfExpectedCallsSizeIsZero_ExpectedCallsSizeGreaterThan0_DoesNotThrow)
   SPEC(ZenMockThrowIfExceptionSet_CallsExceptionThrowerZenMockThrowIfExceptionSet)
   SPECX(ZenMockExitIfExpectedButNotAsserted_ExpectedFalse_DoesNothing)
   SPECX(ZenMockExitIfExpectedButNotAsserted_ExpectedTrue_AssertedTrue_DoesNothing)
   SKIPSPECX("Works when run normally and fails when run from a post-build event", ZenMockExitIfExpectedButNotAsserted_ExpectedTrue_AssertedFalse_ZenMockExceptionIsInPlayFalse_WritesError_Exits1)
   SPEC(ZenMockExitIfExpectedButNotAsserted_ExpectedTrue_AssertedFalse_ZenMockExceptionIsInPlayTrue_DoesNothing)
   SPECEND

   unique_ptr<ZenMocker<ExceptionThrowerMock>> _zenMocker;
   ZENMOCK_VOID1_FREE(exit, int)
   ZENMOCK_NONVOID0_STATIC(const ZenUnit::ZenUnitArgs&, ZenUnit::TestRunner, GetArgs)
   const string ZenMockedFunctionSignature = "virtual void ClassName::FunctionName() const";

   STARTUP
   {
      _zenMocker = make_unique<ZenMocker<ExceptionThrowerMock>>(ZenMockedFunctionSignature);
      _zenMocker->_exit_ZenMockable = ZENBIND1(exit_ZenMock);
      _zenMocker->_TestRunner_GetArgs_ZenMockable = ZENBIND0(GetArgs_ZenMock);
   }

   TEST(Constructor_SetsFields)
   {
      const ZenMocker<ExceptionThrower> zenMocker(ZenMockedFunctionSignature);
      //
      FUNCTION_TARGETS(exit, zenMocker._exit_ZenMockable);
      FUNCTION_TARGETS(ZenUnit::TestRunner::GetArgs, zenMocker._TestRunner_GetArgs_ZenMockable);
      ARE_EQUAL(ZenMockedFunctionSignature, zenMocker.ZenMockedFunctionSignature);
      IS_FALSE(zenMocker._expected);
      IS_FALSE(zenMocker._asserted);
      IS_FALSE(zenMocker._zenMockExceptionIsInPlay);
   }

   TEST(Expect_SetsExpectedTrue_ThrowsIfCalledTwice)
   {
      IS_FALSE(_zenMocker->_expected);
      //
      _zenMocker->Expect();
      //
      IS_TRUE(_zenMocker->_expected);

      THROWS(_zenMocker->Expect(), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(ZenMockedFunctionSignature));
   }

   TEST(ExpectAndThrow_CallsExceptionThrowerExpectAndThrow_SetsExpectedTrue_ThrowsIfCalledTwice_runtime_error_testcase)
   {
      _zenMocker->_exceptionThrower.ExpectCallToExpectAndThrow();
      IS_FALSE(_zenMocker->_expected);
      //
      _zenMocker->ExpectAndThrow<runtime_error>("what");
      //
      _zenMocker->_exceptionThrower.AssertExpectAndThrowCalledOnceWith("std::runtime_error", 1, "what");
      IS_TRUE(_zenMocker->_expected);

      THROWS(_zenMocker->ExpectAndThrow<invalid_argument>("what"), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(ZenMockedFunctionSignature));
   }

   TEST(ExpectAndThrow_CallsExceptionThrowerExpectAndThrow_SetsExpectedTrue_ThrowsIfCalledTwice_CustomException_testcase)
   {
      _zenMocker->_exceptionThrower.ExpectCallToExpectAndThrow();
      IS_FALSE(_zenMocker->_expected);
      //
      _zenMocker->ExpectAndThrow<CustomException>(1, '2', 3.3);
      //
      _zenMocker->_exceptionThrower.AssertExpectAndThrowCalledOnceWith("CustomException", 3, "123.3");
      IS_TRUE(_zenMocker->_expected);

      THROWS(_zenMocker->ExpectAndThrow<invalid_argument>("what"), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(ZenMockedFunctionSignature));

      CustomException customException(1, '2', 3.3); // 100% code coverage
   }

   TEST(ZenMockSetAsserted_SetsAssertedTrue_CallableTwice)
   {
      IS_FALSE(_zenMocker->_asserted);
      //
      _zenMocker->ZenMockSetAsserted();
      //
      IS_TRUE(_zenMocker->_asserted);

      _zenMocker->ZenMockSetAsserted();
      IS_TRUE(_zenMocker->_asserted);
   }

   TEST(ZenMockThrowIfNotExpected_ExpectedTrue_DoesNotThrow)
   {
      _zenMocker->_expected = true;
      NOTHROWS(_zenMocker->ZenMockThrowIfNotExpected());
      NOTHROWS(_zenMocker->ZenMockThrowIfNotExpected(1, 2, 3));
      _zenMocker->_asserted = true;
   }

   TEST(ZenMockThrowIfNotExpected_ExpectedFalse_Throws)
   {
      IS_FALSE(_zenMocker->_expected);
      THROWS(_zenMocker->ZenMockThrowIfNotExpected(), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(ZenMockedFunctionSignature));
      THROWS(_zenMocker->ZenMockThrowIfNotExpected(1, 2, 3), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(ZenMockedFunctionSignature, 1, 2, 3));
   }

   TEST(ZenMockThrowIfExpectedNumberOfCalls0_ExpectedNumberOfCalls0_Throws)
   {
      THROWS(_zenMocker->ZenMockThrowIfExpectedNumberOfCalls0(0), UnsupportedAssertCalledZeroTimesException,
         UnsupportedAssertCalledZeroTimesException::MakeWhat(ZenMockedFunctionSignature));
   }

   TEST1X1(ZenMockThrowIfExpectedNumberOfCalls0_ExpectedNumberOfCallsGreaterThan0_DoesNotThrow,
      size_t expectedNumberOfCalls,
      size_t(1),
      size_t(2))
   {
      NOTHROWS(_zenMocker->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls));
   }

   TEST(ZenMockThrowIfExpectedCallsSizeIsZero_ExpectedCallsSize0_Throws)
   {
      THROWS(_zenMocker->ZenMockThrowIfExpectedCallsSizeIsZero(0), UnsupportedAssertCalledZeroTimesException,
         UnsupportedAssertCalledZeroTimesException::MakeWhat(ZenMockedFunctionSignature));
   }

   TEST1X1(ZenMockThrowIfExpectedCallsSizeIsZero_ExpectedCallsSizeGreaterThan0_DoesNotThrow,
      size_t expectedCallsSize,
      size_t(1),
      size_t(2))
   {
      NOTHROWS(_zenMocker->ZenMockThrowIfExpectedCallsSizeIsZero(expectedCallsSize));
   }

   TEST(ZenMockThrowIfExceptionSet_CallsExceptionThrowerZenMockThrowIfExceptionSet)
   {
      _zenMocker->_exceptionThrower.ExpectCallToZenMockThrowIfExceptionSet();
      //
      _zenMocker->ZenMockThrowIfExceptionSet();
      //
      ZEN(_zenMocker->_exceptionThrower.AssertZenMockThrowIfExceptionSetCalledOnce());
   }

   TEST2X2(ZenMockExitIfExpectedButNotAsserted_ExpectedFalse_DoesNothing,
      bool asserted, bool zenMockExceptionIsInPlay,
      false, false,
      true, false,
      false, true,
      true, true)
   {
      _zenMocker->_expected = false;
      _zenMocker->_asserted = asserted;
      _zenMocker->_zenMockExceptionIsInPlay = zenMockExceptionIsInPlay;
      //
      _zenMocker->ZenMockExitIfExpectedButNotAsserted();
   }

   TEST1X1(ZenMockExitIfExpectedButNotAsserted_ExpectedTrue_AssertedTrue_DoesNothing,
      bool _zenMockExceptionIsInPlay,
      false,
      true)
   {
      _zenMocker->_expected = true;
      _zenMocker->_asserted = true;
      _zenMocker->_zenMockExceptionIsInPlay = _zenMockExceptionIsInPlay;
      //
      _zenMocker->ZenMockExitIfExpectedButNotAsserted();
   }

   TEST2X2(ZenMockExitIfExpectedButNotAsserted_ExpectedTrue_AssertedFalse_ZenMockExceptionIsInPlayFalse_WritesError_Exits1,
      bool exit0, int expectedExitCode,
      false, 1,
      true, 0)
   {
      _zenMocker->_expected = true;
      _zenMocker->_asserted = false;
      _zenMocker->_zenMockExceptionIsInPlay = false;

      ZenUnit::ZenUnitArgs zenUnitArgs;
      zenUnitArgs.exit0 = exit0;
      GetArgs_ZenMock.ExpectAndReturn(zenUnitArgs);
      exit_ZenMock.Expect();

      cout << "\n<ZenMock Error Message Testing>";
      //
      _zenMocker->ZenMockExitIfExpectedButNotAsserted();
      //
      cout << "</ZenMock Error Message Testing>\n";
      ZEN(GetArgs_ZenMock.AssertCalledOnce());
      ZEN(exit_ZenMock.AssertCalledOnceWith(expectedExitCode));
      _zenMocker->_asserted = true;
   }

   TEST(ZenMockExitIfExpectedButNotAsserted_ExpectedTrue_AssertedFalse_ZenMockExceptionIsInPlayTrue_DoesNothing)
   {
      _zenMocker->_expected = true;
      _zenMocker->_asserted = false;
      _zenMocker->_zenMockExceptionIsInPlay = true;
      //
      _zenMocker->ZenMockExitIfExpectedButNotAsserted();
   }

   }; RUN(ZenMockerTests)
}
