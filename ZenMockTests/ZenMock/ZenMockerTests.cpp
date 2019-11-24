#include "pch.h"
#include "ZenMockTests/ZenMock/ExceptionThrowerMock.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomZenUnitArgs.h"

struct CustomException
{
   CustomException(int, char, double) {}
};

namespace ZenMock
{
   TESTS(ZenMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue_runtime_error_testcase)
   AFACT(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue_CustomException_testcase)
   AFACT(ZenMockSetAsserted_SetsAssertedTrue_CallableTwice)
   AFACT(ZenMockThrowIfNotExpected_ExpectedTrue_DoesNotThrow)
   AFACT(ZenMockThrowIfNotExpected_ExpectedFalse_Throws)
   AFACT(ZenMockThrowIfExpectedNumberOfCalls0_ExpectedNumberOfCalls0_Throws)
   FACTS(ZenMockThrowIfExpectedNumberOfCalls0_ExpectedNumberOfCallsGreaterThan0_DoesNotThrow)
   AFACT(ZenMockThrowIfExpectedCallsSizeIsZero_ExpectedCallsSize0_Throws)
   FACTS(ZenMockThrowIfExpectedCallsSizeIsZero_ExpectedCallsSizeGreaterThan0_DoesNotThrow)
   AFACT(ZenMockThrowExceptionIfExceptionSet_CallsExceptionThrowerZenMockThrowIfExceptionSet)
   FACTS(ZenMockExitIfExpectedButNotAsserted_ExpectedFalse_DoesNothing)
   FACTS(ZenMockExitIfExpectedButNotAsserted_ExpectedTrue_AssertedTrue_DoesNothing)
   FACTS(ZenMockExitIfExpectedButNotAsserted_ExpectedTrue_AssertedFalse_ZenMockExceptionIsInFlightFalse_WritesError_Exits1)
   AFACT(ZenMockExitIfExpectedButNotAsserted_ExpectedTrue_AssertedFalse_ZenMockExceptionIsInFlightTrue_DoesNothing)
   EVIDENCE

   unique_ptr<ZenMocker<ExceptionThrowerMock>> _zenMocker;
   ZENMOCK_VOID1_FREE(exit, int)
   ZENMOCK_NONVOID0_STATIC(const ZenUnit::ZenUnitArgs&, ZenUnit::ZenUnitTestRunner, GetZenUnitArgs)
   const string ZenMockedFunctionSignature = "virtual void ClassName::FunctionName() const";

   STARTUP
   {
      _zenMocker = make_unique<ZenMocker<ExceptionThrowerMock>>(ZenMockedFunctionSignature);
      _zenMocker->_call_exit = BIND_1ARG_ZENMOCK_OBJECT(exitMock);
      _zenMocker->_call_ZenUnitTestRunner_GetZenUnitArgs = BIND_0ARG_ZENMOCK_OBJECT(GetZenUnitArgsMock);
   }

   TEST(Constructor_SetsFields)
   {
      const ZenMocker<ExceptionThrower> zenMocker(ZenMockedFunctionSignature);
      //
      STD_FUNCTION_TARGETS(exit, zenMocker._call_exit);
      STD_FUNCTION_TARGETS(ZenUnit::ZenUnitTestRunner::GetZenUnitArgs, zenMocker._call_ZenUnitTestRunner_GetZenUnitArgs);
      ARE_EQUAL(ZenMockedFunctionSignature, zenMocker.ZenMockedFunctionSignature);
      IS_FALSE(zenMocker._wasExpected);
      IS_FALSE(zenMocker._wasAsserted);
      IS_FALSE(zenMocker._zenMockExceptionIsInFlight);
   }

   TEST(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue_runtime_error_testcase)
   {
      _zenMocker->_exceptionThrower.ExpectCallToExpectAndThrowException();
      IS_FALSE(_zenMocker->_wasExpected);
      const string what = Random<string>();
      //
      _zenMocker->ThrowException<runtime_error>(what);
      //
      _zenMocker->_exceptionThrower.AssertExpectAndThrowExceptionCalledOnceWith("std::runtime_error", 1, what);
      IS_TRUE(_zenMocker->_wasExpected);

      _zenMocker->_wasExpected = false; // Set _expected to false to prevent Fatal EBNA
   }

   TEST(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue_CustomException_testcase)
   {
      _zenMocker->_exceptionThrower.ExpectCallToExpectAndThrowException();
      IS_FALSE(_zenMocker->_wasExpected);
      //
      _zenMocker->ThrowException<CustomException>(1, '2', 3.3);
      //
      _zenMocker->_exceptionThrower.AssertExpectAndThrowExceptionCalledOnceWith("CustomException", 3, "123.3");
      IS_TRUE(_zenMocker->_wasExpected);

      _zenMocker->_wasExpected = false; // Set _expected to false to prevent Fatal EBNA
      CustomException customException(1, '2', 3.3); // 100% code coverage
   }

   TEST(ZenMockSetAsserted_SetsAssertedTrue_CallableTwice)
   {
      IS_FALSE(_zenMocker->_wasAsserted);
      //
      _zenMocker->ZenMockSetAsserted();
      //
      IS_TRUE(_zenMocker->_wasAsserted);

      _zenMocker->ZenMockSetAsserted();
      IS_TRUE(_zenMocker->_wasAsserted);
   }

   TEST(ZenMockThrowIfNotExpected_ExpectedTrue_DoesNotThrow)
   {
      _zenMocker->_wasExpected = true;
      DOES_NOT_THROW(_zenMocker->ZenMockThrowIfNotExpected());
      DOES_NOT_THROW(_zenMocker->ZenMockThrowIfNotExpected(1, 2, 3));
      _zenMocker->_wasAsserted = true;
   }

   TEST(ZenMockThrowIfNotExpected_ExpectedFalse_Throws)
   {
      IS_FALSE(_zenMocker->_wasExpected);
      THROWS_EXCEPTION(_zenMocker->ZenMockThrowIfNotExpected(), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(ZenMockedFunctionSignature));
      THROWS_EXCEPTION(_zenMocker->ZenMockThrowIfNotExpected(1, 2, 3), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(ZenMockedFunctionSignature, 1, 2, 3));
   }

   TEST(ZenMockThrowIfExpectedNumberOfCalls0_ExpectedNumberOfCalls0_Throws)
   {
      THROWS_EXCEPTION(_zenMocker->ZenMockThrowIfExpectedNumberOfCalls0(0), UnsupportedCalledZeroTimesException,
         UnsupportedCalledZeroTimesException::MakeWhat(ZenMockedFunctionSignature));
   }

   TEST1X1(ZenMockThrowIfExpectedNumberOfCalls0_ExpectedNumberOfCallsGreaterThan0_DoesNotThrow,
      size_t expectedNumberOfCalls,
      size_t(1),
      size_t(2))
   {
      DOES_NOT_THROW(_zenMocker->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls));
   }

   TEST(ZenMockThrowIfExpectedCallsSizeIsZero_ExpectedCallsSize0_Throws)
   {
      THROWS_EXCEPTION(_zenMocker->ZenMockThrowIfExpectedCallsSizeIsZero(0), UnsupportedCalledZeroTimesException,
         UnsupportedCalledZeroTimesException::MakeWhat(ZenMockedFunctionSignature));
   }

   TEST1X1(ZenMockThrowIfExpectedCallsSizeIsZero_ExpectedCallsSizeGreaterThan0_DoesNotThrow,
      size_t expectedCallsSize,
      size_t(1),
      size_t(2))
   {
      DOES_NOT_THROW(_zenMocker->ZenMockThrowIfExpectedCallsSizeIsZero(expectedCallsSize));
   }

   TEST(ZenMockThrowExceptionIfExceptionSet_CallsExceptionThrowerZenMockThrowIfExceptionSet)
   {
      _zenMocker->_exceptionThrower.ExpectCallToZenMockThrowExceptionIfExceptionSet();
      //
      _zenMocker->ZenMockThrowExceptionIfExceptionSet();
      //
      ZENMOCK(_zenMocker->_exceptionThrower.AssertZenMockThrowExceptionIfExceptionSetCalledOnce());
   }

   TEST2X2(ZenMockExitIfExpectedButNotAsserted_ExpectedFalse_DoesNothing,
      bool asserted, bool zenMockExceptionIsInFlight,
      false, false,
      true, false,
      false, true,
      true, true)
   {
      _zenMocker->_wasExpected = false;
      _zenMocker->_wasAsserted = asserted;
      _zenMocker->_zenMockExceptionIsInFlight = zenMockExceptionIsInFlight;
      //
      _zenMocker->ZenMockExitIfExpectedButNotAsserted();
   }

   TEST1X1(ZenMockExitIfExpectedButNotAsserted_ExpectedTrue_AssertedTrue_DoesNothing,
      bool _zenMockExceptionIsInFlight,
      false,
      true)
   {
      _zenMocker->_wasExpected = true;
      _zenMocker->_wasAsserted = true;
      _zenMocker->_zenMockExceptionIsInFlight = _zenMockExceptionIsInFlight;
      //
      _zenMocker->ZenMockExitIfExpectedButNotAsserted();
   }

   TEST2X2(ZenMockExitIfExpectedButNotAsserted_ExpectedTrue_AssertedFalse_ZenMockExceptionIsInFlightFalse_WritesError_Exits1,
      bool exitZero, int expectedExitCode,
      false, 1,
      true, 0)
   {
      _zenMocker->_wasExpected = true;
      _zenMocker->_wasAsserted = false;
      _zenMocker->_zenMockExceptionIsInFlight = false;

      ZenUnit::ZenUnitArgs zenUnitArgs = ZenUnit::Random<ZenUnitArgs>();
      zenUnitArgs.exitZero = exitZero;
      GetZenUnitArgsMock.Return(zenUnitArgs);
      exitMock.Expect();

      cout << "\n\n<ZenMock Error Message Testing>";
      //
      _zenMocker->ZenMockExitIfExpectedButNotAsserted();
      //
      cout << "</ZenMock Error Message Testing>\n\n";
      ZENMOCK(GetZenUnitArgsMock.CalledOnce());
      ZENMOCK(exitMock.CalledOnceWith(expectedExitCode));
      _zenMocker->_wasAsserted = true;
   }

   TEST(ZenMockExitIfExpectedButNotAsserted_ExpectedTrue_AssertedFalse_ZenMockExceptionIsInFlightTrue_DoesNothing)
   {
      _zenMocker->_wasExpected = true;
      _zenMocker->_wasAsserted = false;
      _zenMocker->_zenMockExceptionIsInFlight = true;
      //
      _zenMocker->ZenMockExitIfExpectedButNotAsserted();
   }

   RUN_TESTS(ZenMockerTests)
}
