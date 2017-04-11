#include "pch.h"
#include "ZenMock/Mock/ExceptionThrowerMock.h"

namespace ZenMock
{
   TESTS(ZeroArgMockerTests)
   SPEC(Constructor_SetsFields)
   SPEC(Expect_AlreadyExpected_Throws)
   SPEC(Expect_NotAlreadyExpected_SetsCallExpectedTrue)
   SPEC(ExpectAndThrow_ExpectedTrue_Throws)
   SPEC(ExpectAndThrow_ExpectedFalse_CallsExceptionThrowerExpectAndThrow_SetsCallExpectedTrue)
   SPEC(ZenMockIt_ExpectedFalse_Throws)
   SPEC(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsExpectAndThrow)
   SPECX(AssertCalledOnce_SetsAssertedTrue_FunctionWasCalledOnce_DoesNotThrow)
   SPEC(AssertCalledNTimes_NIsZero_Throws)
   SPECX(AssertCalledNTimes_SetsAssertedTrue_FunctionWasCalledNTimes_DoesNotThrow)
   SPECEND

   const string ZenMockedFunctionSignature = "void ClassName::FunctionName() const";
   unique_ptr<ZeroArgMocker<ExceptionThrowerMock>> _zeroArgMocker;

   STARTUP
   {
      _zeroArgMocker = make_unique<ZeroArgMocker<ExceptionThrowerMock>>(ZenMockedFunctionSignature);
   }

   void SetAssertedTrueToNotFailDueToExpectedButNotAsesrted()
   {
      _zeroArgMocker->_asserted = true;
   }

   TEST(Constructor_SetsFields)
   {
      const ZeroArgMocker<ExceptionThrowerMock> zeroArgMocker(ZenMockedFunctionSignature);
      //
      ARE_EQUAL(ZenMockedFunctionSignature, zeroArgMocker.ZenMockedFunctionSignature);
      IS_FALSE(zeroArgMocker.expected);
      IS_FALSE(zeroArgMocker._asserted);
      IS_ZERO(zeroArgMocker._numberOfCalls);
   }

   TEST(Expect_AlreadyExpected_Throws)
   {
      _zeroArgMocker->expected = true;
      THROWS(_zeroArgMocker->Expect(), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(ZenMockedFunctionSignature));
   }

   TEST(Expect_NotAlreadyExpected_SetsCallExpectedTrue)
   {
      IS_FALSE(_zeroArgMocker->expected);
      //
      _zeroArgMocker->Expect();
      //
      IS_TRUE(_zeroArgMocker->expected);
      SetAssertedTrueToNotFailDueToExpectedButNotAsesrted();
   }

   TEST(ExpectAndThrow_ExpectedTrue_Throws)
   {
      _zeroArgMocker->expected = true;
      THROWS(_zeroArgMocker->ExpectAndThrow<exception>(), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(ZenMockedFunctionSignature));
   }

   TEST(ExpectAndThrow_ExpectedFalse_CallsExceptionThrowerExpectAndThrow_SetsCallExpectedTrue)
   {
      IS_FALSE(_zeroArgMocker->expected);
      _zeroArgMocker->_exceptionThrower.ExpectCallToExpectAndThrow();
      //
      _zeroArgMocker->ExpectAndThrow<TwoArgTestingException>("arg", 100);
      //
      _zeroArgMocker->_exceptionThrower.AssertExpectAndThrowCalledOnceWith(
         "ZenMock::TwoArgTestingException", 2, "arg100");
      IS_TRUE(_zeroArgMocker->expected);
      SetAssertedTrueToNotFailDueToExpectedButNotAsesrted();
   }

   TEST(ZenMockIt_ExpectedFalse_Throws)
   {
      IS_FALSE(_zeroArgMocker->expected);
      THROWS(_zeroArgMocker->ZenMockIt(), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(ZenMockedFunctionSignature));
   }

   TEST(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsExpectAndThrow)
   {
      _zeroArgMocker->expected = true;
      _zeroArgMocker->_exceptionThrower.ExpectCallToZenMockThrowIfExceptionSet();
      ARE_EQUAL(0, _zeroArgMocker->_numberOfCalls);
      //
      _zeroArgMocker->ZenMockIt();
      //
      ARE_EQUAL(1, _zeroArgMocker->_numberOfCalls);
      ZEN(_zeroArgMocker->_exceptionThrower.AssertZenMockThrowIfExceptionSetCalledOnce());
      _zeroArgMocker->AssertCalledOnce();
   }

   TEST2X2(AssertCalledOnce_SetsAssertedTrue_FunctionWasCalledOnce_DoesNotThrow,
      size_t numberOfCalls, bool expectThrow,
      0ull, true,
      1ull, false,
      2ull, true)
   {
      IS_FALSE(_zeroArgMocker->_asserted);
      //
      _zeroArgMocker->_numberOfCalls = numberOfCalls;
      if (expectThrow)
      {
         THROWS(_zeroArgMocker->AssertCalledOnce(), Anomaly, R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, _numberOfCalls, this->ZenMockedFunctionSignature)
Expected: 1
  Actual: )" + to_string(numberOfCalls) + R"(
 Message: ")" + ZenMockedFunctionSignature + R"("
File.cpp(1))");
      }
      else
      {
         _zeroArgMocker->AssertCalledOnce();
      }
      //
      IS_TRUE(_zeroArgMocker->_asserted);
   }

   TEST(AssertCalledNTimes_NIsZero_Throws)
   {
      THROWS(_zeroArgMocker->AssertCalledNTimes(0), UnsupportedAssertCalledZeroTimesException,
         UnsupportedAssertCalledZeroTimesException::MakeWhat(ZenMockedFunctionSignature));
   }

   TEST3X3(AssertCalledNTimes_SetsAssertedTrue_FunctionWasCalledNTimes_DoesNotThrow,
      size_t expectedNumberOfCalls, size_t numberOfCalls, bool expectThrow,
      1ull, 0ull, true,

      1ull, 1ull, false,
      2ull, 1ull, true,

      1ull, 2ull, true,
      2ull, 2ull, false,
      3ull, 2ull, true)
   {
      IS_FALSE(_zeroArgMocker->_asserted);
      //
      _zeroArgMocker->_numberOfCalls = numberOfCalls;
      if (expectThrow)
      {
         THROWS(_zeroArgMocker->AssertCalledNTimes(expectedNumberOfCalls), Anomaly, R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, _numberOfCalls, this->ZenMockedFunctionSignature)
Expected: )" + to_string(expectedNumberOfCalls) + R"(
  Actual: )" + to_string(numberOfCalls) + R"(
 Message: ")" + ZenMockedFunctionSignature + R"("
File.cpp(1))");
      }
      else
      {
         _zeroArgMocker->AssertCalledNTimes(expectedNumberOfCalls);
      }
      //
      IS_TRUE(_zeroArgMocker->_asserted);
   }

   }; RUN(ZeroArgMockerTests)
}
