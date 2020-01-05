#include "pch.h"
#include "ZenMockTests/ZenMock/ExceptionThrowerMock.h"

namespace ZenMock
{
   TESTS(ZeroArgumentZenMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(ZenMockIt_ExpectedFalse_Throws)
   AFACT(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   FACTS(CalledOnce_SetsAssertedTrue_FunctionWasCalledOnce_DoesNotThrow)
   AFACT(CalledNTimes_NIsZero_Throws)
   FACTS(CalledNTimes_SetsAssertedTrue_FunctionWasCalledNTimes_DoesNotThrow)
   AFACT(CallInstead_CallsSuppliedFunctionWhenZenMockedFunctionIsCalled)
   EVIDENCE

   using ZeroArgumentZenMockerType = ZeroArgumentZenMocker<ExceptionThrowerMock>;
   unique_ptr<ZeroArgumentZenMockerType> _zeroArgumentZenMocker;
   string _zenMockedFunctionSignature;

   STARTUP
   {
      _zenMockedFunctionSignature = ZenUnit::Random<string>();
      _zeroArgumentZenMocker = make_unique<ZeroArgumentZenMockerType>(_zenMockedFunctionSignature);
   }

   TEST(Constructor_SetsFields)
   {
      const ZeroArgumentZenMockerType zeroArgumentZenMocker(_zenMockedFunctionSignature);
      //
      ARE_EQUAL(_zenMockedFunctionSignature, zeroArgumentZenMocker.ZenMockedFunctionSignature);
      IS_FALSE(zeroArgumentZenMocker._wasExpected);
      IS_FALSE(zeroArgumentZenMocker._wasAsserted);
      IS_ZERO(zeroArgumentZenMocker.actualNumberOfCalls);
   }

   TEST(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue)
   {
      IS_FALSE(_zeroArgumentZenMocker->_wasExpected);
      _zeroArgumentZenMocker->_exceptionThrower.ExpectCallToExpectAndThrowException();
      const string argumentStringValue = ZenUnit::Random<string>();
      const int argumentIntValue = ZenUnit::Random<int>();
      //
      _zeroArgumentZenMocker->ThrowException<TestingException>(argumentStringValue, argumentIntValue);
      //
      _zeroArgumentZenMocker->_exceptionThrower.AssertExpectAndThrowExceptionCalledOnceWith(
         "ZenMock::TestingException", 2, argumentStringValue + to_string(argumentIntValue));
      IS_TRUE(_zeroArgumentZenMocker->_wasExpected);
      _zeroArgumentZenMocker->_wasAsserted = true;
   }

   TEST(ZenMockIt_ExpectedFalse_Throws)
   {
      IS_FALSE(_zeroArgumentZenMocker->_wasExpected);
      THROWS_EXCEPTION(_zeroArgumentZenMocker->ZenMockIt(), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(_zenMockedFunctionSignature));
   }

   TEST(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   {
      _zeroArgumentZenMocker->_wasExpected = true;
      _zeroArgumentZenMocker->_exceptionThrower.ExpectCallToZenMockThrowExceptionIfExceptionSet();
      ARE_EQUAL(0, _zeroArgumentZenMocker->actualNumberOfCalls);
      //
      _zeroArgumentZenMocker->ZenMockIt();
      //
      ARE_EQUAL(1, _zeroArgumentZenMocker->actualNumberOfCalls);
      ZENMOCK(_zeroArgumentZenMocker->_exceptionThrower.AssertZenMockThrowExceptionIfExceptionSetCalledOnce());
      DOES_NOT_THROW(_zeroArgumentZenMocker->CalledOnce());
   }

   TEST2X2(CalledOnce_SetsAssertedTrue_FunctionWasCalledOnce_DoesNotThrow,
      size_t numberOfCalls, bool expectThrow,
      size_t(0), true,
      size_t(1), false,
      size_t(2), true)
   {
      IS_FALSE(_zeroArgumentZenMocker->_wasAsserted);
      //
      _zeroArgumentZenMocker->actualNumberOfCalls = numberOfCalls;
      if (expectThrow)
      {
         const string expectedExceptionMessage = ZenUnit::String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->ZenMockedFunctionSignature)
Expected: 1
  Actual: )", numberOfCalls, R"(
 Message: ")", _zenMockedFunctionSignature, R"("
File.cpp(1))");
         THROWS_EXCEPTION(_zeroArgumentZenMocker->CalledOnce(), Anomaly, expectedExceptionMessage);
      }
      else
      {
         _zeroArgumentZenMocker->CalledOnce();
      }
      //
      IS_TRUE(_zeroArgumentZenMocker->_wasAsserted);
   }

   TEST(CalledNTimes_NIsZero_Throws)
   {
      THROWS_EXCEPTION(_zeroArgumentZenMocker->CalledNTimes(0), UnsupportedCalledZeroTimesException,
         UnsupportedCalledZeroTimesException::MakeWhat(_zenMockedFunctionSignature));
   }

   TEST3X3(CalledNTimes_SetsAssertedTrue_FunctionWasCalledNTimes_DoesNotThrow,
      size_t expectedNumberOfCalls, size_t numberOfCalls, bool expectThrow,
      size_t(1), size_t(0), true,

      size_t(1), size_t(1), false,
      size_t(2), size_t(1), true,

      size_t(1), size_t(2), true,
      size_t(2), size_t(2), false,
      size_t(3), size_t(2), true)
   {
      IS_FALSE(_zeroArgumentZenMocker->_wasAsserted);
      //
      _zeroArgumentZenMocker->actualNumberOfCalls = numberOfCalls;
      if (expectThrow)
      {
         const string expectedExceptionMessage = ZenUnit::String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->ZenMockedFunctionSignature)
Expected: )", expectedNumberOfCalls, R"(
  Actual: )", numberOfCalls, R"(
 Message: ")", _zenMockedFunctionSignature, R"("
File.cpp(1))");
         THROWS_EXCEPTION(_zeroArgumentZenMocker->CalledNTimes(expectedNumberOfCalls), Anomaly, expectedExceptionMessage);
      }
      else
      {
         _zeroArgumentZenMocker->CalledNTimes(expectedNumberOfCalls);
      }
      //
      IS_TRUE(_zeroArgumentZenMocker->_wasAsserted);
   }

   TEST(CallInstead_CallsSuppliedFunctionWhenZenMockedFunctionIsCalled)
   {
      bool voidZeroArgFunctionWasCalled = false;
      const auto voidZeroArgFunction = [&]()
      {
         voidZeroArgFunctionWasCalled = true;
      };
      _zeroArgumentZenMocker->_exceptionThrower.ExpectCallToZenMockThrowExceptionIfExceptionSet();
      //
      _zeroArgumentZenMocker->CallInstead(voidZeroArgFunction);
      _zeroArgumentZenMocker->ZenMockIt();
      //
      ZENMOCK(_zeroArgumentZenMocker->_exceptionThrower.AssertZenMockThrowExceptionIfExceptionSetCalledOnce());
      IS_TRUE(voidZeroArgFunctionWasCalled);
   }

   RUN_TESTS(ZeroArgumentZenMockerTests)
}
