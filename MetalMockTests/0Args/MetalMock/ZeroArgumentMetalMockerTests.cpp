#include "pch.h"
#include "MetalMockTests/MetalMock/MetalMockExceptionThrowerMock.h"

namespace MetalMock
{
   TESTS(ZeroArgumentMetalMockerTests)
   AFACT(OneArgConstructor_SetsFields)
   AFACT(ThrowExceptionWhenCalled_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(MetalMockIt_ExpectedIsFalse_ThrowsUnexpectedCallException)
   AFACT(MetalMockIt_ExpectedIsTrue_IncrementsNumberOfCalls_CallsMetalMockThrowIfExceptionSet)
   FACTS(CalledOnce_SetsAssertedToTrue_FunctionWasCalledOnce_DoesNotThrowException)
   AFACT(CalledNTimes_NIsZero_ThrowsUnsupportedCalledZeroTimesException)
   FACTS(CalledNTimes_SetsAssertedTrue_FunctionWasCalledNTimes_DoesNotThrowException)
   AFACT(CallInstead_SetsTheCallInsteadFunction_SetsWasAssertedToTrue_MetalMockItCallsTheInsteadFunctionOnceWhenCalled)
   EVIDENCE

   unique_ptr<ZeroArgumentMetalMocker<MetalMockExceptionThrowerMock>> _zeroArgumentMetalMocker;
   string _metalMockedFunctionSignature;

   STARTUP
   {
      _metalMockedFunctionSignature = ZenUnit::Random<string>();
      _zeroArgumentMetalMocker = make_unique<ZeroArgumentMetalMocker<MetalMockExceptionThrowerMock>>(_metalMockedFunctionSignature);
   }

   TEST(OneArgConstructor_SetsFields)
   {
      const ZeroArgumentMetalMocker<MetalMockExceptionThrowerMock> zeroArgumentMetalMocker(_metalMockedFunctionSignature);
      //
      ARE_EQUAL(_metalMockedFunctionSignature, zeroArgumentMetalMocker.metalMockedFunctionSignature);
      IS_FALSE(zeroArgumentMetalMocker.wasExpected);
      IS_FALSE(zeroArgumentMetalMocker.wasAsserted);
      IS_EMPTY(zeroArgumentMetalMocker.metalMockedFunctionCallSequenceNumbers);
   }

   TEST(ThrowExceptionWhenCalled_CallsExceptionThrowerThrow_SetsExpectedTrue)
   {
      _zeroArgumentMetalMocker->_exceptionThrower.ExpectCallToExpectAndThrowException();
      const string argumentStringValue = ZenUnit::Random<string>();
      const int argumentIntValue = ZenUnit::Random<int>();
      //
      _zeroArgumentMetalMocker->ThrowExceptionWhenCalled<TestingException>(argumentStringValue, argumentIntValue);
      //
      _zeroArgumentMetalMocker->_exceptionThrower.AssertExpectAndThrowExceptionCalledOnceWith(
         "MetalMock::TestingException", 2, argumentStringValue + to_string(argumentIntValue));
      IS_TRUE(_zeroArgumentMetalMocker->wasExpected);
      _zeroArgumentMetalMocker->wasAsserted = true;
   }

   TEST(MetalMockIt_ExpectedIsFalse_ThrowsUnexpectedCallException)
   {
      IS_FALSE(_zeroArgumentMetalMocker->wasExpected);
      //
      const string expectedExceptionMessage = UnexpectedCallException::MakeExceptionMessage(_metalMockedFunctionSignature);
      THROWS_EXCEPTION(_zeroArgumentMetalMocker->MetalMockIt(),
         UnexpectedCallException, expectedExceptionMessage);
   }

   TEST(MetalMockIt_ExpectedIsTrue_IncrementsNumberOfCalls_CallsMetalMockThrowIfExceptionSet)
   {
      const unsigned long long startingGlobalAtomicFunctionCallSequenceNumber = MetalMock::_globalAtomicFunctionCallSequenceNumber;
      _zeroArgumentMetalMocker->wasExpected = true;
      _zeroArgumentMetalMocker->_exceptionThrower.ExpectCallToMetalMockThrowExceptionIfExceptionSet();
      //
      _zeroArgumentMetalMocker->MetalMockIt();
      //
      const unsigned long long endingGlobalAtomicFunctionCallSequenceNumber = MetalMock::_globalAtomicFunctionCallSequenceNumber;
      IS_GT(endingGlobalAtomicFunctionCallSequenceNumber, startingGlobalAtomicFunctionCallSequenceNumber);
      ARE_EQUAL(1, _zeroArgumentMetalMocker->metalMockedFunctionCallSequenceNumbers.size());
      METALMOCK(_zeroArgumentMetalMocker->_exceptionThrower.AssertMetalMockThrowExceptionIfExceptionSetCalledOnce());
      DOES_NOT_THROW(_zeroArgumentMetalMocker->CalledOnce());
   }

   TEST2X2(CalledOnce_SetsAssertedToTrue_FunctionWasCalledOnce_DoesNotThrowException,
      size_t numberOfFunctionCalls, bool expectAnomaly,
      0ULL, true,
      1ULL, false,
      2ULL, true)
   {
      _zeroArgumentMetalMocker->metalMockedFunctionCallSequenceNumbers.resize(numberOfFunctionCalls);
      //
      if (expectAnomaly)
      {
         const string expectedExceptionMessage = ZenUnit::String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallSequenceNumbers.size(), this->metalMockedFunctionSignature)
Expected: 1
  Actual: )", numberOfFunctionCalls, R"(
 Message: ")", _metalMockedFunctionSignature, R"("
File.cpp(1))");
         THROWS_EXCEPTION(_zeroArgumentMetalMocker->CalledOnce(), Anomaly, expectedExceptionMessage);
      }
      else
      {
         _zeroArgumentMetalMocker->CalledOnce();
      }
      //
      IS_TRUE(_zeroArgumentMetalMocker->wasAsserted);
   }

   TEST(CalledNTimes_NIsZero_ThrowsUnsupportedCalledZeroTimesException)
   {
      const string expectedExceptionMessage = UnsupportedCalledZeroTimesException::MakeExceptionMessage(_metalMockedFunctionSignature);
      THROWS_EXCEPTION(_zeroArgumentMetalMocker->CalledNTimes(0),
         UnsupportedCalledZeroTimesException, expectedExceptionMessage);
   }

   TEST3X3(CalledNTimes_SetsAssertedTrue_FunctionWasCalledNTimes_DoesNotThrowException,
      size_t expectedNumberOfCallsToMetalMockedFunction, size_t numberOfFunctionCalls, bool expectAnomaly,
      1ULL, 0ULL, true,

      1ULL, 1ULL, false,
      2ULL, 1ULL, true,

      1ULL, 2ULL, true,
      2ULL, 2ULL, false,
      3ULL, 2ULL, true)
   {
      _zeroArgumentMetalMocker->metalMockedFunctionCallSequenceNumbers.resize(numberOfFunctionCalls);
      //
      if (expectAnomaly)
      {
         const string expectedExceptionMessage = ZenUnit::String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallSequenceNumbers.size(), this->metalMockedFunctionSignature)
Expected: )", expectedNumberOfCallsToMetalMockedFunction, R"(
  Actual: )", numberOfFunctionCalls, R"(
 Message: ")", _metalMockedFunctionSignature, R"("
File.cpp(1))");
         THROWS_EXCEPTION(_zeroArgumentMetalMocker->CalledNTimes(expectedNumberOfCallsToMetalMockedFunction),
            Anomaly, expectedExceptionMessage);
      }
      else
      {
         _zeroArgumentMetalMocker->CalledNTimes(expectedNumberOfCallsToMetalMockedFunction);
      }
      //
      IS_TRUE(_zeroArgumentMetalMocker->wasAsserted);
   }

   TEST(CallInstead_SetsTheCallInsteadFunction_SetsWasAssertedToTrue_MetalMockItCallsTheInsteadFunctionOnceWhenCalled)
   {
      bool voidZeroArgFunctionWasCalled = false;
      const auto callInsteadFunction = [&]()
      {
         voidZeroArgFunctionWasCalled = true;
      };
      _zeroArgumentMetalMocker->_exceptionThrower.ExpectCallToMetalMockThrowExceptionIfExceptionSet();
      //
      _zeroArgumentMetalMocker->CallInstead(callInsteadFunction);
      IS_TRUE(_zeroArgumentMetalMocker->wasAsserted);
      _zeroArgumentMetalMocker->MetalMockIt();
      //
      METALMOCK(_zeroArgumentMetalMocker->_exceptionThrower.AssertMetalMockThrowExceptionIfExceptionSetCalledOnce());
      IS_TRUE(voidZeroArgFunctionWasCalled);
   }

   RUN_TESTS(ZeroArgumentMetalMockerTests)
}
