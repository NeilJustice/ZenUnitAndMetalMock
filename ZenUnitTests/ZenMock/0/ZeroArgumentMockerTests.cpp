#include "pch.h"
#include "ZenUnitTests/ZenMock/Mock/ExceptionThrowerMock.h"

namespace ZenMock
{
   TESTS(ZeroArgumentMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(ExpectAndThrow_ExpectedTrue_Throws)
   AFACT(ExpectAndThrow_ExpectedFalse_CallsExceptionThrowerExpectAndThrow_SetsExpectedTrue)
   AFACT(ZenMockIt_ExpectedFalse_Throws)
   AFACT(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)

   FACTS(CalledOnce_SetsAssertedTrue_FunctionWasCalledOnce_DoesNotThrow)
   AFACT(CalledNTimes_NIsZero_Throws)
   FACTS(CalledNTimes_SetsAssertedTrue_FunctionWasCalledNTimes_DoesNotThrow)
   EVIDENCE

   using MockerType = ZeroArgumentMocker<ExceptionThrowerMock>;
   unique_ptr<MockerType> _mocker;
   string _signature;

   STARTUP
   {
      _signature = ZenUnit::Random<string>();
      _mocker = make_unique<MockerType>(_signature);
   }

   TEST(Constructor_SetsFields)
   {
      const MockerType mocker(_signature);
      //
      ARE_EQUAL(_signature, mocker.ZenMockedFunctionSignature);
      IS_FALSE(mocker._expected);
      IS_FALSE(mocker._asserted);
      IS_ZERO(mocker.actualNumberOfCalls);
   }

   TEST(ExpectAndThrow_ExpectedTrue_Throws)
   {
      _mocker->_expected = true;
      THROWS(_mocker->ExpectAndThrow<exception>(), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(_signature));
   }

   TEST(ExpectAndThrow_ExpectedFalse_CallsExceptionThrowerExpectAndThrow_SetsExpectedTrue)
   {
      IS_FALSE(_mocker->_expected);
      _mocker->_exceptionThrower.ExpectCallToExpectAndThrow();
      //
      _mocker->ExpectAndThrow<TestingException>("argument", 100);
      //
      _mocker->_exceptionThrower.AssertExpectAndThrowCalledOnceWith(
         "ZenMock::TestingException", 2, "argument100");
      IS_TRUE(_mocker->_expected);
      _mocker->_asserted = true;
   }

   TEST(ZenMockIt_ExpectedFalse_Throws)
   {
      IS_FALSE(_mocker->_expected);
      THROWS(_mocker->ZenMockIt(), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(_signature));
   }

   TEST(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   {
      _mocker->_expected = true;
      _mocker->_exceptionThrower.ExpectCallToZenMockThrowIfExceptionSet();
      ARE_EQUAL(0, _mocker->actualNumberOfCalls);
      //
      _mocker->ZenMockIt();
      //
      ARE_EQUAL(1, _mocker->actualNumberOfCalls);
      ZEN(_mocker->_exceptionThrower.AssertZenMockThrowIfExceptionSetCalledOnce());
      NOTHROWS(_mocker->CalledOnce());
   }

   TEST2X2(CalledOnce_SetsAssertedTrue_FunctionWasCalledOnce_DoesNotThrow,
      size_t numberOfCalls, bool expectThrow,
      size_t(0), true,
      size_t(1), false,
      size_t(2), true)
   {
      IS_FALSE(_mocker->_asserted);
      //
      _mocker->actualNumberOfCalls = numberOfCalls;
      if (expectThrow)
      {
         THROWS(_mocker->CalledOnce(), Anomaly, R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->ZenMockedFunctionSignature)
Expected: 1
  Actual: )" + to_string(numberOfCalls) + R"(
 Message: ")" + _signature + R"("
File.cpp(1))");
      }
      else
      {
         _mocker->CalledOnce();
      }
      //
      IS_TRUE(_mocker->_asserted);
   }

   TEST(CalledNTimes_NIsZero_Throws)
   {
      THROWS(_mocker->CalledNTimes(0), UnsupportedCalledZeroTimesException,
         UnsupportedCalledZeroTimesException::MakeWhat(_signature));
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
      IS_FALSE(_mocker->_asserted);
      //
      _mocker->actualNumberOfCalls = numberOfCalls;
      if (expectThrow)
      {
         THROWS(_mocker->CalledNTimes(expectedNumberOfCalls), Anomaly, R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->ZenMockedFunctionSignature)
Expected: )" + to_string(expectedNumberOfCalls) + R"(
  Actual: )" + to_string(numberOfCalls) + R"(
 Message: ")" + _signature + R"("
File.cpp(1))");
      }
      else
      {
         _mocker->CalledNTimes(expectedNumberOfCalls);
      }
      //
      IS_TRUE(_mocker->_asserted);
   }

   }; RUNTESTS(ZeroArgumentMockerTests)
}
