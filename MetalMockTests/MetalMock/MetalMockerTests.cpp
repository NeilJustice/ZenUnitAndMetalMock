#include "pch.h"
#include "MetalMockTests/MetalMock/MetalMockExceptionThrowerMock.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/ZenUnitArgsEqualizerAndRandom.h"

struct CustomException
{
   CustomException(int, char, double) {}
};

namespace MetalMock
{
   TESTS(MetalMockerTests)
   AFACT(OneArgConstructor_SetsFields)
   AFACT(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue_runtime_error_testcase)
   AFACT(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue_CustomException_testcase)
   AFACT(MetalMockSetAsserted_SetsAssertedTrue_CallableTwice)
   AFACT(MetalMockThrowIfNotExpected_ExpectedTrue_DoesNotThrowException)
   AFACT(MetalMockThrowIfNotExpected_ExpectedFalse_ThrowsUnexpectedCallException)
   AFACT(MetalMockThrowIfExpectedNumberOfCalls0_ExpectedNumberOfCalls0_ThrowsUnsupportedCalledZeroTimesException)
   FACTS(MetalMockThrowIfExpectedNumberOfCalls0_ExpectedNumberOfCallsGreaterThan0_DoesNotThrowException)
   AFACT(MetalMockThrowIfExpectedCallsSizeIsZero_ExpectedCallsSize0_ThrowsUnsupportedCalledZeroTimesException)
   FACTS(MetalMockThrowIfExpectedCallsSizeIsZero_ExpectedCallsSizeGreaterThan0_DoesNotThrowException)
   AFACT(MetalMockThrowExceptionIfExceptionSet_CallsExceptionThrowerMetalMockThrowIfExceptionSet)
   FACTS(MetalMockExitIfExpectedButNotAsserted_ExpectedFalse_DoesNothing)
   FACTS(MetalMockExitIfExpectedButNotAsserted_ExpectedTrue_AssertedTrue_DoesNothing)
   FACTS(MetalMockExitIfExpectedButNotAsserted_ExpectedTrue_AssertedFalse_MetalMockExceptionIsInFlightFalse_WritesError_Exits1)
   AFACT(MetalMockExitIfExpectedButNotAsserted_ExpectedTrue_AssertedFalse_MetalMockExceptionIsInFlightTrue_DoesNothing)
   EVIDENCE

   unique_ptr<MetalMocker<MetalMockExceptionThrowerMock>> _metalMocker;
   METALMOCK_VOID1_FREE(exit, int)
   METALMOCK_NONVOID0_STATIC(const ZenUnit::ZenUnitArgs&, ZenUnit::ZenUnitTestRunner, GetZenUnitArgs)
   const string ExpectedMetalMockedFunctionSignature = "virtual void ClassName::FunctionName() const";

   STARTUP
   {
      _metalMocker = make_unique<MetalMocker<MetalMockExceptionThrowerMock>>(ExpectedMetalMockedFunctionSignature);
      _metalMocker->_call_exit = BIND_1ARG_METALMOCK_OBJECT(exitMock);
      _metalMocker->_call_ZenUnitTestRunner_GetZenUnitArgs = BIND_0ARG_METALMOCK_OBJECT(GetZenUnitArgsMock);
   }

   TEST(OneArgConstructor_SetsFields)
   {
      const MetalMocker<MetalMockExceptionThrower> metalMocker(ExpectedMetalMockedFunctionSignature);
      //
      STD_FUNCTION_TARGETS(exit, metalMocker._call_exit);
      STD_FUNCTION_TARGETS(ZenUnit::ZenUnitTestRunner::GetZenUnitArgs, metalMocker._call_ZenUnitTestRunner_GetZenUnitArgs);
      ARE_EQUAL(ExpectedMetalMockedFunctionSignature, metalMocker.metalMockedFunctionSignature);
      IS_FALSE(metalMocker._wasExpected);
      IS_FALSE(metalMocker._wasAsserted);
      IS_FALSE(metalMocker._metalMockExceptionIsInFlight);
   }

   TEST(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue_runtime_error_testcase)
   {
      _metalMocker->_exceptionThrower.ExpectCallToExpectAndThrowException();
      IS_FALSE(_metalMocker->_wasExpected);
      const string what = Random<string>();
      //
      _metalMocker->ThrowExceptionWhenCalled<runtime_error>(what);
      //
      _metalMocker->_exceptionThrower.AssertExpectAndThrowExceptionCalledOnceWith("std::runtime_error", 1, what);
      IS_TRUE(_metalMocker->_wasExpected);

      // Set _expected to false to prevent MetalMocked Function Expected But Not Later Asserted As Having Been Called
      _metalMocker->_wasExpected = false;
   }

   TEST(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue_CustomException_testcase)
   {
      _metalMocker->_exceptionThrower.ExpectCallToExpectAndThrowException();
      IS_FALSE(_metalMocker->_wasExpected);
      //
      _metalMocker->ThrowExceptionWhenCalled<CustomException>(1, '2', 3.3);
      //
      _metalMocker->_exceptionThrower.AssertExpectAndThrowExceptionCalledOnceWith("CustomException", 3, "123.3");
      IS_TRUE(_metalMocker->_wasExpected);

      // Set _expected to false to prevent MetalMocked Function Expected But Not Later Asserted As Having Been Called
      _metalMocker->_wasExpected = false;
      CustomException customException(1, '2', 3.3); // 100% code coverage
   }

   TEST(MetalMockSetAsserted_SetsAssertedTrue_CallableTwice)
   {
      IS_FALSE(_metalMocker->_wasAsserted);
      //
      _metalMocker->MetalMockSetAsserted();
      //
      IS_TRUE(_metalMocker->_wasAsserted);

      _metalMocker->MetalMockSetAsserted();
      IS_TRUE(_metalMocker->_wasAsserted);
   }

   TEST(MetalMockThrowIfNotExpected_ExpectedTrue_DoesNotThrowException)
   {
      _metalMocker->_wasExpected = true;
      DOES_NOT_THROW(_metalMocker->MetalMockThrowIfNotExpected());
      DOES_NOT_THROW(_metalMocker->MetalMockThrowIfNotExpected(1, 2, 3));
      _metalMocker->_wasAsserted = true;
   }

   TEST(MetalMockThrowIfNotExpected_ExpectedFalse_ThrowsUnexpectedCallException)
   {
      IS_FALSE(_metalMocker->_wasExpected);
      const string expectedExceptionMessage1 = UnexpectedCallException::MakeExceptionMessage(ExpectedMetalMockedFunctionSignature);
      THROWS_EXCEPTION(_metalMocker->MetalMockThrowIfNotExpected(),
         UnexpectedCallException, expectedExceptionMessage1);
      const string expectedExceptionMessage2 = UnexpectedCallException::MakeExceptionMessage(ExpectedMetalMockedFunctionSignature, 1, 2, 3);
      THROWS_EXCEPTION(_metalMocker->MetalMockThrowIfNotExpected(1, 2, 3),
         UnexpectedCallException, expectedExceptionMessage2);
   }

   TEST(MetalMockThrowIfExpectedNumberOfCalls0_ExpectedNumberOfCalls0_ThrowsUnsupportedCalledZeroTimesException)
   {
      THROWS_EXCEPTION(_metalMocker->MetalMockThrowIfExpectedNumberOfCalls0(0),
         UnsupportedCalledZeroTimesException, UnsupportedCalledZeroTimesException::MakeExceptionMessage(ExpectedMetalMockedFunctionSignature));
   }

   TEST1X1(MetalMockThrowIfExpectedNumberOfCalls0_ExpectedNumberOfCallsGreaterThan0_DoesNotThrowException,
      size_t expectedNumberOfCallsToMetalMockedFunction,
      1ULL,
      2ULL)
   {
      DOES_NOT_THROW(_metalMocker->MetalMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCallsToMetalMockedFunction));
   }

   TEST(MetalMockThrowIfExpectedCallsSizeIsZero_ExpectedCallsSize0_ThrowsUnsupportedCalledZeroTimesException)
   {
      THROWS_EXCEPTION(_metalMocker->MetalMockThrowIfExpectedCallsSizeIsZero(0),
         UnsupportedCalledZeroTimesException, UnsupportedCalledZeroTimesException::MakeExceptionMessage(ExpectedMetalMockedFunctionSignature));
   }

   TEST1X1(MetalMockThrowIfExpectedCallsSizeIsZero_ExpectedCallsSizeGreaterThan0_DoesNotThrowException,
      size_t expectedCallsSize,
      1ULL,
      2ULL)
   {
      DOES_NOT_THROW(_metalMocker->MetalMockThrowIfExpectedCallsSizeIsZero(expectedCallsSize));
   }

   TEST(MetalMockThrowExceptionIfExceptionSet_CallsExceptionThrowerMetalMockThrowIfExceptionSet)
   {
      _metalMocker->_exceptionThrower.ExpectCallToMetalMockThrowExceptionIfExceptionSet();
      //
      _metalMocker->MetalMockThrowExceptionIfExceptionSet();
      //
      METALMOCK(_metalMocker->_exceptionThrower.AssertMetalMockThrowExceptionIfExceptionSetCalledOnce());
   }

   TEST2X2(MetalMockExitIfExpectedButNotAsserted_ExpectedFalse_DoesNothing,
      bool asserted, bool metalMockExceptionIsInFlight,
      false, false,
      true, false,
      false, true,
      true, true)
   {
      _metalMocker->_wasExpected = false;
      _metalMocker->_wasAsserted = asserted;
      _metalMocker->_metalMockExceptionIsInFlight = metalMockExceptionIsInFlight;
      //
      _metalMocker->MetalMockExitIfExpectedButNotAsserted();
   }

   TEST1X1(MetalMockExitIfExpectedButNotAsserted_ExpectedTrue_AssertedTrue_DoesNothing,
      bool _metalMockExceptionIsInFlight,
      false,
      true)
   {
      _metalMocker->_wasExpected = true;
      _metalMocker->_wasAsserted = true;
      _metalMocker->_metalMockExceptionIsInFlight = _metalMockExceptionIsInFlight;
      //
      _metalMocker->MetalMockExitIfExpectedButNotAsserted();
   }

   TEST2X2(MetalMockExitIfExpectedButNotAsserted_ExpectedTrue_AssertedFalse_MetalMockExceptionIsInFlightFalse_WritesError_Exits1,
      bool alwaysExit0, int expectedExitCode,
      false, 1,
      true, 0)
   {
      _metalMocker->_wasExpected = true;
      _metalMocker->_wasAsserted = false;
      _metalMocker->_metalMockExceptionIsInFlight = false;

      ZenUnit::ZenUnitArgs zenUnitArgs = ZenUnit::Random<ZenUnitArgs>();
      zenUnitArgs.alwaysExit0 = alwaysExit0;
      GetZenUnitArgsMock.Return(zenUnitArgs);
      exitMock.Expect();

      cout << "\n\n<MetalMock Error Message Testing>";
      //
      _metalMocker->MetalMockExitIfExpectedButNotAsserted();
      //
      cout << "</MetalMock Error Message Testing>\n\n";
      METALMOCK(GetZenUnitArgsMock.CalledOnce());
      METALMOCK(exitMock.CalledOnceWith(expectedExitCode));
      _metalMocker->_wasAsserted = true;
   }

   TEST(MetalMockExitIfExpectedButNotAsserted_ExpectedTrue_AssertedFalse_MetalMockExceptionIsInFlightTrue_DoesNothing)
   {
      _metalMocker->_wasExpected = true;
      _metalMocker->_wasAsserted = false;
      _metalMocker->_metalMockExceptionIsInFlight = true;
      //
      _metalMocker->MetalMockExitIfExpectedButNotAsserted();
   }

   RUN_TESTS(MetalMockerTests)
}
