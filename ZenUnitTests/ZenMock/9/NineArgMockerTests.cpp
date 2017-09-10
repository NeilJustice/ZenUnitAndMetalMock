#include "pch.h"
#include "ZenUnit/ZenMock/9/NineArgumentMocker.h"
#include "ZenUnitTests/ZenMock/Mock/ExceptionThrowerMock.h"

namespace ZenMock
{
   TESTS(NineArgumentMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(Expect_AlreadyExpected_Throws)
   AFACT(Expect_NotAlreadyExpected_SetsExpectedTrue)
   AFACT(ExpectAndThrow_ExpectedTrue_Throws)
   AFACT(ExpectAndThrow_ExpectedFalse_CallsExceptionThrowerExpectAndThrow_SetsExpectedTrue)
   AFACT(ZenMockIt_ExpectedFalse_Throws)
   AFACT(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   EVIDENCE

   using MockerType = NineArgumentMocker<int, int, int, int, int, int, int, int, int, ExceptionThrowerMock>;
   unique_ptr<MockerType> _mocker;

   STARTUP
   {
      _mocker = make_unique<MockerType>(Test::Signature);
   }

   void SetAssertedTrueToNotFailDueToExpectedButNotAsserted()
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
      IS_EMPTY(mocker.nineArgumentCalls);
   }

   TEST(Expect_AlreadyExpected_Throws)
   {
      _mocker->_expected = true;
      THROWS(_mocker->Expect(), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(Test::Signature));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(Expect_NotAlreadyExpected_SetsExpectedTrue)
   {
      IS_FALSE(_mocker->_expected);
      //
      _mocker->Expect();
      //
      IS_TRUE(_mocker->_expected);
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
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
      _mocker->ExpectAndThrow<TestingException>("argument", 100);
      //
      _mocker->_exceptionThrower.
         AssertExpectAndThrowCalledOnceWith("ZenMock::TestingException", 2, "argument100");
      IS_TRUE(_mocker->_expected);
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(ZenMockIt_ExpectedFalse_Throws)
   {
      IS_FALSE(_mocker->_expected);
      THROWS(_mocker->ZenMockIt(1, 2, 3, 4, 5, 6, 7, 8, 9), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(Test::Signature, 1, 2, 3, 4, 5, 6, 7, 8, 9));
   }

   TEST(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   {
      _mocker->_expected = true;
      _mocker->_exceptionThrower.ExpectCallToZenMockThrowIfExceptionSet();
      IS_EMPTY(_mocker->nineArgumentCalls);
      //
      _mocker->ZenMockIt(1, 2, 3, 4, 5, 6, 7, 8, 9);
      //
      using CallType = NineArgumentCall<int, int, int, int, int, int, int, int, int>;
      const vector<CallType> expectedCalls 
      { 
         CallType(1, 2, 3, 4, 5, 6, 7, 8, 9)
      };
      VECTORS_EQUAL(expectedCalls, _mocker->nineArgumentCalls);
      ZEN(_mocker->_exceptionThrower.AssertZenMockThrowIfExceptionSetCalledOnce());
      NOTHROWS(_mocker->AssertCalledOnceWith(1, 2, 3, 4, 5, 6, 7, 8, 9));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   }; RUNTESTS(NineArgumentMockerTests)
}
