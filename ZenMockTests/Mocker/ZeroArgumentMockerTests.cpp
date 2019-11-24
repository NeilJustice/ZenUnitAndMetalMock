#include "pch.h"
#include "ZenMockTests/ZenMock/ExceptionThrowerMock.h"

namespace ZenMock
{
   TESTS(ZeroArgumentMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(ZenMockIt_ExpectedFalse_Throws)
   AFACT(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   FACTS(CalledOnce_SetsAssertedTrue_FunctionWasCalledOnce_DoesNotThrow)
   AFACT(CalledNTimes_NIsZero_Throws)
   FACTS(CalledNTimes_SetsAssertedTrue_FunctionWasCalledNTimes_DoesNotThrow)
   AFACT(CallInstead_CallsSuppliedFunctionWhenZenMockedFunctionIsCalled)
   EVIDENCE

   using ZeroArgumentMockerType = ZeroArgumentMocker<ExceptionThrowerMock>;
   unique_ptr<ZeroArgumentMockerType> _zeroArgumentMocker;
   string _zenMockedFunctionSignature;

   STARTUP
   {
      _zenMockedFunctionSignature = ZenUnit::Random<string>();
      _zeroArgumentMocker = make_unique<ZeroArgumentMockerType>(_zenMockedFunctionSignature);
   }

   TEST(Constructor_SetsFields)
   {
      const ZeroArgumentMockerType zeroArgumentMocker(_zenMockedFunctionSignature);
      //
      ARE_EQUAL(_zenMockedFunctionSignature, zeroArgumentMocker.ZenMockedFunctionSignature);
      IS_FALSE(zeroArgumentMocker._wasExpected);
      IS_FALSE(zeroArgumentMocker._wasAsserted);
      IS_ZERO(zeroArgumentMocker.actualNumberOfCalls);
   }

   TEST(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue)
   {
      IS_FALSE(_zeroArgumentMocker->_wasExpected);
      _zeroArgumentMocker->_exceptionThrower.ExpectCallToExpectAndThrowException();
      const string argumentStringValue = ZenUnit::Random<string>();
      const int argumentIntValue = ZenUnit::Random<int>();
      //
      _zeroArgumentMocker->ThrowException<TestingException>(argumentStringValue, argumentIntValue);
      //
      _zeroArgumentMocker->_exceptionThrower.AssertExpectAndThrowExceptionCalledOnceWith(
         "ZenMock::TestingException", 2, argumentStringValue + to_string(argumentIntValue));
      IS_TRUE(_zeroArgumentMocker->_wasExpected);
      _zeroArgumentMocker->_wasAsserted = true;
   }

   TEST(ZenMockIt_ExpectedFalse_Throws)
   {
      IS_FALSE(_zeroArgumentMocker->_wasExpected);
      THROWS_EXCEPTION(_zeroArgumentMocker->ZenMockIt(), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(_zenMockedFunctionSignature));
   }

   TEST(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   {
      _zeroArgumentMocker->_wasExpected = true;
      _zeroArgumentMocker->_exceptionThrower.ExpectCallToZenMockThrowExceptionIfExceptionSet();
      ARE_EQUAL(0, _zeroArgumentMocker->actualNumberOfCalls);
      //
      _zeroArgumentMocker->ZenMockIt();
      //
      ARE_EQUAL(1, _zeroArgumentMocker->actualNumberOfCalls);
      ZENMOCK(_zeroArgumentMocker->_exceptionThrower.AssertZenMockThrowExceptionIfExceptionSetCalledOnce());
      DOES_NOT_THROW(_zeroArgumentMocker->CalledOnce());
   }

   TEST2X2(CalledOnce_SetsAssertedTrue_FunctionWasCalledOnce_DoesNotThrow,
      size_t numberOfCalls, bool expectThrow,
      size_t(0), true,
      size_t(1), false,
      size_t(2), true)
   {
      IS_FALSE(_zeroArgumentMocker->_wasAsserted);
      //
      _zeroArgumentMocker->actualNumberOfCalls = numberOfCalls;
      if (expectThrow)
      {
         const string expectedExceptionMessage = ZenUnit::String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->ZenMockedFunctionSignature)
Expected: 1
  Actual: )", numberOfCalls, R"(
 Message: ")", _zenMockedFunctionSignature, R"("
File.cpp(1))");
         THROWS_EXCEPTION(_zeroArgumentMocker->CalledOnce(), Anomaly, expectedExceptionMessage);
      }
      else
      {
         _zeroArgumentMocker->CalledOnce();
      }
      //
      IS_TRUE(_zeroArgumentMocker->_wasAsserted);
   }

   TEST(CalledNTimes_NIsZero_Throws)
   {
      THROWS_EXCEPTION(_zeroArgumentMocker->CalledNTimes(0), UnsupportedCalledZeroTimesException,
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
      IS_FALSE(_zeroArgumentMocker->_wasAsserted);
      //
      _zeroArgumentMocker->actualNumberOfCalls = numberOfCalls;
      if (expectThrow)
      {
         const string expectedExceptionMessage = ZenUnit::String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->ZenMockedFunctionSignature)
Expected: )", expectedNumberOfCalls, R"(
  Actual: )", numberOfCalls, R"(
 Message: ")", _zenMockedFunctionSignature, R"("
File.cpp(1))");
         THROWS_EXCEPTION(_zeroArgumentMocker->CalledNTimes(expectedNumberOfCalls), Anomaly, expectedExceptionMessage);
      }
      else
      {
         _zeroArgumentMocker->CalledNTimes(expectedNumberOfCalls);
      }
      //
      IS_TRUE(_zeroArgumentMocker->_wasAsserted);
   }

   TEST(CallInstead_CallsSuppliedFunctionWhenZenMockedFunctionIsCalled)
   {
      bool voidZeroArgFunctionWasCalled = false;
      const auto voidZeroArgFunction = [&]()
      {
         voidZeroArgFunctionWasCalled = true;
      };
      _zeroArgumentMocker->_exceptionThrower.ExpectCallToZenMockThrowExceptionIfExceptionSet();
      //
      _zeroArgumentMocker->CallInstead(voidZeroArgFunction);
      _zeroArgumentMocker->ZenMockIt();
      //
      ZENMOCK(_zeroArgumentMocker->_exceptionThrower.AssertZenMockThrowExceptionIfExceptionSetCalledOnce());
      IS_TRUE(voidZeroArgFunctionWasCalled);
   }

   RUN_TESTS(ZeroArgumentMockerTests)
}
