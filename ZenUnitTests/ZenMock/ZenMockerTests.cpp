#include "pch.h"
#include "ZenUnitTests/ZenMock/Mock/ExceptionThrowerMock.h"

struct CustomException
{
   CustomException(int, char, double) {}
};

namespace ZenMock
{
   TESTS(ZenMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(ExpectAndThrow_CallsExceptionThrowerExpectAndThrow_SetsExpectedTrue_ThrowsIfCalledTwice_runtime_error_testcase)
   AFACT(ExpectAndThrow_CallsExceptionThrowerExpectAndThrow_SetsExpectedTrue_ThrowsIfCalledTwice_CustomException_testcase)
   AFACT(ZenMockSetAsserted_SetsAssertedTrue_CallableTwice)
   AFACT(ZenMockThrowIfNotExpected_ExpectedTrue_DoesNotThrow)
   AFACT(ZenMockThrowIfNotExpected_ExpectedFalse_Throws)
   AFACT(ZenMockThrowIfExpectedNumberOfCalls0_ExpectedNumberOfCalls0_Throws)
   FACTS(ZenMockThrowIfExpectedNumberOfCalls0_ExpectedNumberOfCallsGreaterThan0_DoesNotThrow)
   AFACT(ZenMockThrowIfExpectedCallsSizeIsZero_ExpectedCallsSize0_Throws)
   FACTS(ZenMockThrowIfExpectedCallsSizeIsZero_ExpectedCallsSizeGreaterThan0_DoesNotThrow)
   AFACT(ZenMockThrowIfExceptionSet_CallsExceptionThrowerZenMockThrowIfExceptionSet)
   FACTS(ZenMockExitIfExpectedButNotAsserted_ExpectedFalse_DoesNothing)
   FACTS(ZenMockExitIfExpectedButNotAsserted_ExpectedTrue_AssertedTrue_DoesNothing)
   FACTS(ZenMockExitIfExpectedButNotAsserted_ExpectedTrue_AssertedFalse_ZenMockExceptionIsInFlightFalse_WritesError_Exits1)
   AFACT(ZenMockExitIfExpectedButNotAsserted_ExpectedTrue_AssertedFalse_ZenMockExceptionIsInFlightTrue_DoesNothing)
   EVIDENCE

   unique_ptr<ZenMocker<ExceptionThrowerMock>> _zenMocker;
   ZENMOCK_VOID1_FREE(exit, int)
   ZENMOCK_NONVOID0_STATIC(const ZenUnit::ZenUnitArgs&, ZenUnit::TestRunner, GetArgs)
   const string ZenMockedFunctionSignature = "virtual void ClassName::FunctionName() const";

   STARTUP
   {
      _zenMocker = make_unique<ZenMocker<ExceptionThrowerMock>>(ZenMockedFunctionSignature);
      _zenMocker->call_exit = ZENMOCK_BIND1(exit_ZenMock);
      _zenMocker->call_TestRunner_GetArgs = ZENMOCK_BIND0(GetArgs_ZenMock);
   }

   TEST(Constructor_SetsFields)
   {
      const ZenMocker<ExceptionThrower> zenMocker(ZenMockedFunctionSignature);
      //
      STD_FUNCTION_TARGETS(exit, zenMocker.call_exit);
      STD_FUNCTION_TARGETS(ZenUnit::TestRunner::GetArgs, zenMocker.call_TestRunner_GetArgs);
      ARE_EQUAL(ZenMockedFunctionSignature, zenMocker.ZenMockedFunctionSignature);
      IS_FALSE(zenMocker._expected);
      IS_FALSE(zenMocker._asserted);
      IS_FALSE(zenMocker._zenMockExceptionIsInFlight);
   }

   TEST(ExpectAndThrow_CallsExceptionThrowerExpectAndThrow_SetsExpectedTrue_ThrowsIfCalledTwice_runtime_error_testcase)
   {
      _zenMocker->_exceptionThrower.ExpectCallToExpectAndThrow();
      IS_FALSE(_zenMocker->_expected);
      const string what = Random<string>();
      //
      _zenMocker->ExpectAndThrow<runtime_error>(what);
      //
      _zenMocker->_exceptionThrower.AssertExpectAndThrowCalledOnceWith("std::runtime_error", 1, what);
      IS_TRUE(_zenMocker->_expected);

      THROWS(_zenMocker->ExpectAndThrow<invalid_argument>(what), FunctionAlreadyExpectedException,
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
      bool asserted, bool zenMockExceptionIsInFlight,
      false, false,
      true, false,
      false, true,
      true, true)
   {
      _zenMocker->_expected = false;
      _zenMocker->_asserted = asserted;
      _zenMocker->_zenMockExceptionIsInFlight = zenMockExceptionIsInFlight;
      //
      _zenMocker->ZenMockExitIfExpectedButNotAsserted();
   }

   TEST1X1(ZenMockExitIfExpectedButNotAsserted_ExpectedTrue_AssertedTrue_DoesNothing,
      bool _zenMockExceptionIsInFlight,
      false,
      true)
   {
      _zenMocker->_expected = true;
      _zenMocker->_asserted = true;
      _zenMocker->_zenMockExceptionIsInFlight = _zenMockExceptionIsInFlight;
      //
      _zenMocker->ZenMockExitIfExpectedButNotAsserted();
   }

   TEST2X2(ZenMockExitIfExpectedButNotAsserted_ExpectedTrue_AssertedFalse_ZenMockExceptionIsInFlightFalse_WritesError_Exits1,
      bool exit0, int expectedExitCode,
      false, 1,
      true, 0)
   {
      _zenMocker->_expected = true;
      _zenMocker->_asserted = false;
      _zenMocker->_zenMockExceptionIsInFlight = false;

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

   TEST(ZenMockExitIfExpectedButNotAsserted_ExpectedTrue_AssertedFalse_ZenMockExceptionIsInFlightTrue_DoesNothing)
   {
      _zenMocker->_expected = true;
      _zenMocker->_asserted = false;
      _zenMocker->_zenMockExceptionIsInFlight = true;
      //
      _zenMocker->ZenMockExitIfExpectedButNotAsserted();
   }

   }; RUNTESTS(ZenMockerTests)
}
