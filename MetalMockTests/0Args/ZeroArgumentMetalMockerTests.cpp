#include "pch.h"
#include "MetalMockTests/MetalMock/MetalMockExceptionThrowerMock.h"

namespace MetalMock
{
   TESTS(ZeroArgumentMetalMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(ThrowExceptionWhenCalled_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(MetalMockIt_ExpectedFalse_ThrowsUnexpectedCallException)
   AFACT(MetalMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsMetalMockThrowIfExceptionSet)
   FACTS(CalledOnce_SetsAssertedTrue_FunctionWasCalledOnce_DoesNotThrowException)
   AFACT(CalledNTimes_NIsZero_ThrowsUnsupportedCalledZeroTimesException)
   FACTS(CalledNTimes_SetsAssertedTrue_FunctionWasCalledNTimes_DoesNotThrowException)
   AFACT(CallInstead_CallsSuppliedFunctionWhenMetalMockedFunctionIsCalled)
   EVIDENCE

   using ZeroArgumentMetalMockerType = ZeroArgumentMetalMocker<MetalMockExceptionThrowerMock>;
   unique_ptr<ZeroArgumentMetalMockerType> _zeroArgumentMetalMocker;
   string _metalMockedFunctionSignature;

   STARTUP
   {
      _metalMockedFunctionSignature = ZenUnit::Random<string>();
      _zeroArgumentMetalMocker = make_unique<ZeroArgumentMetalMockerType>(_metalMockedFunctionSignature);
   }

   TEST(Constructor_SetsFields)
   {
      const ZeroArgumentMetalMockerType zeroArgumentMetalMocker(_metalMockedFunctionSignature);
      //
      ARE_EQUAL(_metalMockedFunctionSignature, zeroArgumentMetalMocker.MetalMockedFunctionSignature);
      IS_FALSE(zeroArgumentMetalMocker._wasExpected);
      IS_FALSE(zeroArgumentMetalMocker._wasAsserted);
      IS_ZERO(zeroArgumentMetalMocker.actualNumberOfCalls);
   }

   TEST(ThrowExceptionWhenCalled_CallsExceptionThrowerThrow_SetsExpectedTrue)
   {
      IS_FALSE(_zeroArgumentMetalMocker->_wasExpected);
      _zeroArgumentMetalMocker->_exceptionThrower.ExpectCallToExpectAndThrowException();
      const string argumentStringValue = ZenUnit::Random<string>();
      const int argumentIntValue = ZenUnit::Random<int>();
      //
      _zeroArgumentMetalMocker->ThrowExceptionWhenCalled<TestingException>(argumentStringValue, argumentIntValue);
      //
      _zeroArgumentMetalMocker->_exceptionThrower.AssertExpectAndThrowExceptionCalledOnceWith(
         "MetalMock::TestingException", 2, argumentStringValue + to_string(argumentIntValue));
      IS_TRUE(_zeroArgumentMetalMocker->_wasExpected);
      _zeroArgumentMetalMocker->_wasAsserted = true;
   }

   TEST(MetalMockIt_ExpectedFalse_ThrowsUnexpectedCallException)
   {
      IS_FALSE(_zeroArgumentMetalMocker->_wasExpected);
      THROWS_EXCEPTION(_zeroArgumentMetalMocker->MetalMockIt(),
         UnexpectedCallException, UnexpectedCallException::MakeWhat(_metalMockedFunctionSignature));
   }

   TEST(MetalMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsMetalMockThrowIfExceptionSet)
   {
      _zeroArgumentMetalMocker->_wasExpected = true;
      _zeroArgumentMetalMocker->_exceptionThrower.ExpectCallToMetalMockThrowExceptionIfExceptionSet();
      ARE_EQUAL(0, _zeroArgumentMetalMocker->actualNumberOfCalls);
      //
      _zeroArgumentMetalMocker->MetalMockIt();
      //
      ARE_EQUAL(1, _zeroArgumentMetalMocker->actualNumberOfCalls);
      METALMOCK(_zeroArgumentMetalMocker->_exceptionThrower.AssertMetalMockThrowExceptionIfExceptionSetCalledOnce());
      DOES_NOT_THROW(_zeroArgumentMetalMocker->CalledOnce());
   }

   TEST2X2(CalledOnce_SetsAssertedTrue_FunctionWasCalledOnce_DoesNotThrowException,
      size_t numberOfCalls, bool expectThrow,
      size_t(0), true,
      size_t(1), false,
      size_t(2), true)
   {
      IS_FALSE(_zeroArgumentMetalMocker->_wasAsserted);
      //
      _zeroArgumentMetalMocker->actualNumberOfCalls = numberOfCalls;
      if (expectThrow)
      {
         const string expectedExceptionMessage = ZenUnit::String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->MetalMockedFunctionSignature)
Expected: 1
  Actual: )", numberOfCalls, R"(
 Message: ")", _metalMockedFunctionSignature, R"("
File.cpp(1))");
         THROWS_EXCEPTION(_zeroArgumentMetalMocker->CalledOnce(), Anomaly, expectedExceptionMessage);
      }
      else
      {
         _zeroArgumentMetalMocker->CalledOnce();
      }
      //
      IS_TRUE(_zeroArgumentMetalMocker->_wasAsserted);
   }

   TEST(CalledNTimes_NIsZero_ThrowsUnsupportedCalledZeroTimesException)
   {
      THROWS_EXCEPTION(_zeroArgumentMetalMocker->CalledNTimes(0),
         UnsupportedCalledZeroTimesException, UnsupportedCalledZeroTimesException::MakeWhat(_metalMockedFunctionSignature));
   }

   TEST3X3(CalledNTimes_SetsAssertedTrue_FunctionWasCalledNTimes_DoesNotThrowException,
      size_t expectedNumberOfCalls, size_t numberOfCalls, bool expectThrow,
      size_t(1), size_t(0), true,

      size_t(1), size_t(1), false,
      size_t(2), size_t(1), true,

      size_t(1), size_t(2), true,
      size_t(2), size_t(2), false,
      size_t(3), size_t(2), true)
   {
      IS_FALSE(_zeroArgumentMetalMocker->_wasAsserted);
      //
      _zeroArgumentMetalMocker->actualNumberOfCalls = numberOfCalls;
      if (expectThrow)
      {
         const string expectedExceptionMessage = ZenUnit::String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->MetalMockedFunctionSignature)
Expected: )", expectedNumberOfCalls, R"(
  Actual: )", numberOfCalls, R"(
 Message: ")", _metalMockedFunctionSignature, R"("
File.cpp(1))");
         THROWS_EXCEPTION(_zeroArgumentMetalMocker->CalledNTimes(expectedNumberOfCalls), Anomaly, expectedExceptionMessage);
      }
      else
      {
         _zeroArgumentMetalMocker->CalledNTimes(expectedNumberOfCalls);
      }
      //
      IS_TRUE(_zeroArgumentMetalMocker->_wasAsserted);
   }

   TEST(CallInstead_CallsSuppliedFunctionWhenMetalMockedFunctionIsCalled)
   {
      bool voidZeroArgFunctionWasCalled = false;
      const auto voidZeroArgFunction = [&]()
      {
         voidZeroArgFunctionWasCalled = true;
      };
      _zeroArgumentMetalMocker->_exceptionThrower.ExpectCallToMetalMockThrowExceptionIfExceptionSet();
      //
      _zeroArgumentMetalMocker->CallInstead(voidZeroArgFunction);
      _zeroArgumentMetalMocker->MetalMockIt();
      //
      METALMOCK(_zeroArgumentMetalMocker->_exceptionThrower.AssertMetalMockThrowExceptionIfExceptionSetCalledOnce());
      IS_TRUE(voidZeroArgFunctionWasCalled);
   }

   RUN_TESTS(ZeroArgumentMetalMockerTests)
}
