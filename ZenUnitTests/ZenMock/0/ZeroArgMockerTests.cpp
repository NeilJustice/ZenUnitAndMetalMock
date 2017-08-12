#include "pch.h"
#include "ZenMock/Mock/ExceptionThrowerMock.h"

namespace ZenMock
{
   TESTS(ZeroArgMockerTests)
   FACT(Constructor_SetsFields)
   FACT(Expect_AlreadyExpected_Throws)
   FACT(Expect_NotAlreadyExpected_SetsExpectedTrue)
   FACT(ExpectAndThrow_ExpectedTrue_Throws)
   FACT(ExpectAndThrow_ExpectedFalse_CallsExceptionThrowerExpectAndThrow_SetsExpectedTrue)
   FACT(ZenMockIt_ExpectedFalse_Throws)
   FACT(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)

   FACTS(AssertCalledOnce_SetsAssertedTrue_FunctionWasCalledOnce_DoesNotThrow)
   FACT(AssertCalledNTimes_NIsZero_Throws)
   FACTS(AssertCalledNTimes_SetsAssertedTrue_FunctionWasCalledNTimes_DoesNotThrow)
   BEGINPROOF

   using MockerType = ZeroArgMocker<ExceptionThrowerMock>;
   unique_ptr<MockerType> _mocker;

   STARTUP
   {
      _mocker = make_unique<MockerType>(Test::Signature);
   }

   void SetAssertedTrueToNotFailDueToExpectedButNotAsesrted()
   {
      _mocker->_asserted = true;
   }

   TEST(Constructor_SetsFields)
   {
      const MockerType mocker(Test::Signature);
      //
      ARE_EQUAL(Test::Signature, mocker.ZenMockedFunctionSignature);
      IS_FALSE(mocker._expected);
      IS_FALSE(mocker._asserted);
      IS_ZERO(mocker._numberOfCalls);
   }

   TEST(Expect_AlreadyExpected_Throws)
   {
      _mocker->_expected = true;
      THROWS(_mocker->Expect(), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(Test::Signature));
   }

   TEST(Expect_NotAlreadyExpected_SetsExpectedTrue)
   {
      IS_FALSE(_mocker->_expected);
      //
      _mocker->Expect();
      //
      IS_TRUE(_mocker->_expected);
      SetAssertedTrueToNotFailDueToExpectedButNotAsesrted();
   }

   TEST(ExpectAndThrow_ExpectedTrue_Throws)
   {
      _mocker->_expected = true;
      THROWS(_mocker->ExpectAndThrow<exception>(), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(Test::Signature));
   }

   TEST(ExpectAndThrow_ExpectedFalse_CallsExceptionThrowerExpectAndThrow_SetsExpectedTrue)
   {
      IS_FALSE(_mocker->_expected);
      _mocker->_exceptionThrower.ExpectCallToExpectAndThrow();
      //
      _mocker->ExpectAndThrow<TestingException>("arg", 100);
      //
      _mocker->_exceptionThrower.AssertExpectAndThrowCalledOnceWith(
         "ZenMock::TestingException", 2, "arg100");
      IS_TRUE(_mocker->_expected);
      SetAssertedTrueToNotFailDueToExpectedButNotAsesrted();
   }

   TEST(ZenMockIt_ExpectedFalse_Throws)
   {
      IS_FALSE(_mocker->_expected);
      THROWS(_mocker->ZenMockIt(), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(Test::Signature));
   }

   TEST(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   {
      _mocker->_expected = true;
      _mocker->_exceptionThrower.ExpectCallToZenMockThrowIfExceptionSet();
      ARE_EQUAL(0, _mocker->_numberOfCalls);
      //
      _mocker->ZenMockIt();
      //
      ARE_EQUAL(1, _mocker->_numberOfCalls);
      ZEN(_mocker->_exceptionThrower.AssertZenMockThrowIfExceptionSetCalledOnce());
      NOTHROWS(_mocker->AssertCalledOnce());
   }

   TEST2X2(AssertCalledOnce_SetsAssertedTrue_FunctionWasCalledOnce_DoesNotThrow,
      size_t numberOfCalls, bool expectThrow,
      size_t(0), true,
      size_t(1), false,
      size_t(2), true)
   {
      IS_FALSE(_mocker->_asserted);
      //
      _mocker->_numberOfCalls = numberOfCalls;
      if (expectThrow)
      {
         THROWS(_mocker->AssertCalledOnce(), Anomaly, R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, _numberOfCalls, this->ZenMockedFunctionSignature)
Expected: 1
  Actual: )" + to_string(numberOfCalls) + R"(
 Message: ")" + Test::Signature + R"("
File.cpp(1))");
      }
      else
      {
         _mocker->AssertCalledOnce();
      }
      //
      IS_TRUE(_mocker->_asserted);
   }

   TEST(AssertCalledNTimes_NIsZero_Throws)
   {
      THROWS(_mocker->AssertCalledNTimes(0), UnsupportedAssertCalledZeroTimesException,
         UnsupportedAssertCalledZeroTimesException::MakeWhat(Test::Signature));
   }

   TEST3X3(AssertCalledNTimes_SetsAssertedTrue_FunctionWasCalledNTimes_DoesNotThrow,
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
      _mocker->_numberOfCalls = numberOfCalls;
      if (expectThrow)
      {
         THROWS(_mocker->AssertCalledNTimes(expectedNumberOfCalls), Anomaly, R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, _numberOfCalls, this->ZenMockedFunctionSignature)
Expected: )" + to_string(expectedNumberOfCalls) + R"(
  Actual: )" + to_string(numberOfCalls) + R"(
 Message: ")" + Test::Signature + R"("
File.cpp(1))");
      }
      else
      {
         _mocker->AssertCalledNTimes(expectedNumberOfCalls);
      }
      //
      IS_TRUE(_mocker->_asserted);
   }

   }; RUN(ZeroArgMockerTests)
}
