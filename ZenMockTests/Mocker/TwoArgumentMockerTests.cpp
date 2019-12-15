#include "pch.h"
#include "ZenMockTests/ZenMock/ExceptionThrowerMock.h"

namespace ZenMock
{
   TESTS(TwoArgumentMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(ZenMockIt_ExpectedFalse_Throws)
   AFACT(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   AFACT(CallInstead_CallsSuppliedFunctionWhenZenMockedFunctionIsCalled)
   EVIDENCE

   using MockerType = TwoArgumentMocker<int, int, ExceptionThrowerMock>;
   unique_ptr<MockerType> _mocker;
   string _zenMockedFunctionSignature;

   STARTUP
   {
      _zenMockedFunctionSignature = ZenUnit::Random<string>();
      _mocker = make_unique<MockerType>(_zenMockedFunctionSignature);
   }

   void SetAssertedTrueToNotFailDueToExpectedButNotAsserted()
   {
      _mocker->_wasAsserted = true;
   }

   TEST(Constructor_SetsFields)
   {
      const MockerType mocker(_zenMockedFunctionSignature);
      //
      ARE_EQUAL(_zenMockedFunctionSignature, mocker.ZenMockedFunctionSignature);
      IS_FALSE(mocker._wasExpected);
      IS_FALSE(mocker._wasAsserted);
      IS_EMPTY(mocker.zenMockedFunctionCallHistory);
   }

   TEST(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue)
   {
      IS_FALSE(_mocker->_wasExpected);
      _mocker->_exceptionThrower.ExpectCallToExpectAndThrowException();
      //
      _mocker->ThrowException<TestingException>("argument", 100);
      //
      _mocker->_exceptionThrower.AssertExpectAndThrowExceptionCalledOnceWith("ZenMock::TestingException", 2, "argument100");
      IS_TRUE(_mocker->_wasExpected);
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(ZenMockIt_ExpectedFalse_Throws)
   {
      IS_FALSE(_mocker->_wasExpected);
      const string expectedExceptionMessage = UnexpectedCallException::MakeWhat(_zenMockedFunctionSignature, 1, 2);
      THROWS_EXCEPTION(_mocker->ZenMockIt(1, 2),
         UnexpectedCallException, expectedExceptionMessage);
   }

   TEST(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   {
      _mocker->_wasExpected = true;
      _mocker->_exceptionThrower.ExpectCallToZenMockThrowExceptionIfExceptionSet();
      IS_EMPTY(_mocker->zenMockedFunctionCallHistory);
      //
      _mocker->ZenMockIt(1, 2);
      //
      using CallType = TwoArgumentFunctionCall<int, int>;
      const vector<CallType> expectedCalls
      {
         CallType(1, 2)
      };
      VECTORS_EQUAL(expectedCalls, _mocker->zenMockedFunctionCallHistory);
      ZENMOCK(_mocker->_exceptionThrower.AssertZenMockThrowExceptionIfExceptionSetCalledOnce());
      DOES_NOT_THROW(_mocker->CalledOnceWith(1, 2));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(CallInstead_CallsSuppliedFunctionWhenZenMockedFunctionIsCalled)
   {
      VoidTwoArgumentMocker<int, int> voidTwoArgumentMocker(_zenMockedFunctionSignature);

      bool voidTwoArgFunctionWasCalled = false;
      int receivedArg1 = 0;
      int receivedArg2 = 0;
      const auto voidTwoArgFunction = [&](int arg1, int arg2)
      {
         receivedArg1 = arg1;
         receivedArg2 = arg2;
         voidTwoArgFunctionWasCalled = true;
      };
      //
      voidTwoArgumentMocker.CallInstead(voidTwoArgFunction);
      const int arg1 = ZenUnit::Random<int>();
      const int arg2 = ZenUnit::Random<int>();
      voidTwoArgumentMocker.ZenMockIt(arg1, arg2);
      //
      ARE_EQUAL(arg1, receivedArg1);
      ARE_EQUAL(arg2, receivedArg2);
      IS_TRUE(voidTwoArgFunctionWasCalled);
   }

   RUN_TESTS(TwoArgumentMockerTests)
}
