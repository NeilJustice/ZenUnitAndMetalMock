#include "pch.h"
#include "ZenMockTests/ZenMock/ExceptionThrowerMock.h"

namespace ZenMock
{
   TESTS(TwoArgumentZenMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(ZenMockIt_ExpectedFalse_Throws)
   AFACT(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   AFACT(CallInstead_CallsSuppliedFunctionWhenZenMockedFunctionIsCalled)
   EVIDENCE

   using ZenMockerType = TwoArgumentZenMocker<int, int, ExceptionThrowerMock>;
   unique_ptr<ZenMockerType> _zenMocker;
   string _zenMockedFunctionSignature;

   STARTUP
   {
      _zenMockedFunctionSignature = ZenUnit::Random<string>();
      _zenMocker = make_unique<ZenMockerType>(_zenMockedFunctionSignature);
   }

   void SetAssertedTrueToNotFailDueToExpectedButNotAsserted()
   {
      _zenMocker->_wasAsserted = true;
   }

   TEST(Constructor_SetsFields)
   {
      const ZenMockerType mocker(_zenMockedFunctionSignature);
      //
      ARE_EQUAL(_zenMockedFunctionSignature, mocker.ZenMockedFunctionSignature);
      IS_FALSE(mocker._wasExpected);
      IS_FALSE(mocker._wasAsserted);
      IS_EMPTY(mocker.zenMockedFunctionCallHistory);
   }

   TEST(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue)
   {
      IS_FALSE(_zenMocker->_wasExpected);
      _zenMocker->_exceptionThrower.ExpectCallToExpectAndThrowException();
      //
      _zenMocker->ThrowException<TestingException>("argument", 100);
      //
      _zenMocker->_exceptionThrower.AssertExpectAndThrowExceptionCalledOnceWith("ZenMock::TestingException", 2, "argument100");
      IS_TRUE(_zenMocker->_wasExpected);
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(ZenMockIt_ExpectedFalse_Throws)
   {
      IS_FALSE(_zenMocker->_wasExpected);
      const string expectedExceptionMessage = UnexpectedCallException::MakeWhat(_zenMockedFunctionSignature, 1, 2);
      THROWS_EXCEPTION(_zenMocker->ZenMockIt(1, 2),
         UnexpectedCallException, expectedExceptionMessage);
   }

   TEST(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   {
      _zenMocker->_wasExpected = true;
      _zenMocker->_exceptionThrower.ExpectCallToZenMockThrowExceptionIfExceptionSet();
      IS_EMPTY(_zenMocker->zenMockedFunctionCallHistory);
      //
      _zenMocker->ZenMockIt(1, 2);
      //
      using CallType = TwoArgumentFunctionCall<int, int>;
      const vector<CallType> expectedCalls
      {
         CallType(1, 2)
      };
      VECTORS_ARE_EQUAL(expectedCalls, _zenMocker->zenMockedFunctionCallHistory);
      ZENMOCK(_zenMocker->_exceptionThrower.AssertZenMockThrowExceptionIfExceptionSetCalledOnce());
      DOES_NOT_THROW(_zenMocker->CalledOnceWith(1, 2));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(CallInstead_CallsSuppliedFunctionWhenZenMockedFunctionIsCalled)
   {
      VoidTwoArgumentZenMocker<int, int> voidTwoArgumentZenMocker(_zenMockedFunctionSignature);

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
      voidTwoArgumentZenMocker.CallInstead(voidTwoArgFunction);
      const int arg1 = ZenUnit::Random<int>();
      const int arg2 = ZenUnit::Random<int>();
      voidTwoArgumentZenMocker.ZenMockIt(arg1, arg2);
      //
      ARE_EQUAL(arg1, receivedArg1);
      ARE_EQUAL(arg2, receivedArg2);
      IS_TRUE(voidTwoArgFunctionWasCalled);
   }

   RUN_TESTS(TwoArgumentZenMockerTests)
}
