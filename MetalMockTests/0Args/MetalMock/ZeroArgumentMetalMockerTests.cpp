#include "pch.h"
#include "MetalMockTests/MetalMock/MetalMockExceptionThrowerMock.h"

namespace MetalMock
{
   TESTS(ZeroArgumentMetalMockerTests)
   AFACT(OneArgConstructor_SetsFields)
   AFACT(ThrowExceptionWhenCalled_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(MetalMockIt_ExpectedIsFalse_ThrowsUnexpectedCallException)
   AFACT(MetalMockIt_ExpectedIsTrue_IncrementsNumberOfFunctionCalls_CallsMetalMockThrowIfExceptionSet)
   FACTS(CalledOnce_SetsAssertedToTrue_FunctionWasCalledOnce_DoesNotThrowException)
   AFACT(CalledNTimes_NIsZero_ThrowsUnsupportedCalledZeroTimesException)
   FACTS(CalledNTimes_SetsAssertedTrue_FunctionWasCalledNTimes_DoesNotThrowException)
   AFACT(CallInstead_CallsCallInsteadFunctionWhenMetalMockedFunctionIsCalled)
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
      const string metalMockedFunctionSignature = ZenUnit::Random<string>();
      //
      const ZeroArgumentMetalMocker<MetalMockExceptionThrowerMock> zeroArgumentMetalMocker(metalMockedFunctionSignature);
      //
      ARE_EQUAL(metalMockedFunctionSignature, zeroArgumentMetalMocker.p_metalMockedFunctionSignature);
      IS_FALSE(zeroArgumentMetalMocker.p_wasExpected);
      IS_FALSE(zeroArgumentMetalMocker.p_wasAsserted);
      IS_EMPTY(zeroArgumentMetalMocker.p_metalMockedFunctionCallHistory);
   }

   TEST(ThrowExceptionWhenCalled_CallsExceptionThrowerThrow_SetsExpectedTrue)
   {
      _zeroArgumentMetalMocker->p_exceptionThrower.ExpectCallToExpectAndThrowException();
      const string argumentStringValue = ZenUnit::Random<string>();
      const int argumentIntValue = ZenUnit::Random<int>();
      //
      _zeroArgumentMetalMocker->ThrowExceptionWhenCalled<TestingException>(argumentStringValue, argumentIntValue);
      //
      _zeroArgumentMetalMocker->p_exceptionThrower.AssertExpectAndThrowExceptionCalledOnceWith(
         "MetalMock::TestingException", 2, argumentStringValue + to_string(argumentIntValue));
      IS_TRUE(_zeroArgumentMetalMocker->p_wasExpected);
      _zeroArgumentMetalMocker->p_wasAsserted = true;
   }

   TEST(MetalMockIt_ExpectedIsFalse_ThrowsUnexpectedCallException)
   {
      IS_FALSE(_zeroArgumentMetalMocker->p_wasExpected);
      //
      const string expectedExceptionMessage = UnexpectedCallException::MakeExceptionMessage(_metalMockedFunctionSignature);
      THROWS_EXCEPTION(_zeroArgumentMetalMocker->MetalMockIt(),
         UnexpectedCallException, expectedExceptionMessage);
   }

   TEST(MetalMockIt_ExpectedIsTrue_IncrementsNumberOfFunctionCalls_CallsMetalMockThrowIfExceptionSet)
   {
      const unsigned long long startingGlobalAtomicFunctionCallSequenceNumberAndSignature = MetalMock::g_metalMockedFunctionCallSequenceNumber;
      _zeroArgumentMetalMocker->p_wasExpected = true;
      _zeroArgumentMetalMocker->p_exceptionThrower.ExpectCallToMetalMockThrowExceptionIfExceptionSet();
      //
      _zeroArgumentMetalMocker->MetalMockIt();
      //
      const unsigned long long endingGlobalAtomicFunctionCallSequenceNumberAndSignature = MetalMock::g_metalMockedFunctionCallSequenceNumber;
      IS_GREATER_THAN(endingGlobalAtomicFunctionCallSequenceNumberAndSignature, startingGlobalAtomicFunctionCallSequenceNumberAndSignature);
      ARE_EQUAL(1, _zeroArgumentMetalMocker->p_metalMockedFunctionCallHistory.size());
      METALMOCK(_zeroArgumentMetalMocker->p_exceptionThrower.AssertMetalMockThrowExceptionIfExceptionSetCalledOnce());
      _zeroArgumentMetalMocker->CalledOnce();
   }

   TEST2X2(CalledOnce_SetsAssertedToTrue_FunctionWasCalledOnce_DoesNotThrowException,
      size_t numberOfFunctionCalls, bool expectAnomaly,
      0ULL, true,
      1ULL, false,
      2ULL, true)
   {
      _zeroArgumentMetalMocker->p_metalMockedFunctionCallHistory.resize(numberOfFunctionCalls);
      //
      if (expectAnomaly)
      {
         const string expectedExceptionMessage = ZenUnit::String::ConcatValues(R"(
  Failed: ARE_EQUAL(expectedNumberOfFunctionCalls, p_metalMockedFunctionCallHistory.size(), this->p_metalMockedFunctionSignature)
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
      IS_TRUE(_zeroArgumentMetalMocker->p_wasAsserted);
   }

   TEST(CalledNTimes_NIsZero_ThrowsUnsupportedCalledZeroTimesException)
   {
      const string expectedExceptionMessage = UnsupportedCalledZeroTimesException::MakeExceptionMessage(_metalMockedFunctionSignature);
      THROWS_EXCEPTION(_zeroArgumentMetalMocker->CalledNTimes(0),
         UnsupportedCalledZeroTimesException, expectedExceptionMessage);
   }

   TEST3X3(CalledNTimes_SetsAssertedTrue_FunctionWasCalledNTimes_DoesNotThrowException,
      size_t expectedNumberOfFunctionCalls, size_t numberOfFunctionCalls, bool expectAnomaly,
      1ULL, 0ULL, true,

      1ULL, 1ULL, false,
      2ULL, 1ULL, true,

      1ULL, 2ULL, true,
      2ULL, 2ULL, false,
      3ULL, 2ULL, true)
   {
      _zeroArgumentMetalMocker->p_metalMockedFunctionCallHistory.resize(numberOfFunctionCalls);
      //
      if (expectAnomaly)
      {
         const string expectedExceptionMessage = ZenUnit::String::ConcatValues(R"(
  Failed: ARE_EQUAL(expectedNumberOfFunctionCalls, p_metalMockedFunctionCallHistory.size(), this->p_metalMockedFunctionSignature)
Expected: )", expectedNumberOfFunctionCalls, R"(
  Actual: )", numberOfFunctionCalls, R"(
 Message: ")", _metalMockedFunctionSignature, R"("
File.cpp(1))");
         THROWS_EXCEPTION(_zeroArgumentMetalMocker->CalledNTimes(expectedNumberOfFunctionCalls),
            Anomaly, expectedExceptionMessage);
      }
      else
      {
         _zeroArgumentMetalMocker->CalledNTimes(expectedNumberOfFunctionCalls);
      }
      //
      IS_TRUE(_zeroArgumentMetalMocker->p_wasAsserted);
   }

   TEST(CallInstead_CallsCallInsteadFunctionWhenMetalMockedFunctionIsCalled)
   {
      bool voidZeroArgFunctionWasCalled = false;
      const auto callInsteadFunction = [&]()
      {
         voidZeroArgFunctionWasCalled = true;
      };
      _zeroArgumentMetalMocker->p_exceptionThrower.ExpectCallToMetalMockThrowExceptionIfExceptionSet();
      //
      _zeroArgumentMetalMocker->CallInstead(callInsteadFunction);
      IS_TRUE(_zeroArgumentMetalMocker->p_wasAsserted);
      _zeroArgumentMetalMocker->MetalMockIt();
      //
      METALMOCK(_zeroArgumentMetalMocker->p_exceptionThrower.AssertMetalMockThrowExceptionIfExceptionSetCalledOnce());
      IS_TRUE(voidZeroArgFunctionWasCalled);
   }

   RUN_TESTS(ZeroArgumentMetalMockerTests)
}
